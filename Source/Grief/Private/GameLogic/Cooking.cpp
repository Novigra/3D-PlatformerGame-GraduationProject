// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/Cooking.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/NPC/NPC.h"
#include "UserInterface/GameplayHUDUI.h"
#include "Components/BoxComponent.h"
#include "UserInterface/CookingTimerWidget.h"
#include "UserInterface/NumberOfIngredients.h"


// Sets default values
ACooking::ACooking()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	DefaultSceneRoot->SetupAttachment(GetRootComponent());

	Pot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_GateDoor"));
	Pot->SetupAttachment(DefaultSceneRoot);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(DefaultSceneRoot);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACooking::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ACooking::OnOverlapEnd);

	CookingTimerWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("CookingTimerWidget"));
	CookingTimerWidget->SetupAttachment(DefaultSceneRoot);

	NumberOfIngredientsWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("NumberOfIngredientsWidget"));
	NumberOfIngredientsWidget->SetupAttachment(DefaultSceneRoot);

	bStartTimer = false;
	CookingTimerStart = 5.0f;
	CookingTimer = CookingTimerStart;
	CookingTimerSpeedRate = 1.0f;

	SetupOnce = true;
	Index = 0;
}

// Called when the game starts or when spawned
void ACooking::BeginPlay()
{
	Super::BeginPlay();
	
	SetupTimerWidget();
}

// Called every frame
void ACooking::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStartTimer && TimerWidget && (CookingTimer >= 0.0f))
		TimerWidget->SetTimerText(static_cast<int>(CookingTimer -= (CookingTimerSpeedRate * DeltaTime)));
}

void ACooking::SetupTimerWidget()
{
	if (CookingTimerWidget)
	{
		UUserWidget* Widget = CookingTimerWidget->GetWidget();
		if (Widget)
		{
			TimerWidget = Cast<UCookingTimerWidget>(Widget);
			if (TimerWidget)
				TimerWidget->SetTimerText(static_cast<int>(CookingTimer));
			CookingTimerWidget->SetHiddenInGame(true);
		}
	}

	NumberOfIngredientsWidget->SetHiddenInGame(true);
}

void ACooking::SetupNumberOfIngredientsWidgets()
{
	if (NumberOfIngredientsWidget)
	{
		UUserWidget* Widget = NumberOfIngredientsWidget->GetWidget();
		if (Widget)
		{
			NumberWidget = Cast<UNumberOfIngredients>(Widget);
			if (NumberWidget)
				NumberWidget->SetNumberText(Player->NumberOfIngredients);
			NumberOfIngredientsWidget->SetHiddenInGame(true);

			SetupOnce = false;
		}
	}
}

void ACooking::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		Player = Cast<AMotherRabbit>(OtherActor);
		if (Player)
		{
			if (SetupOnce)
				SetupNumberOfIngredientsWidgets();

			Player->SetInteractWidgetVisibility(true);

			if (NumberWidget)
				NumberWidget->SetNumberText(Player->NumberOfIngredients);
			NumberOfIngredientsWidget->SetHiddenInGame(false);

			if (CookingTimer > 0.0f)
			{
				Player->OnInteractAction.AddDynamic(this, &ACooking::PlaceIngredient);
			}
			else
			{
				Player->OnInteractAction.AddDynamic(this, &ACooking::CollectDish);
			}
		}
	}
}

void ACooking::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Player)
	{
		Player->SetInteractWidgetVisibility(false);
		NumberOfIngredientsWidget->SetHiddenInGame(true);

		Player->OnInteractAction.RemoveDynamic(this, &ACooking::PlaceIngredient);
		Player->OnInteractAction.RemoveDynamic(this, &ACooking::CollectDish);
	}
}

void ACooking::PlaceIngredient()
{
	int32 Length = Player->PlayerItem.Num();
	for (int32 I = Length - 1; I >= 0; --I)
	{
		if (Player->PlayerItem[I].ItemType.Equals("Ingredient"))
		{
			Index++;
			Player->PlayerItem.RemoveAt(I);

			if (Index == 3)
			{
				bStartTimer = true;
				CookingTimerWidget->SetHiddenInGame(false);

				Player->NumberOfIngredients = 0;
				if (NumberWidget)
					NumberWidget->SetNumberText(Player->NumberOfIngredients);
				Index = 0;
				return;
			}
		}
	}
}

void ACooking::CollectDish()
{
	Player->bCanPlaceDish = true;
	bStartTimer = false;
	CookingTimerWidget->SetHiddenInGame(true);
	CookingTimer = CookingTimerStart;
	Player->SetInteractWidgetVisibility(false);
	Player->OnInteractAction.RemoveDynamic(this, &ACooking::CollectDish);
}
