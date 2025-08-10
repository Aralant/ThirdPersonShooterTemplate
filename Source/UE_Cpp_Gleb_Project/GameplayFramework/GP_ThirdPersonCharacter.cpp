// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_ThirdPersonCharacter.h"

#include "GP_HUD.h"
#include "UE_Cpp_Gleb_ProjectPlayerController.h"
#include "Containers/Map.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Interface/GP_InteractableWidgetInterface.h"
#include "UE_Cpp_Gleb_Project/GlobalResource/GlobalResource.h"
#include "UE_Cpp_Gleb_Project/Weapons/GP_MeleeWeapon.h"


// Sets default values
AGP_ThirdPersonCharacter::AGP_ThirdPersonCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGP_ThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	WeaponSlotMap.Add(EWeaponSlot::Primary, false);
	WeaponSlotMap.Add(EWeaponSlot::Secondary, false);
	WeaponSlotMap.Add(EWeaponSlot::Melee, false);
}

// Called every frame
void AGP_ThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGP_ThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool AGP_ThirdPersonCharacter::OnInteract_Implementation(AActor* InteractBy)
{
	if (InteractBy->Implements<UGP_InteractableWidgetInterface>() && GetController()->Implements<UGP_Interact>())
	{
		return IGP_Interact::Execute_OnInteract(GetController(), InteractBy);
	}
	return false;
}

void AGP_ThirdPersonCharacter::SwitchWeapon(AGP_BaseWeapon* NewWeapon)
{
	AGP_BaseWeapon* SwapWeaponSlot = nullptr;
	USkeletalMeshComponent* CharacterMesh = GetMesh();
	if (SecondWeapon)
	{
		SecondWeapon->GetWeaponMesh()->SetVisibility(true);
	}
	if (CurrentWeapon != NewWeapon)
	{
		if (CurrentWeapon)
		{
			if (CurrentWeapon->GetWeaponSlot() == EWeaponSlot::Melee)
			{
				HideMeleeWeapon(CurrentWeapon);
			}
			else
			{
				{
					CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
					CurrentWeapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("SpineWeaponSocket"));
				}
			}
		}
		if (NewWeapon)
		{
			NewWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			NewWeapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponSocket"));
		}
		SetCurrentWeapon(NewWeapon);
	}
}

void AGP_ThirdPersonCharacter::TakeKnife()
{
	USkeletalMeshComponent* CharacterMesh = GetMesh();
	if (CurrentWeapon)
	{
		if (CurrentWeapon->GetWeaponSlot() != EWeaponSlot::Melee)
		{
			CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			CurrentWeapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("SpineWeaponSocket"));
			if (WeaponSlotMap[EWeaponSlot::Primary] && WeaponSlotMap[EWeaponSlot::Secondary])
			{
				SecondWeapon->GetWeaponMesh()->SetVisibility(false);	
			}
		}
	}
	if (WeaponSlotMap[EWeaponSlot::Melee])
	{
		MeleeWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		MeleeWeapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponSocket"));
		SetCurrentWeapon(MeleeWeapon);
	}
	
}

void AGP_ThirdPersonCharacter::HideMeleeWeapon(AGP_BaseWeapon* Weapon)
{
	USkeletalMeshComponent* CharacterMesh = GetMesh();
	if (MeleeWeapon)
	{
		MeleeWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}
	Weapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponKnifeSocket"));
	SetMeleeWeapon(Weapon);
}

EWeaponSlot AGP_ThirdPersonCharacter::GetEmptyWeaponSlot(AGP_BaseWeapon* Weapon)
{
	if (Weapon->ActorHasTag("RangeWeapon"))
	{
		if (WeaponSlotMap[EWeaponSlot::Primary] && WeaponSlotMap[EWeaponSlot::Secondary])
		{
			return EWeaponSlot::None;
		}
		if (WeaponSlotMap[EWeaponSlot::Primary] && !WeaponSlotMap[EWeaponSlot::Secondary])
		{
			return EWeaponSlot::Secondary;
		}
		if (!WeaponSlotMap[EWeaponSlot::Primary])
		{
			return EWeaponSlot::Primary;
		}
	}
	if (Weapon->ActorHasTag("MeleeWeapon"))
	{
		return EWeaponSlot::Melee;
	}
	return EWeaponSlot::None;
}

