// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_SamraGameMode.h"
#include "Project_SamraCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_SamraGameMode::AProject_SamraGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
