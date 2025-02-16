// Copyright Eric Downey - 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItem.h"

#include "InventorySlot.generated.h"

/**
 * Structure to hold `FUInventoryItem` and the amount "stacked" as a single slot.
 */
UCLASS(BlueprintType)
class <PROJECT_API> UInventorySlot : public UObject
{
	GENERATED_BODY()
	
public:
    
    UInventorySlot();
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Item"))
    FUInventoryItem Item;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Count"))
    int32 Count;
};
