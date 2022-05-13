// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


int32 UInventoryComponent::TryAddItem(UItem* Item)
{
	/**How much item want to add */
	const int32 AddAmount = Item->GetQuantity();

	/** check stackable */
	if (Item->bStackble)
	{
		/**usually we don't have item amount more than a stack */
		ensure(Item->GetQuantity() <= Item->GetMaxStackSize());

		/**Find all items of item's class */
		TArray<UItem*> InventoryItems = FindItems(Item);

		/**If array not empty need to find item with not full stack and add quantity to it */
		if (InventoryItems.Num() > 0)
		{
			int32 AddedAmount = 0;
			for (auto ExistingItem : InventoryItems)
			{
				/**If we still have something to add */
				if (AddedAmount < AddAmount)
				{
					/**check if item has space in the stack */
					if (ExistingItem->GetQuantity() < ExistingItem->GetMaxStackSize())
					{
						/**How much item can add */
						const int32 CapacityMaxAddAmount = ExistingItem->GetMaxStackSize() - ExistingItem->GetQuantity();
						int32 ActualAddAmount = FMath::Min(AddAmount, CapacityMaxAddAmount);
						ExistingItem->SetQuantity(ExistingItem->GetQuantity() + ActualAddAmount);

						/** in case we add too much */
						ensure(ExistingItem->GetQuantity() <= ExistingItem->GetMaxStackSize());

						AddedAmount += ActualAddAmount;
					}
					else // stack is full can't add amount and try to find another item in the inventory
					{
						AddedAmount += 0;
					}
				}
			} // end loop where trying to add quantity for every existing item in the inventory

			/**If we still has something to add after we has checked inventory and there is space in the inventory */
			if ((AddedAmount != AddAmount) && ((Items.Num()) < Capacity) )
			{
				AddItem(Item, (AddAmount - AddedAmount));
				AddedAmount += AddAmount - AddedAmount;
			}
			
			/** Update UI */
			FOnAddedToInventory.Broadcast(Item, AddedAmount);
			return AddedAmount;
			
		}
		else if ((Items.Num()) < Capacity) //if array empty there are no such items in the inventory, and we can just add new item if there are slots in the inventory
		{
			AddItem(Item, AddAmount);
			return AddAmount;
		}
		else //can't add item
		{
			/** Update UI */
			FOnAddedToInventory.Broadcast(Item, 0);
			return 0;
		}

	}
	else if ((Items.Num()) < Capacity) //non stackable, check only available slots
	{
		/**non stackable item usually have only one quantity */
		ensure(Item->GetQuantity() == 1);
		AddItem(Item, AddAmount);

		return AddAmount;
	}
	else //can't add item
	{
		/** Update UI */
		FOnAddedToInventory.Broadcast(Item, 0);
		return 0;
	}
	
}

void UInventoryComponent::AddItem(UItem* Item, int32 Quantity)
{
	/**Creating new item and fill parameters */
	UItem* NewItem = NewObject<UItem>(GetOwner(), Item->GetClass());
	NewItem->World = GetWorld();
	NewItem->SetQuantity(Quantity);
	NewItem->SetOwningInventory(this);
	NewItem->AddedToInventory(this);
	Items.Add(NewItem);

	/** Update UI */
	OnInventoryUpdated.Broadcast();
	FOnAddedToInventory.Broadcast(Item, Quantity);
}

void UInventoryComponent::RemoveItem(UItem* Item)
{
	/**Check if item is valid */
	if (Item)
	{
		Items.RemoveSingle(Item);
	}

	/**Need to update UI */
	OnInventoryUpdated.Broadcast();
}

int32 UInventoryComponent::ConsumeItem(UItem* Item, int32 Quantity)
{
	/**Check if item is valid */
	if (Item)
	{
		/**If want to consume more than have, than consume only what we have */
		const int32 RemoveQuantity = FMath::Min(Quantity, Item->GetQuantity());

		/**We shouldn't have a negative amount of the item after the drop */
		ensure(!(Item->GetQuantity() - RemoveQuantity < 0));
		
		/**Change the amount of the item */
		Item->SetQuantity(Item->GetQuantity() - RemoveQuantity);

		/**If get 0 after consuming remove the item from inventory */
		if (Item->GetQuantity() <= 0)
		{
			RemoveItem(Item);
		}

		return RemoveQuantity;
	}
	return 0;
}

UItem* UInventoryComponent::FindItem(UItem* Item) const
{
	/**search in all items and return the first found item if class of items is equal */
	for (auto& InvItem : Items)
	{
		if (InvItem && InvItem->GetClass() == Item->GetClass())
		{
			return InvItem;
		}
	}
	return nullptr;
}

TArray<UItem*> UInventoryComponent::FindItems(UItem* Item) const
{
	/**Array to hold found items */
	TArray<UItem*> FoundItems;

	/**Add item to the array if class of given item and found item is equal */
	for (auto& InvItem : Items)
	{
		if (InvItem && InvItem->GetClass() == Item->GetClass())
		{
			FoundItems.Add(InvItem);
		}
	}

	return FoundItems;
}

void UInventoryComponent::SetCapacity(const int32 NewCapacity)
{
	Capacity = NewCapacity;
	OnInventoryUpdated.Broadcast();
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}




