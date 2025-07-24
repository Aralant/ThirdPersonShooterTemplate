// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_WeaponWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "UE_Cpp_Gleb_Project/Weapons/GP_BaseWeapon.h"
#include "UE_Cpp_Gleb_Project/Weapons/GP_MeleeWeapon.h"
#include "UE_Cpp_Gleb_Project/Weapons/GP_RangeWeapon.h"

void UGP_WeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (WeaponName)
	{
		WeaponName->TextDelegate.BindDynamic(this, &UGP_WeaponWidget::GetWeaponName);
		WeaponName->SynchronizeProperties();
	}
	if (WeaponIcon)
	{
		WeaponIcon->BrushDelegate.BindDynamic(this, &UGP_WeaponWidget::GetWeaponIcon);
		WeaponIcon->SynchronizeProperties();
	}
	if (CurrentAmmo)
	{
		CurrentAmmo->TextDelegate.BindDynamic(this, &UGP_WeaponWidget::GetCurrentAmmo);
		CurrentAmmo->SynchronizeProperties();
	}
	if (MaxAmmoInClip)
	{
		MaxAmmoInClip->TextDelegate.BindDynamic(this, &UGP_WeaponWidget::GetMaxAmmoInClip);
		MaxAmmoInClip->SynchronizeProperties();
	}
	if (TotalAmmo)
	{
		TotalAmmo->TextDelegate.BindDynamic(this, &UGP_WeaponWidget::GetTotalAmmo);
		TotalAmmo->SynchronizeProperties();
	}
	if (AmmoVerticalBox)
	{
		AmmoVerticalBox->VisibilityDelegate.BindDynamic(this, &UGP_WeaponWidget::AmmoInfoVisibility);
		AmmoVerticalBox->SynchronizeProperties();
	}
	
}

FText UGP_WeaponWidget::GetWeaponName()
{
	if (Weapon)
	{
		return FText::FromString(Weapon->GetName());
	}
	return FText::FromString("");
}

FText UGP_WeaponWidget::GetCurrentAmmo()
{
	if (Weapon)
	{
		if (AGP_RangeWeapon* RangeWeapon = Cast<AGP_RangeWeapon>(Weapon))
		{
			return FText::AsNumber(RangeWeapon->GetCurrentAmmo());
		}
	}
	return FText::FromString("");
}

FText UGP_WeaponWidget::GetMaxAmmoInClip()
{
	
	if (Weapon)
	{
		if (AGP_RangeWeapon* RangeWeapon = Cast<AGP_RangeWeapon>(Weapon))
		{
			return FText::AsNumber(RangeWeapon->GetMaxAmmoInClip());
		}
	}
	return FText::FromString("");
}

FText UGP_WeaponWidget::GetTotalAmmo()
{
	
	if (Weapon)
	{
		if (AGP_RangeWeapon* RangeWeapon = Cast<AGP_RangeWeapon>(Weapon))
		{
			return FText::AsNumber(RangeWeapon->GetTotalAmmo());
		}
	}
	return FText::FromString("");
}

FSlateBrush UGP_WeaponWidget::GetWeaponIcon()
{
	FSlateBrush Brush;
	if (Weapon)
	{
		if (WeaponIcon)
		{
			if (Weapon->GetWeaponIcon())
			{
				Brush.SetResourceObject(Weapon->GetWeaponIcon());
			}
		}
	}
	return Brush;
}

ESlateVisibility UGP_WeaponWidget::AmmoInfoVisibility()
{
	if (Weapon)
	{
		if (Cast<AGP_MeleeWeapon>(Weapon))
		{
			return ESlateVisibility::Hidden;
		}
	}
	return ESlateVisibility::Visible;
}
