// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/FlyingBook.h"
#include "Debug/Debug.h"


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

	// Character Movement Setup
	GetCharacterMovement()->bNotifyApex = false;
	GetCharacterMovement()->AirControl = 1.0f;
	LaunchCharacterVelocity = 800.0f;
	JumpCounter = 1;
	ApexJumpTimerDelay = 0.25f;
	VectorRotation = 45.0f;
	VectorEndPoint = 7.0f;
	MaxWallTilt = 0.2f;
	WallRunSpeed = 850.0f;
	WallRunGravityTarget = 0.25f;
	InterpSpeed = 30.0f;
	WallJumpForce = 400.0f;
	Force = FVector(0.0f);
	WallJumpRotation = 45.0f;
	InitialWallRunVelocity = 300.0f;
	bIsWallRunning = false;
	bStopWallRunning = false;
	bFirstContact = true;

	// Book - (UI)
	CameraLocation = FVector(0.0f);
	CameraFrontLocation = FVector(0.0f);
	CameraFront = 70.0f;
	CameraRight = 140.0f;
	bStopMovement = false;
	bBookDestroyed = false;

	// Inventory
	CollectedMaps = 0;
	CollectedKeys = 0;
	CollectedCoins = 192;

#ifdef UE_BUILD_DEBUG

	CameraBoom->bDrawDebugLagMarkers = true;

#endif // UE_BUILD_DEBUG


}

// Called when the game starts or when spawned
void AMotherRabbit::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			// Note: Player may or may not exist in the game, so managing controls will be moved to a player controller class later on!
			Subsystem->AddMappingContext(UserInterfaceMappingContext, 0);
		}
	}

	CurrentLevel = GetWorld();
}

// Called every frame
void AMotherRabbit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	WallRunning(DeltaTime);
}

// Called to bind functionality to input
void AMotherRabbit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Use CastChecked so when casting fails, crash the game
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked< UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(EnterAction, ETriggerEvent::Started, this, &AMotherRabbit::EnterInput);
		EnhancedInputComponent->BindAction(BackAction, ETriggerEvent::Canceled, this, &AMotherRabbit::BackInput);
		EnhancedInputComponent->BindAction(BackAction, ETriggerEvent::Triggered, this, &AMotherRabbit::CloseInput);
		EnhancedInputComponent->BindAction(NavigationAction, ETriggerEvent::Started, this, &AMotherRabbit::Navigation);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AMotherRabbit::PauseGame);

		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMotherRabbit::Movement);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMotherRabbit::Jumping);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMotherRabbit::Look);
	}
}

void AMotherRabbit::EnterInput(const FInputActionValue& Value)
{
	const bool bActionValue = Value.Get<bool>();

	if (Controller && bActionValue)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("You pressed Enter!!!"));
		OnPressingEnterAction.Broadcast();
	}
}

void AMotherRabbit::BackInput(const FInputActionValue& Value)
{
	const bool bActionValue = Value.Get<bool>();

	if (Controller && !(bActionValue))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("You pressed Back!!!"));
		OnPressingBackAction.Broadcast();
	}
}

void AMotherRabbit::CloseInput(const FInputActionValue& Value)
{
	const bool bActionValue = Value.Get<bool>();

	if (Controller && bActionValue)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("You pressed Close!!!"));
		OnPressingClosingAction.Broadcast();
	}
}

void AMotherRabbit::Navigation(const FInputActionValue& Value)
{
	const float ActionValue = Value.Get<float>();

	if (Controller && (ActionValue != 0.0f))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Current Navigation (Action Value) = %f"), ActionValue));
		OnPressingNavigationAction.Broadcast(ActionValue);
	}
}

void AMotherRabbit::PauseGame(const FInputActionValue& Value)
{
	const bool bActionValue = Value.Get<bool>();

	if (Controller && bActionValue)
	{
		bStopMovement = true;

		if (APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
		{
			APlayerCameraManager* PlayerCamera = PlayerController->PlayerCameraManager;

			CameraFrontLocation = PlayerCamera->GetCameraLocation() + (PlayerCamera->GetActorForwardVector() * CameraFront);
			CameraLocation = PlayerCamera->GetCameraLocation();

			FVector BookSpawnLocation = CameraFrontLocation + (PlayerCamera->GetActorRightVector() * CameraRight);
			FRotator BookSpawnRotation = PlayerCamera->GetCameraRotation();

			AFlyingBook* Book = CurrentLevel->SpawnActor<AFlyingBook>(FlyingBook, BookSpawnLocation, BookSpawnRotation);
			AActor* RabbitHead = CurrentLevel->SpawnActor<AActor>(RabbitHeadTex, FVector(0.0f, 0.0f, -10000.0f), FRotator(0.0f));

			RemovePlayerMappingContext(MovementMappingContext);
			SetPlayerMappingContext(UserInterfaceMappingContext, 0);
		}	
	}
}

void AMotherRabbit::Movement(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();

	if (Controller && !bStopMovement && (MovementValue != FVector2D(0.0f)))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, MovementValue.Y);
		
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, MovementValue.X);		
	}
}

