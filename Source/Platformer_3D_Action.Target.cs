// @Ludus Académie Etudiant

using UnrealBuildTool;
using System.Collections.Generic;

public class Platformer_3D_ActionTarget : TargetRules
{
	public Platformer_3D_ActionTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Platformer_3D_Action" } );
	}
}
