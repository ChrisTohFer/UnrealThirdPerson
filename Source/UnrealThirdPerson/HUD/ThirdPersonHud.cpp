// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonHud.h"

#include "Engine/Engine.h"


void AThirdPersonHud::BeginPlay()
{
	Super::BeginPlay();

	

}

void AThirdPersonHud::ToggleInventoryVisibility()
{
	if (InventoryWidget != nullptr)
	{
		if (InventoryWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