void AMotherRabbit::Jumping(const FInputActionValue& Value)
{
	const bool bJumpValue = Value.Get<bool>();

	if (bJumpValue == true && !bStopMovement)
	{
		ACharacter::Jump();
		GetCharacterMovement()->GravityScale = 1.0f;
		GetCharacterMovement()->bNotifyApex = true;

		if ((GetCharacterMovement()->IsFalling() == true) && (JumpCounter > 0) && (bIsWallRunning == false))
		{
			LaunchCharacter(FVector(FVector2D(0.0f), LaunchCharacterVelocity), false, false);
			JumpCounter--;
			
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AMotherRabbit::ChangeJumpGravity, 0.1f, false, ApexJumpTimerDelay);
		}
		else if (bIsWallRunning == true)
		{
			bStopWallRunning = true;

			Force *= WallJumpForce;
			LaunchCharacter(Force, false, false);

			bIsWallRunning = false;
		}
	}
}

void AMotherRabbit::NotifyJumpApex()
{
	Super::NotifyJumpApex();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Reached my apex"));
	if (GetCharacterMovement()->bNotifyApex == false)
	{
		GetCharacterMovement()->GravityScale = 2.0f;
	}
}

void AMotherRabbit::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	JumpCounter = 1;
	
	bIsWallRunning = false;
	bStopWallRunning = false;
	bFirstContact = true;
}

void AMotherRabbit::ChangeJumpGravity()
{
	GetCharacterMovement()->GravityScale = 2.0f;
}

void AMotherRabbit::WallRunning(float DeltaTime)
{
	if (CurrentLevel)
	{
		FVector CurrentMovement = GetCharacterMovement()->Velocity;
		FVector RightVector = UKismetMathLibrary::RotateAngleAxis(FVector(CurrentMovement.X, CurrentMovement.Y, 0.0f), VectorRotation, FVector(FVector2D(0.0f), 1.0f));
		FVector LeftVector = UKismetMathLibrary::RotateAngleAxis(FVector(CurrentMovement.X, CurrentMovement.Y, 0.0f), -VectorRotation, FVector(FVector2D(0.0f), 1.0f));

		FVector CurrentActorLocation = GetActorLocation();

		FHitResult HitResult;
		FHitResult RightHitResult;
		FHitResult LeftHitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(GetOwner());

		// Right ray cast
		FVector RightVectorEndPoint = RightVector / VectorEndPoint;
		FVector RightEndPoint = CurrentActorLocation + RightVectorEndPoint;
		CurrentLevel->LineTraceSingleByChannel(RightHitResult, CurrentActorLocation, RightEndPoint, ECollisionChannel::ECC_Visibility, QueryParams);

		DrawDebugLine(CurrentLevel, CurrentActorLocation, RightEndPoint, RightHitResult.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 2.0f);

		// Left ray cast
		FVector LeftVectorEndPoint = LeftVector / VectorEndPoint;
		FVector LeftEndPoint = CurrentActorLocation + LeftVectorEndPoint;
		CurrentLevel->LineTraceSingleByChannel(LeftHitResult, CurrentActorLocation, LeftEndPoint, ECollisionChannel::ECC_Visibility, QueryParams);

		DrawDebugLine(CurrentLevel, CurrentActorLocation, LeftEndPoint, LeftHitResult.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 2.0f);

		if ((LeftHitResult.bBlockingHit || RightHitResult.bBlockingHit) && GetCharacterMovement()->IsFalling() && (bStopWallRunning == false))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("WallRun!!!"));
			bIsWallRunning = true;
			FVector NormalVector;

			if (RightHitResult.bBlockingHit)
			{
				NormalVector = RightHitResult.Normal;
			}
			else if (LeftHitResult.bBlockingHit)
			{
				NormalVector = LeftHitResult.Normal;
			}

			bool bCanRun = FMath::IsWithinInclusive(NormalVector.Z, -MaxWallTilt, MaxWallTilt);
			if (bCanRun)
			{
				if (bFirstContact)
				{
					FVector CurrentVelocity = GetCharacterMovement()->Velocity;
					GetCharacterMovement()->Velocity = FVector(FVector2D(CurrentVelocity), InitialWallRunVelocity);

					bFirstContact = false;
				}

				FVector WallForce = (CurrentActorLocation - NormalVector).Length() * NormalVector;
				LaunchCharacter(WallForce, false, false);

				FVector WallRunVelocity;
				if (RightHitResult.bBlockingHit)
					WallRunVelocity = FVector::CrossProduct(NormalVector, FVector(FVector2D(0.0f), 1.0f)) * -WallRunSpeed;
				else if (LeftHitResult.bBlockingHit)
					WallRunVelocity = FVector::CrossProduct(NormalVector, FVector(FVector2D(0.0f), 1.0f)) * WallRunSpeed;
				
				LaunchCharacter(WallRunVelocity, true, false);

				float CurrentGravity = GetCharacterMovement()->GravityScale;
				GetCharacterMovement()->GravityScale = FMath::FInterpTo(CurrentGravity, WallRunGravityTarget, DeltaTime, InterpSpeed);

				Force.X = NormalVector.X;
				Force.Y = NormalVector.Y;
				Force.Z = 1.0f;
			}
		}
	}
}

void AMotherRabbit::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller && !bStopMovement)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void AMotherRabbit::SetPlayerMappingContext(class UInputMappingContext* InputMappingContext, int32 Priority)
{
	Subsystem->AddMappingContext(InputMappingContext, Priority);
}

void AMotherRabbit::RemovePlayerMappingContext(class UInputMappingContext* InputMappingContext)
{
	Subsystem->RemoveMappingContext(InputMappingContext);
}

void AMotherRabbit::RemovePlayerAllMappingContexts()
{
	Subsystem->ClearAllMappings();
}