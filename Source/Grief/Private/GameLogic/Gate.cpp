// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/Gate.h"
#include "Components/BoxComponent.h"
#include "Characters/MotherRabbit/MotherRabbit.h"

// Sets default values
AGate::AGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	DefaultSceneRoot->SetupAttachment(GetRootComponent());

	EnterBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("EnterBoxCollision"));
	EnterBoxCollision->SetupAttachment(DefaultSceneRoot);

	EnterBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AGate::OnEnterOverlapBegin);
	EnterBoxCollision->OnComponentEndOverlap.AddDynamic(this, &AGate::OnEnterOverlapEnd);

	LeaveBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LeaveBoxCollision"));
	LeaveBoxCollision->SetupAttachment(DefaultSceneRoot);

	LeaveBoxCollision->OnComponentEndOverlap.AddDynamic(this, &AGate::OnLeaveOverlapEnd);

	InterpTargetBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InterpTargetBoxCollision"));
	InterpTargetBoxCollision->SetupAttachment(DefaultSceneRoot);

	GateDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_GateDoor"));
	GateDoor->SetupAttachment(DefaultSceneRoot);

	bCanInteract = true;
	bCanInterp = false;
	bMoveUp = true;
	InterpTolerance = 0.01f;
}

// Called when the game starts or when spawned
void AGate::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalGateLocation = GateDoor->GetComponentLocation();
}

// Called every frame
void AGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanInterp)
	{
		MoveGate(DeltaTime);
	}
}

void AGate::OnEnterOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		Player = Cast<AMotherRabbit>(OtherActor);
		if (Player)
		{
			if (Player->CollectedKeys[DoorLLevel] && bCanInteract)
			{
				Player->SetInteractWidgetVisibility(true);
				Player->OnInteractAction.AddDynamic(this, &AGate::OpenGate);
			}
		}
	}
}

void AGate::OnEnterOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Player)
	{
		Player->SetInteractWidgetVisibility(false);
		Player->OnInteractAction.RemoveDynamic(this, &AGate::OpenGate);
	}
}

void AGate::OnLeaveOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bCanInterp = true;
}

void AGate::OpenGate()
{
	bCanInterp = true;
	bCanInteract = false;

	Player->SetInteractWidgetVisibility(false);
	Player->OnInteractAction.RemoveDynamic(this, &AGate::OpenGate);
}

void AGate::MoveGate(float DeltaTime)
{
	if (bMoveUp)
	{
		FVector CurrentLocation = FMath::VInterpConstantTo(GateDoor->GetComponentLocation(), InterpTargetBoxCollision->GetComponentLocation(), DeltaTime, InterpSpeed);
		GateDoor->SetWorldLocation(CurrentLocation);
		if (GateDoor->GetComponentLocation().Equals(InterpTargetBoxCollision->GetComponentLocation(), InterpTolerance))
		{
			bCanInterp = false;
			bMoveUp = false;
		}
	}
	else
	{
		FVector CurrentLocation = FMath::VInterpConstantTo(GateDoor->GetComponentLocation(), OriginalGateLocation, DeltaTime, InterpSpeed);
		GateDoor->SetWorldLocation(CurrentLocation);
		if (GateDoor->GetComponentLocation().Equals(OriginalGateLocation, InterpTolerance))
		{
			bCanInterp = false;
		}
	}
}