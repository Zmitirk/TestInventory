// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupWidget.h"
#include "Components/TextBlock.h"

void UPickupWidget::UpdateInteractionWidget(UInteractionComponent* InteractionComponent, FText Name, int32 Quantity)
{
	/** Set variables with data */
	OwningInteractionComponent = InteractionComponent;

	PickupName->SetText(Name);
	PickupQuantity->SetText(FText::FromString(FString::FromInt(Quantity)));

	/** For BP*/
	OnUpdateInteractionWidget();
}
