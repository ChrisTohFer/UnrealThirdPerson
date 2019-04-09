// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonHud.h"

#include "Actors/BaseInventory.h"


void AThirdPersonHud::BeginPlay()
{
	Super::BeginPlay();

}

//Set visibility state of the inventory
void AThirdPersonHud::SetInventoryVisible(bool Visible)
{
	if (InventoryWidget != nullptr)
	{
		if (Visible)
		{
			ABaseInventory* InventoryPtr = ABaseInventory::GetInventory();
			if (InventoryPtr != nullptr) InventoryPtr->CallInventoryUpdated();

			InventoryWidget->SetVisibility(ESlateVisibility::Visible);
			IsInventoryVisible = true;
		}
		else
		{
			InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
			IsInventoryVisible = false;
		}
	}
}
//Return true if inventory is visible
bool AThirdPersonHud::GetInventoryVisible()
{
	return IsInventoryVisible;
}
