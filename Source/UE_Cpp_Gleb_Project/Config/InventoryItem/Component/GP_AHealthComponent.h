// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GP_AHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealhChanged, float, NewFloatValue);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UE_CPP_GLEB_PROJECT_API UGP_AHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGP_AHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float MaxHealth = 100.f; //start max health
	float CurrentHealth = 50.f; // Start current health
	bool bIsDead = false;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FOnHealhChanged OnHealthChanged;
	
	UFUNCTION(BlueprintPure)
	float GetMaxHealth(){return MaxHealth;};
	UFUNCTION(BlueprintPure)
	float GetCurrentHealth(){return CurrentHealth;};
	UFUNCTION(BlueprintPure)
	bool GetIsDead(){return bIsDead;};
	UFUNCTION(BlueprintCallable)
	void ChangeHealth(float AddedHealth);
};
