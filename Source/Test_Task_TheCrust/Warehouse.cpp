#include "Warehouse.h"
#include "Carrier.h"

#include <Kismet/GameplayStatics.h>

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

    if (CurrentAmount > MaxCapacity)
        CurrentAmount = MaxCapacity;

    DistributeResourceToNeighbors();
}

void AWarehouse::RemoveResource(int32 Amount)
{
    if (bIsActive && CurrentAmount - Amount >= 0)
        CurrentAmount -= Amount;
}

void AWarehouse::DistributeResourceToNeighbors()
{
    TArray<AWarehouse*> NeighboringWarehouses = FindNeighboringWarehouses();

    if (NeighboringWarehouses.Num() == 0) return;

    float CurrentFillPercentage = static_cast<float>(CurrentAmount) / MaxCapacity;

    for (AWarehouse* NeighborWarehouse : NeighboringWarehouses)
    {
        if (!NeighborWarehouse) continue;
        if (NeighborWarehouse->ResourceType != ResourceType) continue;

        float NeighborFillPercentage = static_cast<float>(NeighborWarehouse->CurrentAmount) / NeighborWarehouse->MaxCapacity;

        ACarrier* AvailableCarrier = FindAvailableCarrier();

        if (NeighborFillPercentage < CurrentFillPercentage)
        {
            int32 ResourceToTransfer = (CurrentAmount - NeighborWarehouse->CurrentAmount) / 2;

            if (ResourceToTransfer > 0)
            {
                if (AvailableCarrier)
                {
                    AvailableCarrier->MoveToWarehouse(NeighborWarehouse);
                    CurrentAmount -= ResourceToTransfer;
                }
            }
        }
        else if (NeighborFillPercentage > CurrentFillPercentage)
        {
            int32 ResourceToTransfer = (NeighborWarehouse->CurrentAmount - CurrentAmount) / 2;

            if (ResourceToTransfer > 0)
            {
                if (AvailableCarrier)
                {
                    AvailableCarrier->MoveToWarehouse(NeighborWarehouse);
                    AvailableCarrier->Action_Type = EActionType::GoToTake;
                }
            }
        }
    }
}

TArray<AWarehouse*> AWarehouse::FindNeighboringWarehouses()
{
    TArray<AWarehouse*> NeighboringWarehouses;
    TArray<AActor*> AllWarehouses;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWarehouse::StaticClass(), AllWarehouses);

    for (AActor* Actor : AllWarehouses)
    {
        AWarehouse* Warehouse = Cast<AWarehouse>(Actor);
        if (Warehouse && Warehouse != this) // Исключаем сам склад
        {
            float Distance = FVector::Dist(Warehouse->GetActorLocation(), GetActorLocation());

            if (Distance <= 1000.0f) // Если склад находится в пределах радиуса 1000 единиц
                NeighboringWarehouses.Add(Warehouse);
        }
    }

    return NeighboringWarehouses;
}

ACarrier* AWarehouse::FindAvailableCarrier()
{
    TArray<AActor*> AllCarriers;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACarrier::StaticClass(), AllCarriers);

    for (AActor* Actor : AllCarriers)
    {
        ACarrier* Carrier = Cast<ACarrier>(Actor);
        if (Carrier && Carrier->Is_Avaliable)
            return Carrier;
    }

    return nullptr;
}