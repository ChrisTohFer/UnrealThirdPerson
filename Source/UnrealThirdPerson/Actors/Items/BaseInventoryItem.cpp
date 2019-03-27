// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseInventoryItem.h"

// Sets default values
ABaseInventoryItem::ABaseInventoryItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


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
const UTexture * ABaseInventoryItem::GetIcon()
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
