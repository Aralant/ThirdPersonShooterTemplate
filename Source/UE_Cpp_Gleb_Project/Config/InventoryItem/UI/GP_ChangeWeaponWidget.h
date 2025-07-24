// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GP_ChangeWeaponWidget.generated.h"

class UGP_WeaponWidget;
/**
 * 
 */
UCLASS()
class UE_CPP_GLEB_PROJECT_API UGP_ChangeWeaponWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UGP_WeaponWidget* WeaponInHandWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UGP_WeaponWidget* WeaponOnWorldWidget;

protected:
	UFUNCTION()
	ESlateVisibility GetWeaponInHandWidgetVisibility();
	
	UFUNCTION()
	ESlateVisibility GetWeaponOnWorldWidgetVisibility();
	
	virtual void NativeConstruct() override;
};
