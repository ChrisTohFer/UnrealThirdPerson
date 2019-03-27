// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonController.h"
#include "HUD/ThirdPersonHud.h"

void AThirdPersonController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ShowInventory", IE_Pressed, this, &AThirdPersonController::ToggleInventoryVisibility);
	
}

//Call the toggle inventory visibility method on AThirdPersonHud
void AThirdPersonController::ToggleInventoryVisibility()
{
	AThirdPersonHud* Hud = Cast<AThirdPersonHud>(GetHUD());

	if (Hud != nullptr)
	{
		if (PlayerPawn == nullptr)
		{
			PlayerPawn = GetPawn();
			SetPawn(nullptr);
		}
		else
		{
			SetPawn(PlayerPawn);
			PlayerPawn = nullptr;
		}

		Hud->ToggleInventoryVisibility();
	}
}
