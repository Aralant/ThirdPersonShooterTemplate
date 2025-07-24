// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_InventoryWidget.h"

#include "GP_InventoryFilterButton.h"
#include "GP_InventoryGridWidget.h"
#include "GP_SlotInventoryWidget.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/GPInventoryComponent.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Component/GP_InventorySlotsComponent.h"

void UGP_InventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (SlotInventoryWidget && InvComponent)
	{
		SlotInventoryWidget->InvComponent = InvComponent;
	}
	if (AddItemToSlot)
	{
		AddItemToSlot->bIsEnabledDelegate.BindDynamic(this, &UGP_InventoryWidget::GetAddButtonIsEnable);
		if (!AddItemToSlot->OnClicked.IsBound())
		{
			AddItemToSlot->OnClicked.AddDynamic(this, &UGP_InventoryWidget::AddButtonClick);
		}
		AddItemToSlot->SynchronizeProperties();
	}
	if (RemoveItemFromSlot)
	{
		RemoveItemFromSlot->bIsEnabledDelegate.BindDynamic(this, &UGP_InventoryWidget::GetRemoveButtonIsEnable);
		if (!RemoveItemFromSlot->OnClicked.IsBound())
		{
			RemoveItemFromSlot->OnClicked.AddDynamic(this, &UGP_InventoryWidget::RemoveItemClicked);
		}
		RemoveItemFromSlot->SynchronizeProperties();
	}

	if (DestroyItemButton)
	{
		DestroyItemButton->bIsEnabledDelegate.BindDynamic(this, &UGP_InventoryWidget::GetDestroyButtonIsEnable);
		if (!DestroyItemButton->OnClicked.IsBound())
		{
			DestroyItemButton->OnClicked.AddDynamic(this, &UGP_InventoryWidget::OnDestroyItemClicked);
		}
		DestroyItemButton->SynchronizeProperties();
	}
	
	if (CategoryItemButtonHB)
	{
		
		for (auto& Button: CategoryItemButtonHB->GetAllChildren())
		{
			if (UGP_InventoryFilterButton* FilterButton = Cast<UGP_InventoryFilterButton>(Button))
			{
				if (!FilterButton->ButtonClickedDelegate.IsBound())
				{
					FilterButton->ButtonClickedDelegate.AddDynamic(this, &UGP_InventoryWidget::OnFilterButtonClicked);
				}
				FilterButton->SynchronizeProperties();
			}
		}
	}
	if (CategoryItemButtonHB)
	{
		SetButtonColorIsSelected(AllItemButton);
	}
	
}

void UGP_InventoryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
}

void UGP_InventoryWidget::InitInventoryComponent_Implementation(UGPInventoryComponent* InitInventoryComponent,
	int InventoryComponentIndex)
{
	IGP_InteractableWidgetInterface::Execute_InitInventoryComponent(WBP_AvailableItems, InitInventoryComponent,0);
	InvComponent = InitInventoryComponent;
}

void UGP_InventoryWidget::InitSlotComponent_Implementation(UGP_InventorySlotsComponent* InitSlotComponent)
{
	IGP_SlotInventoryInterface::Execute_InitSlotComponent(SlotInventoryWidget, InitSlotComponent);
	if (InvComponent)
	{
		SlotInventoryWidget->InvComponent = InvComponent;
	}
	SlotsComponent = InitSlotComponent;
}

void UGP_InventoryWidget::UpdateInventory()
{
	if (InvItemWidget == nullptr)
	{
		return;
	}
}

bool UGP_InventoryWidget::GetRemoveButtonIsEnable()
{
	bool bIsEnable = false;
	if (SlotInventoryWidget && SlotInventoryWidget->LastSelectedSlot)
	{
		if (SlotInventoryWidget->LastSelectedSlot->ItemWidget->BPO_Item)
		{
			bIsEnable = true;
		}
	}
	return bIsEnable;
}


void UGP_InventoryWidget::OnInvItemSelected(UGPInventoryItemWidget* SelectedItem)
{
}

void UGP_InventoryWidget::RemoveItemClicked()
{
	if (SlotsComponent && SlotInventoryWidget && SlotInventoryWidget->LastSelectedSlot)
	{
		SlotsComponent->ClearSlot_Implementation(SlotInventoryWidget->LastSelectedSlot->SlotType);
		SlotInventoryWidget->LastSelectedSlot->SetSlotUnselected();
		WBP_AvailableItems->LastSelectedItem = nullptr;
	}
}

void UGP_InventoryWidget::OnFilterButtonClicked(UGP_InventoryFilterButton* FilterButton)
{
	WBP_AvailableItems->ApplyInventoryFilter(FilterButton->ButtonFilterType);
	SetButtonColorIsSelected(FilterButton);
	
}

void UGP_InventoryWidget::SetButtonColorIsSelected(UGP_InventoryFilterButton* PressedButton)
{
	TArray<UWidget*> CategoryButtonArray = CategoryItemButtonHB->GetAllChildren();
	for (auto& Button : CategoryButtonArray)
	{
		if (UGP_InventoryFilterButton* FilterButton = Cast<UGP_InventoryFilterButton>(Button))
		{
			FilterButton->SetButtonStyle(PressedButton == FilterButton);
		}
	}
}

bool UGP_InventoryWidget::GetAddButtonIsEnable()
{
	if (WBP_AvailableItems->LastSelectedItem && SlotInventoryWidget && SlotInventoryWidget->LastSelectedSlot)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UGP_InventoryWidget::AddButtonClick()
{
	if (SlotInventoryWidget && SlotsComponent)
	{
		if (WBP_AvailableItems->LastSelectedItem && SlotInventoryWidget->LastSelectedSlot)
		{
			if (SlotsComponent->EquipItem(WBP_AvailableItems->LastSelectedItem, SlotInventoryWidget->LastSelectedSlot->SlotType))
			{
				SlotInventoryWidget->LastSelectedSlot->SetSlotUnselected();
				SlotInventoryWidget->LastSelectedSlot = nullptr;
				WBP_AvailableItems->LastSelectedItem = nullptr;
			}
		}
	}
}

bool UGP_InventoryWidget::GetDestroyButtonIsEnable()
{
	return WBP_AvailableItems->LastSelectedItem == nullptr ? false : true;
}

void UGP_InventoryWidget::OnDestroyItemClicked()
{
	if (WBP_AvailableItems->LastSelectedItem)
	{
		
		InvComponent->DestroyItem(WBP_AvailableItems->LastSelectedItem);
		WBP_AvailableItems->LastSelectedItem = nullptr;
	}
}


