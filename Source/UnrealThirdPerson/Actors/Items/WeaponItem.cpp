// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponItem.h"

#include "Actors/BaseInventory.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "ActorComponents/WeaponTarget.h"
#include "WeaponInventoryItem.h"
#include "DrawDebugHelpers.h"

AWeaponItem::AWeaponItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

void AWeaponItem::BeginPlay()
{
	Super::BeginPlay();

	//Set last time fired so that gun can be fired immediately
	LastTimeFired = UGameplayStatics::GetTimeSeconds(GetWorld()) - Cooldown;
}

//Attempt to add the item to the inventory; returns false if inventory full
//Override sets the loaded ammo variable of the inventory item
ABaseInventoryItem * AWeaponItem::PickUpItem()
{
	ABaseInventoryItem *InventoryItem = ABaseItem::PickUpItem();

	AWeaponInventoryItem* WeaponItem = Cast<AWeaponInventoryItem>(InventoryItem);
	if (WeaponItem != nullptr)
	{
		WeaponItem->SetLoadedAmmo(LoadedAmmo);
	}

	return InventoryItem;
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
	//Check cooldown
	if (UGameplayStatics::GetTimeSeconds(GetWorld()) >= Cooldown + LastTimeFired)
	{
		//Check ammo

		if (AmmoCapacity == 0)
		{
			ABaseInventoryItem* AmmoPtr = GetAmmoPtr();
			if (AmmoPtr != nullptr)
			{
				AmmoPtr->ChangeQuantity(-1);

				FireFunction();

				return true;
			}
			else if (AmmoType == "")
			{
				FireFunction();

				return true;
			}
			else
			{
				
				return false;
			}
		}
		else if (LoadedAmmo > 0)
		{
			--LoadedAmmo;

			FireFunction();

			return true;
		}
		else
		{
			Reload();

			return false;
		}
	}
	else return false;

}
//Reload the weapon, returns true if successful
bool AWeaponItem::Reload()
{
	ABaseInventoryItem* AmmoPtr = GetAmmoPtr();

	if (AmmoPtr != nullptr)
	{
		//WILL MOVE THIS TO A DELAYED METHOD AFTER CONFIRMED TO WORK
		int AmmoToLoad = FMath::Min(AmmoPtr->GetQuantity(), AmmoCapacity - LoadedAmmo);

		LoadedAmmo += AmmoToLoad;
		AmmoPtr->ChangeQuantity(-AmmoToLoad);

		return true;
	}
	else return false;
}
//Set the amount of ammo loaded
void AWeaponItem::SetAmmoLoaded(int Value)
{
	LoadedAmmo = Value;
}
//Returns the amount of ammo loaded in weapon
int AWeaponItem::GetAmmoLoaded()
{
	return LoadedAmmo;
}
//Returns the amount of ammo available in inventory
int AWeaponItem::GetAmmoInventory()
{
	ABaseInventoryItem* AmmoPtr = GetAmmoPtr();

	if (AmmoPtr != nullptr)
	{
		return AmmoPtr->GetQuantity();
	}
	else return 0;
}
//Returns the ammo type as string
FString AWeaponItem::GetAmmoType()
{
	return AmmoType;
}
//Returns the ammo capacity
int AWeaponItem::GetAmmoCapacity()
{
	return AmmoCapacity;
}
//Return damage value
float AWeaponItem::GetDamage()
{
	return DamagePerShot;
}
//Return true if automatic
bool AWeaponItem::IsAutomatic()
{
	return Automatic;
}
//Set pointer to inventory weapon parent
void AWeaponItem::SetInventoryWeaponPtr(AWeaponInventoryItem* Value)
{
	InventoryWeaponPtr = Value;
}
//Get pointer to inventory weapon parent
AWeaponInventoryItem * AWeaponItem::GetInventoryWeaponPtr()
{
	return InventoryWeaponPtr;
}
//Get pointer to appropriate ammotype if in inventory
ABaseInventoryItem* AWeaponItem::GetAmmoPtr()
{
	ABaseInventory* Inventory = ABaseInventory::GetInventory();

	if (Inventory != nullptr)
	{
		return Inventory->GetItemByName(AmmoType);
	}
	else
	{
		return nullptr;
	}
}
//Handle raycast and events during firing
void AWeaponItem::FireFunction()
{
	LastTimeFired = UGameplayStatics::GetTimeSeconds(GetWorld());

	//Raycast
	FHitResult HitResult;
	FRotator ActorRotation = GetActorRotation();
	FVector StartTrace = GetActorLocation() + ActorRotation.RotateVector(MuzzleRelativeLocation);
	FVector EndTrace = StartTrace + 10000.f * ActorRotation.Vector();

	//Debug line
	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, true, 1.f);

	//Check if hit anything
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Pawn))
	{
		if (HitResult.Actor != nullptr)
		{
			UWeaponTarget* TargetComponent = HitResult.Actor->FindComponentByClass<UWeaponTarget>();
			if (TargetComponent != nullptr)
			{
				TargetComponent->HitByWeapon(this);
			}
		}
	}

	WeaponFired.Broadcast();
}
