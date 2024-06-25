// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ingredient.generated.h"

UCLASS()
class GRIEF_API AIngredient : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIngredient();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IngredientProperties")
	class USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IngredientProperties")
	FString IngredientName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IngredientProperties")
	class UStaticMeshComponent* Ingredient;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IngredientProperties")
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IngredientProperties")
	class UWidgetComponent* IngredientNameWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IngredientProperties")
	int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IngredientProperties")
	int32 InventoryCapacity;

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
	void CollectIndgredient();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
