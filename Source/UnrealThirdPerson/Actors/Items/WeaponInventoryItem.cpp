// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponInventoryItem.h"

#include "Engine/World.h"

//Method to equip this weapon
void AWeaponInventoryItem::Equip()
{
	if (WeaponItem == nullptr)
	{
		WeaponItem = GetWorld()->SpawnActor<AWeaponItem>(ItemBlueprint);

		WeaponItem->Equip();
	}
}

//Method to unequip this weapon
void AWeaponInventoryItem::Unequip()
{
	if (WeaponItem != nullptr)
	{
		WeaponItem->Destroy();
		WeaponItem = nullptr;
	}
}
//Get a reference to the equipped weapon
AWeaponItem * AWeaponInventoryItem::GetWeapon()
{
	return WeaponItem;
}