void AGP_ThirdPersonCharacter::EquipRangeWeapon(AGP_BaseWeapon* Weapon, USkeletalMeshComponent* CharacterMesh)
{
	EWeaponSlot EmptyWeaponSlot = GetEmptyWeaponSlot(Weapon);
	EWeaponSlot ChangedWeaponSlot;
	switch (EmptyWeaponSlot)
	{
	case EWeaponSlot::None:
		ChangedWeaponSlot = CurrentWeapon->GetWeaponSlot();
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentWeapon->DropWeapon();
		WeaponSlotMap[ChangedWeaponSlot] = false;
		//drop current Weapon()
		Weapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponSocket"));
		Weapon->SetWeaponSlot(ChangedWeaponSlot);
		switch (ChangedWeaponSlot)
		{
		case EWeaponSlot::Primary:
			SetPrimaryWeapon(Weapon);
			break;
		case EWeaponSlot::Secondary:
			SetSecondWeapon(Weapon);
			break;
		}
		SetCurrentWeapon(Weapon);
		WeaponSlotMap[ChangedWeaponSlot] = true;
		break;
	case EWeaponSlot::Primary:
		//Attach in hand
		Weapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponSocket"));
		Weapon->SetWeaponSlot(EWeaponSlot::Primary);
		SetPrimaryWeapon(Weapon);
		SetCurrentWeapon(Weapon);
		WeaponSlotMap[EWeaponSlot::Primary] = true;
		break;
	case EWeaponSlot::Secondary:
		//Attach to spine
		Weapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("SpineWeaponSocket"));
		Weapon->SetWeaponSlot(EWeaponSlot::Secondary);
		SetSecondWeapon(Weapon);
		WeaponSlotMap[EWeaponSlot::Secondary] = true;
		break;
	}
}

void AGP_ThirdPersonCharacter::EquipMeleeWeapon(AGP_BaseWeapon* Weapon, USkeletalMeshComponent* CharacterMesh)
{
	if (!WeaponSlotMap[EWeaponSlot::Melee])
	{
		Weapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponKnifeSocket"));
		Weapon->SetWeaponSlot(EWeaponSlot::Melee);
		SetMeleeWeapon(Weapon);
		WeaponSlotMap[EWeaponSlot::Melee] = true;
	}
	else
	{
		EWeaponSlot ChangedWeaponSlot = MeleeWeapon->GetWeaponSlot();
		MeleeWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		MeleeWeapon->DropWeapon();
		WeaponSlotMap[EWeaponSlot::Melee] = false;
		//drop current Weapon()
		Weapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponKnifeSocket"));
		Weapon->SetWeaponSlot(EWeaponSlot::Melee);
		SetMeleeWeapon(Weapon);
		WeaponSlotMap[EWeaponSlot::Melee] = true;
	}
}

void AGP_ThirdPersonCharacter::DropCurrentWeapon()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		WeaponSlotMap[CurrentWeapon->GetWeaponSlot()] =  false;
		CurrentWeapon->DropWeapon();
		CurrentWeapon = nullptr;
	}
}



void AGP_ThirdPersonCharacter::EquipWeapon(AGP_BaseWeapon* Weapon)
{
	if (Weapon)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			AUE_Cpp_Gleb_ProjectPlayerController* MyPC = Cast<AUE_Cpp_Gleb_ProjectPlayerController>(PC);
			if (MyPC)
			{
				AGP_HUD* GP_HUD = Cast<AGP_HUD>(MyPC->GetHUD());
				if (CurrentWeapon)
				{
					GP_HUD->BindToWeapon(Weapon, CurrentWeapon->GetWeaponSlot());
				}
				else
				{
					GP_HUD->BindToWeapon(Weapon, GetEmptyWeaponSlot(Weapon));
				}
				
			}
		}
		//SetWeapon(Weapon);
		USkeletalMeshComponent* CharacterMesh = GetMesh();
		if (CharacterMesh)
		{
			if (!Weapon->ActorHasTag("MeleeWeapon"))
			{
				if (WeaponSlotMap[EWeaponSlot::Melee] && CurrentWeapon == MeleeWeapon)
				{
					HideMeleeWeapon(CurrentWeapon);
				}
				EquipRangeWeapon(Weapon, CharacterMesh);
			}
			else
			{
				EquipMeleeWeapon(Weapon, CharacterMesh);
			}		
		}
	}
}

