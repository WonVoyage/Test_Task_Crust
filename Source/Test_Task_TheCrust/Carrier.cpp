#include "Carrier.h"
#include "Warehouse.h"
//-------------------------------------------------------------------------------------------------------------
ACarrier::ACarrier()
{
    Is_Avaliable = true;
    Carried_Resource = -1;  // Грузчик пуст по умолчанию
    Carried_Amount = 0;
    Target_Warehouse = nullptr;
    Source_Warehouse = nullptr;
    Action_Type = EActionType::None;
}
//-------------------------------------------------------------------------------------------------------------
void ACarrier::BeginPlay()
{
    Super::BeginPlay();
}
//-------------------------------------------------------------------------------------------------------------
void ACarrier::Pick_Up_Resource(AWarehouse *from_warehouse)
{
    if (from_warehouse && from_warehouse->Current_Amount > 0 && (Carried_Resource == -1 || from_warehouse->Resource == Carried_Resource))
    {
        int amount_to_pick;

        amount_to_pick = FMath::Min(from_warehouse->Current_Amount, 50); // Забираем до 50 ресурсов за раз
        from_warehouse->Remove_Resource(amount_to_pick);
        Carried_Amount += amount_to_pick;
        Source_Warehouse = from_warehouse;
        Is_Avaliable = false;
    }
}
//-------------------------------------------------------------------------------------------------------------
void ACarrier::Deliver_Resource(AWarehouse *to_warehouse)
{
    if (to_warehouse && to_warehouse->Resource == Carried_Resource && to_warehouse->Current_Amount + Carried_Amount <= to_warehouse->Capacity)
    {
        to_warehouse->Add_Resource(Carried_Amount);
        Carried_Amount = 0;
        Target_Warehouse = to_warehouse;
        Is_Avaliable = true;
    }
}
//-------------------------------------------------------------------------------------------------------------
void ACarrier::Move_To_Warehouse(AWarehouse *to_warehouse)
{
    if (to_warehouse)
    {
        Target_Warehouse = to_warehouse;

        // Команда для перемещения грузчика к складу

        //CarrierAIController = Cast<AAIController>(GetController());
        //if (CarrierAIController)
        //    CarrierAIController->MoveToActor(Warehouse, 50.0f);
    }
}
//-------------------------------------------------------------------------------------------------------------
void ACarrier::On_Arrived_At_Warehouse()
{
    if (Target_Warehouse)
    {
        switch (Action_Type)
        {
        case EActionType::None:
            break;

        case EActionType::Go_To_Waiting_Point:
            break;

        case EActionType::Go_To_Take:
            Target_Warehouse->Distribute_Resource_To_Neighbors();
            break;

        case EActionType::Go_To_Give:
            Target_Warehouse->Add_Resource(Carried_Amount);
            Carried_Amount = 0;
            Is_Avaliable = true;
            break;

        default:
            break;
        }
    }
}
//-------------------------------------------------------------------------------------------------------------
