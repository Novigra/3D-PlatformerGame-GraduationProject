// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cooking.generated.h"

UCLASS()
class GRIEF_API ACooking : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACooking();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CookProperties")
	class USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CookProperties")
	class UStaticMeshComponent* Pot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CookProperties")
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CookProperties")
	class UWidgetComponent* CookingTimerWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CookProperties")
	class UWidgetComponent* NumberOfIngredientsWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CookProperties")
	class UCookingTimerWidget* TimerWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CookProperties")
	class UNumberOfIngredients* NumberWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CookProperties")
	bool bStartTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CookProperties")
	float CookingTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CookProperties")
	float CookingTimerStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CookProperties")
	float CookingTimerSpeedRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CookProperties")
	int32 Index;

	UPROPERTY()
	bool SetupOnce;

	UPROPERTY()
	class AMotherRabbit* Player;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupTimerWidget();

	void SetupNumberOfIngredientsWidgets();

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void PlaceIngredient();

	UFUNCTION()
	void CollectDish();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
