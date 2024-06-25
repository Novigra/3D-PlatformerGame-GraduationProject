// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/Child.h"
#include "Characters/NPC/NPC.h"
#include "Components/SphereComponent.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/MotherRabbit/PlayerGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Debug/Debug.h"

// Sets default values
AChild::AChild()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(GetRootComponent());

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AChild::OnOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AChild::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AChild::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerGameModeBase* GameMode = Cast<APlayerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->OnDestroyActors.AddDynamic(this, &AChild::DestroySubActor);
	}
}

// Called every frame
void AChild::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChild::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		Player = Cast<AMotherRabbit>(OtherActor);
		if (Player)
		{
			PrintScreen(true, 2.0f, FColor::Green, "Player is in");
			Player->OnCatchAction.AddDynamic(this, &AChild::CatchActor);
		}
	}
}

void AChild::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Player)
	{
		Player->OnCatchAction.RemoveDynamic(this, &AChild::CatchActor);
	}
}

void AChild::CatchActor()
{
	PrintScreen(true, 2.0f, FColor::Green, "Yay, you got the kid!!!");
	APlayerController* PlayerController = Cast<APlayerController>(Player->GetController());
	if (PlayerController)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(PlayerController, CatchMessageUI);
		Widget->AddToViewport();
	}

	if (Player)
	{
		Player->OnDestroyAction.Broadcast();
	}

	if (ANPC* NPC = Cast<ANPC>(Player->CurrentInteractNPC))
	{
		NPC->SetSpawnSubActor(false);
		NPC->OnFinishObjective();
		NPC->SetObjectiveComplete(true);
	}

	Destroy();
}

void AChild::DestroySubActor()
{
	if (AssociatedNPC)
	{
		if (!AssociatedNPC->GetSpawnSubActor())
		{
			Destroy();
		}
	}
}