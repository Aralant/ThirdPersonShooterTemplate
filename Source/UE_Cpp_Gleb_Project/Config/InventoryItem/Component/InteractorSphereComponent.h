// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableSphereComponent.h"
#include "Components/SphereComponent.h"
#include "InteractorSphereComponent.generated.h"


class AGP_InteractableActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class UE_CPP_GLEB_PROJECT_API UInteractorSphereComponent : public USphereComponent
{
	GENERATED_BODY()

	UPROPERTY()
	UPrimitiveComponent* HoveredComponent = nullptr;
	UPROPERTY()
	AGP_InteractableActor* NearestActor = nullptr;
	UPROPERTY()
	AGP_InteractableActor* NewNearestActor = nullptr;
public:
	// Sets default values for this component's properties
	UInteractorSphereComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	FVector GetControllerForwardVector();
	void GetNearestInteractItem(TArray<UPrimitiveComponent*> InteractableActorComponent);
	UFUNCTION(BlueprintCallable)
	void CheckInteractableObjectNearCharacter();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
							bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp,
					  AActor* OtherActor,
					  UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex);
	UFUNCTION(BlueprintCallable)
	bool Interact();
private:
	bool HoverComponent(UActorComponent* ComponentForHover);
	void UnhoverComponent(UActorComponent* ComponentForUnhover);
};
