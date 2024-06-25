// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Child.generated.h"

UCLASS()
class GRIEF_API AChild : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChild();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChildProperties")
	class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	TSubclassOf<class UUserWidget> CatchMessageUI;

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
	void CatchActor();

	UFUNCTION()
	void DestroySubActor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
