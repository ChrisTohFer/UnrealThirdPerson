// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseItem.h"
#include "Actors/BaseInventory.h"
#include "Engine/World.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
}

//Attempt to pick up the item
void ABaseItem::PickUpItem()
{
	ABaseInventory* Inventory = ABaseInventory::GetInventory();

	if (Inventory != nullptr)
	{
		if (InventoryItemBlueprint != nullptr)
		{
			ABaseInventoryItem* InventoryItem = GetWorld()->SpawnActor<ABaseInventoryItem>(InventoryItemBlueprint);
			InventoryItem->SetQuantity(Quantity);

			int PickedUp = Inventory->PickUpItem(InventoryItem);
			Quantity -= PickedUp;

			if (Quantity <= 0)
			{
				Destroy();
			}
		}
	}
}
//Set the quantity of the item
void ABaseItem::SetQuantity(int NewQuantity)
{
	Quantity = NewQuantity;
}
