// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseInventory.h"
#include "Items/WeaponInventoryItem.h"
#include "Items/WeaponItem.h"

#include "WeaponInventory.generated.h"

/**
 * 
 */
UCLASS()
class UNREALTHIRDPERSON_API AWeaponInventory : public ABaseInventory
{
	GENERATED_BODY()
	
public:

	//Override BaseInventory methods to keep track of weapons when picked up or lost

	virtual int PickUpItem(ABaseInventoryItem* NewItem) override;
	//Attempts to drop item back into world
	virtual bool DropItem(int Index, FVector Position = FVector::ZeroVector, FRotator Rotator = FRotator::ZeroRotator);
	//Remove item from the inventory without dropping
	virtual void RemoveItem(int Index);

	//Set equipped weapon
	UFUNCTION(BlueprintCallable)
	void SetEquippedWeapon(int Index);

	//Equip next weapon
	UFUNCTION(BlueprintCallable)
	void EquipNextWeapon();

	//Equip previous weapon
	UFUNCTION(BlueprintCallable)
	void EquipPreviousWeapon();

	//Get currently equipped weapon
	UFUNCTION(BlueprintCallable)
	AWeaponItem* GetCurrentWeapon();

protected:

	//Array of weapon items
	UPROPERTY()
	TArray<AWeaponInventoryItem*> Weapons;

	//Pointer to currently equipped weapon (inventory form)
	UPROPERTY()
	AWeaponInventoryItem* CurrentWeapon = nullptr;

	//Index of current weapon
	int WeaponIndex = 0;

	//Refills weapons array, checks if equipped weapon is dropped
	UFUNCTION()
	void UpdateWeaponList();


};
