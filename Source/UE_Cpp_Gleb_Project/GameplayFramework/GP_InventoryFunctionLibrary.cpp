// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_InventoryFunctionLibrary.h"

#include "UE_Cpp_Gleb_Project/Config/InventoryItem/GPInventoryComponent.h"

 



bool UGP_InventoryFunctionLibrary::MoveItem(UGPInventoryComponent* MoveFrom, UGPInventoryComponent* MoveTo,
	UObject* Item)
{
	if(UObj_GP_InventoryItem* InItem = Cast<UObj_GP_InventoryItem>(Item))
	{
		if(MoveFrom->HasItem(InItem) && !MoveTo->HasItem(InItem))
		{
			MoveFrom->RemoveItem(InItem);
			MoveTo->AddItem(InItem);
			return true;
		}
	}
	return false;
}

bool UGP_InventoryFunctionLibrary::CanEquipTypeToSlot(ESlot Slot, EInventoryType ItemType)
{
	switch(Slot)
	{
	case ESlot::Head:
		return ItemType == EInventoryType::Head;
	case ESlot::LeftHand:
		return  ItemType == EInventoryType::Hand;
	case ESlot::RightHand:
		return ItemType == EInventoryType::Hand;
	case ESlot::Leg:
		return ItemType == EInventoryType::Leg;
	case ESlot::Torso:
		return ItemType == EInventoryType::Torso;
	}
	return false;
}
