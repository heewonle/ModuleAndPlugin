#include "MySpartaSpeechStyleDataAsset.h"

UMySpartaSpeechStyleDataAsset::UMySpartaSpeechStyleDataAsset()
{
	DisplayDuration = 2.0f;
	RelativeOffset = FVector(0.f, 0.f, 110.f);
	DrawSize = FVector2D(300.f, 100.f);
	bWidgetSpaceScreen = false;
	DefaultTextColor = FLinearColor::White;
	DefaultFontSize = 24;
	SocketName = NAME_None;
	bUseScreenSpace = false;
	bFaceCameraInWorldSpace = true;
	bUseBubbleTail = true;
	WarningTextColor = FLinearColor(1.f, 0.8f, 0.1f, 1.f);
	ErrorTextColor = FLinearColor(1.f, 0.2f, 0.2f, 1.f);
}