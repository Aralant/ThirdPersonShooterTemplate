// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_Chest.h"

#include "GPInventoryComponent.h"
#include "UI/GP_InventoryGridWidget.h"


// Sets default values
AGP_Chest::AGP_Chest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>("ChestMesh");
	//ChestMesh->SetMaterial(0, OpenedChestMaterial);
}

// Called when the game starts or when spawned
void AGP_Chest::BeginPlay()
{
	Super::BeginPlay();
	TArray<UGPInventoryComponent*> FoundComponents;
	GetComponents<UGPInventoryComponent>(FoundComponents);
	if (FoundComponents.Num() > 0)
	{
		InvComponent = FoundComponents[0];
	}
	if (InvComponent)
	{
		InvComponent->FillInventoryItemsObject();
	}
}

// Called every frame
void AGP_Chest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGP_Chest::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bIsCharacterOverlap = true;
	if (OverlapWidget)
	{
			OverlapWidget->AddToViewport();
			bIsCharacterOverlap = true;
	}
}

void AGP_Chest::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OverlapWidget)
	{
		ESlateVisibility OverlapWidgetVisibility = OverlapWidget->GetVisibility();
		if (OverlapWidgetVisibility == ESlateVisibility::Visible || OverlapWidgetVisibility == ESlateVisibility::SelfHitTestInvisible)
		{
			OverlapWidget->RemoveFromParent();
		}
	}
	bIsCharacterOverlap = false;
}



