// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "PickupWidget.h"
#include "Components/SphereComponent.h"
#include "TestProjectCharacter.h"

UInteractionComponent::UInteractionComponent()
{
	/**No need for ticking */
	SetComponentTickEnabled(false);

	/** UI settings*/
	Space = EWidgetSpace::Screen;
	DrawSize = FIntPoint(600, 100);
	bDrawAtDesiredSize = true;

	SetActive(true);
	SetHiddenInGame(true);
}

void UInteractionComponent::RefreshWidget(FText InteractableName, int32 InteractableQuantity)
{
	/** Get widget from BP */
	if (UPickupWidget* PickupWidget = Cast<UPickupWidget>(GetUserWidgetObject()))
	{
		/** To be sure that widget fully initialized */
		InitWidget();
		
		/** Update widget with new data */
		PickupWidget->UpdateInteractionWidget(this, InteractableName, InteractableQuantity);
	}
}

void UInteractionComponent::Interact(ATestProjectCharacter* Character)
{
	/** Send that character has interacted with interactable */
	OnInteract.Broadcast(Character);
}
