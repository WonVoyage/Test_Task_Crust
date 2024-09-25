#include "Warehouse.h"
#include "Carrier.h"

#include <Kismet/GameplayStatics.h>
//-------------------------------------------------------------------------------------------------------------
AWarehouse::AWarehouse()
{
    PrimaryActorTick.bCanEverTick = true;

    Capacity = FMath::RandRange(10, 500);
    Current_Amount = 0;
    Resource = FMath::RandRange(0, 49);
    Is_Active = true;
}
//-------------------------------------------------------------------------------------------------------------
void AWarehouse::BeginPlay()
{
    Super::BeginPlay();
    ACarrier* carrier = Find_Available_Carrier();

    float nearest_distance = FLT_MAX;
    int carried_resource = 0;
    TArray<AActor*> found_warehouses;
    AWarehouse* nearest_warehouse = nullptr;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWarehouse::StaticClass(), found_warehouses);

    carried_resource = carrier->Carried_Resource;

    for (AActor *warehouse_actor : found_warehouses)
    {
        AWarehouse *warehouse = Cast<AWarehouse>(warehouse_actor);

        if (warehouse == carrier->Target_Warehouse) continue;
        if (warehouse && warehouse->Resource == carried_resource)
        {
            // Сравниваем расстояния, чтобы найти ближайший склад
            float distance = FVector::Dist(warehouse->GetActorLocation(), carrier->GetActorLocation());

            if (distance < nearest_distance)
            {
                nearest_warehouse = warehouse;
                nearest_distance = distance;
                carrier->Source_Warehouse = carrier->Target_Warehouse;
                carrier->Target_Warehouse = nearest_warehouse;
            }
        }
    }


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
                    //available_carrier->Move_To_Warehouse(neighbor_warehouse);
                    Current_Amount -= resource_to_transfer;
                }
            }
        }
        else if (neighbor_fill_percentage > current_fill_percentage)
        {
            int resource_to_Transfer = (neighbor_warehouse->Current_Amount - Current_Amount) / 2;

            if (resource_to_Transfer > 0)
            {
                if (available_carrier)
                {
                    //available_carrier->Move_To_Warehouse(neighbor_warehouse);
                    available_carrier->Action_Type = EActionType::Go_To_Take;
                }
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------
TArray<AWarehouse*> AWarehouse::Find_Neighboring_Warehouses()
{
    TArray<AWarehouse*> neighboring_warehouses;
    TArray<AActor*> AllWarehouses;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWarehouse::StaticClass(), AllWarehouses);

    for (AActor* Actor : AllWarehouses)
    {
        AWarehouse* Warehouse = Cast<AWarehouse>(Actor);
        if (Warehouse && Warehouse != this) // Исключаем сам склад
        {
            float Distance = FVector::Dist(Warehouse->GetActorLocation(), GetActorLocation());

            if (Distance <= 1000.0f) // Если склад находится в пределах радиуса 1000 единиц
                neighboring_warehouses.Add(Warehouse);
        }
    }

    return neighboring_warehouses;
}
//-------------------------------------------------------------------------------------------------------------
ACarrier* AWarehouse::Find_Available_Carrier()
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
//-------------------------------------------------------------------------------------------------------------
