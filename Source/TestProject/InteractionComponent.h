// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, class ATestProjectCharacter*, Character);

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTPROJECT_API UInteractionComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	/** It's a constructor */
	UInteractionComponent();

	/** Updates the pickup widget */
	UFUNCTION(BlueprintCallable)
	void RefreshWidget(FText InteractableName, int32 InteractableQuantity);

	/** Called when the player has interacted with the interactable  */
	UPROPERTY(BlueprintAssignable)
	FOnInteract OnInteract;

	/** Actual interaction */
	void Interact(class ATestProjectCharacter* Character);

};
