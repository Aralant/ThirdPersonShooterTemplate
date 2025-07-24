// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GP_PlayerState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFloatValueChangedSignature, float, NewFloatValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIntValueChangedSignature, int, NewIntValue);

UCLASS()
class UE_CPP_GLEB_PROJECT_API AGP_PlayerState : public APlayerState
{
	GENERATED_BODY()
protected:
	float MoneyValue = 0.f;
	int PlayerLevel = 1.f;
	float LevelProgress = 2.f;
	float MaxProgress = 10.f;
public:
	UFUNCTION(BlueprintPure)
	float GetMoney(){return MoneyValue;}
	UFUNCTION(BlueprintPure)
	float GetMaxProgress(){return MaxProgress;};
	UFUNCTION(BlueprintPure)
	int GetPlayerLevel(){return PlayerLevel;};
	UFUNCTION(BlueprintPure)
	float GetLevelProgress(){return LevelProgress;};
	UFUNCTION(BlueprintCallable)
	void AddMoney(float AddedMoney);
	UFUNCTION(BlueprintCallable)
	void AddPlayerLevel(int AddedPlayerLevel);
	UFUNCTION(BlueprintCallable)
	void AddLevelProgress(float AddedLevelProgress);
	FOnFloatValueChangedSignature OnMoneyChanged;
	FOnIntValueChangedSignature OnPlayerLevelChanged;
	FOnFloatValueChangedSignature OnLevelProgressChanged;
};
