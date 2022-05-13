// Fill out your copyright notice in the Description page of Project Settings.


#include "HealItem.h"
#include "TestProjectCharacter.h"
#include "InventoryComponent.h"


UHealItem::UHealItem()
{
	/** How much health restore character after using this */
	HealAmount = 20.f;
}

void UHealItem::Use(ATestProjectCharacter* Character)
{
	/**Call parent version */
	Super::Use(Character);

	/** Updating character's health */
	Character->SetCurrentHealth(Character->GetCurrentHealth() + HealAmount);

}
