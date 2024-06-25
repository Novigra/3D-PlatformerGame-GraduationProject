// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestroyActors);

class USaveLocalPlayerGame;

UCLASS()
class GRIEF_API APlayerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	APlayerGameModeBase();

	UPROPERTY()
	class AMotherRabbit* Player;

	/*
	* Save every data
	* @param SaveDataType : Choose whether you save the data synchronously (0) or asynchronously (1)
	*/
	UFUNCTION(BlueprintCallable)
	void SaveAllPlayerData(int32 SaveDataType);
	void LoadAllPlayerData();
	void TestCalling();

	UPROPERTY(BlueprintAssignable)
	FOnDestroyActors OnDestroyActors;

protected:
	virtual void BeginPlay() override;

	USaveLocalPlayerGame* GetSaveGame();

	void LoadData(const FString& SaveSlotName, const int32 UserIndex, class USaveGame* LoadGame);
	void SaveResult(const FString& SaveSlotName, const int32 UserIndex, bool bSuccess);
};
