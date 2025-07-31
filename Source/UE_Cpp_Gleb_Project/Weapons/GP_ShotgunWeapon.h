// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GP_RangeWeapon.h"
#include "GP_ShotgunWeapon.generated.h"

UCLASS()
class UE_CPP_GLEB_PROJECT_API AGP_ShotgunWeapon : public AGP_RangeWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGP_ShotgunWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InternalPromoteShoot() override;
	
	UPROPERTY(EditAnywhere, Category="Weapon characteristics")
	int ShotgunCount = 8;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
