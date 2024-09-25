#include "Test_Task_TheCrustGameMode.h"
#include "Test_Task_TheCrustPlayerController.h"
#include "Test_Task_TheCrustCharacter.h"
#include "UObject/ConstructorHelpers.h"
//-------------------------------------------------------------------------------------------------------------
ATest_Task_TheCrustGameMode::ATest_Task_TheCrustGameMode()
{
	PlayerControllerClass = ATest_Task_TheCrustPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
		DefaultPawnClass = PlayerPawnBPClass.Class;

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
		PlayerControllerClass = PlayerControllerBPClass.Class;
}
//-------------------------------------------------------------------------------------------------------------
