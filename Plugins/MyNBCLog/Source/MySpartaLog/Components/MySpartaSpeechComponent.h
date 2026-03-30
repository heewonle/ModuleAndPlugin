#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MySpartaSpeechComponent.generated.h"

class UWidgetComponent;
class UMySpartaSpeechBubbleWidgetBase;
class UMySpartaSpeechStyleDataAsset;
class USceneComponent;

UCLASS(ClassGroup=(MySpartaLog), meta=(BlueprintSpawnableComponent))
class MYSPARTALOG_API UMySpartaSpeechComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMySpartaSpeechComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "MySpartaLog|Speech")
	void ShowSpeech(const FText& InText);

	UFUNCTION(BlueprintCallable, Category = "MySpartaLog|Speech")
	void ShowSpeechWithStyle(const FText& InText, UMySpartaSpeechStyleDataAsset* InStyle);

	UFUNCTION(BlueprintCallable, Category = "MySpartaLog|Speech")
	void HideSpeech();

	UFUNCTION(BlueprintCallable, Category = "MySpartaLog|Speech")
	void RefreshFromDefaultSettings();

	UFUNCTION(BlueprintPure, Category = "MySpartaLog|Speech")
	bool IsSpeechVisible() const;
	
	UFUNCTION(BlueprintCallable, Category = "MySpartaLog|Speech")
	void SetSpeechTextColor(const FLinearColor& InColor);

	UFUNCTION(BlueprintCallable, Category = "MySpartaLog|Speech")
	void SetSpeechFontSize(int32 InFontSize);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Speech")
	bool bAutoCreateWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Speech")
	TObjectPtr<UWidgetComponent> ExistingWidgetComponent;

	UPROPERTY(Transient)
	TObjectPtr<UWidgetComponent> RuntimeWidgetComponent;

	UPROPERTY(Transient)
	TObjectPtr<UMySpartaSpeechStyleDataAsset> ActiveStyle;

	FTimerHandle HideSpeechTimerHandle;
	virtual void TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
) override;
	

protected:
	UWidgetComponent* GetOrCreateWidgetComponent();
	UMySpartaSpeechStyleDataAsset* ResolveDefaultStyle() const;
	USceneComponent* ResolveAttachParent() const;
	void ApplyStyleToWidgetComponent(UWidgetComponent* WidgetComponent, const UMySpartaSpeechStyleDataAsset* Style) const;
	UMySpartaSpeechBubbleWidgetBase* GetSpeechWidget() const;
private:
	void UpdateFaceCamera();
};