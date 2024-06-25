// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/NPC.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Components/ArrowComponent.h"
#include "Debug/Debug.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(GetRootComponent());

	PlayerResetPlacement = CreateDefaultSubobject<USphereComponent>(TEXT("PlayerResetPlacement"));
	PlayerResetPlacement->SetupAttachment(GetRootComponent());

	DialogueCameraPlacementArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DialogueCameraPlacementArrow"));
	DialogueCameraPlacementArrow->SetupAttachment(GetRootComponent());

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ANPC::OnOverlapEnd);

	bStartCameraTransition = false;
	bStartReverseCameraTransition = false;
	bCanInteract = true;
	bIsObjectiveComplete = false;
	bSpawnSubActor = true;
	CameraTransitionSpeed = 2.0f;
	NumberOfCompletedSubObjectives = 0;
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
		if (Player && bCanInteract)
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
		//Player->CurrentInteractNPC = nullptr;
		Player->SetInteractWidgetVisibility(false);
		Player->OnInteractAction.RemoveAll(this);
	}
}

void ANPC::StartDialogue()
{
	bStartCameraTransition = true;
	Player->CurrentInteractNPC = this;

	Player->RemovePlayerAllMappingContexts();
	Player->SetPlayerMappingContext(Player->DialogueMappingContext, 0);

	APlayerController* PlayerController = Cast<APlayerController>(Player->GetController());
	if (PlayerController)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(PlayerController, DialogueMenuUI);
		Widget->AddToViewport();
	}

	Player->SetInteractWidgetVisibility(false);
}

void ANPC::CameraTransition(float DeltaTime)
{
	if (bStartCameraTransition)
	{
		FTransform PlayerCamera = Player->GetPlayerCameraTransform();
		FTransform CameraPlacement = DialogueCameraPlacementArrow->GetComponentTransform();

		FVector CurrentCameraLocation = FMath::VInterpTo(PlayerCamera.GetLocation(), CameraPlacement.GetLocation(), DeltaTime, CameraTransitionSpeed);
		FQuat CurrentCameraRotation = FMath::QInterpTo(PlayerCamera.GetRotation(), CameraPlacement.GetRotation(), DeltaTime, CameraTransitionSpeed);

		FTransform Transition;
		Transition.SetLocation(CurrentCameraLocation);
		Transition.SetRotation(CurrentCameraRotation);
		Transition.SetScale3D(FVector(1.0f));

		Player->SetPlayerCameraTransform(Transition);

		PrintScreen(false, 2.0f, FColor::Green, "CurrentCameraLocation = %f X : %f Y : %f Z", CurrentCameraLocation.X, CurrentCameraLocation.Y, CurrentCameraLocation.Y);
	}
}

void ANPC::OnFinishDialogue()
{
	Player->OnInteractAction.RemoveDynamic(this, &ANPC::StartDialogue);
}

void ANPC::OnFinishObjective()
{
	bCanInteract = true;
	PrintScreen(false, 5.0f, FColor::Green, "Will add NPC interact delegate");
}