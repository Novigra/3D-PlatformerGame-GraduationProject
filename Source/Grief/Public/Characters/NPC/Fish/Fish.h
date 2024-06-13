// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fish.generated.h"

UCLASS()
class GRIEF_API AFish : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFish();

	UPROPERTY()
	class USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FishProperties")
	class UStaticMeshComponent* FishStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FishProperties")
	class USkeletalMeshComponent* FishSkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FishProperties")
	class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FishProperties")
	class UWidgetComponent* FishLocationMarkerWidget;

	UPROPERTY()
	class AMotherRabbit* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|UserInterface")
	TSubclassOf<class UUserWidget> FishMiniGameUI;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void StartFishingMinigame();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
