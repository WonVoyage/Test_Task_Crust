#pragma once

#include "Warehouse.h"
#include "Carrier.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "LoaderAIController.generated.h"
//-------------------------------------------------------------------------------------------------------------
UCLASS()
class ALoaderAIController : public AAIController
{
    GENERATED_BODY()

public:
    ALoaderAIController();

protected:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable) void Move_To_Warehouse();
};
//-------------------------------------------------------------------------------------------------------------
