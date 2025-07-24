// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UE_Cpp_Gleb_Project/GlobalResource/GlobalResource.h"
#include "UObject/Object.h"
#include "GP_SlotInventoryInterface.generated.h"

class UObj_GP_InventoryItem;
class UGP_InventorySlotsComponent;

UINTERFACE()
class UE_CPP_GLEB_PROJECT_API UGP_SlotInventoryInterface : public UInterface
{
	GENERATED_BODY()
};


/**
 * 
 */
class UE_CPP_GLEB_PROJECT_API IGP_SlotInventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//virtual void Interact(AActor* Interactor) = 0;
	UFUNCTION(BlueprintNativeEvent)
	void InitSlotComponent(UGP_InventorySlotsComponent* InitSlotComponent);

	UFUNCTION(BlueprintNativeEvent)
	void AddItem(UObj_GP_InventoryItem* Item, ESlot Slot);

	UFUNCTION(BlueprintNativeEvent)
	void ClearSlot(ESlot Slot);
};