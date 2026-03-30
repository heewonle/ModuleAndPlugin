// MySpartaLog.cpp

#include "MySpartaLog.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogMySpartaModule);

void FMySpartaLog::StartupModule()
{
	UE_LOG(LogMySpartaModule, Warning, TEXT("MySpartaLog is Start"));
}

void FMySpartaLog::ShutdownModule()
{
	UE_LOG(LogMySpartaModule, Log, TEXT("MySpartaLog module shutdown."));
}

IMPLEMENT_MODULE(FMySpartaLog, MySpartaLog);