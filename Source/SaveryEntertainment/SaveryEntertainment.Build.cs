// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SaveryEntertainment : ModuleRules
{
	public SaveryEntertainment(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[]
			{
				
			}
		);

		PrivateIncludePaths.AddRange(
			new string[]
			{
		
			}
		);
		
		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
			}
		);
		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
