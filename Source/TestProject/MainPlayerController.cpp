// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "TestProjectCharacter.h"
#include "HUDWidget.h"
#include "HealthBarWidget.h"

AMainPlayerController::AMainPlayerController()
{

}



void AMainPlayerController::BeginPlay()
{
	/** Bind function for health's changes */
	ATestProjectCharacter* TestProjectCharacter = Cast<ATestProjectCharacter>(GetCharacter());
	if (TestProjectCharacter)
	{
		TestProjectCharacter->OnHealthChanged.AddDynamic(this, &AMainPlayerController::UpdateHealthBarWidget);
	}
}

void AMainPlayerController::UpdateHealthBarWidget(class ATestProjectCharacter* Char, float CurrentHealth, float MaxHealth)
{
	/** Get the health bar widget and update it with new data */
	UHealthBarWidget* HealthBarWidget = HUDWidget->GetHealthBarWidget();
	if (HealthBarWidget)
	{
		if (Char)
		{
			HealthBarWidget->UpdateHealthBarWidget(Char, CurrentHealth, MaxHealth);
		}
	}
}