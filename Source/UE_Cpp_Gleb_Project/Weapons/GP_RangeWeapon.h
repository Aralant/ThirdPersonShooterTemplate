// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GP_BaseWeapon.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Interface/GP_Reloadable.h"
#include "GP_RangeWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangeAmmo, int, CurrentAmmo, int, TotalAmmo);

UCLASS()
class UE_CPP_GLEB_PROJECT_API AGP_RangeWeapon : public AGP_BaseWeapon,  public IGP_Reloadable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGP_RangeWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Weapon characteristics")
	int TotalAmmo = 0;
	
	UPROPERTY(EditAnywhere, Category = "Weapon characteristics")
	int CurrentAmmo = 0;
	UPROPERTY(EditAnywhere, Category = "Weapon characteristics")
	int MaxAmmoInClip = 0;
	
	UPROPERTY(EditAnywhere, Category = "Weapon characteristics")
	float ReloadTime = 0.f;
	
	UPROPERTY(EditAnywhere, Category = "Weapon characteristics")
	bool bIsReloading = false;
	
	UPROPERTY(EditAnywhere, Category = "Weapon characteristics")
	bool bIsAmmoEmpty =  false;
	
	UPROPERTY(EditAnywhere, Category="Weapon characteristics")
	float SpreadAngle = 1.0f;
	
	virtual bool CanAttack() const override;

	virtual void InternalPromoteShoot();
	
	void PromoteShoot();
	
#pragma region ReloadableInterface
	virtual void CompleteReload() override;
	
	virtual bool CanReload() const override;

	virtual float GetReloadTime() const override;

	virtual void SetIsReload(bool bIsReload) override;
#pragma endregion
	
	virtual void OnPrimaryActionStarted() override;
	virtual void OnPrimaryActionFinished() override;
	void SetCurrentAmmo(int NewCurrentAmmo);
	void PromoteDamageTrace(float SpreadAngleDegrees);
public:
	UFUNCTION()
	int GetCurrentAmmo(){return CurrentAmmo;};
	UFUNCTION()
	int GetMaxAmmoInClip(){return MaxAmmoInClip;}
	UFUNCTION()
	int GetTotalAmmo(){return TotalAmmo;}
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintAssignable)
	FOnChangeAmmo OnChangeAmmo;
	virtual void PromotePrimaryAction() override;
};
