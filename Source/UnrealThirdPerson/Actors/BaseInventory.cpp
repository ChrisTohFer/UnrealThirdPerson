// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseInventory.h"

//Initialisation
ABaseInventory* ABaseInventory::SingletonPtr = nullptr;
// Sets default values
ABaseInventory::ABaseInventory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
//Set static pointer to inventory
void ABaseInventory::BeginPlay()
{
	Super::BeginPlay();

	SingletonPtr = this;
}

//Static functions

//Returns pointer to the inventory
ABaseInventory * ABaseInventory::GetInventory()
{
	return SingletonPtr;
}

//Functions

//Return true if all inventory slots are occupied (not necessarily to capacity)
bool ABaseInventory::IsFull()
{
	return Items.Num() >= MaxItems && MaxItems != 0;
}
//For a given item, returns how many more can be held
int ABaseInventory::GetRemainingCapacity(ABaseInventoryItem * NewItem)
{
	ABaseInventoryItem* ItemInInventory = GetItem(NewItem->GetName());

	if (ItemInInventory != nullptr)
	{
		return ItemInInventory->GetQuantityMax() - ItemInInventory->GetQuantity();
	}
	else if(IsFull())
	{
		return 0;
	}
	else
	{
		return NewItem->GetQuantityMax();
	}
}
/*
	*Pick up an item, either adding quantity to existing stack or creating a new one
	*Will either destroy NewItem or add to array
*/
int ABaseInventory::PickUpItem(ABaseInventoryItem* NewItem)
{
	int RemainingCapacity = GetRemainingCapacity(NewItem);

	if (RemainingCapacity > 0)
	{
		int AddedQuantity = FMath::Min(RemainingCapacity, NewItem->GetQuantity());
		ABaseInventoryItem* ItemInInventory = GetItem(NewItem->GetName());

		if (ItemInInventory != nullptr)
		{
			ItemInInventory->ChangeQuantity(AddedQuantity);
			NewItem->Destroy();
		}
		else
		{
			Items.Add(NewItem);
			NewItem->SetQuantity(AddedQuantity);
		}

		InventoryUpdated.Broadcast();

		return AddedQuantity;
	}
	else
	{
		NewItem->Destroy();
		return 0;
	}
}
/*
//Add an item to the inventory; returns false if item was not added
bool ABaseInventory::AddItem(ABaseInventoryItem* NewItem)
{
	if (!IsFull())
	{
		Items.Add(NewItem);
		InventoryUpdated.Broadcast();
		return true;
	}
	else return false;
}*/
//Attempts to drop item back into world
bool ABaseInventory::DropItem(int Index, FVector Position, FRotator Rotator)
{
	ABaseInventoryItem* InventoryItem = GetItem(Index);

	if (InventoryItem != nullptr)
	{
		if (InventoryItem->DropItem(Position, Rotator))
		{
			Items.RemoveAt(Index);
			InventoryItem->Destroy();
			InventoryUpdated.Broadcast();
			return true;
		}
		else return false;
		
	}
	else return false;
}
//Return the item stored at index, or nullptr if out of range
ABaseInventoryItem * ABaseInventory::GetItem(int Index)
{
	if (Index < Items.Num())
	{
		return Items[Index];
	}
	else
	{
		return nullptr;
	}
}
//Return pointer to inventory item, or nullptr if not present
ABaseInventoryItem* ABaseInventory::GetItem(FString Name)
{
	for (int i = 0; i < Items.Num(); ++i)
	{
		if (Items[i] != nullptr && Items[i]->GetName() == Name)
		{
			return Items[i];
		}
	}

	return nullptr;
}