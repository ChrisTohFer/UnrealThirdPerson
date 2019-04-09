// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "Actors/WeaponInventory.h"
#include "GameFramework/PlayerController.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, this, &APlayerCharacter::NextWeapon);
	PlayerInputComponent->BindAction("PreviousWeapon", IE_Pressed, this, &APlayerCharacter::PreviousWeapon);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Repeat, this, &APlayerCharacter::AutomaticFire);
	PlayerInputComponent->BindAction("PickUpItem", IE_Pressed, this, &APlayerCharacter::Interact);
}

void APlayerCharacter::NextWeapon()
{
	AWeaponInventory* Weapons = Cast<AWeaponInventory>(ABaseInventory::GetInventory());

	if (Weapons != nullptr)
	{
		Weapons->EquipNextWeapon();
	}
}

void APlayerCharacter::PreviousWeapon()
{
	AWeaponInventory* Weapons = Cast<AWeaponInventory>(ABaseInventory::GetInventory());

	if (Weapons != nullptr)
	{
		Weapons->EquipNextWeapon();
	}
}

void APlayerCharacter::Fire()
{
	AWeaponInventory* Weapons = Cast<AWeaponInventory>(ABaseInventory::GetInventory());

	if (Weapons != nullptr)
	{
		AWeaponItem* Weapon = Weapons->GetCurrentWeapon();

		if (Weapon != nullptr)
		{
			Weapon->Fire();
		}
	}
}

void APlayerCharacter::AutomaticFire()
{
	AWeaponInventory* Weapons = Cast<AWeaponInventory>(ABaseInventory::GetInventory());

	if (Weapons != nullptr)
	{
		AWeaponItem* Weapon = Weapons->GetCurrentWeapon();

		if (Weapon != nullptr && Weapon->IsAutomatic())
		{
			Weapon->Fire();
		}
	}
}

void APlayerCharacter::Interact()
{
	PlayerInteraction.Broadcast();
}

