// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/Dish.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/NPC/NPC.h"
#include "UserInterface/GameplayHUDUI.h"
#include "Components/BoxComponent.h"

// Sets default values
ADish::ADish()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	DefaultSceneRoot->SetupAttachment(GetRootComponent());

	Dish = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Dish"));
	Dish->SetupAttachment(DefaultSceneRoot);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(DefaultSceneRoot);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ADish::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ADish::OnOverlapEnd);

	bCanInteract = true;
	MaxOfCookedDishes = 3;
}

// Called when the game starts or when spawned
void ADish::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADish::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		Player = Cast<AMotherRabbit>(OtherActor);
		if (Player && bCanInteract)
		{
			Player->SetInteractWidgetVisibility(true);
			Player->OnInteractAction.AddDynamic(this, &ADish::PlaceDish);
		}
	}
}

void ADish::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Player)
	{
		Player->SetInteractWidgetVisibility(false);
		Player->OnInteractAction.RemoveDynamic(this, &ADish::PlaceDish);
	}
}

void ADish::PlaceDish()
{
	if (Player->bCanPlaceDish)
	{
		Player->NumberOfCookedDishes++;
		if (Player->NumberOfCookedDishes == MaxOfCookedDishes)
		{
			if (ANPC* NPC = Cast<ANPC>(Player->CurrentInteractNPC))
			{
				NPC->NumberOfCompletedSubObjectives++;
				if (NPC->NumberOfCompletedSubObjectives == 2)
				{
					NPC->OnFinishObjective();
					NPC->SetObjectiveComplete(true);
					UGameplayHUDUI* GameWidget = Player->GameplayHUDWidget;
					GameWidget->OnFinishedObjective();
				}
			}
		}

		Dish->SetHiddenInGame(false);
		Player->bCanPlaceDish = false;
		Player->bCanCollect = true;
		//Player->NumberOfIngredients = 0;

		Player->SetInteractWidgetVisibility(false);
		Player->OnInteractAction.RemoveDynamic(this, &ADish::PlaceDish);
	}
}