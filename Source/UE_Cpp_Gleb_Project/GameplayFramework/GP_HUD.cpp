// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_HUD.h"

#include "Blueprint/UserWidget.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/GPInventoryComponent.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Component/GP_AHealthComponent.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Component/GP_InventorySlotsComponent.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Interface/GP_InteractableWidgetInterface.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Interface/GP_SlotInventoryInterface.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/UI/GP_HUDWidget.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/UI/GP_WeaponWidget.h"
#include "UE_Cpp_Gleb_Project/Weapons/GP_BaseWeapon.h"

void AGP_HUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (HUDWidgetClass)
	{
		APlayerController* OwningPlayerController = GetOwningPlayerController();
		APawn* OwningPlayerPawn = OwningPlayerController->GetPawn();
		UGP_AHealthComponent* HealthComponent = OwningPlayerPawn->FindComponentByClass<UGP_AHealthComponent>();
		UUserWidget* HUDUserWidget = CreateWidget<UUserWidget>(GetOwningPlayerController() , HUDWidgetClass);
		HUDWidget = Cast<UGP_HUDWidget>(HUDUserWidget);
		if (HUDWidget && HealthComponent)
		{
			HUDWidget->HealthComponent = HealthComponent;
			HUDWidget->SynchronizeProperties();
			HUDWidget->AddToViewport(0);
		}
	}
}

void AGP_HUD::ShowInventoryWidget(bool bIsShow)
{
	if (bIsShow)
	{
		if (!PlayerInventoryWidget && PlayerInventoryWidgetClass)
		{
			APlayerController* OwningPlayerController = GetOwningPlayerController();
			APawn* OwningPlayerPawn = OwningPlayerController->GetPawn();
			PlayerInventoryWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), PlayerInventoryWidgetClass);
			if (PlayerInventoryWidget->Implements<UGP_InteractableWidgetInterface>())
			{
				IGP_InteractableWidgetInterface::Execute_InitInventoryComponent(PlayerInventoryWidget, OwningPlayerPawn->FindComponentByClass<UGPInventoryComponent>(), 0);
			}
			if (PlayerInventoryWidget->Implements<UGP_SlotInventoryInterface>())
			{
				IGP_SlotInventoryInterface::Execute_InitSlotComponent(PlayerInventoryWidget, OwningPlayerPawn->FindComponentByClass<UGP_InventorySlotsComponent>());
			}
		}
		if (PlayerInventoryWidget && HUDWidget && !PlayerInventoryWidget->IsInViewport())
		{
			UGP_HUDWidget* GP_HUDWidget = Cast<UGP_HUDWidget>(HUDWidget);
			GP_HUDWidget->ShowWidget(PlayerInventoryWidget);
		}
	}
	else
	{
		if (HUDWidget)
		{
			UGP_HUDWidget* GP_HUDWidget = Cast<UGP_HUDWidget>(HUDWidget);
			GP_HUDWidget->ClearContainer();
		}
	}
}

bool AGP_HUD::InteractWithInventory(AActor* InteractActor)
{
	APlayerController* OwningPlayerController = GetOwningPlayerController();
	APawn* OwningPlayerPawn = OwningPlayerController->GetPawn();
	UGPInventoryComponent* OtherInventoryComponent = InteractActor->FindComponentByClass<UGPInventoryComponent>();
	UGPInventoryComponent* MyInventoryComponent = OwningPlayerPawn->FindComponentByClass<UGPInventoryComponent>();
	EWidgetType WidgetType = IGP_InteractableWidgetInterface::Execute_GetWidgetType(InteractActor);
	TSubclassOf<UUserWidget> InventoryWidgetClass = nullptr;
	switch (WidgetType)
	{
	case EWidgetType::SwapInventory:
		InventoryWidgetClass = SwapWidgetClass;
		break;
	case EWidgetType::TradeInventory:
		InventoryWidgetClass = TradeWidgetClass;
		break;
	}
	if (MyInventoryComponent && OtherInventoryComponent && InventoryWidgetClass)
	{
		UUserWidget* InventoryInteractWidget = CreateWidget<UUserWidget>(Cast<APlayerController>(OwningPlayerController), InventoryWidgetClass);
		if (InventoryInteractWidget && InventoryInteractWidget->Implements<UGP_InteractableWidgetInterface>())
		{
			IGP_InteractableWidgetInterface::Execute_InitInventoryComponent(InventoryInteractWidget, MyInventoryComponent, 0);
			IGP_InteractableWidgetInterface::Execute_InitInventoryComponent(InventoryInteractWidget, OtherInventoryComponent, 1);
			
			if (HUDWidget)
			{
				HUDWidget->ShowWidget(InventoryInteractWidget);
			}
			return true;
		}
	}
	return false;
}

void AGP_HUD::BindToWeapon(AGP_BaseWeapon* Weapon, EWeaponSlot ChangedSlot)
{
	if (Weapon)
	{
		Weapon->OnWeaponPickUp.AddDynamic(this, &AGP_HUD::HandleWeaponPickUp);
	}
}

void AGP_HUD::HandleWeaponPickUp(AGP_BaseWeapon* PickedUpWeapon, EWeaponSlot ChangedSlot)
{
	if (HUDWidget)
	{
		if (PickedUpWeapon->ActorHasTag("RangeWeapon"))
		{
			switch (ChangedSlot)
			{
			case EWeaponSlot::Primary:
				HUDWidget->FirstWeaponWidgetSlot->Weapon = nullptr;
				HUDWidget->FirstWeaponWidgetSlot->SynchronizeProperties();
				HUDWidget->FirstWeaponWidgetSlot->Weapon = PickedUpWeapon;
				HUDWidget->SynchronizeProperties();
				break;
			case EWeaponSlot::Secondary:
				HUDWidget->SecondWeaponWidgetSlot->Weapon = nullptr;
				HUDWidget->SecondWeaponWidgetSlot->SynchronizeProperties();
				HUDWidget->SecondWeaponWidgetSlot->Weapon = PickedUpWeapon;
				HUDWidget->SynchronizeProperties();
				break;
			}
		}
		if (PickedUpWeapon->ActorHasTag("MeleeWeapon"))
		{
				HUDWidget->MeleeWeaponWidgetSlot->Weapon = PickedUpWeapon;
				HUDWidget->MeleeWeaponWidgetSlot->SynchronizeProperties();
		}
	}
}
