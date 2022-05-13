// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PickupWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UPickupWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** Use this to update UI when showing/hiding widget */
	UFUNCTION(BlueprintCallable)
	void UpdateInteractionWidget(class UInteractionComponent* InteractionComponent, FText Name, int32 Quantity);

	/** BP version for update UI */
	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateInteractionWidget();

protected:

	/** Reference for the interaction component that will be show this widget*/
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	class UInteractionComponent* OwningInteractionComponent;

	/** Reference in c++ to BP variable in the widget. Shows name of the pickup */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* PickupName;

	/** Reference in c++ to BP variable in the widget. Shows amount of the pickup */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* PickupQuantity;
};
