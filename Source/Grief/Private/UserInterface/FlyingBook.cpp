// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/FlyingBook.h"
#include "Components/SkeletalMeshComponent.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/MotherRabbit/MyPlayerController.h" 
#include "UserInterface/PauseMenuUI.h"
#include "Kismet/GameplayStatics.h"
#include "Debug/Debug.h"

// Sets default values
AFlyingBook::AFlyingBook()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	DefaultSceneRoot->SetupAttachment(GetRootComponent());

	SkBook = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkBook->SetupAttachment(DefaultSceneRoot);

	bReachedDestVer = false;
	bReachedDestHor = false;
	bCanDelay = true;
	bStartTimer = true;
	bToggleWidgetSpawn = true;

	Delay = 0.8f;
	InterpSpeedHor = 130.0f;
	InterpSpeedVer = 100.0f;
	Temp = 0.0f;
	BookDistance = 0.0f;
	UISpawnDistance = 20.0f;
}

// Called when the game starts or when spawned
void AFlyingBook::BeginPlay()
{
	Super::BeginPlay();
	
	Player = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<AMotherRabbit>();

	if (OpenBookAnim)
		SkBook->PlayAnimation(OpenBookAnim, false);
}

// Called every frame
void AFlyingBook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Book movement
	BookInterpolation(DeltaTime);

	// Spawn Pause UI
	SpawnPauseUI();
}

void AFlyingBook::BookInterpolation(float DeltaTime)
{
	if (bReachedDestHor)
	{
		if (!bReachedDestVer)
		{
			if (bCanDelay)
			{
				Temp = DeltaTime;

				if (bStartTimer)
				{
					GetWorldTimerManager().SetTimer(TimerHandle, this, &AFlyingBook::DelayedInterpToPlayer, Delay, false);
					bStartTimer = false;
				}
			}
			else
			{
				InterpToTarget(DeltaTime, Player->CameraLocation, InterpSpeedVer);
			}

			if (GetActorLocation() == Player->CameraLocation)
			{
				bReachedDestVer = true;
				Player->bStopMovement = false;
				Player->bBookDestroyed = Destroy();
			}
		}
	}
	else
	{
		InterpToTarget(DeltaTime, Player->CameraFrontLocation, InterpSpeedHor);

		if (GetActorLocation() == Player->CameraFrontLocation)
			bReachedDestHor = true;
	}
}

void AFlyingBook::InterpToTarget(float DeltaTime, FVector Target, float InterpSpeed)
{
	FVector InterpLocation = FMath::VInterpConstantTo(GetActorLocation(), Target, DeltaTime, InterpSpeed);
	SetActorLocation(InterpLocation);
}

void AFlyingBook::DelayedInterpToPlayer()
{
	bCanDelay = false;

	FVector InterpLocation = FMath::VInterpConstantTo(GetActorLocation(), Player->CameraLocation, Temp, InterpSpeedVer);
	SetActorLocation(InterpLocation);

	if (GetActorLocation() == Player->CameraLocation)
		bReachedDestVer = true;
}

void AFlyingBook::SpawnPauseUI()
{
	if (bToggleWidgetSpawn)
	{
		BookDistance = FVector::Dist(Player->CameraLocation, GetActorLocation());
		//PrintScreen(5.0f, FColor::Red, "Distance between Player and the book: %f", BookDistance);
		if (BookDistance <= UISpawnDistance)
		{
			//PrintScreen(10.0f, FColor::Cyan, "Openning The Pause Menu!!!");
			if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
			{
				PlayerController->CurrentHUD = CreateWidget<UUserWidget>(PlayerController, PauseMenuUI);
				PlayerController->CurrentHUD->AddToViewport();
				PlayerController->SetInputMode(FInputModeGameAndUI());
				PlayerController->SetShowMouseCursor(true);
			}

			bToggleWidgetSpawn = false;
		}
	}
}