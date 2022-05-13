// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestProjectCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChanged, class ATestProjectCharacter*, Character, float, CurrentHealth, float, MaxHealth);

UCLASS(config=Game)
class ATestProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/**
	*
	* Additional functionality
	*
	*/

	/** Inventory component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* PlayerInventory;

public:
	ATestProjectCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	/**
	*
	* Additional functionality
	*
	*/

	/** Hold character's current health amount */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurrentHealth;

	/** Hold character's max health amount */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxHealth;

	/** Variable for active overlapping interactable component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	class UInteractionComponent* ActiveInteractable;

	/**Pickup use blueprint base class, need a reference to it when spawning */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class APickup> PickupClass;

	/**Action key input */
	void ActionDown();
	void ActionUp();

	/**Called when character use item */
	UFUNCTION(BlueprintCallable)
	void UseItem(class UItem* Item);
	
	/**Called when player want to drop item */
	UFUNCTION(BlueprintCallable)
	void DropItem(class UItem* Item, int32 Quantity);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/**
	*
	* Additional functionality
	*
	*/

	/** Returns PlayerInventory subobject **/
	FORCEINLINE class UInventoryComponent* GetPlayerInventory() const { return PlayerInventory; }

	/**Returns Active Overlapping interactable component */
	FORCEINLINE class UInteractionComponent* GetActiveInteractable() const { return ActiveInteractable; }

	/** Set new Active Overlapping interactable component for the character */
	FORCEINLINE void SetActiveInteractable(class UInteractionComponent* NewActiveInteractable) { ActiveInteractable = NewActiveInteractable; }

	/** Return current health of the character */
	FORCEINLINE float GetCurrentHealth() { return CurrentHealth; }

	/** Call this when character's health (current or max) is changed. For example for update UI*/
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	/** Set new current health for character and clamp health amount between 0 - MaxHealth */
	UFUNCTION(BlueprintCallable)
	void SetCurrentHealth(float NewHealthAmount);

	/** Returns max health of the character */
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }

	/** Set new max health for the character */
	FORCEINLINE void SetMaxHealth(float NewMaxAmount) { MaxHealth = NewMaxAmount; }
};

