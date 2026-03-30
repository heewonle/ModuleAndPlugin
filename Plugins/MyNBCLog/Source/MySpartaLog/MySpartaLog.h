// MySpartaLog.h

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

MYSPARTALOG_API DECLARE_LOG_CATEGORY_EXTERN(LogMySpartaModule, Log, All);

class FMySpartaLog : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};