// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_InventoryFilterButton.h"

void UGP_InventoryFilterButton::ButtonClicked()
{
	ButtonClickedDelegate.Broadcast(this);
	
}

void UGP_InventoryFilterButton::SetButtonStyle(bool bIsSelected)
{
	FilterButton->SetStyle(bIsSelected? SelectedButtonStyle: UnselectedButtonStyle);
}

void UGP_InventoryFilterButton::NativeConstruct()
{
	Super::NativeConstruct();
	if (FilterButton)
	{
		if (!FilterButton->OnClicked.IsBound())
		{
			FilterButton->OnClicked.AddDynamic(this, &UGP_InventoryFilterButton::ButtonClicked);
		}
		FilterButton->SynchronizeProperties();
	}
}
