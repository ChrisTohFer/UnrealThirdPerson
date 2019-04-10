// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponTargetCharacter.h"

// Sets default values
AWeaponTargetCharacter::AWeaponTargetCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

//Method called when this character is hit by a gun
void AWeaponTargetCharacter::HitByWeapon(AWeaponItem * Weapon)
{
	if (Weapon != nullptr)
	{
		WeaponHit.Broadcast(Weapon);
	}
}
