using UnrealBuildTool;

public class Toy : ModuleRules
{
	public Toy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrivateIncludePaths.Add(ModuleDirectory);


		PrivateDependencyModuleNames.Add("Core");


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"EditorStyle",
				"LevelEditor",
				"Projects",
				"GameplayDebugger",
				"PropertyEditor",
				"U08_Features",
				"MainFrame",
				"DesktopPlatform"
			}
		);
	}
}
