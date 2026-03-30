#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MySpartaSpeechBubbleWidgetBase.generated.h"

class UTextBlock;

UCLASS(Abstract, Blueprintable)
class MYSPARTALOG_API UMySpartaSpeechBubbleWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Speech")
	virtual void SetSpeechText(const FText& InText);

	UFUNCTION(BlueprintCallable, Category = "Speech")
	virtual void SetSpeechTextColor(const FLinearColor& InColor);

	UFUNCTION(BlueprintCallable, Category = "Speech")
	virtual void SetSpeechFontSize(int32 InFontSize);

	UFUNCTION(BlueprintPure, Category = "Speech")
	const FText& GetCurrentSpeechText() const { return CurrentSpeechText; }

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> Text_Message;

	UPROPERTY(BlueprintReadOnly, Category = "Speech")
	FText CurrentSpeechText;

	UPROPERTY(BlueprintReadOnly, Category = "Speech")
	FLinearColor CurrentTextColor;

	UPROPERTY(BlueprintReadOnly, Category = "Speech")
	int32 CurrentFontSize = 24;

	UFUNCTION(BlueprintImplementableEvent, Category = "Speech")
	void BP_OnSpeechUpdated(const FText& InText, const FLinearColor& InColor, int32 InFontSize);
};