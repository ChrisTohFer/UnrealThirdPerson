// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Items/BaseItem.h"
#include "Components/StaticMeshComponent.h"

#include "WeaponItem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFired);

UCLASS()
class UNREALTHIRDPERSON_API AWeaponItem : public ABaseItem
{
	GENERATED_BODY()
	
public:

	AWeaponItem();

	virtual void BeginPlay() override;

	//Attempt to add the item to the inventory; returns false if inventory full
	//Override sets the loaded ammo variable of the inventory item
	virtual ABaseInventoryItem* PickUpItem() override;

	//Set weapon parent to player, disable collider
	UFUNCTION(BlueprintCallable)
	virtual void Equip();

	//Attempt to fire the weapon; returns false if unable to fire for any reason
	UFUNCTION(BlueprintCallable)
	virtual bool Fire();

	//Reload the weapon, returns true if successful
	UFUNCTION(BlueprintCallable)
	bool Reload();

	//Set the amount of ammo loaded
	UFUNCTION(BlueprintCallable)
	void SetAmmoLoaded(int Value);

	//Returns the amount of ammo loaded in weapon
	UFUNCTION(BlueprintCallable)
	int GetAmmoLoaded();

	//Returns the amount of ammo available in inventory
	UFUNCTION(BlueprintCallable)
	int GetAmmoInventory();

	//Return damage value
	UFUNCTION(BlueprintCallable)
	float GetDamage();
	
	//Return true if automatic
	UFUNCTION(BlueprintCallable)
	bool IsAutomatic();

	//Event called when weapon is fired
	UPROPERTY(BlueprintAssignable)
	FWeaponFired WeaponFired;

protected:

	//The name of the ammo this weapon uses; leave blank for ammoless weapons
	UPROPERTY(EditAnywhere)
	FString AmmoType;

	//Reference to the ammo in inventory
	UPROPERTY()
	ABaseInventoryItem* AmmoPtr = nullptr;

	//Define the location of the gun muzzle
	UPROPERTY(EditAnywhere)
	FVector MuzzleRelativeLocation = FVector::ZeroVector;

	//Damage dealt per shot
	UPROPERTY(EditAnywhere)
	float DamagePerShot = 1.f;

	//Cooldown between shots
	UPROPERTY(EditAnywhere)
	float Cooldown = 0.4f;

	//Currently loaded ammo
	UPROPERTY(EditAnywhere)
	int LoadedAmmo = 0;

	//Ammo capacity
	UPROPERTY(EditAnywhere)
	int AmmoCapacity = 0;

	//Continous fire when button held down?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Automatic = false;

	//Save the time when firing, to check when next shot is possible
	float LastTimeFired;

	//Static mesh component
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	//Get pointer to appropriate ammotype if in inventory
	ABaseInventoryItem* GetAmmoPtr();

};
