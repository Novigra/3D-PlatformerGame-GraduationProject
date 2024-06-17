// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/CatchActorSite.h"
#include "Components/BoxComponent.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "UserInterface/GameplayHUDUI.h"
#include "Debug/Debug.h"

// Sets default values
ACatchActorSite::ACatchActorSite()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(GetRootComponent());

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACatchActorSite::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ACatchActorSite::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ACatchActorSite::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACatchActorSite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACatchActorSite::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		Player = Cast<AMotherRabbit>(OtherActor);
		if (Player)
		{
			Player->SetPlayerMappingContext(Player->CatchActorMappingContext, 1);
			PrintScreen(true, 2.0f, FColor::Green, "IMC has been set");

			Player->OnDestroyAction.AddDynamic(this, &ACatchActorSite::DestroyActor);
		}
	}
}

void ACatchActorSite::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Player)
	{
		Player->RemovePlayerMappingContext(Player->CatchActorMappingContext);
	}
}

void ACatchActorSite::DestroyActor()
{
	if (Player)
	{
		Player->RemovePlayerMappingContext(Player->CatchActorMappingContext);
		UGameplayHUDUI* GameWidget = Player->GameplayHUDWidget;
		GameWidget->OnFinishedObjective();
	}

	Destroy();
}