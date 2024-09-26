#include "Warehouse.h"
#include "Carrier.h"
#include "Waiting_Point.h"

#include <Kismet/GameplayStatics.h>
//-------------------------------------------------------------------------------------------------------------
AWarehouse::AWarehouse()
{
    PrimaryActorTick.bCanEverTick = true;

    Capacity = FMath::RandRange(10, 500);
    Resource = FMath::RandRange(0, 49);
    Current_Amount = 0;
    Is_Active = true;
}
//-------------------------------------------------------------------------------------------------------------
void AWarehouse::BeginPlay()
{
    Super::BeginPlay();
}
//-------------------------------------------------------------------------------------------------------------
void AWarehouse::Add_Resource(int amount)
{
    if (Is_Active && Current_Amount + amount <= Capacity)
        Current_Amount += amount;

    if (Current_Amount > Capacity)
        Current_Amount = Capacity;

    Distribute_Resource_To_Neighbors();
}
//-------------------------------------------------------------------------------------------------------------
void AWarehouse::Remove_Resource(int amount)
{
    if (Is_Active && Current_Amount - amount >= 0)
        Current_Amount -= amount;
}
//-------------------------------------------------------------------------------------------------------------
void AWarehouse::Distribute_Resource_To_Neighbors()
{
    TArray<AWarehouse*> neighboring_warehouses = Find_Neighboring_Warehouses();

    if (neighboring_warehouses.Num() == 0) return;

    float current_fill_percentage = static_cast<float>(Current_Amount) / Capacity;

    for (AWarehouse *neighbor_warehouse : neighboring_warehouses)
    {
        if (!neighbor_warehouse) continue;
        if (neighbor_warehouse->Resource != Resource) continue;

        float neighbor_fill_percentage = static_cast<float>(neighbor_warehouse->Current_Amount) / neighbor_warehouse->Capacity;

        ACarrier *available_carrier = Find_Available_Carrier();

        if (neighbor_fill_percentage < current_fill_percentage)
        {
            int resource_to_transfer = (Current_Amount - neighbor_warehouse->Current_Amount) / 2;

            if (resource_to_transfer > 0)
            {
                if (available_carrier)
                {
                    available_carrier->Move_To_Warehouse(neighbor_warehouse);
                    available_carrier->Carried_Amount += resource_to_transfer;
                    available_carrier->Action_Type = EActionType::Go_To_Give;
                    Current_Amount -= resource_to_transfer;
                }
            }
            else
            {
                AActor* waiting_point_actor = UGameplayStatics::GetActorOfClass(GetWorld(), AWaiting_Point::StaticClass());
                AWaiting_Point* waiting_point = Cast<AWaiting_Point>(waiting_point_actor);
                available_carrier->Move_To_Warehouse(waiting_point);
                available_carrier->Action_Type = EActionType::Is_Waiting;
            }

        }
        else if (neighbor_fill_percentage > current_fill_percentage)
        {
            int resource_to_Transfer = (neighbor_warehouse->Current_Amount - Current_Amount) / 2;

            if (resource_to_Transfer > 0)
            {
                if (available_carrier)
                {
                    available_carrier->Move_To_Warehouse(neighbor_warehouse);
                    available_carrier->Action_Type = EActionType::Go_To_Take;
                }
            }
            else
            {
                AActor* waiting_point_actor = UGameplayStatics::GetActorOfClass(GetWorld(), AWaiting_Point::StaticClass());
                AWaiting_Point* waiting_point = Cast<AWaiting_Point>(waiting_point_actor);
                available_carrier->Move_To_Warehouse(waiting_point);
                available_carrier->Action_Type = EActionType::Is_Waiting;
            }

        }
        else
        {
           AActor *waiting_point_actor = UGameplayStatics::GetActorOfClass(GetWorld(), AWaiting_Point::StaticClass());
           AWaiting_Point *waiting_point = Cast<AWaiting_Point>(waiting_point_actor);
           available_carrier->Move_To_Warehouse(waiting_point);
           available_carrier->Action_Type = EActionType::Is_Waiting;
        }
    }
}
//-------------------------------------------------------------------------------------------------------------
TArray<AWarehouse*> AWarehouse::Find_Neighboring_Warehouses()
{
    TArray<AWarehouse*> neighboring_warehouses;
    TArray<AActor*> all_warehouses;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWarehouse::StaticClass(), all_warehouses);

    for (AActor *actor : all_warehouses)
    {
        AWarehouse *warehouse = Cast<AWarehouse>(actor);
        if (warehouse && warehouse != this) // Исключаем сам склад
        {
            float Distance = FVector::Dist(warehouse->GetActorLocation(), GetActorLocation());

            if (Distance <= 1000.0f) // Если склад находится в пределах радиуса 1000 единиц
                neighboring_warehouses.Add(warehouse);
        }
    }

    return neighboring_warehouses;
}
//-------------------------------------------------------------------------------------------------------------
ACarrier* AWarehouse::Find_Available_Carrier()
{
    TArray<AActor*> all_carriers;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACarrier::StaticClass(), all_carriers);

    for (AActor *actor : all_carriers)
    {
        ACarrier *carrier = Cast<ACarrier>(actor);
        if (carrier && carrier->Is_Avaliable)
            return carrier;
    }

    return nullptr;
}
//-------------------------------------------------------------------------------------------------------------
