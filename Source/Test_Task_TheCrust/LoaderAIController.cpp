#include "LoaderAIController.h"
#include "Kismet/GameplayStatics.h"
//-------------------------------------------------------------------------------------------------------------
ALoaderAIController::ALoaderAIController()
{
    PrimaryActorTick.bCanEverTick = true;
}
//-------------------------------------------------------------------------------------------------------------
void ALoaderAIController::BeginPlay()
{
    Super::BeginPlay();
    Move_To_Warehouse();
}
//-------------------------------------------------------------------------------------------------------------
void ALoaderAIController::Move_To_Warehouse()
{
    //float nearest_distance = FLT_MAX;
    //int carried_resource = 0;
    //TArray<AActor*> found_warehouses;
    //AWarehouse* nearest_warehouse = nullptr;
    ACarrier* carrier = Cast<ACarrier>(GetPawn());
    //UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWarehouse::StaticClass(), found_warehouses);

    if (!carrier)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to get Carrier"));
        return;
    }

    //carried_resource = carrier->Carried_Resource;

    //for (AActor *warehouse_actor : found_warehouses)
    //{
    //    AWarehouse *warehouse = Cast<AWarehouse>(warehouse_actor);

    //    if (warehouse == carrier->Target_Warehouse) continue;
    //    if (warehouse && warehouse->Resource == carried_resource)
    //    {
    //        // Сравниваем расстояния, чтобы найти ближайший склад
    //        float distance = FVector::Dist(warehouse->GetActorLocation(), carrier->GetActorLocation());

    //        if (distance < nearest_distance)
    //        {
    //            nearest_warehouse = warehouse;
    //            nearest_distance = distance;
    //            carrier->Source_Warehouse = carrier->Target_Warehouse;
    //            carrier->Target_Warehouse = nearest_warehouse;
    //        }
    //    }
    //}

    if (carrier->Target_Warehouse)
    {
        if (GetNavAgentPropertiesRef().bCanCrouch || GetNavAgentPropertiesRef().bCanFly || GetNavAgentPropertiesRef().bCanJump || GetNavAgentPropertiesRef().bCanSwim || GetNavAgentPropertiesRef().bCanWalk)
        {
            MoveToActor(carrier->Target_Warehouse);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("AIController cannot move to the actor."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No suitable warehouse found."));
    }
}
//-------------------------------------------------------------------------------------------------------------
