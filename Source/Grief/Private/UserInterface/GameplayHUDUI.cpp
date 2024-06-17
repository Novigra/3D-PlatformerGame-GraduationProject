// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/GameplayHUDUI.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/NPC/NPC.h"
#include "Components/TextBlock.h"

UGameplayHUDUI::UGameplayHUDUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bStartTimer = false;
	TimerRate = 1.0f;
}

void UGameplayHUDUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (bStartTimer)
	{
		CurrentTimer -= (TimerRate * InDeltaTime);
		Timer->SetText(FText::AsNumber(static_cast<int>(CurrentTimer)));
	}
}

void UGameplayHUDUI::OnFinishedObjective()
{
	bStartTimer = false;
	OnFinishedObjectiveEvent();

	Player->NumberOfLives = 3;
}