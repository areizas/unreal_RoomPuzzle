// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class unreal_RoomPuzzleEditorTarget : TargetRules
{
	public unreal_RoomPuzzleEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "unreal_RoomPuzzle" } );
	}
}
