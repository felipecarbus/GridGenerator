// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "GridGenerator.h"
#include "GridGeneratorGameMode.h"
#include "GridGeneratorPlayerController.h"

AGridGeneratorGameMode::AGridGeneratorGameMode()
{
	// no pawn by default
	DefaultPawnClass = NULL;
	// use our own player controller class
	PlayerControllerClass = AGridGeneratorPlayerController::StaticClass();
}
