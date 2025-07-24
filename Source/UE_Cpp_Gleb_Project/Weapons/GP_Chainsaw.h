// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GP_MeleeWeapon.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Interface/GP_Reloadable.h"
#include "GP_Chainsaw.generated.h"

UCLASS()
class UE_CPP_GLEB_PROJECT_API AGP_Chainsaw : public AGP_MeleeWeapon, public IGP_Reloadable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGP_Chainsaw();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float TotalFuel = 0.0f;

	float CurrentFuel = 0.0f;

	float FuelRate = 0.0f;

	bool bIsFuelEmpty = false;

	bool bIsReloading = false;
	
	virtual bool CanAttack() const override;

	virtual void PromotePrimaryAction() override;
};
