// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GP_Interact.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UGP_Interact : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE_CPP_GLEB_PROJECT_API IGP_Interact
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//virtual void Interact(AActor* Interactor) = 0;
	
	UFUNCTION(BlueprintNativeEvent)
	bool OnHovered(AActor* HoveredBy);
	
	UFUNCTION(BlueprintNativeEvent)
	bool OnUnhovered(AActor* UnhoveredBy);
	
	UFUNCTION(BlueprintNativeEvent)
	bool OnInteract(AActor* InteractBy);
};
