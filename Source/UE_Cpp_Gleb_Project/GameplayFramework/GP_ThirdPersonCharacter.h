// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Interface/GP_Interact.h"
#include "UE_Cpp_Gleb_Project/Weapons/GP_BaseWeapon.h"
#include "GP_ThirdPersonCharacter.generated.h"

enum class EWeaponSlot : uint8;

UCLASS()
class UE_CPP_GLEB_PROJECT_API AGP_ThirdPersonCharacter : public ACharacter, public IGP_Interact, public IGP_WeaponInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGP_ThirdPersonCharacter();

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PlayerInventoryWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> SwapWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> TradeWidgetClass;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UUserWidget* PlayerInventoryWidget = nullptr;

	UPROPERTY(EditAnywhere)
	AGP_BaseWeapon* CurrentWeapon = nullptr;
	
	UPROPERTY(EditAnywhere)
	AGP_BaseWeapon* PrimaryWeapon = nullptr;
	
	UPROPERTY(EditAnywhere)
	AGP_BaseWeapon* SecondWeapon = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AGP_BaseWeapon* MeleeWeapon = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<EWeaponSlot, bool> WeaponSlotMap;
	
	UPROPERTY()
	bool bIsKnifeInHand = false;

public:
		
	UFUNCTION(BlueprintCallable)
	void SwitchWeapon(AGP_BaseWeapon* NewWeapon);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool OnInteract_Implementation(AActor* InteractBy);
	/*bool OnHovered_Implementation(AActor* HoveredBy){return false;};
	bool OnUnhovered_Implementation(AActor* UnhoveredBy){return false;};*/

	bool InteractWithInventory(AActor* InteractActor);

	UFUNCTION(BlueprintPure)
	AGP_BaseWeapon* GetCurrentWeapon() const {return CurrentWeapon;};
	
	UFUNCTION(BlueprintPure)
	AGP_BaseWeapon* GetPrimaryWeapon() const {return PrimaryWeapon;};

	UFUNCTION(BlueprintPure)
	AGP_BaseWeapon* GetSecondaryWeapon() const {return SecondWeapon;};

	UFUNCTION()
	void SetCurrentWeapon(AGP_BaseWeapon* NewWeapon){CurrentWeapon = NewWeapon;};
	
	UFUNCTION()
	void SetPrimaryWeapon(AGP_BaseWeapon* NewWeapon){PrimaryWeapon = NewWeapon;};

	UFUNCTION()
	void SetSecondWeapon(AGP_BaseWeapon* NewWeapon){SecondWeapon = NewWeapon;};

	UFUNCTION()
	void SetMeleeWeapon(AGP_BaseWeapon* NewWeapon){MeleeWeapon = NewWeapon;};

	UFUNCTION(BlueprintCallable)
	void TakeKnife();

	UFUNCTION(BlueprintCallable)
	void HideMeleeWeapon(AGP_BaseWeapon* Weapon);

	UFUNCTION(BlueprintCallable)
	EWeaponSlot GetEmptyWeaponSlot(AGP_BaseWeapon* Weapon);

	UFUNCTION(BlueprintCallable)
	void EquipRangeWeapon(AGP_BaseWeapon* Weapon, USkeletalMeshComponent* CharacterMesh);

	UFUNCTION(BlueprintCallable)
	void EquipMeleeWeapon(AGP_BaseWeapon* Weapon, USkeletalMeshComponent* CharacterMesh);
	virtual void EquipWeapon(AGP_BaseWeapon* Weapon) override;
};
