// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ToastyConquest : ModuleRules
{
	public ToastyConquest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D"});

        PrivateDependencyModuleNames.AddRange(new string[] {});
    }
}
