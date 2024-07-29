using UnrealBuildTool;

public class SimpleCanvasPanel : ModuleRules
{
	public SimpleCanvasPanel(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UMG",
			}
		);
	}
}
