// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MotherRabbit.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPressingNavigationAction, float, ActionValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPressingEnterAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPressingBackAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPressingClosingAction);

USTRUCT(BlueprintType)
struct FPlayerItemStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDetails")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDetails")
	bool bOwnItem;
};

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|UserInterface")
	class UInputAction* PauseAction;

	UPROPERTY(BlueprintAssignable)
	FOnPressingNavigationAction OnPressingNavigationAction;

	UPROPERTY(BlueprintAssignable)
	FOnPressingEnterAction OnPressingEnterAction;

	UPROPERTY(BlueprintAssignable)
	FOnPressingBackAction OnPressingBackAction;

	UPROPERTY(BlueprintAssignable)
	FOnPressingClosingAction OnPressingClosingAction;

	/*
	* BookOpenning (UI)
	*/

	// Book that you need to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|BookMechanics(UI)")
	TSubclassOf<class AFlyingBook> FlyingBook;

	// Rabbit texture used in The book (It is an actor that has 3d model in it and we need to spawn it)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|BookMechanics(UI)")
	TSubclassOf<class AActor> RabbitHeadTex;

	// Current location of the "CameraFront"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|BookMechanics(UI)")
	FVector CameraFrontLocation;

	// Current camera location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|BookMechanics(UI)")
	FVector CameraLocation;

	// Indicate how far the point is from the Camera(Front)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|BookMechanics(UI)")
	float CameraFront;

	// Indicate how far the point is from the Camera(Right)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|BookMechanics(UI)")
	float CameraRight;

	// Stop the movement of the player and camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|BookMechanics(UI)")
	bool bStopMovement;

	// Check if the book got destroyed (Despawned), so We can open the Pause Menu Interface
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|BookMechanics(UI)")
	bool bBookDestroyed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay|BookMechanics(UI)")
	float ElapsedTime;

	/*
	* Player Inventory
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Inventory")
	int32 CollectedMaps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Inventory")
	int32 CollectedKeys;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Inventory")
	int32 CollectedCoins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Inventory")
	TArray<FPlayerItemStruct> PlayerItem;

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
	void CloseInput(const FInputActionValue& Value);
	void Navigation(const FInputActionValue& Value);
	void PauseGame(const FInputActionValue& Value);

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

	FORCEINLINE void SetCollectedCoins(int32 Coins) { CollectedCoins = Coins; }
	FORCEINLINE int32 GetCollectedCoins() { return CollectedCoins; }
};
