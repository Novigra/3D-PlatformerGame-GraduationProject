// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerGameModeBase.generated.h"

UCLASS()
class GRIEF_API APlayerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	APlayerGameModeBase();

	UPROPERTY()
	class APlayerGameModeBase* CurrentGameModeBase;

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE APlayerGameModeBase* GetCurrentGameMode() { return CurrentGameModeBase; }
};
