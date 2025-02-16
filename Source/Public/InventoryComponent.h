// Copyright Eric Downey - 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItem.h"
#include "InventorySlot.h"

#include "InventoryComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class <PROJECT_API> UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChangeDelegate);
    
    UPROPERTY(BlueprintAssignable, Category="Delegates")
    FOnInventoryChangeDelegate OnInventoryChangeEvent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame, meta=(DisplayName="MaxSlotSize"))
    int32 MaxSlotSize;
    
    UInventoryComponent();
    
    UFUNCTION(BlueprintCallable, Category="Inventory")
    virtual bool AddItem(FUInventoryItem Item, int32 Count);
    
    UFUNCTION(BlueprintCallable, Category="Inventory")
    virtual bool RemoveItemAtIndex(int32 Index, int32 Count);
    
    UFUNCTION(BlueprintCallable, Category="Inventory")
    virtual bool RemoveItems(TArray<FUInventoryItem> Items);
    
    UFUNCTION(BlueprintCallable, Category="Inventory")
    virtual void Clear();
    
    UFUNCTION(BlueprintCallable, Category="Inventory")
    virtual int32 GetLength();
    
    UFUNCTION(BlueprintCallable, Category="Inventory")
    virtual int32 GetMaxSize();
    
    UFUNCTION(BlueprintCallable, Category="Inventory")
    virtual UInventorySlot* GetSlot(int32 Index);
    
    UFUNCTION(BlueprintCallable, Category="Inventory")
    virtual TArray<UInventorySlot*> GetSlots();
    
protected:
	virtual void BeginPlay() override;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame, meta=(DisplayName="InventorySlots"))
    TArray<UInventorySlot*> InventorySlots;

private:
    
    void AddItemToNewSlot(FUInventoryItem Item, int32 Count);
};
