// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/DataTable.h"
#include "UE_Cpp_Gleb_Project/GlobalResource/GlobalResource.h"
#include "Obj_GP_InventoryItem.generated.h"



USTRUCT(Blueprintable)
struct FGPInventoryItemData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGuid ItemId = FGuid::NewGuid();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* ItemIcon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ItemLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EInventoryType ItemType = EInventoryType::None;
	
};
class UObj_GP_InventoryItem;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedChanged, UObject*, SelectedObject);

/**
 * 
 */
UCLASS(Blueprintable)
class UE_CPP_GLEB_PROJECT_API UObj_GP_InventoryItem : public UObject
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAction, UObj_GP_InventoryItem*, Item);
	
public:
	UPROPERTY()
	FOnSelectedChanged OnSelectedChanged;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSelected = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGPInventoryItemData ItemData;

	UPROPERTY(BlueprintAssignable)
	FOnItemAction OnItemDragStarted;
	UPROPERTY(BlueprintAssignable)
	FOnItemAction OnItemDragCanceled;
	UPROPERTY(BlueprintAssignable)
	FOnItemAction OnItemSelected;
	UPROPERTY(BlueprintAssignable)
	FOnItemAction OnItemDragCompleted;

	UFUNCTION(BlueprintCallable)
	void ItemDragStarted();
	UFUNCTION(BlueprintCallable)
	void ItemDragCanceled();
	UFUNCTION(BlueprintCallable)
	void ItemSelected();
	UFUNCTION(BlueprintCallable)
	void ItemDragCompleted();
};
