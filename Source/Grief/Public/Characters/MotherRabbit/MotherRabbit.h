// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MotherRabbit.generated.h"


UCLASS()
class GRIEF_API AMotherRabbit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMotherRabbit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Placeholder)
	class UStaticMeshComponent* PlaceholderStaticMesh;


	// Camera Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;


	// Player Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* RabbitMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* LookAction;

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


	void Movement(const FInputActionValue& Value);

	void Jumping(const FInputActionValue& Value);
	virtual void NotifyJumpApex() override;
	virtual void Landed(const FHitResult& Hit) override;
	void ChangeJumpGravity();

	void Look(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
