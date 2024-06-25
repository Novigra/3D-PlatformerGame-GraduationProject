// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CatchActorSite.generated.h"

UCLASS()
class GRIEF_API ACatchActorSite : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACatchActorSite();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChildProperties")
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	class ANPC* AssociatedNPC;

	UPROPERTY()
	class AMotherRabbit* Player;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void DestroyActor();

	UFUNCTION()
	void DestroySubActor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
