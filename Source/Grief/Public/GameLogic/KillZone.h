// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillZone.generated.h"

UCLASS()
class GRIEF_API AKillZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKillZone();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "KillZoneProperties")
	class USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "KillZoneProperties")
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KillZoneProperties")
	TSubclassOf<class UUserWidget> LostUI;

	UPROPERTY()
	class AMotherRabbit* Player;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
