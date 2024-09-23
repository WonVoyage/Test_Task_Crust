#include "Warehouse.h"

AWarehouse::AWarehouse()
{
    PrimaryActorTick.bCanEverTick = true;

    MaxCapacity = FMath::RandRange(10, 500); // Случайный лимит от 10 до 500
    CurrentAmount = 0;
    ResourceType = FMath::RandRange(0, 49); // Случайный тип ресурса
    bIsActive = true;
}

void AWarehouse::BeginPlay()
{
    Super::BeginPlay();
}

void AWarehouse::AddResource(int32 Amount)
{
    if (bIsActive && CurrentAmount + Amount <= MaxCapacity)
        CurrentAmount += Amount;
}

void AWarehouse::RemoveResource(int32 Amount)
{
    if (bIsActive && CurrentAmount - Amount >= 0)
        CurrentAmount -= Amount;
}

void AWarehouse::UpdateAmount(int32 amount)
{
    CurrentAmount = amount;
}