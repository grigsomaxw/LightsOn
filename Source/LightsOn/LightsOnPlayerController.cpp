// Copyright Epic Games, Inc. All Rights Reserved.

#include "LightsOnPlayerController.h"

ALightsOnPlayerController::ALightsOnPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
