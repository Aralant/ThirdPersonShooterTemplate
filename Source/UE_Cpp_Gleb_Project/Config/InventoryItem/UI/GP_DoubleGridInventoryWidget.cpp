// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_DoubleGridInventoryWidget.h"

#include "GP_InventoryGridWidget.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/GPInventoryComponent.h"
#include "UE_Cpp_Gleb_Project/GameplayFramework/GP_InventoryFunctionLibrary.h"

void UGP_DoubleGridInventoryWidget::InitInventoryComponent_Implementation(UGPInventoryComponent* InitInventoryComponent,
                                                                          int InventoryComponentIndex)
{
	UGP_InventoryGridWidget* GridForInit = nullptr;
	switch(InventoryComponentIndex)
	{
		case 0:
			GridForInit = RightItems;
			break;
		case 1:
			GridForInit = LeftItems;
			break;
	}
	if(GridForInit)
	{
		IGP_InteractableWidgetInterface::Execute_InitInventoryComponent(GridForInit, InitInventoryComponent, 0);
	}
}

void UGP_DoubleGridInventoryWidget::OnLeftItemSelectionChanged(UObject* LeftSelectedItem)
{
	if (LeftSelectedItem)
	{
		UObj_GP_InventoryItem* InventoryItem = Cast<UObj_GP_InventoryItem>(LeftSelectedItem);
		if (InventoryItem)
		{
			if (LastSelectedStashItem)
			{
				if (LastSelectedStashItem == InventoryItem)
				{
				}
				else
				{
					LastSelectedStashItem = InventoryItem;
				}
			}
			else
			{
				LastSelectedStashItem = InventoryItem;
			}
			
		}
	}
}

void UGP_DoubleGridInventoryWidget::OnRightItemSelectionChanged(UObject* RightSelectedItem)
{
	if (RightSelectedItem)
	{
		UObj_GP_InventoryItem* InventoryItem = Cast<UObj_GP_InventoryItem>(RightSelectedItem);
		if (InventoryItem)
		{
			if (LastSelectedInventoryItem)
			{
				if (LastSelectedInventoryItem == InventoryItem)
				{
				}
				else
				{
					LastSelectedInventoryItem = InventoryItem;
				}
			}
			else
			{
				LastSelectedInventoryItem = InventoryItem;
			}
			
		}
	}
}

bool UGP_DoubleGridInventoryWidget::GetMoveToStashButtonIsEnable()
{
	return LastSelectedInventoryItem == nullptr ? false : true;
}

bool UGP_DoubleGridInventoryWidget::GetMoveToInventoryButtonIsEnable()
{
	return LastSelectedStashItem == nullptr ? false : true;
}

void UGP_DoubleGridInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (TakeAllButton)
	{
		if (!TakeAllButton->OnClicked.IsBound())
		{
			TakeAllButton->OnClicked.AddDynamic(this, &UGP_DoubleGridInventoryWidget::OnTakeAllButtonClicked);
		}
	}
	if (MoveToStashButton)
	{
		if (!MoveToStashButton->OnClicked.IsBound())
		{
			MoveToStashButton->OnClicked.AddDynamic(this, &UGP_DoubleGridInventoryWidget::OnMoveToStashButtonClicked);
		}
		MoveToStashButton->bIsEnabledDelegate.BindDynamic(this, &UGP_DoubleGridInventoryWidget::GetMoveToStashButtonIsEnable);
		MoveToStashButton->SynchronizeProperties();
	}
	if (MoveToInventoryButton)
	{
		if (!MoveToInventoryButton->OnClicked.IsBound())
		{
			MoveToInventoryButton->OnClicked.AddDynamic(this, &UGP_DoubleGridInventoryWidget::OnMoveToInventoryButtonClicked);
		}
		MoveToInventoryButton->bIsEnabledDelegate.BindDynamic(this, &UGP_DoubleGridInventoryWidget::GetMoveToInventoryButtonIsEnable);
		MoveToInventoryButton->SynchronizeProperties();
	}
	if (LeftItems)
	{
		LeftItems->InventoryGrid->OnItemSelectionChanged().AddUObject(this, &UGP_DoubleGridInventoryWidget::OnLeftItemSelectionChanged);
	}
	if (RightItems)
	{
		RightItems->InventoryGrid->OnItemSelectionChanged().AddUObject(this, &UGP_DoubleGridInventoryWidget::OnRightItemSelectionChanged);
	}
}

void UGP_DoubleGridInventoryWidget::OnTakeAllButtonClicked()
{
	if (RightItems && LeftItems)
	{
		UGPInventoryComponent* RightInventoryComponent = RightItems->InventoryComponent;
		UGPInventoryComponent* LeftInventoryComponent = LeftItems->InventoryComponent;
		if (RightInventoryComponent && LeftInventoryComponent)
		{
			for (auto& Item : LeftInventoryComponent->GetItems(EInventoryType::None))
			{
				RightInventoryComponent->AddItem(Item);
				LeftInventoryComponent->RemoveItem(Item);
			}
		}
	}
}

void UGP_DoubleGridInventoryWidget::OnMoveToStashButtonClicked()
{
	if (RightItems && LeftItems && LastSelectedInventoryItem)
	{
		UGP_InventoryFunctionLibrary::MoveItem(RightItems->InventoryComponent, LeftItems->InventoryComponent, LastSelectedInventoryItem);
		LastSelectedInventoryItem = nullptr;
	}
}

void UGP_DoubleGridInventoryWidget::OnMoveToInventoryButtonClicked()
{
	if (RightItems && LeftItems && LastSelectedStashItem)
	{
		UGP_InventoryFunctionLibrary::MoveItem(LeftItems->InventoryComponent, RightItems->InventoryComponent, LastSelectedStashItem);
		LastSelectedStashItem = nullptr;
	}
}
