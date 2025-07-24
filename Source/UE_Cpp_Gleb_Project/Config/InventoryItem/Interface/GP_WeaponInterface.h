// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/TouchInterface.h"
#include "GP_WeaponInterface.generated.h"

class AGP_BaseWeapon;
/**
 * 
 */
UINTERFACE()
class UGP_WeaponInterface : public UInterface
{
	GENERATED_BODY()
};

class UE_CPP_GLEB_PROJECT_API IGP_WeaponInterface
{
	GENERATED_BODY()

public:
	
	virtual void EquipWeapon(AGP_BaseWeapon* Weapon);
};
