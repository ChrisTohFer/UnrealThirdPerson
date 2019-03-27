// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UserWidget.h"

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

	void ToggleInventoryVisibility();

protected:

	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> InventoryWidgetBlueprint;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* InventoryWidget;

	

};
