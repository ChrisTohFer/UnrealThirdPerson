// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "Actors/WeaponInventory.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"

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
//
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Raycast screen centre and save hitresult for use in derived classes/blueprints
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController != nullptr)
	{
		FVector2D ViewPortCentre = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY()) / 2.f;
		PlayerController->GetHitResultAtScreenPosition(ViewPortCentre, ECC_WorldStatic, true, ScreenCentreHitResult);
	}

	//Handle automatic fire
	if (FireHeld)
	{
		AutomaticFire();
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, this, &APlayerCharacter::NextWeapon);
	PlayerInputComponent->BindAction("PreviousWeapon", IE_Pressed, this, &APlayerCharacter::PreviousWeapon);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Repeat, this, &APlayerCharacter::AutomaticFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::StopFire);
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
			FireHeld = true;
		}
	}
}

void APlayerCharacter::StopFire()
{
	FireHeld = false;
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

