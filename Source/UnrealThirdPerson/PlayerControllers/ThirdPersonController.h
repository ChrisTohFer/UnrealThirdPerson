// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThirdPersonController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALTHIRDPERSON_API AThirdPersonController : public APlayerController
{
	GENERATED_BODY()
	
public:

	//Initialitation

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	//Functions
	
	//Returns the player pawn
	UFUNCTION(BlueprintCallable)
	APawn* GetPlayerPawn();

protected:

	//Toggle inventory visibility and player input
	void ToggleInventoryVisibility();

	APawn* PlayerPawn;

};
