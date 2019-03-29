// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseInventoryItem.h"
#include "Engine/World.h"

// Sets default values
ABaseInventoryItem::ABaseInventoryItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


//Attempt to drop item into world; return true if successful
bool ABaseInventoryItem::DropItem(FVector Location, FRotator Rotation)
{
	if (ItemBlueprint != nullptr)
	{
		GetWorld()->SpawnActor<ABaseItem>(ItemBlueprint, Location, Rotation);
		return true;
	}
	else return false;
}


//Get methods

//Return the name of this item
FString ABaseInventoryItem::GetName()
{
	return Name;
}
//Return the description of this item
FString ABaseInventoryItem::GetDescription()
{
	return Description;
}
//Return the icon of this item
const UTexture2D * ABaseInventoryItem::GetIcon()
{
	return Icon;
}
//Return the maximum quantity
int ABaseInventoryItem::GetQuantityMax()
{
	return QuantityMax;
}
//Return the current quantity
int ABaseInventoryItem::GetQuantity()
{
	return Quantity;
}
