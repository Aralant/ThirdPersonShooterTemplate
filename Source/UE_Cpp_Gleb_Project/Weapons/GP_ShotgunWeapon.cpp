// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_ShotgunWeapon.h"


// Sets default values
AGP_ShotgunWeapon::AGP_ShotgunWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGP_ShotgunWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGP_ShotgunWeapon::InternalPromoteShoot()
{
	if (ShotgunCount > 0)
	{
		for (int i = 0; i < ShotgunCount; i++)
		{
			PromoteDamageTrace(SpreadAngle);
		}
	}
}

// Called every frame
void AGP_ShotgunWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

