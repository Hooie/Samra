// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using UnrealBuildTool.Rules;

public class Project_Samra : ModuleRules
{
	public Project_Samra(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"GameplayAbilities",
            "GameplayTags", 
			"GameplayTasks", 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"EnhancedInput", 
			"UMG", 
			"Paper2D",
            "MotionWarping",
            "AnimGraphRuntime",
            "MoviePlayer",
            "Niagara",
            "GeometryCollectionEngine"
            });	

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore"});
    }
}
