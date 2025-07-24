// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Interface/GP_SlotInventoryInterface.h"
#include "GP_InventorySlotsComponent.generated.h"


enum class ESlot : uint8;
class UObj_GP_InventoryItem;
class UGPInventoryComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemEquiped, bool, bIsEquiped, ESlot, SlotType, UObj_GP_InventoryItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemChagedInSlot);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UE_CPP_GLEB_PROJECT_API UGP_InventorySlotsComponent : public UActorComponent, public IGP_SlotInventoryInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGP_InventorySlotsComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UGPInventoryComponent* InventoryComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ESlot, UObj_GP_InventoryItem*> InventorySlotMap;

	UPROPERTY(BlueprintAssignable)
	FOnItemEquiped OnItemEquipped;
	
	UFUNCTION()
	bool EquipItem(UObj_GP_InventoryItem* Item, ESlot Slot);
	
	UFUNCTION()
	void ClearSlot_Implementation(ESlot Slot);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	bool IsSlotEmpty(ESlot Slot);
};
