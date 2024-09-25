#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Carrier.generated.h"

class AWarehouse;
//-------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
enum class EActionType : uint8
{
    None,
    Go_To_Waiting_Point,
    Go_To_Take,
    Go_To_Give
};
//-------------------------------------------------------------------------------------------------------------
UCLASS()
class ACarrier : public ACharacter
{
    GENERATED_BODY()

public:
    ACarrier();

    UFUNCTION(BlueprintCallable, Category = "Loader") void Pick_Up_Resource(AWarehouse *from_warehouse);
    UFUNCTION(BlueprintCallable, Category = "Loader") void Deliver_Resource(AWarehouse *to_warehouse);
    UFUNCTION(BlueprintCallable, Category = "Loader") void On_Arrived_At_Warehouse();
    
    void Move_To_Warehouse(AWarehouse *to_warehouse);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loader") bool Is_Avaliable;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loader") int Carried_Resource;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loader") int Carried_Amount;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loader") AWarehouse *Target_Warehouse;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loader") AWarehouse *Source_Warehouse;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loader") EActionType Action_Type;

protected:
    virtual void BeginPlay() override;
};
//-------------------------------------------------------------------------------------------------------------
