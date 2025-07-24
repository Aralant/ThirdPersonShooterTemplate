// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GP_InteractableWidgetInterface.generated.h"

enum class EWidgetType : uint8;
class UGPInventoryComponent;
/**
 * 
*/


UINTERFACE()
class UE_CPP_GLEB_PROJECT_API UGP_InteractableWidgetInterface : public UInterface
{
	GENERATED_BODY()
};


/**
 * 
 */
class UE_CPP_GLEB_PROJECT_API IGP_InteractableWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//virtual void Interact(AActor* Interactor) = 0;
	UFUNCTION(BlueprintNativeEvent)
	void InitInventoryComponent(UGPInventoryComponent* InitInventoryComponent, int InventoryComponentIndex = 0);

	UFUNCTION(BlueprintNativeEvent)
	EWidgetType GetWidgetType();
};