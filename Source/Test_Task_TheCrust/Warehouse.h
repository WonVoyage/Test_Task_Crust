#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Warehouse.generated.h"

UCLASS()
class AWarehouse : public AActor
{
    GENERATED_BODY()

public:
    AWarehouse();

    UFUNCTION(BlueprintCallable, Category = "Warehouse") void AddResource(int32 Amount);
    UFUNCTION(BlueprintCallable, Category = "Warehouse") void RemoveResource(int32 Amount);
    UFUNCTION(BlueprintCallable, Category = "Warehouse") void UpdateAmount(int32 amount);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Warehouse") int32 ResourceType;  // (от 0 до 49)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Warehouse") int32 MaxCapacity;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Warehouse") int32 CurrentAmount;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Warehouse") bool bIsActive;
    
protected:
    virtual void BeginPlay() override;
};