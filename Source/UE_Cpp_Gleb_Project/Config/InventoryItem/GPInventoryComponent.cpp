// Fill out your copyright notice in the Description page of Project Settings.


#include "GPInventoryComponent.h"


bool UGPInventoryComponent::AddItem(UObj_GP_InventoryItem* Item)
{
	if(!InventoryItemsObject.Contains(Item))
	{
		InventoryItemsObject.Add(Item);
		Item->OnItemSelected.AddDynamic(this, &UGPInventoryComponent::ItemSelected);
		Item->OnItemDragStarted.AddDynamic(this, &UGPInventoryComponent::ItemDragStarted);
		Item->OnItemDragCanceled.AddDynamic(this, &UGPInventoryComponent::ItemDragCanceled);
		Item->OnItemDragCompleted.AddDynamic(this, &UGPInventoryComponent::ItemDragCompleted);
		OnInventoryChanged.Broadcast();
		return true;
	}
	return false;
}

bool UGPInventoryComponent::RemoveItem(UObj_GP_InventoryItem* Item)
{
	if(InventoryItemsObject.Contains(Item))
	{
		InventoryItemsObject.Remove(Item);
		Item->OnItemSelected.RemoveDynamic(this,  &UGPInventoryComponent::ItemSelected);
		Item->OnItemDragStarted.RemoveDynamic(this, &UGPInventoryComponent::ItemDragStarted);
		Item->OnItemDragCanceled.RemoveDynamic(this, &UGPInventoryComponent::ItemDragCanceled);
		Item->OnItemDragCompleted.RemoveDynamic(this, &UGPInventoryComponent::ItemDragCompleted);
		OnInventoryChanged.Broadcast();
		return true;
	}
	return false;
}

void UGPInventoryComponent::DestroyItem(UObj_GP_InventoryItem* Item)
{
	if(InventoryItemsObject.Contains(Item))
	{
		InventoryItemsObject.Remove(Item);
		OnInventoryChanged.Broadcast();
		Item->ConditionalBeginDestroy();
	}
}

TArray<UObj_GP_InventoryItem*> UGPInventoryComponent::GetItems(EInventoryType Type) const
{
	if(Type == EInventoryType::None)
	{
		return InventoryItemsObject;
	}

	
	TArray<UObj_GP_InventoryItem*> OutItems;

	for(UObj_GP_InventoryItem* Item : InventoryItemsObject)
	{
		if(Item->ItemData.ItemType == Type)
		{
			OutItems.Add(Item);
		}
	}
	return OutItems;
	
	
	
}

// Sets default values for this component's properties
UGPInventoryComponent::UGPInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

/*void UGPInventoryComponent::AddItemData(FGPInventoryItemData NewData)
{
	
}

void UGPInventoryComponent::TestAddItem()
{
	UObj_GP_InventoryItem* TestItem = nullptr; // не nullptr - тест
	UpgradeItemAction(TestItem); //меняем что то внутри item
	//просле обращения к TestItem получим обновленные данные

	FGPInventoryItemData TestItemData;
	AddItemData(TestItemData); //увеличили количество
	//после изменения в NewData, TestItem останется прежним и не применится к TestItemData
}

void UGPInventoryComponent::AddItemDataLink(FGPInventoryItemData& NewData)
{
	//передаем ссылка на участок памяти
	//Нет проверки на валидность как nullptr для указатели
	//При отсутсвии объекта будет ошибка
	//Если здесь поменять данные - это аналогично работе с указателем
	NewItemData.ItemName - //обращение через точку
}*/



// Called when the game starts
void UGPInventoryComponent::BeginPlay()
{
#if WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Yellow, "UGPInventoryComponent::BeginPlay");
#endif
#if PLATFORM_WINDOWS
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Yellow, "Windows");
#endif
	Super::BeginPlay();

	APlayerController* PC = nullptr;

	if(APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		PC = Cast<APlayerController>(Pawn->GetController());
	}

	if(!PC)
	{
		return;
	}
	FillInventoryItemsObject();
	
}

// Called every frame
void UGPInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGPInventoryComponent::FillInventoryItemsObject()
{
	static const FString ContextString(TEXT("DataTable Context"));
	if (!InitialInventoryItems)
	{
		return;
	}
	TArray<FName> ItemRowsNames = InitialInventoryItems->GetRowNames();
	for (auto& Name : ItemRowsNames)
	{
		FGPInventoryItemData* FindData = InitialInventoryItems->FindRow<FGPInventoryItemData>(Name, ContextString);
		if (InitialInventoryItems->FindRow<FGPInventoryItemData>(Name, ContextString))
		{
			UObj_GP_InventoryItem* NewItemObj = NewObject<UObj_GP_InventoryItem>();
			NewItemObj->ItemData.ItemIcon = FindData->ItemIcon;
			NewItemObj->ItemData.ItemId = FindData->ItemId;
			NewItemObj->ItemData.ItemLevel = FindData->ItemLevel;
			NewItemObj->ItemData.ItemName = FindData->ItemName;
			NewItemObj->ItemData.ItemType = FindData->ItemType;
			NewItemObj->IsSelected = false;
			NewItemObj->OnItemSelected.AddDynamic(this, &UGPInventoryComponent::ItemSelected);
			NewItemObj->OnItemDragStarted.AddDynamic(this, &UGPInventoryComponent::ItemDragStarted);
			NewItemObj->OnItemDragCanceled.AddDynamic(this, &UGPInventoryComponent::ItemDragCanceled);
			NewItemObj->OnItemDragCompleted.AddDynamic(this, &UGPInventoryComponent::ItemDragCompleted);
			InventoryItemsObject.AddUnique(NewItemObj);
		}
	}
}

UDataTable* UGPInventoryComponent::GetInventoryItems()
{
	return InitialInventoryItems;
}

void UGPInventoryComponent::SetInvItemObjEmpty()
{
	InventoryItemsObject.Empty();
}

EInventoryType UGPInventoryComponent::GetCurrentCategory()
{
	return CurrentCategory;
}

void UGPInventoryComponent::SetCurrentCategory(EInventoryType Category)
{
	CurrentCategory = Category;
}

TArray<class UObj_GP_InventoryItem*> UGPInventoryComponent::GetItemByCategory(EInventoryType Category)
{
	CurrentCategory = Category;
	InventoryItemsObjectByCategory.Empty();
	for (auto& Item : InventoryItemsObject)
	{
		if (Category == EInventoryType::None)
		{
			InventoryItemsObjectByCategory.AddUnique(Item);
		}
		else
		{
			if (Item->ItemData.ItemType == Category)
			{
				InventoryItemsObjectByCategory.AddUnique(Item);
			}
		}
	}
	return InventoryItemsObjectByCategory;
}

void UGPInventoryComponent::ShowInventoryWidget()
{
}

void UGPInventoryComponent::ItemSelected(UObj_GP_InventoryItem* Item)
{
	OnItemSelected.Broadcast(Item);
}

void UGPInventoryComponent::ItemDragStarted(UObj_GP_InventoryItem* Item)
{
	OnItemDragStarted.Broadcast(Item);
}

void UGPInventoryComponent::ItemDragCanceled(UObj_GP_InventoryItem* Item)
{
	OnItemDragCanceled.Broadcast(Item);
}

void UGPInventoryComponent::ItemDragCompleted(UObj_GP_InventoryItem* Item)
{
	OnItemDragCompleted.Broadcast(Item);
}

