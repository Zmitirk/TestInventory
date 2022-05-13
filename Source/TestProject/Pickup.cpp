// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "InventoryComponent.h"
#include "TestProjectCharacter.h"
#include "Item.h"
#include "MainPlayerController.h"
#include "InteractionComponent.h"

// Sets default values
APickup::APickup()
{

	if (RootComponent == nullptr)
	{
		SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));
	}

	/**Default mesh for pickups */
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(GetRootComponent());

	/**Collision sphere for interaction */
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	TriggerSphere->SetupAttachment(GetRootComponent());

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	InteractionComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	/**Bind overlapping events to pickups functions */
	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlapBegin);
	TriggerSphere->OnComponentEndOverlap.AddDynamic(this, &APickup::OnOverlapEnd);

	/** Bind event for interaction */
	InteractionComponent->OnInteract.AddDynamic(this, &APickup::OnTakePickup);

	/**At the begging of the game need to initialize pickup with proper mesh */
	if (Item)
	{
		PickupMesh->SetStaticMesh(Item->GetPickupMesh());
		InteractionComponent->RefreshWidget(Item->GetItemName(), Item->GetQuantity());
	}

}

void APickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/**On begin overlap check if it is our character, than set character ActiveOverlappingPickup */
	if (OtherActor)
	{
		ATestProjectCharacter* Character = Cast<ATestProjectCharacter>(OtherActor);
		if (Character)
		{
			/** remove widget from old current overlapping pickup*/
			if (Character->GetActiveInteractable())
			{
				Character->GetActiveInteractable()->SetHiddenInGame(true);
			}

			Character->SetActiveInteractable(InteractionComponent);

			/**Update UI 
			In case of dropping item from inventory event can occur sooner than there will be item in pickup */
			if (Item)
			{
				InteractionComponent->RefreshWidget(Item->GetItemName(), Item->GetQuantity());
			}
			InteractionComponent->SetHiddenInGame(false);
		}
	}
}

void APickup::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	/**When overlap end set ActiveOverlappingPickup to null*/
	if (OtherActor)
	{
		ATestProjectCharacter* Character = Cast<ATestProjectCharacter>(OtherActor);
		if (Character)
		{
			/**Update UI */
			InteractionComponent->SetHiddenInGame(true);

			/**if current overlapping item not equal item that call overlap end, than there is no need to resetting overlapping item */
			if (Character->GetActiveInteractable() == InteractionComponent)
			{
				Character->SetActiveInteractable(nullptr);

				/**Character can overlap with other pickup if so need to set new overlapping item */
				TArray<AActor*> OverlappingActors; // need this for GetOverlappingActors
				Character->GetOverlappingActors(OverlappingActors, this->StaticClass());

				if (OverlappingActors.Num() != 0)
				{
					APickup* NewOverlap = Cast<APickup>(OverlappingActors[0]);
					if (NewOverlap)
					{
						Character->SetActiveInteractable(NewOverlap->InteractionComponent);

						/**Update UI */
						InteractionComponent->RefreshWidget(Item->GetItemName(), Item->GetQuantity());
						NewOverlap->InteractionComponent->SetHiddenInGame(false);
					}
				}
			}
		}
	}
}

void APickup::OnTakePickup(ATestProjectCharacter* Character)
{
	/**If character and item are valid, get inventory and try to add item to it */
	if (Character && Item)
	{
		UInventoryComponent* PlayerInvetntory = Character->GetPlayerInventory();
		if (PlayerInvetntory)
		{
			/**TryAddItem return added amount of the item  */
			int32 AddedAmount = PlayerInvetntory->TryAddItem(Item);

			/**Need update UI after adding item to the inventory */
			PlayerInvetntory->OnInventoryUpdated.Broadcast();

			/**If added amount is less then item quantity than need to change pickup amount */
			if (AddedAmount < Item->GetQuantity())
			{
				Item->SetQuantity(Item->GetQuantity() - AddedAmount);
				InteractionComponent->RefreshWidget(Item->GetItemName(), Item->GetQuantity());
			}
			else // give all amount, need to destroy pickup
			{
				Destroy();
			}
		}
	}
}

void APickup::InitializePickup(UItem* ItemTemplate, int32 Quantity)
{
	/**Check if item is valid and there is no sense to spawn item with 0 quantity */
	if (ItemTemplate && Quantity > 0)
	{
		Item = NewObject<UItem>(this, ItemTemplate->GetClass());
		Item->SetQuantity(Quantity);
		PickupMesh->SetStaticMesh(ItemTemplate->GetPickupMesh());
		InteractionComponent->RefreshWidget(Item->GetItemName(), Item->GetQuantity());
	}
}

#if WITH_EDITOR
void APickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	/** If a new pickup is selected in the property editor, change the mesh to reflect the new item being selected*/
	if (PropertyName == GET_MEMBER_NAME_CHECKED(APickup, Item))
	{
		if (Item)
		{
			PickupMesh->SetStaticMesh(Item->GetPickupMesh());
			InteractionComponent->RefreshWidget(Item->GetItemName(), Item->GetQuantity());
		}
	}
}
#endif
