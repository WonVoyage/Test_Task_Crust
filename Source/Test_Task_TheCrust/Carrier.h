#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Carrier.generated.h"

class AWarehouse;

UENUM(BlueprintType)
enum class EActionType : uint8
{
    NoneActive,
    IsWaiting,
    GoToWaitingPoint,
    GoToTake,
    GoToGive
};


UCLASS()
class ACarrier : public ACharacter
{
    GENERATED_BODY()

public:
    ACarrier();

    UFUNCTION(BlueprintCallable, Category = "Loader") void PickUpResource(AWarehouse* FromWarehouse);
    UFUNCTION(BlueprintCallable, Category = "Loader") void DeliverResource(AWarehouse* ToWarehouse);
    UFUNCTION(BlueprintCallable, Category = "Loader") void OnArrivedAtWarehouse();
    
    void MoveToWarehouse(AWarehouse* ToWarehouse);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loader") int32 CarriedResourceType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loader") int32 CarriedAmount;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loader") AWarehouse* TargetWarehouse;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loader") AWarehouse* SourceWarehouse;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loader") EActionType Action_Type;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loader") bool Is_Avaliable;

protected:
    virtual void BeginPlay() override;
};
