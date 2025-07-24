// Fill out your copyright notice in the Description page of Project Settings.


#include "GPInventoryItemWidget.h"

#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Obj_GP_InventoryItem.h"


FGuid UGPInventoryItemWidget::GetItemID()
{
	if (BPO_Item)
	{
		return BPO_Item->ItemData.ItemId;
	}
	return FGuid();
}

FText UGPInventoryItemWidget::GetItemName()
{
	if (BPO_Item)
	{
		return FText::FromString(BPO_Item->ItemData.ItemName);
	}
	return FText::FromString("");
}

FText UGPInventoryItemWidget::GetItemLevel()
{
	if (BPO_Item)
	{
		return FText::AsNumber(BPO_Item->ItemData.ItemLevel);
	}
	return FText::AsNumber(0);
}

FSlateBrush UGPInventoryItemWidget::GetItemIcon()
{
	FSlateBrush Brush;
	if (BPO_Item)
	{
		if (ItemIcon)
		{
			Brush = ItemIcon->GetBrush();
			if (BPO_Item->ItemData.ItemIcon)
			{
				Brush.SetResourceObject(BPO_Item->ItemData.ItemIcon);
			}
		}
	}
	return Brush;
}

void UGPInventoryItemWidget::SelectedChanged(UObject* SelectedObject)
{
	SetItemBgUnselected();
}

void UGPInventoryItemWidget::SetItemBgSelected()
{
	if (ItemBG)
	{
		ItemBG->SetBrushColor(FLinearColor::Green);
	}
}

void UGPInventoryItemWidget::SetItemBgUnselected()
{
	if (ItemBG)
	{
		ItemBG->SetBrushColor(FLinearColor::White);
	}
}

void UGPInventoryItemWidget::SetItemVisual(UObj_GP_InventoryItem* DragItem)
{
	BPO_Item = Cast<UObj_GP_InventoryItem>(DragItem);
	if (BPO_Item)
	{
		SetItemBgUnselected();
		ItemId = BPO_Item->ItemData.ItemId;
		ItemIcon->SetBrushFromTexture(BPO_Item->ItemData.ItemIcon);
		ItemLevel->SetText(FText::AsNumber(BPO_Item->ItemData.ItemLevel));
		ItemName->SetText(FText::FromString(BPO_Item->ItemData.ItemName));
	}
}


void UGPInventoryItemWidget::SetListItemObjectData(UObject* ListItemObject)
{
	BPO_Item = Cast<UObj_GP_InventoryItem>(ListItemObject);
	ItemId = BPO_Item->ItemData.ItemId;
	ItemIcon->SetBrushFromTexture(BPO_Item->ItemData.ItemIcon);
	ItemLevel->SetText(FText::AsNumber(BPO_Item->ItemData.ItemLevel));
	ItemName->SetText(FText::FromString(BPO_Item->ItemData.ItemName));
}

void UGPInventoryItemWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
	BPO_Item->ItemSelected();
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Red,  FString::Printf(TEXT("bIsSelected: %s"), bIsSelected? TEXT("true") : TEXT("false")));
	bIsSelected ? SetItemBgSelected() : SetItemBgUnselected();

}

void UGPInventoryItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                                  UDragDropOperation*& OutOperation)
{
	UDragDropOperation* DragOperation = NewObject<UDragDropOperation>();
	DragOperation->Payload = this;
	SetVisibility(ESlateVisibility::Hidden);
	UGPInventoryItemWidget* DragVisual = CreateWidget<UGPInventoryItemWidget>(GetWorld(), GetClass());
	DragVisual->BPO_Item = BPO_Item;
	DragOperation->DefaultDragVisual = DragVisual;
	OutOperation = DragOperation;
	BPO_Item->ItemDragStarted();
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Red, "DragStarted");
}

void UGPInventoryItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (ItemIcon)
	{
		ItemIcon->BrushDelegate.BindDynamic(this, &UGPInventoryItemWidget::GetItemIcon);
		ItemIcon->SynchronizeProperties();
	}
	if (ItemLevel)
	{
		ItemLevel->TextDelegate.BindDynamic(this, &UGPInventoryItemWidget::GetItemLevel);
		ItemLevel->SynchronizeProperties();
	}
	if (ItemName)
	{
		ItemName->TextDelegate.BindDynamic(this, &UGPInventoryItemWidget::GetItemName);
		ItemName->SynchronizeProperties();
	}
	SetItemBgUnselected();
}

void UGPInventoryItemWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	BPO_Item->ItemDragCanceled();
	SetVisibility(ESlateVisibility::Visible);
}

