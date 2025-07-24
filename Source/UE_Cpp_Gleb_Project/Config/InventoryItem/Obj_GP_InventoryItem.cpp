// Fill out your copyright notice in the Description page of Project Settings.


#include "Obj_GP_InventoryItem.h"

void UObj_GP_InventoryItem::ItemDragStarted()
{
	OnItemDragStarted.Broadcast(this);
}

void UObj_GP_InventoryItem::ItemDragCanceled()
{
	OnItemDragCanceled.Broadcast(this);
}

void UObj_GP_InventoryItem::ItemSelected()
{
	OnItemSelected.Broadcast(this);
}

void UObj_GP_InventoryItem::ItemDragCompleted()
{
	OnItemDragCompleted.Broadcast(this);
}
