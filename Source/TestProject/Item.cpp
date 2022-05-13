// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "TestProjectCharacter.h"
#include "InventoryComponent.h"

/**Return just world object for the item */
class UWorld* UItem::GetWorld() const
{
	return World;
}

UItem::UItem()
{
	/**By default */
	ItemDisplayName = FText::FromString("Item");
	bStackble = true;
	Quantity = 1;
	MaxStackSize = 5;
}

void UItem::SetQuantity(const int32 NewQuantity)
{
	/**Change quantity only if it is different */
	if (NewQuantity != Quantity)
	{
		/**If the item is stackable max amount can't be more than max stack size */
		int32 MaxQuantity;
		if (bStackble)
		{
			MaxQuantity = MaxStackSize;
		}
		else // in other case amount is 1
		{
			MaxQuantity = 1;
		}

		Quantity = FMath::Clamp(NewQuantity, 0, MaxQuantity);

		/**Need to update UI */
		OnItemModified.Broadcast();
	}
}

void UItem::Use(ATestProjectCharacter* Character)
{
	/**If character is valid, than get inventory and call function to consume item */
	if (Character)
	{
		UInventoryComponent* Inventory = Character->GetPlayerInventory();
		if (Inventory)
		{
			int32 UsedAmount = Inventory->ConsumeItem(this, 1);
		}
	}

	/**Need to update UI */
	OnItemModified.Broadcast();
}

void UItem::AddedToInventory(UInventoryComponent* Inventory)
{
	/**Can do some actions when add item to the inventory */
}
