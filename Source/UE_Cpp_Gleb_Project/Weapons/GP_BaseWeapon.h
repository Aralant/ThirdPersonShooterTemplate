// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UE_Cpp_Gleb_Project/Blueprints/GP_InteractableActor.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Interface/GP_WeaponInterface.h"
#include "UE_Cpp_Gleb_Project/GlobalResource/GlobalResource.h"
#include "GP_BaseWeapon.generated.h"

enum class EWeaponSlot : uint8;
class UInteractableSphereComponent;
class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponPickUp, AGP_BaseWeapon*, PickupedWeapon, EWeaponSlot, EquipedSlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponDrop, AGP_BaseWeapon*, DroppedWeapon, EWeaponSlot, EquipedSlot);

UCLASS()
class UE_CPP_GLEB_PROJECT_API AGP_BaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGP_BaseWeapon();

protected:
	UFUNCTION()
	void ShowChangeWidget(AActor* Interactor);
	
	UFUNCTION()
	void HiddenWeaponChangeWidget(AActor* Interactor);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UInteractableSphereComponent* WeaponPickUpComponent = nullptr;//для возможности подбора
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* WeaponMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FString WeaponName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UTexture2D* WeaponIcon = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	bool bIsPickedUp = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon characteristics")
	float WeaponDamage = 0.f;
	
	UPROPERTY(EditAnywhere, Category = "Weapon characteristics")
	float FireRate =  0.f;
	
	UPROPERTY(EditAnywhere, Category = "Weapon characteristics")
	bool bIsAutoFire =  false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon characteristics")
	UMaterialInterface* CanInteractMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon characteristics")
	UMaterialInterface* BaseMaterial;
	
	UPROPERTY()
	bool bIsReadyForNextAttack =  true;

	UPROPERTY()
	EWeaponSlot WeaponSlot = EWeaponSlot::None;

	UPROPERTY()
	AActor* CurrentOwner = nullptr;
	
	virtual void OnPrimaryActionStarted();
	virtual void OnPrimaryActionFinished();
	virtual void OnSecondaryActionStarted();
	virtual void OnSecondaryActionFinished();
	UFUNCTION()
	virtual void PromotePrimaryAction();
	
	UFUNCTION()
	virtual bool CanAttack() const;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void PrimaryAction(bool bIsStarted);
	
	UFUNCTION(BlueprintCallable)
	void SecondaryAction(bool bIsStarted);
	
	UFUNCTION(BlueprintCallable)
	void AttachToActor(AActor* Actor);

	UFUNCTION()
	void DropWeapon();
	
	UFUNCTION(BlueprintCallable)
	FString GetName(){return WeaponName;}

	UFUNCTION(BlueprintCallable)
	EWeaponSlot GetWeaponSlot() const {return WeaponSlot;};

	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetWeaponMesh(){return WeaponMesh;};
	
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetWeaponIcon(){return WeaponIcon;};
	
	UFUNCTION()
	void TryToAttach(AActor* InteractActor);

	UFUNCTION()
	void HideChangeWidget();
	
	UFUNCTION()
	void CanInteract(bool bCanInteract, AActor* Interactor);

	UFUNCTION()
	void SetWeaponSlot(EWeaponSlot NewSlot){WeaponSlot =  NewSlot;};
	
	FOnWeaponPickUp OnWeaponPickUp;

private:
	UFUNCTION()
	virtual void PrimaryActionInternal();
	FTimerHandle AutofireTimerHandle;
	virtual bool IsReadyForNextAttack();
};
