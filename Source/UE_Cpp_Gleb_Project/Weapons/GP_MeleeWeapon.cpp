// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_MeleeWeapon.h"

#include "Components/BoxComponent.h"
#include "Engine/OverlapResult.h"
#include "Kismet/GameplayStatics.h"
#include "ProfilingDebugging/CookStats.h"


// Sets default values
AGP_MeleeWeapon::AGP_MeleeWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!Tags.Contains("MeleeWeapon"))
	{
		Tags.Add("MeleeWeapon");
	}
	HitCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("HitCollision"));
	HitCollision->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AGP_MeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGP_MeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGP_MeleeWeapon::PromotePrimaryAction()
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
	DrawDebugSphere(GetWorld(), AttackActorLocation, MeleeRange, 16, FColor::Purple, false, 1.0f);
}

