// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Test_Task_TheCrust : ModuleRules
{
	public Test_Task_TheCrust(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput" });
    }
}
