// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAddedToInventory, UItem*, Item, int32,  Quantity);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	//friend class UItem;

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	/**Get all items form the inventory */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FORCEINLINE TArray<class UItem*> GetItems() const { return Items; }

	/**Called when add item in the inventory
	* return amount of the added item */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 TryAddItem(class UItem* Item);

	/**Called when item remove from inventory */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(class UItem* Item);

	/**Called when item used from inventory */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 ConsumeItem(class UItem* Item, int32 Quantity);

	/**Return the first item with the same class as ItemClass.*/
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UItem* FindItem(class UItem* Item) const;

	/**Get all inventory items that are a child of ItemClass */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<UItem*> FindItems(UItem* Item) const;

	/**Change capacity of the inventory */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetCapacity(const int32 NewCapacity);

	/**Delegate for updating inventory */
	UPROPERTY(BlueprintAssignable)
	FOnInventoryUpdated OnInventoryUpdated;

	/**Delegate for show widget when pickup item */
	UPROPERTY(BlueprintAssignable)
	FOnAddedToInventory FOnAddedToInventory;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:

	/**The max amount of items than inventory can hold */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (ClampMin = 0))
	int32 Capacity;

	/**The list of items in the inventory */
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<class UItem*> Items;

private:
	/**Add item to inventory */
	UFUNCTION()
	void AddItem(class UItem* Item, int32 Quantity);
};
