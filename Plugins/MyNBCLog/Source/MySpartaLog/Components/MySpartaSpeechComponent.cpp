#include "MySpartaSpeechComponent.h"

#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "../Data/MySpartaLogDeveloperSettings.h"
#include "../Data/MySpartaSpeechStyleDataAsset.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "../MySpartaLog.h"
#include "../Widgets/MySpartaSpeechBubbleWidgetBase.h"

UMySpartaSpeechComponent::UMySpartaSpeechComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bAutoCreateWidgetComponent = true;
}
void UMySpartaSpeechComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateFaceCamera();
}


void UMySpartaSpeechComponent::UpdateFaceCamera()
{
	UWidgetComponent* WidgetComp = ExistingWidgetComponent ? ExistingWidgetComponent : RuntimeWidgetComponent;
	if (!WidgetComp || !ActiveStyle)
	{
		return;
	}

	if (ActiveStyle->bUseScreenSpace)
	{
		return;
	}

	if (!ActiveStyle->bFaceCameraInWorldSpace)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	APlayerController* PC = World->GetFirstPlayerController();
	if (!PC || !PC->PlayerCameraManager)
	{
		return;
	}

	const FVector CameraLocation = PC->PlayerCameraManager->GetCameraLocation();
	const FVector WidgetLocation = WidgetComp->GetComponentLocation();

	FVector LookDir = CameraLocation - WidgetLocation;
	LookDir.Z = 0.f;

	if (!LookDir.Normalize())
	{
		return;
	}

	const FRotator LookRot = LookDir.Rotation();
	WidgetComp->SetWorldRotation(FRotator(0.f, LookRot.Yaw + 180.f, 0.f));
}
void UMySpartaSpeechComponent::BeginPlay()
{
	Super::BeginPlay();
	RefreshFromDefaultSettings();
}

void UMySpartaSpeechComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HideSpeechTimerHandle);
	}

	Super::EndPlay(EndPlayReason);
}

void UMySpartaSpeechComponent::RefreshFromDefaultSettings()
{
	ActiveStyle = ResolveDefaultStyle();

	if (UWidgetComponent* WidgetComp = GetOrCreateWidgetComponent())
	{
		ApplyStyleToWidgetComponent(WidgetComp, ActiveStyle);
		WidgetComp->SetVisibility(false);

		if (!WidgetComp->GetWidget() && WidgetComp->GetWidgetClass())
		{
			WidgetComp->InitWidget();
		}
	}
}

void UMySpartaSpeechComponent::ShowSpeech(const FText& InText)
{
	ShowSpeechWithStyle(InText, ResolveDefaultStyle());
}

void UMySpartaSpeechComponent::ShowSpeechWithStyle(const FText& InText, UMySpartaSpeechStyleDataAsset* InStyle)
{
	if (!GetOwner())
	{
		return;
	}

	UMySpartaSpeechStyleDataAsset* StyleToUse = InStyle ? InStyle : ResolveDefaultStyle();
	if (!StyleToUse)
	{
		UE_LOG(LogMySpartaModule, Warning, TEXT("ShowSpeech failed: no speech style asset assigned."));
		return;
	}

	ActiveStyle = StyleToUse;

	UWidgetComponent* WidgetComp = GetOrCreateWidgetComponent();
	if (!WidgetComp)
	{
		UE_LOG(LogMySpartaModule, Warning, TEXT("ShowSpeech failed: widget component could not be created."));
		return;
	}

	ApplyStyleToWidgetComponent(WidgetComp, StyleToUse);

	if (!WidgetComp->GetWidget() && WidgetComp->GetWidgetClass())
	{
		WidgetComp->InitWidget();
	}

	if (UMySpartaSpeechBubbleWidgetBase* SpeechWidget = GetSpeechWidget())
	{
		SpeechWidget->SetSpeechText(InText);
		SpeechWidget->SetSpeechTextColor(StyleToUse->DefaultTextColor);
		SpeechWidget->SetSpeechFontSize(StyleToUse->DefaultFontSize);
	}

	WidgetComp->SetVisibility(true);

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HideSpeechTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(
			HideSpeechTimerHandle,
			this,
			&UMySpartaSpeechComponent::HideSpeech,
			StyleToUse->DisplayDuration,
			false
		);
	}
}
void UMySpartaSpeechComponent::SetSpeechTextColor(const FLinearColor& InColor)
{
	if (UMySpartaSpeechBubbleWidgetBase* SpeechWidget = GetSpeechWidget())
	{
		SpeechWidget->SetSpeechTextColor(InColor);
	}
}

void UMySpartaSpeechComponent::SetSpeechFontSize(int32 InFontSize)
{
	if (UMySpartaSpeechBubbleWidgetBase* SpeechWidget = GetSpeechWidget())
	{
		SpeechWidget->SetSpeechFontSize(InFontSize);
	}
}

