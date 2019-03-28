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

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:

	//Toggle inventory visibility and player input
	void ToggleInventoryVisibility();

	APawn* PlayerPawn;

};
