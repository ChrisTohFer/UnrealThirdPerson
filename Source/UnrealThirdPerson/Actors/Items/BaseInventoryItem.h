// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Texture.h"
#include "BaseItem.h"

#include "BaseInventoryItem.generated.h"

UCLASS()
class UNREALTHIRDPERSON_API ABaseInventoryItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInventoryItem();

	//Return the name of this item
	FString GetName();
	//Return the description of this item
	FString GetDescription();
	//Return the icon of this item
	const UTexture* GetIcon();
	//Return the maximum quantity
	int GetQuantityMax();
	//Return the current quantity
	int GetQuantity();

protected:
	//Name to identify the item type
	UPROPERTY(EditAnywhere)
	FString Name;

	//Provide further information when in inventory
	UPROPERTY(EditAnywhere)
	FString Description;

	//Image for item when in inventory
	UPROPERTY(EditAnywhere)
	UTexture* Icon;

	//Maximum number of this item that can stack in an inventory slot
	UPROPERTY(EditAnywhere)
	int QuantityMax = 1;

	//Current number of this item
	UPROPERTY(EditAnywhere)
	int Quantity = 1;

	//Pointer to non-inventory item blueprint
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseItem> ItemBlueprint;

};
