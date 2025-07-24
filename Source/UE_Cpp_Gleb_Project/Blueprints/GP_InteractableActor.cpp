// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_InteractableActor.h"

#include "ViewportInteractionTypes.h"


// Sets default values
AGP_InteractableActor::AGP_InteractableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	ActorPivot = CreateDefaultSubobject<USceneComponent>(TEXT("ActorPivot"));
	ActorPivot->SetupAttachment(RootScene);

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	ActorMesh->SetupAttachment(ActorPivot);

}

// Called when the game starts or when spawned
void AGP_InteractableActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGP_InteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGP_InteractableActor::CanInteract(bool bCanInteract)
{
	
	if (bCanInteract)
	{
		ActorMesh->SetMaterial(0, CanInteractMaterial);
	}
	else
	{
		ActorMesh->SetMaterial(0, BaseMaterial);
	}
}

