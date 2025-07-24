// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obj_GP_InventoryItem.h"
#include "GP_InventoryItemDataAsset.h"
#include "Components/ActorComponent.h"
#include "UI/GP_InventoryWidget.h"
#include "GPInventoryComponent.generated.h"

struct FItemData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UE_CPP_GLEB_PROJECT_API UGPInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAction, UObj_GP_InventoryItem*, Item);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UObj_GP_InventoryItem*> InventoryItemsObject;
	UPROPERTY(BlueprintAssignable)
	FOnItemAction OnItemDragStarted;
	UPROPERTY(BlueprintAssignable)
	FOnItemAction OnItemDragCanceled;
	UPROPERTY(BlueprintAssignable)
	FOnItemAction OnItemSelected;
	UPROPERTY(BlueprintAssignable)
	FOnItemAction OnItemDragCompleted;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	UDataTable* InitialInventoryItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UObj_GP_InventoryItem*> InventoryItemsObjectByCategory;

	UPROPERTY()
	EInventoryType CurrentCategory = EInventoryType::None;

public:
	
	UPROPERTY(BlueprintAssignable)
	FOnInventoryChanged OnInventoryChanged;
	
	UFUNCTION(BlueprintCallable)
	bool AddItem(UObj_GP_InventoryItem* Item);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(UObj_GP_InventoryItem* Item);

	UFUNCTION(BlueprintCallable)
	void DestroyItem(UObj_GP_InventoryItem* Item);

	UFUNCTION(BlueprintPure)
	TArray<UObj_GP_InventoryItem*> GetItems(EInventoryType Type = EInventoryType::None) const;

	UFUNCTION(BlueprintPure)
	bool HasItem(const UObj_GP_InventoryItem* Item) const {return InventoryItemsObject.Contains(Item);}
	UGPInventoryComponent();

	/*UFUNCTION()
	void AddItemData(FGPInventoryItemData NewData);

	UFUNCTION()
	void TestAddItem();

	UFUNCTION()
	void AddItemDataLink(FGPInventoryItemData& NewData);*/
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	void FillInventoryItemsObject();

	UDataTable* GetInventoryItems();
	TArray<class UObj_GP_InventoryItem*> GetItemByCategory(EInventoryType Type);
	void SetInvItemObjEmpty();
	EInventoryType GetCurrentCategory();
	void SetCurrentCategory(EInventoryType Category);
	void ShowInventoryWidget();

	UFUNCTION()
	void ItemSelected(UObj_GP_InventoryItem* Item);
	UFUNCTION()
	void ItemDragStarted(UObj_GP_InventoryItem* Item);
	UFUNCTION()
	void ItemDragCanceled(UObj_GP_InventoryItem* Item);
	UFUNCTION()
	void ItemDragCompleted(UObj_GP_InventoryItem* Item);
};