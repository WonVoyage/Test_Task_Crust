#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Warehouse.generated.h"

class ACarrier;
//-------------------------------------------------------------------------------------------------------------
UCLASS()
class AWarehouse : public AActor
{
    GENERATED_BODY()

public:
    AWarehouse();

    UFUNCTION(BlueprintCallable, Category = "Warehouse") void Add_Resource(int amount);
    UFUNCTION(BlueprintCallable, Category = "Warehouse") void Remove_Resource(int amount);

    void Distribute_Resource_To_Neighbors();
    TArray<AWarehouse*> Find_Neighboring_Warehouses();
    ACarrier* Find_Available_Carrier();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Warehouse") int Resource;  // (от 0 до 49)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Warehouse") int Capacity;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Warehouse") int Current_Amount;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Warehouse") bool Is_Active;
    
protected:
    virtual void BeginPlay() override;
};
//-------------------------------------------------------------------------------------------------------------
