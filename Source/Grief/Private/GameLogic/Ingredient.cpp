// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/Ingredient.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/NPC/NPC.h"
#include "Components/BoxComponent.h"
#include "Debug/Debug.h"

// Sets default values
AIngredient::AIngredient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	DefaultSceneRoot->SetupAttachment(GetRootComponent());

	Ingredient = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Ingredient"));
	Ingredient->SetupAttachment(DefaultSceneRoot);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(DefaultSceneRoot);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AIngredient::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AIngredient::OnOverlapEnd);

	IngredientNameWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("IngredientNameWidget"));
	IngredientNameWidget->SetupAttachment(DefaultSceneRoot);


}

// Called when the game starts or when spawned
void AIngredient::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIngredient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIngredient::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		Player = Cast<AMotherRabbit>(OtherActor);
		if (Player)
		{
			Player->SetInteractWidgetVisibility(true);
			Player->OnInteractAction.AddDynamic(this, &AIngredient::CollectIndgredient);
		}
	}
}

void AIngredient::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Player)
	{
		Player->SetInteractWidgetVisibility(false);
		Player->OnInteractAction.RemoveDynamic(this, &AIngredient::CollectIndgredient);
	}
}

void AIngredient::CollectIndgredient()
{
	if (!(Player->NumberOfIngredients == InventoryCapacity))
	{
		FPlayerItemStruct PlayerItem;
		PlayerItem.ItemName = IngredientName;
		PlayerItem.ItemType = "Ingredient";
		PlayerItem.bOwnItem = true;

		Player->PlayerItem.Add(PlayerItem);
		Player->NumberOfIngredients++;
		Player->OnPickingItemEvent();
	}
}