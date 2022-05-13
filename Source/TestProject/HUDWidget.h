// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected: 

	/** Reference in c++ to BP variable in the widget. Shows actual health bar widget */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UHealthBarWidget* HealthBarWidget;
	
public:

	/** Returns health bar widget from the player's hud */
	FORCEINLINE class UHealthBarWidget* GetHealthBarWidget() {	return HealthBarWidget;	}
};
