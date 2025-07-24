// Fill out your copyright notice in the Description page of Project Settings.


#include "GPInventorySlot.h"

#include "GP_InventoryWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Component/GP_InventorySlotsComponent.h"
#include "UE_Cpp_Gleb_Project/GameplayFramework/GP_InventoryFunctionLibrary.h"

FEventReply UGPInventorySlot::SlotSelected(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	OnSlotSelected.Broadcast(this);
	FillSlotBorder->SetBrushColor(FLinearColor::Yellow);
	ItemWidget->SetItemBgSelected();
	NoItemWidget->SetBrushColor(FLinearColor::Blue);
	FEventReply Reply;
	return Reply;
}

void UGPInventorySlot::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (SlotNameText)
	{
		SlotNameText->SetText(SlotName);
	}
}

void UGPInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
	if (ItemWidget)
	{
		ItemWidget->VisibilityDelegate.BindDynamic(this, &UGPInventorySlot::GetItemWidgetVisibility);
		FillSlotBorder->OnMouseButtonUpEvent.BindDynamic(this, &UGPInventorySlot::SlotSelected);
		ItemWidget->SynchronizeProperties();
	}
	if (NoItemWidget)
	{
		NoItemWidget->VisibilityDelegate.BindDynamic(this, &UGPInventorySlot::GetNoInfoWidgetVisibility);
		NoItemWidget->OnMouseButtonUpEvent.BindDynamic(this,&UGPInventorySlot::SlotSelected);
		NoItemWidget->SynchronizeProperties();
	}
}

ESlateVisibility UGPInventorySlot::GetItemWidgetVisibility()
{
	return ItemWidget->BPO_Item == nullptr ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
}

ESlateVisibility UGPInventorySlot::GetNoInfoWidgetVisibility()
{
	return ItemWidget->BPO_Item == nullptr ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
}

void UGPInventorySlot::SetSlotUnselected()
{
	ItemWidget->SetItemBgUnselected();
	NoItemWidget->SetBrushColor(FLinearColor(0.05625f, 0.05625f, 0.05625f, 1.0f));
}

void UGPInventorySlot::SetSlotCanEquipColor()
{
	if (!ItemWidget->BPO_Item)
	{
		FillSlotBorder->SetBrushColor(FLinearColor(0.041649f, 0.05625f, 0.0f, 1.0f));
	}
	NoItemWidget->SetBrushColor(FLinearColor(0.041649f, 0.05625f, 0.0f, 1.0f));
}


void UGPInventorySlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}

bool UGPInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	UGPInventoryItemWidget* DragItem = Cast<UGPInventoryItemWidget>(InOperation->Payload);
	if (!DragItem || !SlotsComponent->EquipItem(DragItem->BPO_Item, SlotType))
	{
		NativeOnDragCancelled(InDragDropEvent, InOperation);
		DragItem->BPO_Item->ItemDragCanceled();
		return false;
	}
	DragItem->BPO_Item->ItemDragCompleted();
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UGPInventorySlot::OnSlotChange(bool bIsEquiped, ESlot InSlotType, UObj_GP_InventoryItem* Item)
{
	if (InSlotType != SlotType)
	{
		return;
	}
	if (!bIsEquiped)
	{
		ItemWidget->BPO_Item = nullptr;
	}
	else
	{
		if (Item)
		{
			ItemWidget->BPO_Item = Item;
		}
	}
}

void UGPInventorySlot::InitSlotComponent_Implementation(UGP_InventorySlotsComponent* InitSlotComponent)
{
	SlotsComponent = InitSlotComponent;
	SlotsComponent->OnItemEquipped.AddDynamic(this, &UGPInventorySlot::OnSlotChange);
	
}

