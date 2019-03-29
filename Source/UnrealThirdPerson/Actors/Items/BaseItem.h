// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInventoryItem.h"

#include "BaseItem.generated.h"

UCLASS()
class UNREALTHIRDPERSON_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();


	//Attempt to add the item to the inventory; returns false if inventory full
	UFUNCTION(BlueprintCallable)
	virtual bool PickUpItem();

protected:

	
	//
	UPROPERTY(EditAnywhere)
	class TSubclassOf<class ABaseInventoryItem> InventoryItemBlueprint;

};
