// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GPInventoryItemWidget.h"
#include "GPInventorySlot.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Interface/GP_InteractableWidgetInterface.h"
#include "GP_InventoryWidget.generated.h"

class UGP_InventoryFilterButton;
class UGP_SlotInventoryWidget;
class UGP_InventoryGridWidget;

/**
 * 
 */
UCLASS()
class UE_CPP_GLEB_PROJECT_API UGP_InventoryWidget : public UUserWidget, public IGP_InteractableWidgetInterface, public IGP_SlotInventoryInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGPInventoryItemWidget> InvItemWidget;
	
	/*UPROPERTY()
	UGPInventorySlot* LastSelectedSlot = nullptr;*/
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UGP_InventoryGridWidget* WBP_AvailableItems;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UGP_SlotInventoryWidget* SlotInventoryWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> AddItemToSlot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> RemoveItemFromSlot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* DestroyItemButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGP_InventoryFilterButton> AllItemButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGP_InventoryFilterButton> HandItemButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGP_InventoryFilterButton> LegItemButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGP_InventoryFilterButton> HeadItemButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGP_InventoryFilterButton> TorsoItemButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> CategoryItemButtonHB;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UGPInventoryComponent> InvComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UGP_InventorySlotsComponent> SlotsComponent;

	void UpdateInventory();
protected:
	UFUNCTION()
	bool GetRemoveButtonIsEnable();
	UFUNCTION()
	void OnInvItemSelected(UGPInventoryItemWidget* SelectedItem);
	UFUNCTION()
	void RemoveItemClicked();
	UFUNCTION()
	void OnFilterButtonClicked(UGP_InventoryFilterButton* FilterButton);
	void SetButtonColorIsSelected(UGP_InventoryFilterButton* PressedButton);
	UFUNCTION()
	bool GetAddButtonIsEnable();
	UFUNCTION()
	void AddButtonClick();
	UFUNCTION()
	bool GetDestroyButtonIsEnable();
	UFUNCTION()
	void OnDestroyItemClicked();
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void InitInventoryComponent_Implementation(UGPInventoryComponent* InitInventoryComponent, int InventoryComponentIndex = 0);
	void InitSlotComponent_Implementation(UGP_InventorySlotsComponent* InitSlotComponent);
};
