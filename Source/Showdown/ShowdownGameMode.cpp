// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ShowdownGameMode.h"
#include "ShowdownCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShowdownGameMode::AShowdownGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
