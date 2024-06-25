// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/Ring.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/NPC/NPC.h"
#include "UserInterface/GameplayHUDUI.h"
#include "Components/SphereComponent.h"
#include "Debug/Debug.h"

// Sets default values
ARing::ARing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	DefaultSceneRoot->SetupAttachment(GetRootComponent());

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(DefaultSceneRoot);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ARing::OnOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ARing::OnOverlapEnd);

	Ring = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Ring"));
	Ring->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void ARing::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator ActorCurrentRotation = GetActorRotation();
	SetActorRotation(FRotator(ActorCurrentRotation.Pitch, ActorCurrentRotation.Yaw + (DeltaTime * RotationSpeed), ActorCurrentRotation.Roll));
}

void ARing::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		Player = Cast<AMotherRabbit>(OtherActor);
		if (Player)
		{
			Player->SetInteractWidgetVisibility(true);
			Player->OnInteractAction.AddDynamic(this, &ARing::CollectRing);
			PrintScreen(false, 2.0f, FColor::Green, "Testing...");
		}
	}
}

void ARing::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Player)
	{
		Player->SetInteractWidgetVisibility(false);
		Player->OnInteractAction.RemoveDynamic(this, &ARing::CollectRing);
	}
}

void ARing::CollectRing()
{
	APlayerController* PlayerController = Cast<APlayerController>(Player->GetController());
	if (PlayerController)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(PlayerController, RingMessageUI);
		Widget->AddToViewport();
	}

	if (ANPC* NPC = Cast<ANPC>(Player->CurrentInteractNPC))
	{
		NPC->OnFinishObjective();
		NPC->SetObjectiveComplete(true);
	}

	UGameplayHUDUI* GameWidget = Player->GameplayHUDWidget;
	GameWidget->OnFinishedObjective();

	Destroy();
}