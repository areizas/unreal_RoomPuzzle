// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class unreal_RoomPuzzleTarget : TargetRules
{
	public unreal_RoomPuzzleTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "unreal_RoomPuzzle" } );
	}
}
