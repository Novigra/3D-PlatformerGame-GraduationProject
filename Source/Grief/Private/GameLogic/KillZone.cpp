// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/KillZone.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/MotherRabbit/PlayerGameModeBase.h"
#include "Components/BoxComponent.h"
#include "UserInterface/GameplayHUDUI.h"
#include "Components/Image.h"

// Sets default values
AKillZone::AKillZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	DefaultSceneRoot->SetupAttachment(GetRootComponent());

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(DefaultSceneRoot);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AKillZone::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AKillZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKillZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKillZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		Player = Cast<AMotherRabbit>(OtherActor);
		if (Player)
		{
			UGameplayHUDUI* GameWidget = Player->GameplayHUDWidget;

			switch (Player->NumberOfLives)
			{
			case 3:
				Player->NumberOfLives--;
				GameWidget->Heart3->SetOpacity(0.0f);
				break;
			case 2:
				Player->NumberOfLives--;
				GameWidget->Heart2->SetOpacity(0.0f);
				break;
			case 1:
				if (APlayerController* PlayerController = Cast<APlayerController>(Player->GetController()))
				{
					UUserWidget* Widget = CreateWidget<UUserWidget>(PlayerController, LostUI);
					Widget->AddToViewport();
				}

				APlayerGameModeBase* GameMode = Player->GetPlayerGameMode();
				if (GameMode)
				{
					GameMode->LoadAllPlayerData();
				}
				Player->NumberOfLives = 3;
				GameWidget->Heart2->SetOpacity(0.0f);
				GameWidget->Heart3->SetOpacity(0.0f);
				break;
			}
		}
	}
}