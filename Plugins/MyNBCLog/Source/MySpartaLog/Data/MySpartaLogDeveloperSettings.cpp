#include "MySpartaLogDeveloperSettings.h"

UMySpartaLogDeveloperSettings::UMySpartaLogDeveloperSettings()
{
	bPrintToOutputLogByDefault = true;
	bPrintToScreenByDefault = false;
	DefaultScreenLogDuration = 2.0f;
	DefaultScreenLogColor = FColor::White;
}

FName UMySpartaLogDeveloperSettings::GetCategoryName() const
{
	return TEXT("Plugins");
}