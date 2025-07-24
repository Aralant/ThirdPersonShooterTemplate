// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_SlotInventoryWidget.h"

#include "GPInventorySlot.h"
#include "Components/GridPanel.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/GPInventoryComponent.h"
#include "UE_Cpp_Gleb_Project/GameplayFramework/GP_InventoryFunctionLibrary.h"
#include "UE_Cpp_Gleb_Project/GlobalResource/GlobalResource.h"

void UGP_SlotInventoryWidget::OnSlotSelected(UGPInventorySlot* SelectedSlot)
{
	if (SelectedSlot)
	{
		if (LastSelectedSlot != SelectedSlot && LastSelectedSlot != nullptr)
		{
			LastSelectedSlot->NoItemWidget->SetBrushColor(FLinearColor(0.05625f, 0.05625f, 0.05625f, 1.0f));
			LastSelectedSlot->ItemWidget->SetItemBgUnselected();
			LastSelectedSlot = SelectedSlot;
		}
		else
		{
			LastSelectedSlot = SelectedSlot;
		}
	}
}

void UGP_SlotInventoryWidget::ItemDragCanceled(UObj_GP_InventoryItem* Item)
{
	if (SlotsWidget.Num() > 0)
	{
		for (auto& SlotWidget : SlotsWidget)
		{
			if (UGP_InventoryFunctionLibrary::CanEquipTypeToSlot(SlotWidget->SlotType, Item->ItemData.ItemType))
			{
				SlotWidget->SetSlotUnselected();
			}
		}
	}
}

void UGP_SlotInventoryWidget::ItemDragCompleted(UObj_GP_InventoryItem* Item)
{
	if (SlotsWidget.Num() > 0)
	{
		for (auto& SlotWidget : SlotsWidget)
		{
			if (UGP_InventoryFunctionLibrary::CanEquipTypeToSlot(SlotWidget->SlotType, Item->ItemData.ItemType))
			{
				SlotWidget->SetSlotUnselected();
			}
		}
	}
}

void UGP_SlotInventoryWidget::ItemSelected(UObj_GP_InventoryItem* Item)
{
	if (SlotsWidget.Num() > 0)
	{
		for (auto& SlotWidget : SlotsWidget)
		{
			SlotWidget->SetSlotUnselected();
		}
	}
}

void UGP_SlotInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (InvComponent)
	{
		InvComponent->OnItemDragStarted.AddDynamic(this, &UGP_SlotInventoryWidget::ItemDragDetected);
		InvComponent->OnItemDragCanceled.AddDynamic(this, &UGP_SlotInventoryWidget::ItemDragCanceled);
		InvComponent->OnItemDragCompleted.AddDynamic(this, &UGP_SlotInventoryWidget::ItemDragCompleted);
		InvComponent->OnItemSelected.AddDynamic(this, &UGP_SlotInventoryWidget::ItemSelected);
	}
}

void UGP_SlotInventoryWidget::ItemDragDetected(UObj_GP_InventoryItem* Item)
{
	if (SlotsWidget.Num() > 0)
	{
		for (auto& SlotWidget : SlotsWidget)
		{
			if (UGP_InventoryFunctionLibrary::CanEquipTypeToSlot(SlotWidget->SlotType, Item->ItemData.ItemType))
			{
				SlotWidget->SetSlotCanEquipColor();
			}
		}
	}
}

void UGP_SlotInventoryWidget::InitSlotComponent_Implementation(UGP_InventorySlotsComponent* InitSlotComponent)
{
	SlotsComponent = InitSlotComponent;
	SlotsWidget.Empty();
	auto InitSlot = [&](UGPInventorySlot* InventorySlot)
	{
		if (InventorySlot->Implements<UGP_SlotInventoryInterface>())
		{
			IGP_SlotInventoryInterface::Execute_InitSlotComponent(InventorySlot, SlotsComponent);
		}
		if (!InventorySlot->OnSlotSelected.IsBound())
		{
			InventorySlot->OnSlotSelected.AddDynamic(this, &UGP_SlotInventoryWidget::OnSlotSelected);
		}
	};
	TArray<UWidget*> Widgets = SlotContainer->GetAllChildren();
	for (UWidget* Widget : Widgets)
	{
		if (UGPInventorySlot* SlotWidget = Cast<UGPInventorySlot>(Widget))
		{
			SlotsWidget.AddUnique(SlotWidget);
		}
	}
	if (SlotsWidget.Num() > 0)
	{
		for (auto& SlotWidget : SlotsWidget)
		{
			InitSlot(SlotWidget);
		}
	}
};

