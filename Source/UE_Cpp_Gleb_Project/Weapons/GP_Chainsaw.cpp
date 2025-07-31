// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_Chainsaw.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AGP_Chainsaw::AGP_Chainsaw()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FireRate = 0.5f;
}

// Called when the game starts or when spawned
void AGP_Chainsaw::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AGP_Chainsaw::CanAttack() const
{
	if (CurrentFuel <= 0)
	{
		return false;
	}
	if (bIsReloading)
	{
		return false;
	}
	if (bIsFuelEmpty)
	{
		return false;
	}
	return true;
}

void AGP_Chainsaw::PromotePrimaryAction()
{
	
	//Damage from animation
	/*
	TArray<AActor*> ActorsToDamage;
	HitCollision->GetOverlappingActors(ActorsToDamage);
	for (AActor* Actor : ActorsToDamage)
	{
		if (Actor != CurrentOwner)
		{
			UGameplayStatics::ApplyDamage(Actor, WeaponDamage, nullptr, this, nullptr);
		}
	}*/
	TArray<AActor*> OverlappingActors;
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), MeleeRange, AffectedCollisionTypes, AActor::StaticClass(),
		{this, CurrentOwner}, OverlappingActors);
	FVector AttackActorLocation = GetActorLocation();
	FVector AttackActorForwardVector = GetActorForwardVector();
	float Radius = MeleeRange;
	
	for (AActor* DamagedActor : OverlappingActors)
	{
		if (!DamagedActor) continue;
		UGameplayStatics::ApplyDamage(DamagedActor, WeaponDamage, nullptr, this, nullptr);
	}
	DrawDebugSphere(GetWorld(), AttackActorLocation, MeleeRange, 16, FColor::Red, false, 1.0f);
}

// Called every frame
void AGP_Chainsaw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

