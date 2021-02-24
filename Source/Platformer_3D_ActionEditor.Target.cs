// @Ludus Académie Etudiant

using UnrealBuildTool;
using System.Collections.Generic;

public class Platformer_3D_ActionEditorTarget : TargetRules
{
	public Platformer_3D_ActionEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Platformer_3D_Action" } );
	}
}
