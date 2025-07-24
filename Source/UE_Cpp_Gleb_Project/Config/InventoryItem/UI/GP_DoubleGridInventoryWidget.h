// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GP_InventoryWidget.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Interface/GP_InteractableWidgetInterface.h"
#include "GP_DoubleGridInventoryWidget.generated.h"

class UGP_InventoryGridWidget;
/**
 * 
 */
UCLASS()
class UE_CPP_GLEB_PROJECT_API UGP_DoubleGridInventoryWidget : public UUserWidget, public IGP_InteractableWidgetInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UGP_InventoryGridWidget* LeftItems;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UGP_InventoryGridWidget* RightItems;

	

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* TakeAllButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* MoveToStashButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* MoveToInventoryButton;

	UPROPERTY(BlueprintReadOnly)
	UObj_GP_InventoryItem* LastSelectedInventoryItem = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UObj_GP_InventoryItem* LastSelectedStashItem = nullptr;
	
	void InitInventoryComponent_Implementation(UGPInventoryComponent* InitInventoryComponent, int InventoryComponentIndex = 0);

protected:
	void OnLeftItemSelectionChanged(UObject* LeftSelectedItem);
	void OnRightItemSelectionChanged(UObject* RightSelectedItem);
	UFUNCTION()
	bool GetMoveToStashButtonIsEnable();
	UFUNCTION()
	bool GetMoveToInventoryButtonIsEnable();
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnTakeAllButtonClicked();
	UFUNCTION()
	void OnMoveToStashButtonClicked();
	UFUNCTION()
	void OnMoveToInventoryButtonClicked();
};
