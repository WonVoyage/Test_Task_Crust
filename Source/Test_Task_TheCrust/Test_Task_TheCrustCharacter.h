#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Test_Task_TheCrustCharacter.generated.h"
//-------------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable)
class ATest_Task_TheCrustCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATest_Task_TheCrustCharacter();

	virtual void Tick(float delta_seconds) override;

	FORCEINLINE class UCameraComponent *Get_TopDown_CameraComponent() const;
	FORCEINLINE class USpringArmComponent *Get_CameraBoom() const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) class UCameraComponent* TopDown_CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) class USpringArmComponent* CameraBoom;
};
//-------------------------------------------------------------------------------------------------------------
