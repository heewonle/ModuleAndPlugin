#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MySpartaLogBPLibrary.generated.h"

class AActor;
class UMySpartaSpeechStyleDataAsset;

UENUM(BlueprintType)
enum class EMySpartaLogType : uint8
{
	Info,
	Warning,
	Error
};

UCLASS()
class MYSPARTALOG_API UMySpartaLogBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MySpartaLog")
	static void LogText(
		const FString& Message,
		bool bPrintToOutputLog = true,
		bool bPrintToScreen = false,
		float ScreenDuration = 2.0f,
		FLinearColor ScreenColor = FLinearColor::White
	);

	UFUNCTION(BlueprintCallable, Category = "MySpartaLog")
	static void LogTextToActor(
		AActor* TargetActor,
		const FString& Message,
		bool bPrintToOutputLog = true,
		bool bPrintToScreen = false,
		float ScreenDuration = 2.0f,
		FLinearColor ScreenColor = FLinearColor::White
	);

	UFUNCTION(BlueprintCallable, Category = "MySpartaLog")
	static void LogTypedTextToActor(
		AActor* TargetActor,
		const FString& Message,
		EMySpartaLogType InLogType,
		bool bPrintToOutputLog = true,
		bool bPrintToScreen = false,
		float ScreenDuration = 2.0f
	);

	UFUNCTION(BlueprintCallable, Category = "MySpartaLog")
	static void ShowSpeechToActor(
		AActor* TargetActor,
		const FText& Message,
		UMySpartaSpeechStyleDataAsset* OverrideStyle = nullptr
	);
};