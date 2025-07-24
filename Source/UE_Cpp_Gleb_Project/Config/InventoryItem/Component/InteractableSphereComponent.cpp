// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableSphereComponent.h"


// Sets default values for this component's properties
UInteractableSphereComponent::UInteractableSphereComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractableSphereComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractableSphereComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInteractableSphereComponent::OnHovered_Implementation(AActor* HoveredBy)
{
	OnHovered.Broadcast(HoveredBy);
	return true;
}

bool UInteractableSphereComponent::OnUnhovered_Implementation(AActor* UnhoveredBy)
{
	OnUnhovered.Broadcast(UnhoveredBy);
	return true;
}

bool UInteractableSphereComponent::OnInteract_Implementation(AActor* InteractBy)
{
	OnInteractAction.Broadcast(InteractBy);
	if (InteractBy->Implements<UGP_Interact>())
	{
		IGP_Interact::Execute_OnInteract(InteractBy, GetOwner());
	}
	return true;
}

