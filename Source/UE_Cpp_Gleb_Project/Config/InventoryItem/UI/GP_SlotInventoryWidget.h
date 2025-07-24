// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Interface/GP_SlotInventoryInterface.h"
#include "GP_SlotInventoryWidget.generated.h"

class UGridPanel;
class UGP_InventorySlotsComponent;
enum class EInventoryType : uint8;
class UGP_InventoryWidget;
class UObj_GP_InventoryItem;
class UGPInventoryComponent;
class UGPInventorySlot;
/**
 * 
 */
UCLASS()
class UE_CPP_GLEB_PROJECT_API UGP_SlotInventoryWidget : public UUserWidget, public IGP_SlotInventoryInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UGridPanel* SlotContainer;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGPInventorySlot> HeadSlot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGPInventorySlot> TorsSlot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGPInventorySlot> RightHandSlot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGPInventorySlot> LeftHandSlot;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UGPInventorySlot> LegSlot;

	UPROPERTY()
	TArray<UGPInventorySlot*> SlotsWidget;
	
	UPROPERTY()
	UGPInventorySlot* LastSelectedSlot;
	
	UPROPERTY()
	UGPInventoryComponent* InvComponent;

	UPROPERTY()
	UGP_InventorySlotsComponent* SlotsComponent;

	UPROPERTY()
	UGP_InventoryWidget* GPInventoryWidget;

protected:
	
	UFUNCTION()
	void OnSlotSelected(UGPInventorySlot* SelectedSlot);
	UFUNCTION()
	void ItemDragCanceled(UObj_GP_InventoryItem* Item);
	UFUNCTION()
	void ItemDragCompleted(UObj_GP_InventoryItem* Item);
	UFUNCTION()
	void ItemSelected(UObj_GP_InventoryItem* Item);
	void NativeConstruct() override;
	UFUNCTION()
	void ItemDragDetected(UObj_GP_InventoryItem* Item);
	void InitSlotComponent_Implementation(UGP_InventorySlotsComponent* InitSlotComponent);
};
