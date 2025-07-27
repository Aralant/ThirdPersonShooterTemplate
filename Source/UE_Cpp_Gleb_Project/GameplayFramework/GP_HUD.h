// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GP_HUD.generated.h"

enum class EWeaponSlot : uint8;
class UGP_WeaponWidget;
class AGP_BaseWeapon;
class UGP_HUDWidget;
/**
 * 
 */
UCLASS()
class UE_CPP_GLEB_PROJECT_API AGP_HUD : public AHUD
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PlayerInventoryWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> SwapWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> TradeWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY()
	UUserWidget* PlayerInventoryWidget = nullptr;

	UPROPERTY()
	UGP_HUDWidget* HUDWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGP_WeaponWidget> WeaponHUDWidgetClass;
public:

	virtual void BeginPlay() override;
	/*bool OnInteract_Implementation(AActor* InteractBy);
	bool OnHovered_Implementation(AActor* HoveredBy){return false;};
	bool OnUnhovered_Implementation(AActor* UnhoveredBy){return false;};*/

	//bool InteractWithInventory(AActor* InteractActor);

	UFUNCTION(BlueprintCallable)
	void ShowInventoryWidget(bool bIsShow);
	bool InteractWithInventory(AActor* InteractActor);
	void BindToWeapon(AGP_BaseWeapon* Weapon, EWeaponSlot ChangedSlot);
	UFUNCTION()
	UGP_HUDWidget* GetHUDWidget(){return HUDWidget;};
protected:
	UFUNCTION()
	void HandleWeaponPickUp(AGP_BaseWeapon* PickedUpWeapon, EWeaponSlot ChangedSlot);
};
