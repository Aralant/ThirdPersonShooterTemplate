// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GP_GameAlertSubsystem.generated.h"

UENUM (BlueprintType)
enum class EGP_AlertStatus_Enum : uint8
{
	None,
	Critical,
	Warning,
	Positive
};

USTRUCT(BlueprintType)
struct FGP_AlertStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alert")
	FText AlertText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alert")
	EGP_AlertStatus_Enum AlertStatus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alert")
	FName TextID;

};
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAlertAction);

UCLASS()
class UE_CPP_GLEB_PROJECT_API UGP_GameAlertSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
private:
	TArray<FGP_AlertStruct> Alerts;
public:
	UPROPERTY(BlueprintAssignable, Category = "Alert")
	FOnAlertAction OnAlertAdded;
	
	UFUNCTION(BlueprintCallable, Category = "Alert")
	bool GetFirstAlert(FGP_AlertStruct& Alert);

	UFUNCTION(BlueprintCallable, Category = "Alert")
	void AddAlert(const FGP_AlertStruct Alert);
};

