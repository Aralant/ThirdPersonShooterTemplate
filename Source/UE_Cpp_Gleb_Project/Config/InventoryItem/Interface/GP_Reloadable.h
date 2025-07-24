// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GP_Reloadable.generated.h"

class AGP_BaseWeapon;
/**
 * 
 */
UINTERFACE()
class UE_CPP_GLEB_PROJECT_API UGP_Reloadable : public UInterface
{
	GENERATED_BODY()
};

class UE_CPP_GLEB_PROJECT_API IGP_Reloadable
{
	GENERATED_BODY()

public:
	
	virtual void ReloadWeapon();
	
	virtual void CompleteReload();
	
	virtual void StartReload();

	virtual bool CanReload() const;

	virtual void SetIsReload(bool bIsReload);

	virtual float GetReloadTime() const;
};
