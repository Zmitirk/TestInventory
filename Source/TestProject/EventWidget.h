// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EventWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UEventWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	/** Shows item name */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Item;

	/** Shows item amount */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Quantity;
};
