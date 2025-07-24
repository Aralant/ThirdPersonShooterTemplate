// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UE_Cpp_Gleb_Project/GlobalResource/GlobalResource.h"
#include "GP_InventoryItemDataAsset.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UE_CPP_GLEB_PROJECT_API UGP_InventoryItemDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid ItemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInventoryType ItemType = EInventoryType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemIcon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemLevel;
	void GetItemConfig(FGuid Id);
};
