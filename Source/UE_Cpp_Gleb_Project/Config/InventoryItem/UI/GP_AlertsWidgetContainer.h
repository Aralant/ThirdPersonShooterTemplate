// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GP_AlertWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "UE_Cpp_Gleb_Project/Subsystems/GP_GameAlertSubsystem.h"
#include "GP_AlertsWidgetContainer.generated.h"

/**
 * 
 */


UCLASS()
class UE_CPP_GLEB_PROJECT_API UGP_AlertsWidgetContainer : public UUserWidget
{
	GENERATED_BODY()
protected:

	TObjectPtr<UGP_GameAlertSubsystem> GameAlertSubsystem;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGP_AlertWidget> AlertWidgetClass;

	UPROPERTY(EditAnywhere)
	int AlertsAmount = 3;

	UPROPERTY(meta = (bindWidget))
	UVerticalBox* AlertsWidgetVB;

	UFUNCTION(BlueprintCallable)
	void OnAlertCompleted(UGP_AlertWidget* AlertWidget);
	
	void CreateAlertWidget(const FGP_AlertStruct AlertData);

	UFUNCTION()
	void UpdateAlerts();
	
	virtual void NativeOnInitialized() override;	
};
