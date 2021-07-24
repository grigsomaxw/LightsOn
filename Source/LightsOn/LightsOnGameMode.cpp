// Copyright Epic Games, Inc. All Rights Reserved.

#include "LightsOnGameMode.h"
#include "LightsOnPlayerController.h"
#include "LightsOnPawn.h"

ALightsOnGameMode::ALightsOnGameMode()
{
	// no pawn by default
	DefaultPawnClass = ALightsOnPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ALightsOnPlayerController::StaticClass();
}
