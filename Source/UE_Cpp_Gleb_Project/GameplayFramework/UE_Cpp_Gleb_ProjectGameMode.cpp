// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_Cpp_Gleb_ProjectGameMode.h"
#include "UE_Cpp_Gleb_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE_Cpp_Gleb_ProjectGameMode::AUE_Cpp_Gleb_ProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
