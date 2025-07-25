﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_BaseWeapon.h"

#include "GP_RangeWeapon.h"
#include "Blueprint/UserWidget.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Component/InteractableSphereComponent.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/UI/GP_ChangeWeaponWidget.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/UI/GP_WeaponWidget.h"
#include "UE_Cpp_Gleb_Project/GameplayFramework/GP_ThirdPersonCharacter.h"


// Sets default values
AGP_BaseWeapon::AGP_BaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

	WeaponPickUpComponent = CreateDefaultSubobject<UInteractableSphereComponent>(TEXT("PickupSphere"));
	WeaponPickUpComponent->SetupAttachment(RootComponent);
	WeaponPickUpComponent->SetSphereRadius(100.f);
	WeaponPickUpComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}


void AGP_BaseWeapon::ShowChangeWidget(AActor* Interactor)
{
	if (Interactor && WeaponPickUpComponent->OverlapWidgetClass)
	{
		if (Cast<AGP_ThirdPersonCharacter>(Interactor))
		{
			AGP_ThirdPersonCharacter* PlayerCharacter = Cast<AGP_ThirdPersonCharacter>(Interactor);
			UGP_ChangeWeaponWidget* ChangeWidget = CreateWidget<UGP_ChangeWeaponWidget>(GetWorld(), WeaponPickUpComponent->OverlapWidgetClass);
			if (PlayerCharacter->GetCurrentWeapon())
			{
				ChangeWidget->WeaponInHandWidget->Weapon = PlayerCharacter->GetCurrentWeapon();
				ChangeWidget->WeaponInHandWidget->SynchronizeProperties();
			}
			ChangeWidget->WeaponOnWorldWidget->Weapon = this;
			ChangeWidget->WeaponOnWorldWidget->SynchronizeProperties();
			ChangeWidget->AddToViewport();
			WeaponPickUpComponent->OverlapWidget = ChangeWidget;
		}
	}
}

void AGP_BaseWeapon::HiddenWeaponChangeWidget(AActor* Interactor)
{
	if (WeaponPickUpComponent->OverlapWidget)
	{
		WeaponPickUpComponent->OverlapWidget->RemoveFromParent();
		WeaponPickUpComponent->OverlapWidget = nullptr;
	}
}

// Called when the game starts or when spawned
void AGP_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	WeaponPickUpComponent->OnHovered.AddDynamic(this, &AGP_BaseWeapon::ShowChangeWidget);
	WeaponPickUpComponent->OnUnhovered.AddDynamic(this, &AGP_BaseWeapon::HiddenWeaponChangeWidget);
	WeaponPickUpComponent->OnInteractAction.AddDynamic(this, &AGP_BaseWeapon::TryToAttach);
}

void AGP_BaseWeapon::OnPrimaryActionStarted()
{
}

void AGP_BaseWeapon::OnPrimaryActionFinished()
{
}

void AGP_BaseWeapon::OnSecondaryActionStarted()
{
}

void AGP_BaseWeapon::OnSecondaryActionFinished()
{
}

void AGP_BaseWeapon::PromotePrimaryAction()
{
}

bool AGP_BaseWeapon::CanAttack() const
{
	return true;
}

// Called every frame
void AGP_BaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGP_BaseWeapon::PrimaryAction(bool bIsStarted)
{
	if (bIsStarted)
	{
		if (FireRate > 0.f)
		{
			GetWorld()->GetTimerManager().SetTimer(AutofireTimerHandle, this, &AGP_BaseWeapon::PrimaryActionInternal,FireRate, bIsAutoFire);
		}
		PrimaryActionInternal();
		OnPrimaryActionStarted();
	}
	else
	{
		if (AutofireTimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(AutofireTimerHandle);
		}
		OnPrimaryActionFinished();
	}
}

void AGP_BaseWeapon::SecondaryAction(bool bIsStarted)
{
	bIsStarted ? OnSecondaryActionStarted() : OnSecondaryActionFinished();
}

void AGP_BaseWeapon::AttachToActor(AActor* Actor)
{
	if (!Actor) return;

	IGP_WeaponInterface* WeaponUser = Cast<IGP_WeaponInterface>(Actor);
	if (WeaponUser)
	{
		WeaponUser->EquipWeapon(this);
		OnWeaponPickUp.Broadcast(this);
		WeaponPickUpComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WeaponMesh->SetSimulatePhysics(false);
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		UE_LOG(LogTemp, Warning, TEXT("Оружие подобрано"));
	}

}

void AGP_BaseWeapon::TryToAttach(AActor* InteractActor)
{
	if (CurrentOwner)
	{
		return;
	}
	if (InteractActor->Implements<UGP_WeaponInterface>())
	{
		//проверка, что можно приатачить(персонаж может воспользоваться, например достаточен уровень)
		//Вызов виджета о предложении смены оружия.
		CurrentOwner = InteractActor;
		AttachToActor(InteractActor);
	}
}

void AGP_BaseWeapon::PrimaryActionInternal()
{
	if (IsReadyForNextAttack())
	{
		PromotePrimaryAction();
		FTimerHandle ReadyForNextAttackTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(ReadyForNextAttackTimerHandle,[this](){bIsReadyForNextAttack = true;}, FireRate - 0.001f, false);
		bIsReadyForNextAttack = false;
	}
}

bool AGP_BaseWeapon::IsReadyForNextAttack()
{
	return bIsReadyForNextAttack && CanAttack();
}

