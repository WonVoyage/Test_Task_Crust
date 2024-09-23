#pragma once

#include "Warehouse.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Carrier.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
    NoneActive,
    IsWaiting,
    GoToWaitingPoint,
    GoToTake,
    GoToGive
};


UCLASS()
class ACarrier : public ACharacter
{
    GENERATED_BODY()

public:
    ACarrier();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loader")
    int32 CarriedResourceType; // ��� �������, ������� ����� �������

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loader")
    int32 CarriedAmount; // ���������� �������

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loader")
    AWarehouse* TargetWarehouse;  // �����, �� ������� ���� �������

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loader")
    AWarehouse* SourceWarehouse;  // �����, � �������� ���� �������

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loader") EActionType Action_Type;

    UFUNCTION(BlueprintCallable, Category = "Loader")
    void PickUpResource(AWarehouse* FromWarehouse);

    UFUNCTION(BlueprintCallable, Category = "Loader")
    void DeliverResource(AWarehouse* ToWarehouse);

protected:
    virtual void BeginPlay() override;
};
