#include "Carrier.h"

ACarrier::ACarrier()
{
    CarriedResourceType = -1;  // Грузчик пуст по умолчанию
    CarriedAmount = 0;
    TargetWarehouse = nullptr;
    SourceWarehouse = nullptr;
    Action_Type = EActionType::NoneActive;
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

        CarriedResourceType = FromWarehouse->ResourceType;
        CarriedAmount += AmountToPick;
        SourceWarehouse = FromWarehouse;
    }
}

void ACarrier::DeliverResource(AWarehouse* ToWarehouse)
{
    if (ToWarehouse && ToWarehouse->ResourceType == CarriedResourceType && ToWarehouse->CurrentAmount + CarriedAmount <= ToWarehouse->MaxCapacity)
    {
        ToWarehouse->AddResource(CarriedAmount);
        CarriedAmount = 0;  // Грузчик пуст
        TargetWarehouse = ToWarehouse;  // Помечаем склад, куда доставили
    }
}