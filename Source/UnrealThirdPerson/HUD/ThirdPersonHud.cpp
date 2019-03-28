// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonHud.h"

#include "Engine/Engine.h"


void AThirdPersonHud::BeginPlay()
{
	Super::BeginPlay();

}

//Set visibility state of the inventory
void AThirdPersonHud::SetInventoryVisible(bool Visible)
{
	if (Visible)
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		IsInventoryVisible = true;
	}
	else
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		IsInventoryVisible = false;
	}
}

bool AThirdPersonHud::GetInventoryVisible()
{
	return IsInventoryVisible;
}
