// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CSGArea : ModuleRules
{
	public CSGArea(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[]
			{
				// ... add public include paths required here ...
			}
		);


		PrivateIncludePaths.AddRange(
			new string[]
			{
				// ... add other private include paths required here ...
			}
		);


		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core"
				// ... add other public dependencies that you statically link with here ...
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"GeometryScriptingCore",
				"GeometryFramework",
				"PhysicsCore"

				// ... add private dependencies that you statically link with here ...	
			}
		);

		if (Target.bBuildEditor)
			PrivateDependencyModuleNames.AddRange(
				new[]
				{
					"Settings"
				}
			);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);
	}
}