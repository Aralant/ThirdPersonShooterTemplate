// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_ChangeWeaponWidget.h"

#include "GP_WeaponWidget.h"

ESlateVisibility UGP_ChangeWeaponWidget::GetWeaponInHandWidgetVisibility()
{
	return WeaponInHandWidget->Weapon ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
}

ESlateVisibility UGP_ChangeWeaponWidget::GetWeaponOnWorldWidgetVisibility()
{
	return WeaponOnWorldWidget->Weapon ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
}

void UGP_ChangeWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (WeaponInHandWidget)
	{
		WeaponInHandWidget->VisibilityDelegate.BindDynamic(this, &UGP_ChangeWeaponWidget::GetWeaponInHandWidgetVisibility);
		WeaponInHandWidget->SynchronizeProperties();
	}
	if (WeaponOnWorldWidget)
	{
		WeaponOnWorldWidget->VisibilityDelegate.BindDynamic(this, &UGP_ChangeWeaponWidget::GetWeaponOnWorldWidgetVisibility);
		WeaponOnWorldWidget->SynchronizeProperties();
	}
}
