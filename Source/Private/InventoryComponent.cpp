// Copyright Eric Downey - 2025

#include "InventoryComponent.h"
#include "Engine/Engine.h"

#pragma mark - Actor Component

UInventoryComponent::UInventoryComponent() {
    InventorySlots.Reserve(GetMaxSize());
}

void UInventoryComponent::BeginPlay() {
	Super::BeginPlay();
}

#pragma mark - IInventory

bool UInventoryComponent::AddItem(FUInventoryItem Item, int32 Count) {
    UInventorySlot *slot = nil;
    for (UInventorySlot *iSlot : InventorySlots) {
        if (iSlot->Item.ID == Item.ID) {
            bool canAddAmount = iSlot->Item.IsStackable && (iSlot->Count + Count) <= iSlot->Item.StackSize;
            if (canAddAmount) {
                slot = iSlot;
                break;
            }
        }
    }
    
    // Inventory Slot exists and has space, increase count
    if (IsValid(slot)) {
        slot->Count += Count;
        OnInventoryChangeEvent.Broadcast();
        return true;
    }
    
    // Add new slot if under max size
    if (GetLength() < GetMaxSize()) {
        AddItemToNewSlot(Item, Count);
        OnInventoryChangeEvent.Broadcast();
        return true;
    }
    
    return false;
}

bool UInventoryComponent::RemoveItemAtIndex(int32 Index, int32 Count) {
    if (!InventorySlots.IsValidIndex(Index)) {
        return false;
    }
    
    UInventorySlot *slot = InventorySlots[Index];
    slot->Count -= Count;
    if (slot->Count <= 0) {
        InventorySlots.RemoveAt(Index);
    }
    
    OnInventoryChangeEvent.Broadcast();
    return true;
}

bool UInventoryComponent::RemoveItems(TArray<FUInventoryItem> Items) {
    for (const FUInventoryItem item : Items) {
        for (int32 index=0; index<InventorySlots.Num();) {
            UInventorySlot *iSlot = InventorySlots[index];
            if (iSlot->Item.ID == item.ID) {
                iSlot->Count -= 1;
                
                if (iSlot->Count <= 0) {
                    InventorySlots.RemoveAt(index);
                    continue; // Don't increment index, continue looping
                }
            }
            
            ++index;
        }
    }
    
    OnInventoryChangeEvent.Broadcast();
    return true;
}

int32 UInventoryComponent::GetLength() {
    return InventorySlots.Num();
}

int32 UInventoryComponent::GetMaxSize() {
    return this->MaxSlotSize;
}

void UInventoryComponent::Clear() {
    InventorySlots.Empty();
    OnInventoryChangeEvent.Broadcast();
}

UInventorySlot* UInventoryComponent::GetSlot(int32 Index) {
    if (InventorySlots.IsValidIndex(Index)) {
        return InventorySlots[Index];
    }
    return nil;
}

TArray<UInventorySlot*> UInventoryComponent::GetSlots() {
    return InventorySlots;
}

#pragma mark - Private Functions

void UInventoryComponent::AddItemToNewSlot(FUInventoryItem Item, int32 Count) {
    UInventorySlot *slot = NewObject<UInventorySlot>();
    slot->Item = Item;
    slot->Count = Count;
    InventorySlots.Emplace(slot);
}
