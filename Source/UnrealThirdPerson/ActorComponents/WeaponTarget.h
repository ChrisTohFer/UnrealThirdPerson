// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actors/Items/WeaponItem.h"

#include "WeaponTarget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponHit, AWeaponItem*, Weapon);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALTHIRDPERSON_API UWeaponTarget : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponTarget();

	//Method called when actor is hit by a gun
	UFUNCTION()
	void HitByWeapon(AWeaponItem* Weapon);

	//Event called on weapon hit
	UPROPERTY(BlueprintAssignable)
	FWeaponHit WeaponHit;

		
};
