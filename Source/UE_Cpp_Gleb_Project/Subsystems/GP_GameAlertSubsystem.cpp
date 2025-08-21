// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_GameAlertSubsystem.h"

bool UGP_GameAlertSubsystem::GetFirstAlert(FGP_AlertStruct& Alert)
{
	if (Alerts.Num() > 0)
	{
		Alert = Alerts[0];
		Alerts.RemoveAt(0);
		return true;
	}
	return false;
}

void UGP_GameAlertSubsystem::AddAlert(const FGP_AlertStruct Alert)
{
	Alerts.Add(Alert);
	OnAlertAdded.Broadcast();
}
