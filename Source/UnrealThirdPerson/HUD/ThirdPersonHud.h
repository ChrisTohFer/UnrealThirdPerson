// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UserWidget.h"
#include "Actors/BaseInventory.h"

#include "ThirdPersonHud.generated.h"

/**
 * 
 */
UCLASS()
class UNREALTHIRDPERSON_API AThirdPersonHud : public AHUD
{
	GENERATED_BODY()
	

public:

	virtual void BeginPlay() override;

	//Set visibility state of the inventory
	void SetInventoryVisible(bool Visible);
	//Return true if inventory is visible
	bool GetInventoryVisible();

protected:

	//Blueprint of inventory widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> InventoryWidgetBlueprint;
	//Reference to widget in game
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* InventoryWidget;

	//Is the inventory visible?
	UPROPERTY(BlueprintReadOnly)
	bool IsInventoryVisible = false;

	//Reference to inventory
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ABaseInventory* Inventory;
};
