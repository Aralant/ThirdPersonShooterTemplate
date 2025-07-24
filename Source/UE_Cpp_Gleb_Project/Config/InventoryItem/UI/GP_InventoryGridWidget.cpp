// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_InventoryGridWidget.h"

#include "UE_Cpp_Gleb_Project/Config/InventoryItem/GPInventoryComponent.h"

void UGP_InventoryGridWidget::UpdateInventoryTileView()
{
	InventoryGrid->SetListItems(InventoryComponent->GetItems(EInventoryType::None));
}

void UGP_InventoryGridWidget::InitInventoryComponent_Implementation(UGPInventoryComponent* InInventoryComponent,
                                                                    int InventoryComponentIndex)
{
	InventoryComponent = InInventoryComponent;
	TArray<UObj_GP_InventoryItem*> InventoryComponentArray = InventoryComponent->GetItems(EInventoryType::None);
	InventoryGrid->SetListItems(InventoryComponentArray);
	InventoryComponent->OnInventoryChanged.AddDynamic(this, &UGP_InventoryGridWidget::UpdateInventoryTileView);
	/*InventoryComponent->OnItemDragCanceled.AddDynamic(this, &UGP_InventoryGridWidget::ItemDragCanceled);
	InventoryComponent->OnItemDragCompleted.AddDynamic(this, &UGP_InventoryGridWidget::ItemDragCompleted);
	InventoryComponent->OnItemDragStarted.AddDynamic(this, &UGP_InventoryGridWidget::ItemDragStarted);
	InventoryComponent->OnItemSelected.AddDynamic(this, &UGP_InventoryGridWidget::ItemSelected);*/
	//OnItemAdd/OnItemRemoveBinding
}

void UGP_InventoryGridWidget::ApplyInventoryFilter(EInventoryType FilterName)
{
	TArray<UObj_GP_InventoryItem*> ItemsByCategory = InventoryComponent->GetItems(FilterName);
	InventoryGrid->SetListItems(ItemsByCategory);
}

void UGP_InventoryGridWidget::ItemSelectedChanged(UObject* SelectedItem)
{
	if (SelectedItem)
	{
		UObj_GP_InventoryItem* InventoryItem = Cast<UObj_GP_InventoryItem>(SelectedItem);
		if (InventoryItem)
		{
			if (LastSelectedItem)
			{
				if (LastSelectedItem == InventoryItem)
				{
				}
				else
				{
					LastSelectedItem = InventoryItem;
				}
			}
			else
			{
				LastSelectedItem = InventoryItem;
			}
		}
	}
}

void UGP_InventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (InventoryGrid)
	{
		InventoryGrid->OnItemSelectionChanged().AddUObject(this, &UGP_InventoryGridWidget::ItemSelectedChanged);
	}
}
