// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "UE_Cpp_Gleb_Project/GlobalResource/GlobalResource.h"
#include "GP_InventoryFilterButton.generated.h"

class UTextBlock;
class UGP_InventoryFilterButton;
enum class EInventoryType : uint8;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTypeSelected, UGP_InventoryFilterButton*, FilterButton);

UCLASS()
class UE_CPP_GLEB_PROJECT_API UGP_InventoryFilterButton : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	UButton* FilterButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	EInventoryType ButtonFilterType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	UTextBlock* ButtonName;
	UPROPERTY(BlueprintAssignable)
	FOnTypeSelected ButtonClickedDelegate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FButtonStyle SelectedButtonStyle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FButtonStyle UnselectedButtonStyle;
	UFUNCTION()
	void SetButtonStyle(bool bIsSelected);
protected:
	UFUNCTION()
	void ButtonClicked();
	virtual void NativeConstruct() override;
};
