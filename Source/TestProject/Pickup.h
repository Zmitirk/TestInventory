// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class TESTPROJECT_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	/**The item that will be added to the inventory on pickup  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	class UItem* Item;

	/**Default pickup mesh */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* PickupMesh;
	
	/**Check this for overlapping events */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USphereComponent* TriggerSphere;

	/**Interaction component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInteractionComponent* InteractionComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**When change property in editor update mesh */
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif 


public:	
	/**Takes the item to create the pickup from it on dropping from inventory */
	void InitializePickup(class UItem* ItemTemplate, int32 Quantity);

	/** need to be compatible with OnComponentBeginOverlap */
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** same for the overlapend. Has different signature */
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/**call this when player pickup item */
	UFUNCTION()
	void OnTakePickup(class ATestProjectCharacter* Character);

};
