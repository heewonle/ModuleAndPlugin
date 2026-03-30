#include "MySpartaLogBPLibrary.h"

#include "Components/MySpartaSpeechComponent.h"
#include "Data/MySpartaLogDeveloperSettings.h"
#include "Data/MySpartaSpeechStyleDataAsset.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "MySpartaLog.h"

void UMySpartaLogBPLibrary::LogText(
	const FString& Message,
	bool bPrintToOutputLog,
	bool bPrintToScreen,
	float ScreenDuration,
	FLinearColor ScreenColor
)
{
	const UMySpartaLogDeveloperSettings* Settings = GetDefault<UMySpartaLogDeveloperSettings>();

	const bool bUseOutputLog = bPrintToOutputLog || (Settings && Settings->bPrintToOutputLogByDefault);
	const bool bUseScreen = bPrintToScreen || (Settings && Settings->bPrintToScreenByDefault);
	const float FinalDuration = bPrintToScreen
		? ScreenDuration
		: (Settings ? Settings->DefaultScreenLogDuration : ScreenDuration);
	const FColor FinalColor = bPrintToScreen
		? ScreenColor.ToFColor(true)
		: (Settings ? Settings->DefaultScreenLogColor : ScreenColor.ToFColor(true));

	if (bUseOutputLog)
	{
		UE_LOG(LogMySpartaModule, Log, TEXT("%s"), *Message);
	}

	if (bUseScreen && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			FinalDuration,
			FinalColor,
			Message
		);
	}
}

void UMySpartaLogBPLibrary::LogTextToActor(
	AActor* TargetActor,
	const FString& Message,
	bool bPrintToOutputLog,
	bool bPrintToScreen,
	float ScreenDuration,
	FLinearColor ScreenColor
)
{
	LogText(Message, bPrintToOutputLog, bPrintToScreen, ScreenDuration, ScreenColor);
	ShowSpeechToActor(TargetActor, FText::FromString(Message), nullptr);
}

void UMySpartaLogBPLibrary::LogTypedTextToActor(
	AActor* TargetActor,
	const FString& Message,
	EMySpartaLogType InLogType,
	bool bPrintToOutputLog,
	bool bPrintToScreen,
	float ScreenDuration
)
{
	FLinearColor BubbleColor = FLinearColor::White;

	switch (InLogType)
	{
	case EMySpartaLogType::Warning:
		BubbleColor = FLinearColor(1.f, 0.85f, 0.2f, 1.f);
		if (bPrintToOutputLog)
		{
			UE_LOG(LogMySpartaModule, Warning, TEXT("%s"), *Message);
		}
		break;

	case EMySpartaLogType::Error:
		BubbleColor = FLinearColor(1.f, 0.25f, 0.25f, 1.f);
		if (bPrintToOutputLog)
		{
			UE_LOG(LogMySpartaModule, Error, TEXT("%s"), *Message);
		}
		break;

	case EMySpartaLogType::Info:
	default:
		BubbleColor = FLinearColor::White;
		if (bPrintToOutputLog)
		{
			UE_LOG(LogMySpartaModule, Log, TEXT("%s"), *Message);
		}
		break;
	}

	if (bPrintToScreen && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			ScreenDuration,
			BubbleColor.ToFColor(true),
			Message
		);
	}

	if (!TargetActor)
	{
		return;
	}

	if (UMySpartaSpeechComponent* SpeechComp = TargetActor->FindComponentByClass<UMySpartaSpeechComponent>())
	{
		SpeechComp->ShowSpeech(FText::FromString(Message));
		SpeechComp->SetSpeechTextColor(BubbleColor);
	}
	else
	{
		UE_LOG(
			LogMySpartaModule,
			Warning,
			TEXT("LogTypedTextToActor failed: actor '%s' has no MySpartaSpeechComponent."),
			*TargetActor->GetName()
		);
	}
}

void UMySpartaLogBPLibrary::ShowSpeechToActor(
	AActor* TargetActor,
	const FText& Message,
	UMySpartaSpeechStyleDataAsset* OverrideStyle
)
{
	if (!TargetActor)
	{
		return;
	}

	UMySpartaSpeechComponent* SpeechComponent = TargetActor->FindComponentByClass<UMySpartaSpeechComponent>();
	if (!SpeechComponent)
	{
		UE_LOG(
			LogMySpartaModule,
			Warning,
			TEXT("ShowSpeechToActor failed: actor '%s' has no MySpartaSpeechComponent."),
			*TargetActor->GetName()
		);
		return;
	}

	if (OverrideStyle)
	{
		SpeechComponent->ShowSpeechWithStyle(Message, OverrideStyle);
	}
	else
	{
		SpeechComponent->ShowSpeech(Message);
	}
}