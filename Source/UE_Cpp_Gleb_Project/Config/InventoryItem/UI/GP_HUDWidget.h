// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UE_Cpp_Gleb_Project/Weapons/GP_BaseWeapon.h"
#include "GP_HUDWidget.generated.h"

class UGP_WeaponWidget;
class UGP_AHealthComponent;
class UOverlay;
class AGP_PlayerState;
class UTextBlock;
class UProgressBar;
class UHorizontalBox;
/**
 * 
 */
UCLASS()
class UE_CPP_GLEB_PROJECT_API UGP_HUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HealthProgressBar;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock*	HealthText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* LevelText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ExperienceProgressBar;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UOverlay* WidgetContainer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UGP_WeaponWidget* FirstWeaponWidgetSlot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UGP_WeaponWidget* SecondWeaponWidgetSlot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UGP_WeaponWidget* MeleeWeaponWidgetSlot;
	
	UPROPERTY()
	UGP_AHealthComponent* HealthComponent =  nullptr;
	
	UFUNCTION()
	void ShowWidget(UUserWidget* InContainerWidget);
	
	UFUNCTION()
	void ClearContainer();

	void SortWeaponWidget();
	
	UFUNCTION()
	void AddWeaponWidget(UGP_WeaponWidget* NewWeaponWidget);

protected:
	UFUNCTION()
	ESlateVisibility GetFirstWeaponSlotVisibility();
	
	UFUNCTION()
	ESlateVisibility GetSecondWeaponSlotVisibility();
	
	UFUNCTION()
	ESlateVisibility GetMeleeWeaponSlotVisibility();
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	AGP_PlayerState* GetPlayerState();

	UFUNCTION()
	float SetHealthBarPercent();

	UFUNCTION()
	FText SetHealthText();

	UFUNCTION()
	float SetExperienceBarPercent();

	UFUNCTION()
	FText SetLevelText();

	
};
