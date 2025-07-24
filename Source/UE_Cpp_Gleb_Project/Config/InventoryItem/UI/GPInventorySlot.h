// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GPInventoryItemWidget.h"
#include "Blueprint/UserWidget.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Interface/GP_SlotInventoryInterface.h"
#include "GPInventorySlot.generated.h"

class UGPInventoryItemWidget;
//DECLARE_MULTICAST_DELEGATE(FOnItemDropped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemDropped, UGPInventorySlot*, DroppedSlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotSelected, UGPInventorySlot*, SelectedSlot);
/**
 * 
 */
UCLASS()
class UE_CPP_GLEB_PROJECT_API UGPInventorySlot : public UUserWidget, public IGP_SlotInventoryInterface
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintAssignable)
	FOnItemDropped OnItemDropped;
	UPROPERTY(BlueprintAssignable)
	FOnSlotSelected OnSlotSelected;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESlot SlotType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SlotName = FText::FromString("None");
	/*
	 *Bindings
	 */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> FillSlotBorder;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UGPInventoryItemWidget* ItemWidget;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> NoItemWidget;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> SlotNameText;

	UPROPERTY()
	UGP_InventorySlotsComponent* SlotsComponent;

	UFUNCTION()
	void SetSlotUnselected();
	UFUNCTION()
	void SetSlotCanEquipColor();

protected:
	UFUNCTION()
	FEventReply SlotSelected(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	UFUNCTION()
	ESlateVisibility GetItemWidgetVisibility();
	UFUNCTION()
	ESlateVisibility GetNoInfoWidgetVisibility();
	void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UFUNCTION()
	void OnSlotChange(bool bIsEquiped, ESlot InSlotType, UObj_GP_InventoryItem* Item);
	void InitSlotComponent_Implementation(UGP_InventorySlotsComponent* InitSlotComponent);
	
};
