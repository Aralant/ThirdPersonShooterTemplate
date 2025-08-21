// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_AlertsWidgetContainer.h"

#include "UE_Cpp_Gleb_Project/Subsystems/GP_GameAlertSubsystem.h"


void UGP_AlertsWidgetContainer::OnAlertCompleted(UGP_AlertWidget* AlertWidget)
{
	AlertWidget->OnAlertCompleted.RemoveDynamic(this, &UGP_AlertsWidgetContainer::OnAlertCompleted);
	GetWorld()->GetTimerManager().SetTimerForNextTick([this](){UpdateAlerts();});
}

void UGP_AlertsWidgetContainer::CreateAlertWidget(const FGP_AlertStruct AlertData)
{
	if (AlertWidgetClass)
	{
		UGP_AlertWidget* NewAlertWidget = CreateWidget<UGP_AlertWidget>(GetOwningPlayer(), AlertWidgetClass);
		NewAlertWidget->SetAlertData(AlertData);
		NewAlertWidget->OnAlertCompleted.AddDynamic(this, &UGP_AlertsWidgetContainer::OnAlertCompleted);
		AlertsWidgetVB->AddChild(NewAlertWidget);
	}
}

void UGP_AlertsWidgetContainer::UpdateAlerts()
{
	int ChildCount = AlertsWidgetVB->GetAllChildren().Num();
	if (ChildCount < AlertsAmount)
	{
		FGP_AlertStruct AlertData;
		if (GameAlertSubsystem)
		{
			if (GameAlertSubsystem->GetFirstAlert(AlertData))
			{
				CreateAlertWidget(AlertData);
				UpdateAlerts();
			}
		}
	}
}

void UGP_AlertsWidgetContainer::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	GameAlertSubsystem = GetWorld()->GetSubsystem<UGP_GameAlertSubsystem>();
	GameAlertSubsystem->OnAlertAdded.AddDynamic(this, &UGP_AlertsWidgetContainer::UpdateAlerts);
	UpdateAlerts();
}
