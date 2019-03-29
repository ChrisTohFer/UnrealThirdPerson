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

//Attempt to add the item to the inventory; returns false if inventory full
bool ABaseItem::PickUpItem()
{
	ABaseInventory* Inventory = ABaseInventory::GetInventory();

	if (Inventory != nullptr)
	{
		if (!Inventory->IsFull())
		{
			ABaseInventoryItem* InventoryItem = GetWorld()->SpawnActor<ABaseInventoryItem>(InventoryItemBlueprint);
			Inventory->AddItem(InventoryItem);
			Destroy();

			return true;
		}
		else return false;
	}
	else return false;
}
