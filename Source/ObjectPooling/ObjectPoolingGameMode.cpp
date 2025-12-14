// Copyright Epic Games, Inc. All Rights Reserved.

#include "ObjectPoolingGameMode.h"
#include "ObjectPoolingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AObjectPoolingGameMode::AObjectPoolingGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
