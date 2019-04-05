// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Items/BaseItem.h"
#include "Components/StaticMeshComponent.h"

#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class UNREALTHIRDPERSON_API AWeaponItem : public ABaseItem
{
	GENERATED_BODY()
	
public:

	AWeaponItem();

	virtual void BeginPlay() override;

	//Set weapon parent to player, disable collider
	UFUNCTION(BlueprintCallable)
	virtual void Equip();

	//Attempt to fire the weapon; returns false if unable to fire for any reason
	UFUNCTION(BlueprintCallable)
	virtual bool Fire();


protected:

	//The name of the ammo this weapon uses; leave blank for ammoless weapons
	UPROPERTY(EditAnywhere)
	FString AmmoType;

	//Reference to the ammo in inventory
	ABaseInventoryItem* AmmoPtr;

	//Define the location of the gun muzzle
	UPROPERTY(EditAnywhere)
	FVector MuzzleRelativeLocation = FVector::ZeroVector;

	//Damage dealt per shot
	UPROPERTY(EditAnywhere)
	float DamagePerShot = 1.f;

	//Cooldown between shots
	UPROPERTY(EditAnywhere)
	float Cooldown = 0.4f;

	//Continous fire when button held down?
	UPROPERTY(EditAnywhere)
	bool Automatic = false;

	//Save the time when firing, to check when next shot is possible
	float LastTimeFired;

	//Static mesh component
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	//Sets AmmoPtr to appropriate ammotype if in inventory
	void GetAmmoPtr();

};
