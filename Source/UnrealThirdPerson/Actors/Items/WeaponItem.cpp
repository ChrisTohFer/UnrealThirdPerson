// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponItem.h"

#include "Actors/BaseInventory.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

AWeaponItem::AWeaponItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

void AWeaponItem::BeginPlay()
{
	Super::BeginPlay();

	LastTimeFired = UGameplayStatics::GetTimeSeconds(GetWorld()) - Cooldown;

	AmmoDestroyedFunction.BindUFunction(this, "AmmoDestroyed");
}

//Set weapon parent to player, disable collider
void AWeaponItem::Equip()
{
	//Disable collision
	Mesh->SetSimulatePhysics(false);
	Mesh->SetCollisionProfileName("NoCollision");
	
	//Attach to the player
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
	Mesh->AttachToComponent(Player->GetMesh(), AttachRules, FName("Gun"));
}

//Attempt to fire the weapon; returns false if unable to fire for any reason
bool AWeaponItem::Fire()
{
	//Check ammo
	if (AmmoPtr == nullptr && AmmoType != "")
	{
		GetAmmoPtr();
		if (AmmoPtr == nullptr)
		{
			return false;
		}
	}

	//Check cooldown
	float CurrentTime = UGameplayStatics::GetTimeSeconds(GetWorld());
	if (CurrentTime >= Cooldown + LastTimeFired)
	{
		LastTimeFired = CurrentTime;
		if (AmmoPtr != nullptr)
		{
			AmmoPtr->ChangeQuantity(-1);
		}

		//Raycast
		FHitResult HitResult;
		FVector StartTrace = GetActorLocation() + MuzzleRelativeLocation;
		FVector EndTrace = StartTrace + 10000.f * GetActorRotation().Vector();
		GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Pawn);

		//Do stuff with result

		WeaponFired.Broadcast();

		return true;
	}
	else return false;

}
//Returns the amount of ammo available
int AWeaponItem::GetAmmoAmount()
{
	//Check ammo reference and attempt to find if missing
	if (AmmoPtr == nullptr && AmmoType != "")
	{
		GetAmmoPtr();
		if (AmmoPtr == nullptr)
		{
			return 0;
		}
	}

	return AmmoPtr->GetQuantity();
}
bool AWeaponItem::IsAutomatic()
{
	return Automatic;
}
//Sets AmmoPtr to appropriate ammotype if in inventory
void AWeaponItem::GetAmmoPtr()
{
	ABaseInventory* Inventory = ABaseInventory::GetInventory();

	if (Inventory != nullptr)
	{
		AmmoPtr = Inventory->GetItemByName(AmmoType);
	}
	else
	{
		AmmoPtr = nullptr;
	}

	if (AmmoPtr != nullptr)
	{
		AmmoPtr->OnDestroyed.Add(AmmoDestroyedFunction);
	}
}
//Null the ammo pointer when ammo item is destroyed
void AWeaponItem::AmmoDestroyed()
{
	AmmoPtr->OnDestroyed.Remove(AmmoDestroyedFunction);
	AmmoPtr = nullptr;
}
