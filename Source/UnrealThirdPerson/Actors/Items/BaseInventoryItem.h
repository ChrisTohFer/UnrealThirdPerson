// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.h"

#include "BaseInventoryItem.generated.h"

UCLASS()
class UNREALTHIRDPERSON_API ABaseInventoryItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInventoryItem();

	//Attempt to drop item into world; return true if successful
	bool DropItem(FVector Location, FRotator Rotation, int Quantity);

	//Get methods
	//Return the name of this item
	FString GetName();
	//Return the description of this item
	FString GetDescription();
	//Return the icon of this item
	const UTexture2D* GetIcon();
	//Return the maximum quantity
	int GetQuantityMax();
	//Return the current quantity
	int GetQuantity();
	//Change the quantity and return the new quantity
	int ChangeQuantity(int Change);
	//Set the value of quantity
	void SetQuantity(int NewQuantity);

protected:
	//Name to identify the item type
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	//Provide further information when in inventory
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Description;

	//Image for item when in inventory
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon;

	//Maximum number of this item that can stack in an inventory slot
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int QuantityMax = 1;

	//Current number of this item
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Quantity = 1;

	//Pointer to non-inventory item blueprint
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABaseItem> ItemBlueprint;

};
