// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class UNREALTHIRDPERSON_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	//Get the name of this item
	FString GetName();

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

};
