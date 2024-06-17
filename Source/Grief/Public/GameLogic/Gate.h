// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gate.generated.h"

UCLASS()
class GRIEF_API AGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGate();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GateProperties")
	class USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GateProperties")
	class UBoxComponent* EnterBoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GateProperties")
	class UBoxComponent* LeaveBoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GateProperties")
	class UBoxComponent* InterpTargetBoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GateProperties")
	class UStaticMeshComponent* GateDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GateProperties")
	FVector OriginalGateLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GateProperties")
	int32 DoorLLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GateProperties")
	bool bCanInteract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GateProperties")
	bool bMoveUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GateProperties")
	float InterpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GateProperties")
	bool bCanInterp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GateProperties")
	float InterpTolerance;

	UPROPERTY()
	class AMotherRabbit* Player;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnEnterOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEnterOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void OnLeaveOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OpenGate();

	UFUNCTION()
	void MoveGate(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
