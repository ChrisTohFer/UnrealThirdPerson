// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

//Get the name of this item
FString AItemBase::GetName()
{
	return Name;
}

