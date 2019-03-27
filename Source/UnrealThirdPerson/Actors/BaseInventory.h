// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/BaseInventoryItem.h"

#include "BaseInventory.generated.h"

UCLASS()
class UNREALTHIRDPERSON_API ABaseInventory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInventory();

	//Return pointer to inventory item, or nullptr if not present
	ABaseInventoryItem* GetItem(FString Name);
	
	//Return true if inventory is full
	bool IsFull();

	//Add an item to the inventory; returns false if item was not added
	virtual bool AddItem(ABaseInventoryItem* NewItem);

protected:
	//Array of all items currently in inventory
	TArray<ABaseInventoryItem*> Items;

	//Max number of items in inventory
	UPROPERTY(EditAnywhere)
	int MaxItems = 0;



};
