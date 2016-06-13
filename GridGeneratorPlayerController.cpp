// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "GridGenerator.h"
#include "GridGeneratorPlayerController.h"

AGridGeneratorPlayerController::AGridGeneratorPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
