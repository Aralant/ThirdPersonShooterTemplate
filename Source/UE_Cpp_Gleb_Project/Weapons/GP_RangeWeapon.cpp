// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_RangeWeapon.h"

#include "HeadMountedDisplayTypes.h"
#include "Engine/StaticMeshSocket.h"
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

void AGP_RangeWeapon::InternalPromoteShoot()
{
	PromoteDamageTrace(SpreadAngle);
}

void AGP_RangeWeapon::PromoteShoot()
{
	SetCurrentAmmo(CurrentAmmo - 1);
	InternalPromoteShoot();
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

void AGP_RangeWeapon::PromoteDamageTrace(float SpreadAngleDegrees)
{
	AActor* Actor = GetOwner();
	FVector CameraLocation;
	FRotator CameraRotation;
	AController* Controller = CurrentOwner->GetInstigatorController();
	float SpreadAngleRad = FMath::DegreesToRadians(SpreadAngle);
	if (Controller)
	{
		Controller->GetPlayerViewPoint(CameraLocation, CameraRotation);
		FVector MuzzleLocation = GetWeaponMesh()->GetSocketLocation(FName("Muzzle"));
		FVector ShootDirection = FMath::VRandCone(CameraRotation.Vector(), SpreadAngleRad);
		FVector TraceEnd = CameraLocation + ShootDirection * 5000.0f;
		FHitResult Hit;
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.AddIgnoredActor(CurrentOwner);
		bool bHit = GetWorld()->LineTraceSingleByChannel(
			Hit, CameraLocation, TraceEnd, ECC_Visibility, TraceParams);
		FVector FinalTracePoint = bHit ? Hit.ImpactPoint : TraceEnd;
		DrawDebugLine(GetWorld(), CameraLocation, FinalTracePoint, FColor::Green, false, 1.0f);
		DrawDebugLine(GetWorld(), MuzzleLocation, FinalTracePoint, FColor::Purple, false, 1.0f);
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


