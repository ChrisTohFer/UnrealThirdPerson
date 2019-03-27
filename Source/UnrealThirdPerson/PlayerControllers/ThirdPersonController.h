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

	virtual void SetupInputComponent() override;

protected:

	//Call the toggle inventory visibility method on AThirdPersonHud
	void ToggleInventoryVisibility();

	APawn* PlayerPawn;

};
