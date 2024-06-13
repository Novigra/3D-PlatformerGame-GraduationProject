// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/NPC.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "Debug/Debug.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(GetRootComponent());

	DialogueCameraPlacementArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DialogueCameraPlacementArrow"));
	DialogueCameraPlacementArrow->SetupAttachment(GetRootComponent());

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ANPC::OnOverlapEnd);

	bStartCameraTransition = false;
	CameraTransitionSpeed = 2.0f;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CameraTransition(DeltaTime);
}

void ANPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		Player = Cast<AMotherRabbit>(OtherActor);
		if (Player)
		{
			PrintScreen(true, 2.0f, FColor::Green, "Actor %s Entered the collision", *Player->GetFName().ToString());
			Player->CurrentInteractNPC = this;
			Player->SetInteractWidgetVisibility(true);
			Player->OnInteractAction.AddDynamic(this, &ANPC::StartDialogue);
		}
	}
}

void ANPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Player)
	{
		PrintScreen(true, 2.0f, FColor::Green, "Actor %s Exited the collision", *Player->GetFName().ToString());
		Player->CurrentInteractNPC = nullptr;
		Player->SetInteractWidgetVisibility(false);
		//Player->OnInteractAction.RemoveAll(this);
	}
}

void ANPC::StartDialogue()
{
	bStartCameraTransition = true;
}

void ANPC::CameraTransition(float DeltaTime)
{
	if (bStartCameraTransition)
	{
		FTransform PlayerCamera = Player->GetPlayerCameraTransform();
		FTransform CameraPlacement = DialogueCameraPlacementArrow->GetComponentTransform();

		FVector CurrentCameraLocation = FMath::VInterpTo(PlayerCamera.GetLocation(), CameraPlacement.GetLocation(), DeltaTime, CameraTransitionSpeed);
		// TO DO: Calculate the rotation of CurrentCamera and then add it to transform, then set it to the player camera
		// Don't forget that you have the initiate state, then the original state
		// Also don't forget to save the original location and rotation (transform, also there's scale but it will always be the same) of the player camera for the original state
	}
}