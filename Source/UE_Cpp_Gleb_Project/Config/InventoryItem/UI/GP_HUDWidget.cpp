// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_HUDWidget.h"

#include "GP_WeaponWidget.h"
#include "Components/Overlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Component/GP_AHealthComponent.h"
#include "UE_Cpp_Gleb_Project/GameplayFramework/GP_PlayerState.h"


void UGP_HUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (HealthProgressBar)
	{
		HealthProgressBar->PercentDelegate.BindDynamic(this, &UGP_HUDWidget::SetHealthBarPercent);
		HealthProgressBar->SynchronizeProperties();
	}
	if (HealthText)
	{
		HealthText->TextDelegate.BindDynamic(this, &UGP_HUDWidget::SetHealthText);
		HealthText->SynchronizeProperties();
	}
	if (ExperienceProgressBar)
	{
		ExperienceProgressBar->PercentDelegate.BindDynamic(this, &UGP_HUDWidget::SetExperienceBarPercent);
		ExperienceProgressBar->SynchronizeProperties();
	}
	if (LevelText)
	{
		LevelText->TextDelegate.BindDynamic(this, &UGP_HUDWidget::SetLevelText);
		LevelText->SynchronizeProperties();
	}
	if (FirstWeaponWidgetSlot)
	{
		FirstWeaponWidgetSlot->VisibilityDelegate.BindDynamic(this, &UGP_HUDWidget::GetFirstWeaponSlotVisibility);
		FirstWeaponWidgetSlot->SynchronizeProperties();
	}
	if (SecondWeaponWidgetSlot)
	{
		SecondWeaponWidgetSlot->VisibilityDelegate.BindDynamic(this, &UGP_HUDWidget::GetSecondWeaponSlotVisibility);
		SecondWeaponWidgetSlot->SynchronizeProperties();
	}
	if (MeleeWeaponWidgetSlot)
	{
		MeleeWeaponWidgetSlot->VisibilityDelegate.BindDynamic(this, &UGP_HUDWidget::GetMeleeWeaponSlotVisibility);
		MeleeWeaponWidgetSlot->SynchronizeProperties();
	}
}

AGP_PlayerState* UGP_HUDWidget::GetPlayerState()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		AGP_PlayerState* PlayerState = Cast<AGP_PlayerState>(PlayerController->PlayerState);
		if (PlayerState)
		{
			return PlayerState;
		}
	}
	return nullptr;
}

float UGP_HUDWidget::SetHealthBarPercent()
{
	if (HealthComponent)
	{
		float HealthPercent = HealthComponent->GetCurrentHealth() / HealthComponent->GetMaxHealth();
		return HealthPercent;
	}
	return 0.0f;
}

FText UGP_HUDWidget::SetHealthText()
{
	if (HealthComponent)
	{
		return FText::AsNumber(HealthComponent->GetCurrentHealth());
	}
	return FText::FromString("");
}

float UGP_HUDWidget::SetExperienceBarPercent()
{
	if (GetPlayerState())
	{
		float ExperiencePercent = GetPlayerState()->GetLevelProgress() / GetPlayerState()->GetMaxProgress();
		return ExperiencePercent;
	}
	return 0.0f;
}

FText UGP_HUDWidget::SetLevelText()
{
	if (GetPlayerState())
	{
		return FText::AsNumber(GetPlayerState()->GetPlayerLevel());
	}
	return FText::FromString("");
}

void UGP_HUDWidget::AddWeaponWidget(UGP_WeaponWidget* NewWeaponWidget)
{
	if (NewWeaponWidget && NewWeaponWidget->Weapon->ActorHasTag("RangeWeapon"))
	{
		if (!FirstWeaponWidgetSlot->Weapon)
		{
			FirstWeaponWidgetSlot = NewWeaponWidget;
			FirstWeaponWidgetSlot->SynchronizeProperties();
			return;
		}
		if (!SecondWeaponWidgetSlot->Weapon)
		{
			SecondWeaponWidgetSlot = NewWeaponWidget;
			SecondWeaponWidgetSlot->SynchronizeProperties();
		}
	}
	if (NewWeaponWidget && NewWeaponWidget->Weapon->ActorHasTag("MeleeWeapon"))
	{
		if (!MeleeWeaponWidgetSlot->Weapon)
		{
			MeleeWeaponWidgetSlot = NewWeaponWidget;
			MeleeWeaponWidgetSlot->SynchronizeProperties();
		}
	}
		
}

ESlateVisibility UGP_HUDWidget::GetFirstWeaponSlotVisibility()
{
	return FirstWeaponWidgetSlot->Weapon ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
}

ESlateVisibility UGP_HUDWidget::GetSecondWeaponSlotVisibility()
{
	return SecondWeaponWidgetSlot->Weapon ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
}

ESlateVisibility UGP_HUDWidget::GetMeleeWeaponSlotVisibility()
{
	return MeleeWeaponWidgetSlot->Weapon ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
}


void UGP_HUDWidget::ShowWidget(UUserWidget* InContainerWidget)
{
	if (!WidgetContainer || !InContainerWidget) return;
	if (InContainerWidget)
	{
		WidgetContainer->ClearChildren();
		WidgetContainer->AddChild(InContainerWidget);
	}
}

void UGP_HUDWidget::ClearContainer()
{
	if (!WidgetContainer) return;
	WidgetContainer->ClearChildren();
}

void UGP_HUDWidget::SortWeaponWidget()
{
}



