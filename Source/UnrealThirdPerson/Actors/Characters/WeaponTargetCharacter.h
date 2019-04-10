// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Actors/Items/WeaponItem.h"

#include "WeaponTargetCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponHit, AWeaponItem*, Weapon);

UCLASS()
class UNREALTHIRDPERSON_API AWeaponTargetCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWeaponTargetCharacter();

	//Method called when this character is hit by a gun
	UFUNCTION()
	void HitByWeapon(AWeaponItem* Weapon);

	//Event called on weapon hit
	UPROPERTY(BlueprintAssignable)
	FWeaponHit WeaponHit;

};