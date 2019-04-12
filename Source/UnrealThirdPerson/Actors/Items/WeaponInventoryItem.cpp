// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponInventoryItem.h"

#include "Engine/World.h"
#include "Actors/BaseInventory.h"


//Attempt to drop item into world; return true if successful
//Override to update loaded ammo quantity
ABaseItem* AWeaponInventoryItem::DropItem(FVector Location, FRotator Rotation, int Quantity)
{
	ABaseItem* Item = ABaseInventoryItem::DropItem(Location, Rotation, Quantity);
	AWeaponItem* Weapon = Cast<AWeaponItem>(Item);

	if (Weapon != nullptr)
	{
		if (WeaponItem != nullptr)
		{
			Weapon->SetAmmoLoaded(WeaponItem->GetAmmoLoaded());
		}
		else
		{
			Weapon->SetAmmoLoaded(LoadedAmmo);
		}
	}

	return Item;
}

//Method to equip this weapon
void AWeaponInventoryItem::Equip()
{
	if (WeaponItem == nullptr)
	{
		WeaponItem = GetWorld()->SpawnActor<AWeaponItem>(ItemBlueprint);
		WeaponItem->SetAmmoLoaded(LoadedAmmo);
		WeaponItem->SetInventoryWeaponPtr(this);
		WeaponItem->Equip();
	}
}

//Method to unequip this weapon
void AWeaponInventoryItem::Unequip()
{
	if (WeaponItem != nullptr)
	{
		LoadedAmmo = WeaponItem->GetAmmoLoaded();
		WeaponItem->Destroy();
		WeaponItem = nullptr;
	}
}
//Get a reference to the equipped weapon
AWeaponItem * AWeaponInventoryItem::GetWeapon()
{
	return WeaponItem;
}
//Get amount of ammo loaded in weapon
int AWeaponInventoryItem::GetLoadedAmmo()
{
	return LoadedAmmo;
}
//Set amount of ammo loaded in weapon
void AWeaponInventoryItem::SetLoadedAmmo(int Value)
{
	LoadedAmmo = Value;
	if (WeaponItem != nullptr)
	{
		WeaponItem->SetAmmoLoaded(Value);
		ABaseInventory* InventoryPtr = ABaseInventory::GetInventory();
		if (InventoryPtr != nullptr)
		{
			InventoryPtr->CallInventoryUpdated();
		}
	}
}
