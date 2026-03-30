#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MySpartaSpeechStyleDataAsset.generated.h"

class UMySpartaSpeechBubbleWidgetBase;
class UTexture2D;

UCLASS(BlueprintType)
class MYSPARTALOG_API UMySpartaSpeechStyleDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UMySpartaSpeechStyleDataAsset();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speech")
	TSoftClassPtr<UMySpartaSpeechBubbleWidgetBase> BubbleWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speech", meta = (ClampMin = "0.1"))
	float DisplayDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speech")
	FVector RelativeOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speech")
	FVector2D DrawSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speech")
	bool bWidgetSpaceScreen;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speech")
	FLinearColor DefaultTextColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speech", meta = (ClampMin = "1"))
	int32 DefaultFontSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speech")
	FName SocketName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speech")
	bool bUseScreenSpace;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speech")
	bool bFaceCameraInWorldSpace;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speech")
	bool bUseBubbleTail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speech")
	FLinearColor WarningTextColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speech")
	FLinearColor ErrorTextColor;
};