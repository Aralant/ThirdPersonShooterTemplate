// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GP_BaseWeapon.h"
#include "GP_MeleeWeapon.generated.h"

class UBoxComponent;

UCLASS()
class UE_CPP_GLEB_PROJECT_API AGP_MeleeWeapon : public AGP_BaseWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGP_MeleeWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	UBoxComponent* HitCollision;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	float MeleeRange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
	TArray<TEnumAsByte<EObjectTypeQuery>> AffectedCollisionTypes;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PromotePrimaryAction() override;
};
