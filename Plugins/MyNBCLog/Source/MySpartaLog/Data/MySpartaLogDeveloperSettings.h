#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MySpartaLogDeveloperSettings.generated.h"

class UMySpartaSpeechStyleDataAsset;

UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="My Sparta Log"))
class MYSPARTALOG_API UMySpartaLogDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UMySpartaLogDeveloperSettings();

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Speech")
	TSoftObjectPtr<UMySpartaSpeechStyleDataAsset> DefaultSpeechStyle;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Log")
	bool bPrintToOutputLogByDefault;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Log")
	bool bPrintToScreenByDefault;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Log", meta = (ClampMin = "0.1"))
	float DefaultScreenLogDuration;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Log")
	FColor DefaultScreenLogColor;

public:
	virtual FName GetCategoryName() const override;
};