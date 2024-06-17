// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/Fish/Fish.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Debug/Debug.h"

// Sets default values
AFish::AFish()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	DefaultSceneRoot->SetupAttachment(GetRootComponent());

	FishStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	FishStaticMesh->SetupAttachment(DefaultSceneRoot);

	FishSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	FishSkeletalMesh->SetupAttachment(DefaultSceneRoot);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(DefaultSceneRoot);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AFish::OnOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AFish::OnOverlapEnd);

	FishLocationMarkerWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("MarkerWidget"));
	FishLocationMarkerWidget->SetupAttachment(DefaultSceneRoot);
	FishLocationMarkerWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

// Called when the game starts or when spawned
void AFish::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFish::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		Player = Cast<AMotherRabbit>(OtherActor);
		if (Player)
		{
			PrintScreen(true, 2.0f, FColor::Green, "Actor %s Entered the collision", *Player->GetFName().ToString());
			Player->ObjectiveActor = this;
			Player->SetInteractWidgetVisibility(true);
			Player->OnInteractAction.AddDynamic(this, &AFish::StartFishingMinigame);
		}
	}
}

void AFish::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Player)
	{
		PrintScreen(true, 2.0f, FColor::Green, "Actor %s Exited the collision", *Player->GetFName().ToString());
		Player->ObjectiveActor = nullptr;
		Player->SetInteractWidgetVisibility(false);
		Player->OnInteractAction.RemoveAll(this);
	}
}

void AFish::StartFishingMinigame()
{
	Player->RemovePlayerAllMappingContexts();
	Player->SetPlayerMappingContext(Player->FishingMappingContext, 0);
	FishLocationMarkerWidget->SetHiddenInGame(true);

	APlayerController* PlayerController = Cast<APlayerController>(Player->GetController());
	if (PlayerController)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(PlayerController, FishMiniGameUI);
		Widget->AddToViewport();
	}

	Player->SetInteractWidgetVisibility(false);
}