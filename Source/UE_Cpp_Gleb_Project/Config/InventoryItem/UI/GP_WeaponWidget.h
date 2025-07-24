// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GP_WeaponWidget.generated.h"

class UVerticalBox;
class UTextBlock;
class UImage;
class AGP_BaseWeapon;
/**
 * 
 */
UCLASS()
class UE_CPP_GLEB_PROJECT_API UGP_WeaponWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGP_BaseWeapon* Weapon = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> WeaponName;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentAmmo;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> MaxAmmoInClip;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> AmmoVerticalBox;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TotalAmmo;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> WeaponIcon;

protected:
	
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	FText GetWeaponName();
	
	UFUNCTION()
	FText GetCurrentAmmo();
	
	UFUNCTION()
	FText GetMaxAmmoInClip();
	
	UFUNCTION()
	FText GetTotalAmmo();
	
	UFUNCTION()
	FSlateBrush GetWeaponIcon();

	UFUNCTION()
	ESlateVisibility AmmoInfoVisibility();
};
