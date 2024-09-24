#include "Carrier.h"
#include "Warehouse.h"

ACarrier::ACarrier()
{
    CarriedResourceType = -1;  // Грузчик пуст по умолчанию
    CarriedAmount = 0;
    TargetWarehouse = nullptr;
    SourceWarehouse = nullptr;
    Action_Type = EActionType::NoneActive;
    Is_Avaliable = true;
}

void ACarrier::BeginPlay()
{
    Super::BeginPlay();
}

void ACarrier::PickUpResource(AWarehouse* FromWarehouse)
{
    if (FromWarehouse && FromWarehouse->CurrentAmount > 0 && (CarriedResourceType == -1 || FromWarehouse->ResourceType == CarriedResourceType))
    {
        int32 AmountToPick = FMath::Min(FromWarehouse->CurrentAmount, 50); // Забираем до 50 ресурсов за раз
        FromWarehouse->RemoveResource(AmountToPick);
        CarriedAmount += AmountToPick;
        SourceWarehouse = FromWarehouse;
        Is_Avaliable = false;
    }
}

void ACarrier::DeliverResource(AWarehouse* ToWarehouse)
{
    if (ToWarehouse && ToWarehouse->ResourceType == CarriedResourceType && ToWarehouse->CurrentAmount + CarriedAmount <= ToWarehouse->MaxCapacity)
    {
        ToWarehouse->AddResource(CarriedAmount);
        CarriedAmount = 0;  // Грузчик пуст
        TargetWarehouse = ToWarehouse;  // Помечаем склад, куда доставили
        Is_Avaliable = true;
    }
}

void ACarrier::MoveToWarehouse(AWarehouse* ToWarehouse)
{
    if (ToWarehouse)
    {
        TargetWarehouse = ToWarehouse;

        // Команда для перемещения грузчика к складу

        //CarrierAIController = Cast<AAIController>(GetController());
        //if (CarrierAIController)
        //    CarrierAIController->MoveToActor(Warehouse, 50.0f);
    }
}

void ACarrier::OnArrivedAtWarehouse()
{
    if (TargetWarehouse)
    {
        switch (Action_Type)
        {
        case EActionType::NoneActive:
            break;

        case EActionType::GoToWaitingPoint:
            break;

        case EActionType::GoToTake:
            TargetWarehouse->DistributeResourceToNeighbors();
            break;

        case EActionType::GoToGive:
            TargetWarehouse->AddResource(CarriedAmount);
            CarriedAmount = 0;
            Is_Avaliable = true;
            break;

        default:
            break;
        }
    }
}