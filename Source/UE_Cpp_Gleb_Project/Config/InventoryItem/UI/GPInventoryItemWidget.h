// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/DataTable.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Obj_GP_InventoryItem.h"
#include "GPInventoryItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE_CPP_GLEB_PROJECT_API UGPInventoryItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "DragDrop")
	TSubclassOf<UUserWidget> DragWidgetClass;

	UPROPERTY(EditAnywhere)
	FKey DragKey;

	//BPO - сокращение Blueprint Object, в плюсах использовать такой префикс нет смысла
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UObj_GP_InventoryItem* BPO_Item = nullptr;	
	
	UPROPERTY(BlueprintReadWrite)
	UPanelWidget* OldPanelWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSelected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSelectInSlot;

	//
	UPROPERTY()
	FGuid ItemId;
	/*
	 *Widget binding
	 */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemName;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemLevel;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> ItemBG;
	UFUNCTION(BlueprintCallable)
	void SetItemBgSelected();
	UFUNCTION(BlueprintCallable)
	void SetItemBgUnselected();
	void SetItemVisual(UObj_GP_InventoryItem* Bpo_Item);

protected:
	FGuid GetItemID();
	UFUNCTION()
	FText GetItemName();
	UFUNCTION()
	FText GetItemLevel();
	UFUNCTION()
	FSlateBrush GetItemIcon();
	UFUNCTION()
	void SelectedChanged(UObject* SelectedObject);
	UFUNCTION(BlueprintCallable)
	void SetListItemObjectData(UObject* ListItemObject);
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeConstruct() override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
};
