// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Use this to update UI when showing/hiding widget */
	UFUNCTION(BlueprintCallable)
	void UpdateHealthBarWidget(class ATestProjectCharacter* Character, float CurrentHealth, float MaxHealth);

	/** BP version for update UI */
	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateHealthBarWidget();
	
protected:

	/** Reference for the character which health will be shown*/
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	class ATestProjectCharacter* OwningCharacter;

	/** Holds current health amount */
	UPROPERTY(BlueprintReadWrite)
	float CurrentHealthAmount;

	/** Holds max health amount */
	UPROPERTY(BlueprintReadWrite)
	float MaxHealthAmount;

	/** Reference to progress bar in c++ from BP widget. Shows actual progress bar in widget */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HealthBar;
};
