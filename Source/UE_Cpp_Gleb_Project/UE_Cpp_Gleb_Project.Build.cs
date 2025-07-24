// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE_Cpp_Gleb_Project : ModuleRules
{
	public UE_Cpp_Gleb_Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "AITestSuite" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AssetRegistry", 
			"UMG", "Slate", "SlateCore" });
	}
}
