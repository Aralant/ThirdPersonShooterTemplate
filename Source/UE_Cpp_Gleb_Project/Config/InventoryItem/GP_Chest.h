// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/GP_InteractableWidgetInterface.h"
#include "UE_Cpp_Gleb_Project/GlobalResource/GlobalResource.h"
#include "GP_Chest.generated.h"

UCLASS(Blueprintable)
class UE_CPP_GLEB_PROJECT_API AGP_Chest : public AActor, public IGP_InteractableWidgetInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GoldValue = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UUserWidget* OverlapWidget = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ChestMesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* ChestMaterial = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* OpenedChestMaterial = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsOpen = false;
	UPROPERTY()
	bool bIsCharacterOverlap = false;
	UPROPERTY()
	bool bIsChestInventoryWidgetVisible = false;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UGPInventoryComponent> InvComponent;
	AGP_Chest();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWidgetType WidgetType = EWidgetType::SwapInventory;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* ChestOverlap;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
							bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp,
					  AActor* OtherActor,
					  UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex);

	void InitInventoryComponent_Implementation(UGPInventoryComponent* InitInventoryComponent, int InventoryComponentIndex = 0){};
	EWidgetType GetWidgetType_Implementation(){return EWidgetType::SwapInventory;}
};
