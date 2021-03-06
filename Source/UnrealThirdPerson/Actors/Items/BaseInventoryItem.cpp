// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseInventoryItem.h"
#include "Engine/World.h"
#include "Actors/BaseInventory.h"

// Sets default values
ABaseInventoryItem::ABaseInventoryItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


//Attempt to drop item into world; return true if successful
ABaseItem* ABaseInventoryItem::DropItem(FVector Location, FRotator Rotation, int Quantity)
{
	if (ItemBlueprint != nullptr)
	{
		ABaseItem* Item = GetWorld()->SpawnActor<ABaseItem>(ItemBlueprint, Location, Rotation);
		Item->SetQuantity(Quantity);
		return Item;
	}
	else return nullptr;
}


//Get methods

//Return the name of this item
FString ABaseInventoryItem::GetName()
{
	return Name;
}
//Return the description of this item
FString ABaseInventoryItem::GetDescription()
{
	return Description;
}
//Return the icon of this item
const UTexture2D * ABaseInventoryItem::GetIcon()
{
	return Icon;
}
//Return the maximum quantity
int ABaseInventoryItem::GetQuantityMax()
{
	return QuantityMax;
}
//Return the current quantity
int ABaseInventoryItem::GetQuantity()
{
	return Quantity;
}
//Change the quantity and return the new quantity
int ABaseInventoryItem::ChangeQuantity(int Change)
{
	Quantity += Change;

	ABaseInventory* InventoryPtr = ABaseInventory::GetInventory();
	if (InventoryPtr != nullptr)
	{
		InventoryPtr->CallInventoryUpdated();
	}

	RemoveIfEmpty();

	return Quantity;
}
//Set the value of quantity
void ABaseInventoryItem::SetQuantity(int NewQuantity)
{
	Quantity = NewQuantity;

	RemoveIfEmpty();
}
//Remove item from inventory if quantity is <= 0
void ABaseInventoryItem::RemoveIfEmpty()
{
	if (Quantity <= 0)
	{
		ABaseInventory* Inventory = ABaseInventory::GetInventory();

		if (Inventory != nullptr)
		{
			Inventory->RemoveItem(Inventory->GetItemIndex(this));
		}
		Destroy();
	}
}
