// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseInventory.h"

ABaseInventory* ABaseInventory::SingletonPtr = nullptr;

// Sets default values
ABaseInventory::ABaseInventory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseInventory::BeginPlay()
{
	Super::BeginPlay();

	SingletonPtr = this;
}

//Returns pointer to the inventory
ABaseInventory * ABaseInventory::GetInventory()
{
	return SingletonPtr;
}

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
bool ABaseInventory::IsFull()
{
	return Items.Num() >= MaxItems && MaxItems != 0;
}
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
