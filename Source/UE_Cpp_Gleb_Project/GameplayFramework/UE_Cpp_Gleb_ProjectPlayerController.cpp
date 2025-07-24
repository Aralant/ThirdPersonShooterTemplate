// Copyright Epic Games, Inc. All Rights Reserved.


#include "UE_Cpp_Gleb_ProjectPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GP_HUD.h"
#include "UE_Cpp_Gleb_ProjectCharacter.h"
#include "Engine/LocalPlayer.h"

void AUE_Cpp_Gleb_ProjectPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AUE_Cpp_Gleb_ProjectPlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AUE_Cpp_Gleb_ProjectPlayerController::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUE_Cpp_Gleb_ProjectPlayerController::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUE_Cpp_Gleb_ProjectPlayerController::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AUE_Cpp_Gleb_ProjectPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GP_HUD = GetHUD<AGP_HUD>();
	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void AUE_Cpp_Gleb_ProjectPlayerController::ShowInventory(bool bIsShow)
{
	GP_HUD->ShowInventoryWidget(bIsShow);
}

bool AUE_Cpp_Gleb_ProjectPlayerController::OnInteract_Implementation(AActor* InteractBy)
{
	if (InteractBy->ActorHasTag(FName ("Inventory")))
	{
		GP_HUD->InteractWithInventory(InteractBy);
		return true;
	}
	return false;
}

void AUE_Cpp_Gleb_ProjectPlayerController::Jump()
{
	GetPawn<ACharacter>()->Jump();
}

void AUE_Cpp_Gleb_ProjectPlayerController::StopJumping()
{
	GetPawn<ACharacter>()->StopJumping();
}

void AUE_Cpp_Gleb_ProjectPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	// add movement 
	GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), MovementVector.Y);
	GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector(), MovementVector.X);
}

void AUE_Cpp_Gleb_ProjectPlayerController::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	// add yaw and pitch input to controller
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}


