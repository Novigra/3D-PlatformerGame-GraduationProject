// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MotherRabbit.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPressingNavigationAction, float, ActionValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPressingEnterAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPressingBackAction);

UCLASS()
class GRIEF_API AMotherRabbit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMotherRabbit();

	// Player Input
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Input|InputLocalPlayerSubsystem")
	class UEnhancedInputLocalPlayerSubsystem* Subsystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|InputMappingContext")
	class UInputMappingContext* MovementMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|InputMappingContext")
	class UInputMappingContext* UserInterfaceMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Movement")
	class UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Movement")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Movement")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|UserInterface")
	class UInputAction* EnterAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|UserInterface")
	class UInputAction* BackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|UserInterface")
	class UInputAction* NavigationAction;

	UPROPERTY(BlueprintAssignable)
	FOnPressingNavigationAction OnPressingNavigationAction;

	UPROPERTY(BlueprintAssignable)
	FOnPressingEnterAction OnPressingEnterAction;

	UPROPERTY(BlueprintAssignable)
	FOnPressingBackAction OnPressingBackAction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Placeholder)
	class UStaticMeshComponent* PlaceholderStaticMesh;

	UPROPERTY()
	UWorld* CurrentLevel;


	// Camera Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	// Gameplay Functionalities

	// Determine how far to launch the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float LaunchCharacterVelocity;

	// Determine how many time you can launch the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 JumpCounter;

	// Used to determine how long can the character stay in the air after the launch (Second Jump)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float ApexJumpTimerDelay;

	// Right and left rotation for the ray cast to define when the player can start running on the wall
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|WallRunningMechanics")
	float VectorRotation;

	// Determine the end point of the ray cast, basically the length of the vector
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|WallRunningMechanics")
	float VectorEndPoint;

	// Rotation on the z component that allows the player to start wall running
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|WallRunningMechanics")
	float MaxWallTilt;

	// How fast can the player wall-running
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|WallRunningMechanics")
	float WallRunSpeed;

	// Determine the gravity force that will affect the player during wall running
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|WallRunningMechanics")
	float WallRunGravityTarget;

	// Determine how fast the gravity scale will change
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|WallRunningMechanics")
	float InterpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|WallRunningMechanics")
	float WallJumpForce;

	FVector Force;

	// Rotation of the wall jump force
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|WallRunningMechanics")
	float WallJumpRotation;

	// Initial Velocity when starting running on the wall (Velocity Z component)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|WallRunningMechanics")
	float InitialWallRunVelocity;

	bool bIsWallRunning;
	bool bStopWallRunning;
	bool bFirstContact;

	/*
	* Player Input
	*/

	// Input Action - UI
	void EnterInput(const FInputActionValue& Value);
	void BackInput(const FInputActionValue& Value);
	void Navigation(const FInputActionValue& Value);

	// Input Action - Movement
	void Movement(const FInputActionValue& Value);
	void Jumping(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	/*
	* Game Logic
	*/

	virtual void NotifyJumpApex() override;
	virtual void Landed(const FHitResult& Hit) override;
	void ChangeJumpGravity();

	void WallRunning(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetPlayerMappingContext(class UInputMappingContext* InputMappingContext, int32 Priority);
	void RemovePlayerMappingContext(class UInputMappingContext* InputMappingContext);
	void RemovePlayerAllMappingContexts();
};
