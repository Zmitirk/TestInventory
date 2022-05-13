// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AMainPlayerController();

	/** Function for update UI widget for character's health */
	UFUNCTION()
	void UpdateHealthBarWidget(class ATestProjectCharacter* Char, float CurrentHealth, float MaxHealth);

protected:

	virtual void BeginPlay() override;

	/** Reference to the player's HUD */
	UPROPERTY(BlueprintReadWrite)
	class UHUDWidget* HUDWidget;

public:

	/** Return player's HUD */
	FORCEINLINE class UHUDWidget* GetHUDWidget() { return HUDWidget; }
};
