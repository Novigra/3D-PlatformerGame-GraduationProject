// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"

// Sets default values
AMotherRabbit::AMotherRabbit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlaceholderStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaceholderStaticMesh"));
	PlaceholderStaticMesh->SetupAttachment(GetRootComponent());

	// Camera Properties
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->bUsePawnControlRotation = true; // Rotate the spring arm

	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = false;
	CameraBoom->CameraLagSpeed = 10.0f;
	CameraBoom->CameraLagMaxDistance = 0.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // Don't need the camera to rotate

	// Fixed the rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

#ifdef UE_BUILD_DEBUG

	CameraBoom->bDrawDebugLagMarkers = true;

#endif // UE_BUILD_DEBUG


}

// Called when the game starts or when spawned
void AMotherRabbit::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(RabbitMappingContext, 0);
		}
	}
}

// Called every frame
void AMotherRabbit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMotherRabbit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Use CastChecked so when casting fails, crash the game
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked< UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMotherRabbit::Movement);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMotherRabbit::Look);
	}
}

void AMotherRabbit::Movement(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();

	if (Controller && (MovementValue != FVector2D(0.0f)))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, MovementValue.Y);
		
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, MovementValue.X);		
	}
}

void AMotherRabbit::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}