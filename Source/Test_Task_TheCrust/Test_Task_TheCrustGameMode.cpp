// Copyright Epic Games, Inc. All Rights Reserved.

#include "Test_Task_TheCrustGameMode.h"
#include "Test_Task_TheCrustPlayerController.h"
#include "Test_Task_TheCrustCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATest_Task_TheCrustGameMode::ATest_Task_TheCrustGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATest_Task_TheCrustPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}