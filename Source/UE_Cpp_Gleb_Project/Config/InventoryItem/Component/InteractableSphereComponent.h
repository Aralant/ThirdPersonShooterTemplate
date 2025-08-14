// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Interface/GP_Interact.h"
#include "InteractableSphereComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractAction, AActor*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCanInteractAction, bool, bCanInteract, AActor*, Interactor);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class UE_CPP_GLEB_PROJECT_API UInteractableSphereComponent : public USphereComponent, public IGP_Interact
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractableSphereComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> OverlapWidgetClass;

	UUserWidget* OverlapWidget = nullptr;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FOnInteractAction OnInteractAction;
	UPROPERTY(BlueprintAssignable)
	FOnInteractAction OnHovered;
	UPROPERTY(BlueprintAssignable)
	FOnInteractAction OnUnhovered;
	UPROPERTY(BlueprintAssignable)
	FOnCanInteractAction OnCanInteract;

	bool OnHovered_Implementation(AActor* HoveredBy);
	bool OnUnhovered_Implementation(AActor* UnhoveredBy);
	bool OnInteract_Implementation(AActor* InteractBy);
	bool OnCanInteract_Implementation(bool bCanInteract, AActor* InteractBy);
};
