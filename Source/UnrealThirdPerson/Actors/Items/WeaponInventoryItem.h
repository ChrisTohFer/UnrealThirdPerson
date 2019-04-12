// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Items/BaseInventoryItem.h"
#include "WeaponItem.h"

#include "WeaponInventoryItem.generated.h"

/**
 * 
 */
UCLASS()
class UNREALTHIRDPERSON_API AWeaponInventoryItem : public ABaseInventoryItem
{
	GENERATED_BODY()
	
public:

	//Attempt to drop item into world; return true if successful
	//Override to update loaded ammo quantity
	ABaseItem* DropItem(FVector Location, FRotator Rotation, int Quantity) override;

	//Method to equip this weapon
	UFUNCTION()
	void Equip();

	//Method to unequip this weapon
	UFUNCTION()
	void Unequip();

	//Get a reference to the equipped weapon
	UFUNCTION()
	AWeaponItem* GetWeapon();

	//Get amount of ammo loaded in weapon
	UFUNCTION(BlueprintCallable)
	int GetLoadedAmmo();

	//Set amount of ammo loaded in weapon
	UFUNCTION(BlueprintCallable)
	void SetLoadedAmmo(int Value);

protected:
	
	//Reference to weapon in game
	UPROPERTY()
	AWeaponItem* WeaponItem = nullptr;

	//Ammo loaded in weapon
	UPROPERTY()
	int LoadedAmmo = 0;

};
