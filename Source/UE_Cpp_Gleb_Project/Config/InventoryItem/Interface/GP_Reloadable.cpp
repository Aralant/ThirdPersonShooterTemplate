// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_Reloadable.h"

#include "AITestsCommon.h"

void IGP_Reloadable::ReloadWeapon()
{
}

void IGP_Reloadable::CompleteReload()
{
	SetIsReload(false);
}

void IGP_Reloadable::StartReload()
{
	if (CanReload())
	{
		//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2, FColor::Blue, FString(TEXT("Start Reload")));
		UE_LOG(LogTemp, Display, TEXT("Start Reload"))
		SetIsReload(true);
		FTimerHandle ReloadTimerHandle;
		GEngine->GameViewport->GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, [this](){CompleteReload();}, GetReloadTime(), false);
	}
}

bool IGP_Reloadable::CanReload() const
{
	return true;
}

void IGP_Reloadable::SetIsReload(bool bIsReload)
{
}

float IGP_Reloadable::GetReloadTime() const
{
	return 0;
}
