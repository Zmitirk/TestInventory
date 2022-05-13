// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::UpdateHealthBarWidget(ATestProjectCharacter* Character, float CurrentHealth, float MaxHealth)
{
	/** Set variables with new data */
	OwningCharacter = Character;
	CurrentHealthAmount = CurrentHealth;
	MaxHealthAmount = MaxHealth;

	/** Set health bar percent to reflect health change*/
	HealthBar->SetPercent(CurrentHealthAmount / MaxHealthAmount);

	/** For BP */
	OnUpdateHealthBarWidget();
}
