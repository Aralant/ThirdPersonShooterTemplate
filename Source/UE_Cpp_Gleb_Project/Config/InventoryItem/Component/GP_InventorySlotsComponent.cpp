// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_InventorySlotsComponent.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/GPInventoryComponent.h"
#include "UE_Cpp_Gleb_Project/GameplayFramework/GP_InventoryFunctionLibrary.h"


// Sets default values for this component's properties
UGP_InventorySlotsComponent::UGP_InventorySlotsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGP_InventorySlotsComponent::BeginPlay()
{
	Super::BeginPlay();
	InventoryComponent = GetOwner()->FindComponentByClass<UGPInventoryComponent>();
	if (!InventoryComponent)
	{
		DestroyComponent();
	}
	// ...
	
}

bool UGP_InventorySlotsComponent::EquipItem(UObj_GP_InventoryItem* Item, ESlot Slot)
{
	if (UGP_InventoryFunctionLibrary::CanEquipTypeToSlot(Slot, Item->ItemData.ItemType))
	{
		if (!IsSlotEmpty(Slot))
		{
			Execute_ClearSlot(this, Slot);
		}
		InventoryComponent->RemoveItem(Item);
		OnItemEquipped.Broadcast(true, Slot, Item);
		InventorySlotMap.Add(Slot, Item);
		return true;
	}
	return false;
}

bool UGP_InventorySlotsComponent::IsSlotEmpty(ESlot Slot)
{
	if (InventorySlotMap.Contains(Slot))
	{
		if (InventorySlotMap[Slot] != nullptr)
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

void UGP_InventorySlotsComponent::ClearSlot_Implementation(ESlot Slot)
{
	if (InventorySlotMap.Contains(Slot))
	{
		InventoryComponent->AddItem(InventorySlotMap[Slot]);
		InventorySlotMap[Slot] = nullptr;
		OnItemEquipped.Broadcast(false, Slot, nullptr);
	}
}


// Called every frame
void UGP_InventorySlotsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

