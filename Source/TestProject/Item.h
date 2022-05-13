// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemModified);

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class TESTPROJECT_API UItem : public UObject
{
	GENERATED_BODY()
	
protected:

	/**Because it is a UObject it does not know about world. This function just return world. */
	virtual class UWorld* GetWorld() const override;

	/**The amount of the item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (UIMin = 1, EditCondition = bStackble))
	int32 Quantity;

	/**The maximum size of stack for the item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 2, EditCondition = bStackble))
	int32 MaxStackSize;

	/**The mesh to display for this item pickup */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	class UStaticMesh* PickupMesh;

	/**The thumbnail for the item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	class UTexture2D* Thumbnail;

	/**The display name for this item in the inventory */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	FText ItemDisplayName;

	/**The inventory that owns this item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	class UInventoryComponent* OwningInventory;


public:

	UItem();

	/**The variable to hold World */
	UPROPERTY(Transient)
	class UWorld* World;

	/**If item can be stacked */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	bool bStackble;


	/**Return static mesh component */
	FORCEINLINE class UStaticMesh* GetPickupMesh() const { return PickupMesh; }

	/**Return item display name */
	FORCEINLINE FText GetItemName() const { return ItemDisplayName; }

	/**Return max stack size */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetMaxStackSize() const { return MaxStackSize; }

	/**Return item amount */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetQuantity() const { return Quantity; }

	/**Set new item quantity */
	UFUNCTION(BlueprintCallable)
	void SetQuantity(const int32 NewQuantity);

	/**Return inventory component */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE class UInventoryComponent* GetOwningInventory() const { return OwningInventory; }

	/**Set new inventory for the item */
	FORCEINLINE void SetOwningInventory(class UInventoryComponent* InventoryToSet) { OwningInventory = InventoryToSet; }


	/**Delegate for updating inventory */
	UPROPERTY(BlueprintAssignable)
	FOnItemModified OnItemModified;

	/**Called when item used */
	UFUNCTION()
	virtual void Use(class ATestProjectCharacter* Character);

	/**Blueprint event for using item */
	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class ATestProjectCharacter* Character);

	/**Called on adding item to inventory */
	UFUNCTION()
	virtual void AddedToInventory(class UInventoryComponent* Inventory);
};
