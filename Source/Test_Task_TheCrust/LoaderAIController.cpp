#include "LoaderAIController.h"
#include "Kismet/GameplayStatics.h"

ALoaderAIController::ALoaderAIController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ALoaderAIController::BeginPlay()
{
    Super::BeginPlay();
    FindNearestWarehouse();
}

void ALoaderAIController::FindNearestWarehouse()
{
    // �������� ��� ������
    TArray<AActor*> FoundWarehouses;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWarehouse::StaticClass(), FoundWarehouses);

    AWarehouse* NearestWarehouse = nullptr;
    float NearestDistance = FLT_MAX;

    // �������� �������� Pawn'�
    ACarrier* Carrier = Cast<ACarrier>(GetPawn());
    if (!Carrier)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to get Carrier"));
        return; // ���� Pawn �� �������, ������� �� �������
    }

    // �������� ������, ������� ����� �������
    int32 CarriedResourceType = Carrier->CarriedResourceType;

    for (AActor* WarehouseActor : FoundWarehouses)
    {
        AWarehouse* Warehouse = Cast<AWarehouse>(WarehouseActor);
        if (Warehouse && Warehouse->ResourceType == CarriedResourceType)
        {
            // ���������� ����������, ����� ����� ��������� �����
            float Distance = FVector::Dist(Warehouse->GetActorLocation(), Carrier->GetActorLocation());

            if (Distance < NearestDistance)
            {
                NearestWarehouse = Warehouse;
                NearestDistance = Distance;
                Carrier->TargetWarehouse = NearestWarehouse;
            }
        }
    }

    if (NearestWarehouse)
    {
        // ���������, ��� AIController ����� ������������
        if (GetNavAgentPropertiesRef().bCanCrouch || GetNavAgentPropertiesRef().bCanFly || GetNavAgentPropertiesRef().bCanJump || GetNavAgentPropertiesRef().bCanSwim || GetNavAgentPropertiesRef().bCanWalk)
        {
            MoveToActor(NearestWarehouse);
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
