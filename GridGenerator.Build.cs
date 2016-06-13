// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GridGenerator : ModuleRules
{
	public GridGenerator(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","Json","JsonUtilities","UMG"});
        PublicDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore"});

    }
}
