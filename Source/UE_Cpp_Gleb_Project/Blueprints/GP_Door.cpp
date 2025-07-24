// Fill out your copyright notice in the Description page of Project Settings.


#include "GP_Door.h"

#include "Components/BoxComponent.h"


AGP_Door::AGP_Door()
{
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	DoorPivot = CreateDefaultSubobject<USceneComponent>(TEXT("DoorPivot"));
	DoorPivot->SetupAttachment(RootScene);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(DoorPivot);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootScene);
	TriggerBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->SetGenerateOverlapEvents(true);
}

void AGP_Door::BeginPlay()
{
	Super::BeginPlay();

	ClosedRotation = DoorPivot->GetRelativeRotation();
	OpenRotation = ClosedRotation + FRotator(0.f, OpenAngle, 0.f);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AGP_Door::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AGP_Door::OnOverlapEnd);
	
	bIsOpening = false;
	CurrentTime = 0.f;

	// Пример: запускаем сразу
	//StartOpen();
}

void AGP_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Alpha = FMath::Clamp<float>(Alpha + (1/OpenningTime)*DeltaTime * (bIsOpening ? 1 : -1), 0.f, 1.f);
	FRotator NewRotation = FMath::Lerp(ClosedRotation, OpenRotation, Alpha);
	DoorPivot->SetRelativeRotation(NewRotation);
}

bool AGP_Door::bNeedOpenDoor(AActor* Actor)
{
	FVector ActorToDoor = Actor->GetActorLocation() - GetActorLocation();
	FVector ActorForwardVector = Actor->GetActorForwardVector();
	FVector DoorRightVector = GetActorForwardVector();
	float DotProduct = FVector::DotProduct(ActorToDoor, DoorRightVector);
	if (DotProduct > 0.f)
	{
		return true;
	}
	return false;
}

void AGP_Door::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (bNeedOpenDoor(OtherActor))
		{
			StartOpen();
		}
	}
}

void AGP_Door::StartOpen()
{
	bIsOpening = true;
}

void AGP_Door::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		bIsOpening = false;
	}
}

