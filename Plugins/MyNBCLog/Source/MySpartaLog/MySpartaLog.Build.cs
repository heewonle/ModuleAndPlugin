// MySpartaLog.Build.cs

using UnrealBuildTool;

public class MySpartaLog : ModuleRules
{
	public MySpartaLog(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
			{
				// Initial Modules
				"Core", "CoreUObject", "Engine", "InputCore","UMG","DeveloperSettings"
			}
		);

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore"
		});

	}
}