// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerInteraction);

UCLASS()
class UNREALTHIRDPERSON_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Swap to next weapon
	UFUNCTION()
	void NextWeapon();
	//Swap to previous weapon
	UFUNCTION()
	void PreviousWeapon();
	//Fire equipped weapon
	UFUNCTION()
	void Fire();
	//Fire equipped weapon if the weapon is automatic
	UFUNCTION()
	void AutomaticFire();
	//Interact with doors/items etc
	UFUNCTION()
	void Interact();

	UPROPERTY(BlueprintAssignable)
	FPlayerInteraction PlayerInteraction;

};
