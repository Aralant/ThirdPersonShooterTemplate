// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_PlayerState.h"

void AGP_PlayerState::AddMoney(float AddedMoney)
{
	if (AddedMoney == 0.0f)
	{
		return;
	}
	if (AddedMoney + MoneyValue > 0.0f)
	{
		MoneyValue += AddedMoney;
	}
	else
	{
		MoneyValue = 0;
	}
	OnMoneyChanged.Broadcast(MoneyValue);
}

void AGP_PlayerState::AddPlayerLevel(int AddedPlayerLevel)
{
	if (AddedPlayerLevel <= 0)
	{
		return;
	}
	PlayerLevel += AddedPlayerLevel;
	MaxProgress *= 2;
	LevelProgress = 0;
	OnPlayerLevelChanged.Broadcast(PlayerLevel);
}

void AGP_PlayerState::AddLevelProgress(float AddedLevelProgress)
{
	if (AddedLevelProgress == 0.0f)
	{
		return;
	}
	float SummaryProgress = LevelProgress + AddedLevelProgress;
	while(SummaryProgress >= MaxProgress)
	{
		SummaryProgress -= MaxProgress;
		AddPlayerLevel(1);
	}
	LevelProgress = SummaryProgress;
	OnLevelProgressChanged.Broadcast(SummaryProgress);
}

