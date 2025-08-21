// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UE_Cpp_Gleb_Project/Subsystems/GP_GameAlertSubsystem.h"
#include "GP_AlertWidget.generated.h"

/**
 * 
 */


class UImage;
class UBorder;
class UTextBlock;

UCLASS()
class UE_CPP_GLEB_PROJECT_API UGP_AlertWidget : public UUserWidget
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAlertAction, UGP_AlertWidget*, AlertWidget);
	
protected:
	UPROPERTY()
	FGP_AlertStruct AlertData;

	UPROPERTY(EditAnywhere)
	float AlertLifeTime = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Alert")
	UTextBlock* AlertText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Alert")
	UImage* AlertIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Alert")
	UBorder* AlertBorder;

	UFUNCTION(BlueprintImplementableEvent, meta = (ForceAsFunction))
	void OnAlertInitialized();

	void UpdateAlertVisual();

	UFUNCTION(BlueprintImplementableEvent, meta = (ForceAsFunction))
	UTexture2D* GetIcon(EGP_AlertStatus_Enum AlertStatus);
	
	UFUNCTION(BlueprintCallable)
	void AlertCompleted();
	
	UFUNCTION(BlueprintImplementableEvent)
	void AlertCompletedAnimation();
public:

	UPROPERTY(BlueprintAssignable)
	FOnAlertAction OnAlertCompleted;

	
	void SetAlertData(const FGP_AlertStruct& InAlertData);
	
};
