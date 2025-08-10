// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractorSphereComponent.h"

#include "InteractableSphereComponent.h"
#include "Chaos/Utilities.h"
#include "UE_Cpp_Gleb_Project/Blueprints/GP_InteractableActor.h"
#include "UE_Cpp_Gleb_Project/Config/InventoryItem/Interface/GP_Interact.h"


// Sets default values for this component's properties
UInteractorSphereComponent::UInteractorSphereComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UInteractorSphereComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this, &UInteractorSphereComponent::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UInteractorSphereComponent::OnOverlapEnd);
	
	// ...
	
}

FVector UInteractorSphereComponent::GetControllerForwardVector()
{
	AActor* Owner = GetOwner();
	if (Owner)
	{
		APawn* Pawn = Cast<APawn>(Owner);
		if (Pawn)
		{
			APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
			if (PC)
			{
				return PC->GetControlRotation().Vector();
			}
		}
	}
	return FVector::ZeroVector;
}


void UInteractorSphereComponent::GetNearestInteractItem(
	TArray<UPrimitiveComponent*> InteractableActorComponents)
{
	float NearestVectorToView = 0.5f;
	for (auto& Component : InteractableActorComponents)
	{
		AActor* ComponentOwner = Component->GetOwner();
		if (ComponentOwner)
		{
			FVector InteractableActorLocation = ComponentOwner->GetActorLocation();
			FVector PlayerLocation = GetOwner()->GetActorLocation();
			FVector PlayerToInteractableActor = (InteractableActorLocation - PlayerLocation).GetSafeNormal();
			FVector PCForwardVector = GetControllerForwardVector().GetSafeNormal();
			float ViewAngle = FVector::DotProduct(PlayerToInteractableActor, PCForwardVector);
			if (ViewAngle > NearestVectorToView)
			{
				NearestVectorToView = ViewAngle;
				NewNearestActor = ComponentOwner;
				NewInteractableSphereComp =  Component;
			}
		}
	}
}

void UInteractorSphereComponent::CheckInteractableObjectNearCharacter()
{
	
	if (GetControllerForwardVector().Length() > 0.0f)
	{
		TArray<UPrimitiveComponent*> OverlappingComps;
		//TArray<UInteractableSphereComponent*> InteractableActorOverlappingComps;
		TArray<UPrimitiveComponent*> InteractableActorOverlappingComps;
		GetOverlappingComponents(OverlappingComps);
		for (auto& OverlappingComp : OverlappingComps)
		{
			UInteractableSphereComponent* InteractableSphereComp = Cast<UInteractableSphereComponent>(OverlappingComp);
			if (OverlappingComp->Implements<UGP_Interact>())
			{
				InteractableActorOverlappingComps.AddUnique(InteractableSphereComp);
			}
		/*	if (InteractableSphereComp)
			{
				InteractableActorOverlappingComps.AddUnique(InteractableSphereComp);
			}*/
		}
		GetNearestInteractItem(InteractableActorOverlappingComps);
		
		if (CurrentInteractableSphereComp)
		{
			if (NewInteractableSphereComp && CurrentInteractableSphereComp != NewInteractableSphereComp)
			{
				if (NewInteractableSphereComp->Implements<UGP_Interact>() && CurrentInteractableSphereComp->Implements<UGP_Interact>())
				{
					IGP_Interact::Execute_OnCanInteract(CurrentInteractableSphereComp, false);
					CurrentInteractableSphereComp = NewInteractableSphereComp;
					IGP_Interact::Execute_OnCanInteract(CurrentInteractableSphereComp, true);
					NewInteractableSphereComp = nullptr;
				}
				
			}
		}
		else
		{
			if (NewInteractableSphereComp && CurrentInteractableSphereComp != NewInteractableSphereComp)
			{
				if (NewInteractableSphereComp->Implements<UGP_Interact>())
				{
					CurrentInteractableSphereComp =  NewInteractableSphereComp;
					IGP_Interact::Execute_OnCanInteract(NewInteractableSphereComp, true);
					NewInteractableSphereComp = nullptr;
				}
				
			}
		}
		//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Green, TEXT(""));
	}
}


// Called every frame
void UInteractorSphereComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckInteractableObjectNearCharacter();

	// ...
}

void UInteractorSphereComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherComp)
	{
		if (OtherComp != HoveredComponent)
		{
			if (HoverComponent(OtherComp))
			{
				UnhoverComponent(HoveredComponent);
				HoveredComponent = OtherComp;
			}
		}
	}
}

void UInteractorSphereComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp == HoveredComponent)
	{
		UnhoverComponent(HoveredComponent);
		HoveredComponent = nullptr;
	}
}

bool UInteractorSphereComponent::Interact()
{
	
	if (HoveredComponent && HoveredComponent->Implements<UGP_Interact>())
	{
		IGP_Interact::Execute_OnInteract(HoveredComponent, GetOwner());
		return true;
	}
	return false;
}

bool UInteractorSphereComponent::HoverComponent(UActorComponent* ComponentForHover)
{
	
	if (ComponentForHover)
	{
		bool bIsInterfaceImpl = ComponentForHover->Implements<UGP_Interact>();
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("%d; %s"), bIsInterfaceImpl ? 1 : 0, *ComponentForHover->GetName()));
		if (ComponentForHover->Implements<UGP_Interact>())
		{
			return IGP_Interact::Execute_OnHovered(ComponentForHover, GetOwner());
		}
	}
	return false;
}

void UInteractorSphereComponent::UnhoverComponent(UActorComponent* ComponentForUnhover)
{
	if (ComponentForUnhover && ComponentForUnhover->Implements<UGP_Interact>())
	{
		IGP_Interact::Execute_OnUnhovered(ComponentForUnhover, GetOwner());
	}
}

