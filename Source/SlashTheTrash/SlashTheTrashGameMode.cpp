// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlashTheTrashGameMode.h"
#include "SlashTheTrashCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASlashTheTrashGameMode::ASlashTheTrashGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
