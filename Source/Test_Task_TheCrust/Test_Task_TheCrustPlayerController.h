#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Test_Task_TheCrustCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Test_Task_TheCrustPlayerController.generated.h"

class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ATest_Task_TheCrustPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATest_Task_TheCrustPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) float ShortPressThreshold;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UNiagaraSystem *FXCursor = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true")) UInputMappingContext *DefaultMappingContext = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true")) UInputAction *SetDestinationClickAction = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true")) UInputAction *SetDestinationTouchAction = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true")) UInputAction* MoveAction = 0;

protected:

	virtual void SetupInputComponent() override;
	virtual void BeginPlay();

	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();
	void Move(const FInputActionValue& Value);

	uint32 bMoveToMouseCursor : 1;

private:

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
	FVector CachedDestination;

};
