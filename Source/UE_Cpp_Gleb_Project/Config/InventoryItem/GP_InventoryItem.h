// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GP_InventoryItemDataAsset.h"
#include "UObject/Object.h"
#include "GP_InventoryItem.generated.h"

USTRUCT(BlueprintType)
struct FItemData: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGuid ItemId = FGuid::NewGuid();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* ItemIcon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ItemLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EInventoryType ItemType = EInventoryType::None;
	
};

/**
 * 
 */
UCLASS()
class UE_CPP_GLEB_PROJECT_API UGP_InventoryItem : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UGP_InventoryItemDataAsset* ItemDataAsset;

	UPROPERTY()
	FItemData ItemData;
};
