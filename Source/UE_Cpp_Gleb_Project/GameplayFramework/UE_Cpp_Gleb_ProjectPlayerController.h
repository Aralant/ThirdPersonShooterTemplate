// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Interface/GP_Interact.h"
#include "UE_Cpp_Gleb_ProjectPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class AGP_HUD;
/**
 *
 */
UCLASS()
class UE_CPP_GLEB_PROJECT_API AUE_Cpp_Gleb_ProjectPlayerController : public APlayerController, public IGP_Interact
{
	GENERATED_BODY()
	
protected:

	UPROPERTY()
	AGP_HUD* GP_HUD = nullptr;

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	void SetupInputComponent() override;
	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ShowInventory(bool bIsShow);

	bool OnInteract_Implementation(AActor* InteractBy);

	UFUNCTION()
	void Jump();

	UFUNCTION()
	void StopJumping();

	UFUNCTION()
	void Move(const FInputActionValue& Value);
	
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	// End Actor interface
};
