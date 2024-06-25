// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "SaveLocalPlayerGame.generated.h"

USTRUCT(BlueprintType)
struct FPlayerOwnedItemStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDetails")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDetails")
	FString ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDetails")
	bool bOwnItem;
};

UCLASS()
class GRIEF_API USaveLocalPlayerGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	USaveLocalPlayerGame();

	UPROPERTY(VisibleAnywhere, Category = "Game|Player")
	FTransform PlayerPosition;

	UPROPERTY(VisibleAnywhere, Category = "Game|Player")
	float Timer;

	UPROPERTY(VisibleAnywhere, Category = "Game|Player")
	int32 Coins;

	UPROPERTY(VisibleAnywhere, Category = "Game|Player")
	int32 NumberOfLives;

	UPROPERTY(VisibleAnywhere, Category = "Game|Player")
	TArray<FPlayerOwnedItemStruct> PlayerOwnedItems;

	UPROPERTY(VisibleAnywhere, Category = "Game|Player")
	TArray<bool> CollectedMaps;

	UPROPERTY(VisibleAnywhere, Category = "Game|Player")
	TArray<bool> CollectedKeys;

	UPROPERTY(VisibleAnywhere, Category = "Game|NPC")
	class AActor* LastMetNPC;

	UPROPERTY(VisibleAnywhere, Category = "Game|NPC")
	int32 DialogueIndex;

	UPROPERTY(VisibleAnywhere, Category = "Game|NPC")
	bool bStartConversation;

	UPROPERTY(VisibleAnywhere, Category = "Game|NPC")
	bool bCanInteract;

	UPROPERTY(VisibleAnywhere, Category = "Game|NPC")
	bool bIsObjectiveComplete;

	UPROPERTY(VisibleAnywhere, Category = "Game|NPC")
	bool bSpawnSubActor;
};
