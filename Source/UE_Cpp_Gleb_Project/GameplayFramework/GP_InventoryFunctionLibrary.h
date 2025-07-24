// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GP_InventoryFunctionLibrary.generated.h"

enum class ESlot : uint8;
enum class EInventoryType : uint8;
class UGPInventoryComponent;
/**
 * 
 */
UCLASS()
class UE_CPP_GLEB_PROJECT_API UGP_InventoryFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static bool MoveItem(UGPInventoryComponent* MoveFrom, UGPInventoryComponent* MoveTo, UObject* Item);

	UFUNCTION(BlueprintCallable)
	static bool CanEquipTypeToSlot(ESlot Slot, EInventoryType ItemType);
};
