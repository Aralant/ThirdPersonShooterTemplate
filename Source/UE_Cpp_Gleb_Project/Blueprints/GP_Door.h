// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GP_Door.generated.h"

class UBoxComponent;

UCLASS()
class UE_CPP_GLEB_PROJECT_API AGP_Door : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGP_Door();

protected:

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* DoorPivot;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	UPROPERTY()
	bool bIsCharacterOverlap = false;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.0f;

	//UPROPERTY(EditAnywhere)
	//float OpenDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OpenningTime = 3.f;
private:
	UPROPERTY()
	float Alpha = 0.f;
	
	FRotator ClosedRotation;
	FRotator OpenRotation;
	float CurrentTime;
	bool bIsOpening;

	bool bNeedOpenDoor(AActor* Actor);
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
							bool bFromSweep, const FHitResult& SweepResult);
	
	void StartOpen();
};
