// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/BaseInventoryItem.h"

#include "BaseInventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryUpdated);

UCLASS()
class UNREALTHIRDPERSON_API ABaseInventory : public AActor
{
	GENERATED_BODY()
	
public:	
	//Initialisation
	//Sets default values for this actor's properties
	ABaseInventory();
	//Set static pointer to inventory
	virtual void BeginPlay() override;

	//Static functions
	//Returns pointer to the inventory
	UFUNCTION(BlueprintCallable)
	static ABaseInventory* GetInventory();

	//Delegates
	//Delegate to allow blueprint to update inventory interface when inventory contents is changed
	UPROPERTY(BlueprintAssignable)
	FInventoryUpdated InventoryUpdated;

	//Functions
	
	
	//Return true if inventory is full
	bool IsFull();

	//Add an item to the inventory; returns false if item was not added
	UFUNCTION(BlueprintCallable)
	virtual bool AddItem(ABaseInventoryItem* NewItem);
	//Attempts to drop item back into world
	UFUNCTION(BlueprintCallable)
	virtual bool DropItem(int Index, FVector Position = FVector::ZeroVector, FRotator Rotator = FRotator::ZeroRotator);
	//Return the item stored at index, or nullptr if out of range
	UFUNCTION(BlueprintCallable)
	ABaseInventoryItem* GetItem(int Index);
	//Return pointer to inventory item, or nullptr if not present
	ABaseInventoryItem* GetItem(FString Name);
	

protected:
	//Array of all items currently in inventory
	TArray<ABaseInventoryItem*> Items;

	//Max number of items in inventory
	UPROPERTY(EditAnywhere)
	int MaxItems = 0;

	static ABaseInventory* SingletonPtr;

};
