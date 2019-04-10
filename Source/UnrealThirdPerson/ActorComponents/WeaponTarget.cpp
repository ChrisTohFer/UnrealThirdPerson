// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponTarget.h"

// Sets default values for this component's properties
UWeaponTarget::UWeaponTarget()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

//Method called when actor is hit by a gun
void UWeaponTarget::HitByWeapon(AWeaponItem * Weapon)
{
	if (Weapon != nullptr)
	{
		WeaponHit.Broadcast(Weapon);
	}
}