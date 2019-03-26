// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory.generated.h"

UCLASS()
class UNREALTHIRDPERSON_API AInventory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	//Array of all items currently in inventory
	TArray<class AItemBase*> Items;
	//Array of weapons currently in inventory
	TArray<class AItemBase*> Weapons;
	//Array of ammunition currently in inventory
	TArray<class AItemBase*> Ammunition;

public:
	//Check if the player is holding the item with specified name
	bool PlayerHasItem(FString Name);
	//


};
