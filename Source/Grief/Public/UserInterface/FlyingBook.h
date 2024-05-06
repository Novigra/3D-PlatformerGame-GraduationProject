// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlyingBook.generated.h"

UCLASS()
class GRIEF_API AFlyingBook : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlyingBook();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Book)
	class AMotherRabbit* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Book)
	class USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Book)
	class USkeletalMeshComponent* SkBook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Book)
	UAnimationAsset* OpenBookAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Book)
	bool bReachedDestVer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Book)
	bool bReachedDestHor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Book)
	bool bCanDelay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Book)
	bool bStartTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Book)
	bool bToggleWidgetSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Book)
	float Delay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Book)
	float InterpSpeedVer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Book)
	float InterpSpeedHor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Book)
	float BookDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Book)
	float UISpawnDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Book)
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Book)
	TSubclassOf<class UUserWidget> PauseMenuUI;

	float Temp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void BookInterpolation(float DeltaTime);
	void InterpToTarget(float DeltaTime, FVector Target, float InterpSpeed);
	void DelayedInterpToPlayer();
	void SpawnPauseUI();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
