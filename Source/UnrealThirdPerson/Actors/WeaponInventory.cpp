// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponInventory.h"

//Override BaseInventory methods to keep track of weapons when picked up or lost
int AWeaponInventory::PickUpItem(ABaseInventoryItem* NewItem)
{
	int NumberPickedUp = ABaseInventory::PickUpItem(NewItem);

	UpdateWeaponList();

	return NumberPickedUp;
}
bool AWeaponInventory::DropItem(int Index, FVector Position, FRotator Rotator)
{
	bool Dropped = ABaseInventory::DropItem(Index, Position, Rotator);

	UpdateWeaponList();

	return Dropped;
}
void AWeaponInventory::RemoveItem(int Index)
{
	ABaseInventory::RemoveItem(Index);

	UpdateWeaponList();
}
//Set equipped weapon
void AWeaponInventory::SetEquippedWeapon(int Index)
{
	if (Weapons.Num() > 0)
	{
		WeaponIndex = Index % Weapons.Num();

		if (Weapons[WeaponIndex] != CurrentWeapon)
		{
			if (CurrentWeapon != nullptr)
			{
				CurrentWeapon->Unequip();
			}

			CurrentWeapon = Weapons[WeaponIndex];
			CurrentWeapon->Equip();
		}
	}
	else
	{
		WeaponIndex = 0;
		if (CurrentWeapon != nullptr)
		{
			CurrentWeapon->Unequip();
			CurrentWeapon = nullptr;
		}
	}

	WeaponSwapped.Broadcast(GetCurrentWeapon());
}
//Equip next weapon
void AWeaponInventory::EquipNextWeapon()
{
	SetEquippedWeapon(WeaponIndex + 1);
}
//Equip previous weapon
void AWeaponInventory::EquipPreviousWeapon()
{
	SetEquippedWeapon(WeaponIndex - 1);
}
//Get currently equipped weapon
AWeaponItem * AWeaponInventory::GetCurrentWeapon()
{
	if (CurrentWeapon != nullptr)
	{
		return CurrentWeapon->GetWeapon();
	}
	else return nullptr;
}

//Refills weapons array, checks if equipped weapon is dropped
void AWeaponInventory::UpdateWeaponList()
{
	Weapons.Empty();

	//Refill weapons array
	bool WeaponDropped = true;
	for (int i = 0; i < Items.Num(); ++i)
	{
		AWeaponInventoryItem* WeaponItem = Cast<AWeaponInventoryItem>(Items[i]);

		if (WeaponItem != nullptr)
		{
			Weapons.Add(WeaponItem);
			if (WeaponItem == CurrentWeapon)
			{
				WeaponDropped = false;
				WeaponIndex = i;
			}
		}
	}

	if (WeaponDropped)
	{
		SetEquippedWeapon(WeaponIndex);
	}
}
