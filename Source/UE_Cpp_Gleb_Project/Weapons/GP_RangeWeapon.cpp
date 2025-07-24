// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_RangeWeapon.h"

#include "HeadMountedDisplayTypes.h"
#include "Kismet/GameplayStatics.h"
#include "UE_Cpp_Gleb_Project/GameplayFramework/GP_ThirdPersonCharacter.h"


// Sets default values
AGP_RangeWeapon::AGP_RangeWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!Tags.Contains("RangeWeapon"))
	{
		Tags.Add("RangeWeapon");
	}
}

// Called when the game starts or when spawned
void AGP_RangeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	
}

bool AGP_RangeWeapon::CanAttack() const
{
	if (CurrentAmmo <= 0)
	{
		return false;
	}
	if (bIsReloading)
	{
		return false;
	}
	if (bIsAmmoEmpty)
	{
		return false;
	}
	return true;
}

void AGP_RangeWeapon::PromoteShoot()
{
	SetCurrentAmmo(CurrentAmmo - 1);
	AActor* Actor = GetOwner();
	FVector CameraLocation;
	FRotator CameraRotation;
	AController* Controller = CurrentOwner->GetInstigatorController();
	if (Controller)
	{
		Controller->GetPlayerViewPoint(CameraLocation, CameraRotation);
	
		FVector TraceEnd = CameraLocation + (CameraRotation.Vector() * 5000.0f);
		FHitResult Hit;
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.AddIgnoredActor(CurrentOwner);
		bool bHit = GetWorld()->LineTraceSingleByChannel(
			Hit, CameraLocation, TraceEnd, ECC_Visibility, TraceParams);
		if (bHit && Hit.GetActor())
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *Hit.GetActor()->GetName());
			UE_LOG(LogTemp, Warning, TEXT("Component: %s"), *Hit.GetComponent()->GetName());
			UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *Hit.ImpactPoint.ToString());
		}
		FVector FinalTracePoint = bHit ? Hit.ImpactPoint : TraceEnd;
		DrawDebugLine(GetWorld(), CameraLocation, FinalTracePoint, FColor::Green, false, 5.0f);
		DrawDebugLine(GetWorld(), GetActorLocation(), FinalTracePoint, FColor::Purple, false, 5.0f);
		if (Hit.GetActor() && Hit.GetActor()->CanBeDamaged())
		{
			UGameplayStatics::ApplyDamage(Hit.GetActor(), WeaponDamage, nullptr, this, nullptr);
		}
		else
		{
			//Add decal
			UE_LOG(LogTemp, Display, TEXT("print decal"))
		}
	}
	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::Magenta, FString(TEXT("Shoot")));
	//UE_LOG(LogTemp, Display, TEXT("Shoot"))
	//иначе пистолет не начинает перезарядку после последнего выстрела
	if (CurrentAmmo <= 0)
	{
		StartReload();
	}
}

void AGP_RangeWeapon::CompleteReload()
{
	TotalAmmo += CurrentAmmo;
	if (TotalAmmo >= MaxAmmoInClip)
	{
		SetCurrentAmmo(MaxAmmoInClip);
		TotalAmmo -= CurrentAmmo;
	}
	else
	{
		SetCurrentAmmo(TotalAmmo);
		TotalAmmo = 0;
	}
	SetIsReload(false);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::Yellow, FString(TEXT("Complete Reload")));
}

bool AGP_RangeWeapon::CanReload() const
{
	if (TotalAmmo <= 0)
	{
		return false;
	}
	if (bIsReloading)
	{
		return false;
	}
	return true;
}

float AGP_RangeWeapon::GetReloadTime() const
{
	return ReloadTime;	
}

void AGP_RangeWeapon::SetIsReload(bool bIsReload)
{
	bIsReloading = bIsReload;
}

/*void AGP_RangeWeapon::StartReload()
{
	if (CanReload())
	{
		//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2, FColor::Blue, FString(TEXT("Start Reload")));
		UE_LOG(LogTemp, Display, TEXT("Start Reload"))
		bIsReloading = true;
		FTimerHandle ReloadTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &AGP_RangeWeapon::CompleteReload,ReloadTime, false);
	}
}*/

void AGP_RangeWeapon::OnPrimaryActionStarted()
{
}

void AGP_RangeWeapon::OnPrimaryActionFinished()
{
}

void AGP_RangeWeapon::SetCurrentAmmo(int NewCurrentAmmo)
{
	CurrentAmmo = FMath::Clamp(NewCurrentAmmo, 0, MaxAmmoInClip);
	OnChangeAmmo.Broadcast(CurrentAmmo, TotalAmmo);
}

// Called every frame
void AGP_RangeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGP_RangeWeapon::PromotePrimaryAction()
{
	if (CanAttack())
	{
		PromoteShoot();
	}
	else
	{
		StartReload();
	}
}


