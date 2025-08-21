// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_AlertWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UGP_AlertWidget::UpdateAlertVisual()
{
	if (AlertText)
	{
		AlertText->SetText(AlertData.AlertText);
	}
	if (AlertIcon)
	{
		AlertIcon->SetBrushFromTexture(GetIcon(AlertData.AlertStatus));
	}
}

void UGP_AlertWidget::AlertCompleted()
{
	OnAlertCompleted.Broadcast(this);
	RemoveFromParent();
}

void UGP_AlertWidget::SetAlertData(const FGP_AlertStruct& InAlertData)
{
	AlertData = InAlertData;
	UpdateAlertVisual();
	OnAlertInitialized();
	FTimerHandle AlertTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(AlertTimerHandle, this,&UGP_AlertWidget::AlertCompletedAnimation,AlertLifeTime);
}
