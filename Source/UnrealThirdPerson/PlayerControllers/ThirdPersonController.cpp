// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonController.h"
#include "HUD/ThirdPersonHud.h"

void AThirdPersonController::BeginPlay()
{
	Super::BeginPlay();

}

void AThirdPersonController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ShowInventory", IE_Pressed, this, &AThirdPersonController::ToggleInventoryVisibility);
	
}

//Toggle inventory visibility and player input
void AThirdPersonController::ToggleInventoryVisibility()
{
	AThirdPersonHud* Hud = Cast<AThirdPersonHud>(GetHUD());
	if (PlayerPawn == nullptr)
	{
		PlayerPawn = GetPawn();
	}

	if (Hud != nullptr)
	{

		if (Hud->GetInventoryVisible())
		{
			SetPawn(PlayerPawn);
			bShowMouseCursor = false;
			Hud->SetInventoryVisible(false);
		}
		else
		{
			SetPawn(nullptr);
			bShowMouseCursor = true;
			Hud->SetInventoryVisible(true);
		}

	}
}
