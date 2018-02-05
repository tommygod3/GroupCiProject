// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CiProjectGameMode.h"
#include "CiProjectCharacter.h"

ACiProjectGameMode::ACiProjectGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ACiProjectCharacter::StaticClass();
	


}
