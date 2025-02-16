// Copyright Eric Downey - 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Sound/SoundCue.h"

#include "InventoryItem.generated.h"

/**
 * Structure for in-game items that can be collected by the Player and stored in an `UInventoryComponent`.
 */
USTRUCT(BlueprintType)
struct <PROJECT_API> FUInventoryItem : public FTableRowBase
{
    GENERATED_BODY()

public:
    /** Inventory Item Identifier */
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(DisplayName="ID", MakeStructureDefaultValue="0"))
    int32 ID;

    /** Inventory Item Display Name */
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, SaveGame, meta=(DisplayName="Name"))
    FString Name;

    /** Inventory Item Display Description */
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, SaveGame, meta=(MultiLine="true", DisplayName="Description"))
    FString Description;

    /** Inventory Item Type used to sort or identify collections of like-types */
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, SaveGame, meta=(DisplayName="Type"))
    FString Type;

    /** Texture used in the Inventory Menu */
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, SaveGame, meta=(DisplayName="IconTexture", MakeStructureDefaultValue="None"))
    TObjectPtr<UTexture2D> IconTexture;

    /** Sound Cue to use when this item is collected within the game world. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="CollectSoundEffect", MakeStructureDefaultValue="None"))
    TObjectPtr<USoundCue> CollectSoundEffect;

    /** Whether the item is stackable or not in Inventory Slots. */
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, SaveGame, meta=(DisplayName="IsStackable", MakeStructureDefaultValue="False"))
    bool IsStackable;
    
    /** The amount of items allowed to be stacked in Inventory Slots, if IsStackable is `true`. */
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, SaveGame, meta=(DisplayName="StackSize", MakeStructureDefaultValue="0"))
    int32 StackSize;
};
