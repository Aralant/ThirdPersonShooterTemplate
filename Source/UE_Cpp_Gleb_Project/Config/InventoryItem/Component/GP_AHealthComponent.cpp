// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_AHealthComponent.h"


// Sets default values for this component's properties
UGP_AHealthComponent::UGP_AHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGP_AHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGP_AHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGP_AHealthComponent::ChangeHealth(float AddedHealth)
{
	if (AddedHealth == 0.0f)
	{
		return;
	}
	if (CurrentHealth + AddedHealth < 0.0f)
	{
		CurrentHealth = 0;
		OnHealthChanged.Broadcast(CurrentHealth);
		bIsDead = true;
		return;
	}
	CurrentHealth += AddedHealth;
	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
		OnHealthChanged.Broadcast(CurrentHealth);
	}
}

