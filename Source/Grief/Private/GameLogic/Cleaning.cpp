// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/Cleaning.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/NPC/NPC.h"
#include "UserInterface/GameplayHUDUI.h"
#include "Components/BoxComponent.h"

// Sets default values
ACleaning::ACleaning()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	DefaultSceneRoot->SetupAttachment(GetRootComponent());

	Broom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Broom"));
	Broom->SetupAttachment(DefaultSceneRoot);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(DefaultSceneRoot);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACleaning::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ACleaning::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ACleaning::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACleaning::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACleaning::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		Player = Cast<AMotherRabbit>(OtherActor);
		if (Player)
		{
			Player->SetInteractWidgetVisibility(true);
			Player->OnInteractAction.AddDynamic(this, &ACleaning::CollectBroom);
		}
	}
}

void ACleaning::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Player)
	{
		Player->SetInteractWidgetVisibility(false);
		Player->OnInteractAction.RemoveDynamic(this, &ACleaning::CollectBroom);
	}
}

void ACleaning::CollectBroom()
{
	Player->bCollectedBroom = true;
	Destroy();
}