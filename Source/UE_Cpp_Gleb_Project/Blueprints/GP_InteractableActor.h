// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GP_InteractableActor.generated.h"
class UBoxComponent;

UCLASS()
class UE_CPP_GLEB_PROJECT_API AGP_InteractableActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGP_InteractableActor();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ActorPivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ActorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* BaseMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* CanInteractMaterial;

	UFUNCTION()
	void CanInteract(bool bCanInteract);
private:

};