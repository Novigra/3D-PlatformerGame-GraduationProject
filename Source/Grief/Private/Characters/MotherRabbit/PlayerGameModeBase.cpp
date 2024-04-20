// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MotherRabbit/PlayerGameModeBase.h"

APlayerGameModeBase::APlayerGameModeBase()
{

}

void APlayerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentGameModeBase = this;
}
