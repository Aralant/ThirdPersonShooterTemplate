// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/TileView.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Obj_GP_InventoryItem.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Interface/GP_InteractableWidgetInterface.h"
#include "GP_InventoryGridWidget.generated.h"

enum class EInventoryType : uint8;
class UGPInventoryComponent;
/**
 * 
 */


UCLASS()
class UE_CPP_GLEB_PROJECT_API UGP_InventoryGridWidget : public UUserWidget, public IGP_InteractableWidgetInterface
{
	GENERATED_BODY()
//	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAction, UObj_GP_InventoryItem*, Item);
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTileView* InventoryGrid;
	UPROPERTY(meta = (BindWidget))
	UBorder* GridBorder;
	UPROPERTY(BlueprintReadOnly)
	UGPInventoryComponent* InventoryComponent;
	UPROPERTY()
	UObj_GP_InventoryItem* LastSelectedItem;
	UFUNCTION()
	void UpdateInventoryTileView();
	UFUNCTION()
	void InitInventoryComponent_Implementation(UGPInventoryComponent* InInventoryComponent, int InventoryComponentIndex);
	UFUNCTION()
	void ApplyInventoryFilter(EInventoryType FilterName);

protected:
	void ItemSelectedChanged(UObject* SelectedItem);
	virtual void NativeConstruct() override;
};