void UMySpartaSpeechComponent::HideSpeech()
{
	if (UWidgetComponent* WidgetComp = GetOrCreateWidgetComponent())
	{
		WidgetComp->SetVisibility(false);
	}
}

bool UMySpartaSpeechComponent::IsSpeechVisible() const
{
	const UWidgetComponent* WidgetComp = ExistingWidgetComponent ? ExistingWidgetComponent : RuntimeWidgetComponent;
	return WidgetComp ? WidgetComp->IsVisible() : false;
}

UWidgetComponent* UMySpartaSpeechComponent::GetOrCreateWidgetComponent()
{
	if (ExistingWidgetComponent)
	{
		return ExistingWidgetComponent;
	}

	if (RuntimeWidgetComponent)
	{
		return RuntimeWidgetComponent;
	}

	if (!bAutoCreateWidgetComponent || !GetOwner())
	{
		return nullptr;
	}

	USceneComponent* AttachParent = ResolveAttachParent();
	if (!AttachParent)
	{
		return nullptr;
	}

	RuntimeWidgetComponent = NewObject<UWidgetComponent>(GetOwner(), TEXT("MySpartaSpeechWidgetComponent"));
	if (!RuntimeWidgetComponent)
	{
		return nullptr;
	}

	RuntimeWidgetComponent->SetupAttachment(AttachParent);
	RuntimeWidgetComponent->RegisterComponent();
	RuntimeWidgetComponent->SetVisibility(false);
	RuntimeWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RuntimeWidgetComponent->SetGenerateOverlapEvents(false);
	RuntimeWidgetComponent->SetTwoSided(true);
	RuntimeWidgetComponent->SetDrawAtDesiredSize(false);

	return RuntimeWidgetComponent;
}

UMySpartaSpeechStyleDataAsset* UMySpartaSpeechComponent::ResolveDefaultStyle() const
{
	const UMySpartaLogDeveloperSettings* Settings = GetDefault<UMySpartaLogDeveloperSettings>();
	if (!Settings)
	{
		return nullptr;
	}

	return Settings->DefaultSpeechStyle.LoadSynchronous();
}

USceneComponent* UMySpartaSpeechComponent::ResolveAttachParent() const
{
	if (const ACharacter* CharacterOwner = Cast<ACharacter>(GetOwner()))
	{
		if (USkeletalMeshComponent* MeshComp = CharacterOwner->GetMesh())
		{
			return MeshComp;
		}
	}

	return GetOwner() ? GetOwner()->GetRootComponent() : nullptr;
}

void UMySpartaSpeechComponent::ApplyStyleToWidgetComponent(UWidgetComponent* WidgetComponent, const UMySpartaSpeechStyleDataAsset* Style) const
{
	if (!WidgetComponent || !Style)
	{
		return;
	}

	if (UClass* WidgetClass = Style->BubbleWidgetClass.LoadSynchronous())
	{
		if (WidgetComponent->GetWidgetClass() != WidgetClass)
		{
			WidgetComponent->SetWidgetClass(WidgetClass);
		}
	}

	WidgetComponent->SetWidgetSpace(
		Style->bUseScreenSpace ? EWidgetSpace::Screen : EWidgetSpace::World
	);
	WidgetComponent->SetRelativeLocation(Style->RelativeOffset);
	WidgetComponent->SetDrawSize(FIntPoint(
		FMath::RoundToInt(Style->DrawSize.X),
		FMath::RoundToInt(Style->DrawSize.Y))
	);
	WidgetComponent->SetPivot(FVector2D(0.5f, 1.0f));

	if (ACharacter* CharacterOwner = Cast<ACharacter>(GetOwner()))
	{
		if (USkeletalMeshComponent* MeshComp = CharacterOwner->GetMesh())
		{
			if (Style->SocketName != NAME_None && MeshComp->DoesSocketExist(Style->SocketName))
			{
				WidgetComponent->AttachToComponent(
					MeshComp,
					FAttachmentTransformRules::SnapToTargetNotIncludingScale,
					Style->SocketName
				);
				WidgetComponent->SetRelativeLocation(Style->RelativeOffset);
			}
		}
	}
}

UMySpartaSpeechBubbleWidgetBase* UMySpartaSpeechComponent::GetSpeechWidget() const
{
	const UWidgetComponent* WidgetComp = ExistingWidgetComponent ? ExistingWidgetComponent : RuntimeWidgetComponent;
	if (!WidgetComp)
	{
		return nullptr;
	}

	return Cast<UMySpartaSpeechBubbleWidgetBase>(WidgetComp->GetWidget());
}