#include "Test_Task_TheCrustCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
//-------------------------------------------------------------------------------------------------------------
ATest_Task_TheCrustCharacter::ATest_Task_TheCrustCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	TopDown_CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDown_CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDown_CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}
//-------------------------------------------------------------------------------------------------------------
void ATest_Task_TheCrustCharacter::Tick(float delta_seconds)
{
    Super::Tick(delta_seconds);
}
//-------------------------------------------------------------------------------------------------------------
UCameraComponent* ATest_Task_TheCrustCharacter::Get_TopDown_CameraComponent() const
{
	return TopDown_CameraComponent;
}
//-------------------------------------------------------------------------------------------------------------
USpringArmComponent* ATest_Task_TheCrustCharacter::Get_CameraBoom() const
{
	return CameraBoom;
}
//-------------------------------------------------------------------------------------------------------------
