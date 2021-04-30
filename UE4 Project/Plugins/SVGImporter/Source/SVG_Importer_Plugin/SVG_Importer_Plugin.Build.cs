// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SVG_Importer_Plugin : ModuleRules
{
	public SVG_Importer_Plugin(ReadOnlyTargetRules Target) : base(Target)
	{
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
			new string[] {"SVG_Importer_Plugin/Public"}
		);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {"SVG_Importer_Plugin/Private"}
		);


        PublicDependencyModuleNames.AddRange(
            new string[] {"Core"}
        );


        PrivateDependencyModuleNames.AddRange(
			new string[] {
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"InputCore",
				"UnrealEd",
				"LevelEditor",
                "PropertyEditor",
                "EditorStyle"
			}
		);
	}
}
