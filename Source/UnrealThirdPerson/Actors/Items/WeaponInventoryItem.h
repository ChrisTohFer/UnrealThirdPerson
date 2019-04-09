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

	//Method to equip this weapon
	UFUNCTION()
	void Equip();

	//Method to unequip this weapon
	UFUNCTION()
	void Unequip();

	//Get a reference to the equipped weapon
	UFUNCTION()
	AWeaponItem* GetWeapon();

protected:
	
	//Reference to weapon in game
	UPROPERTY()
	AWeaponItem* WeaponItem = nullptr;

};
