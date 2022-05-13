// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "HealItem.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UHealItem : public UItem
{
	GENERATED_BODY()
	
public:

	UHealItem();

	/**The amount of restoring health for the item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	float HealAmount;

	/**Function override from parent class. Called when using this item */
	virtual void Use(class ATestProjectCharacter* Character) override;
};
