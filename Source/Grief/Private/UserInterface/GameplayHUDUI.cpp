// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/GameplayHUDUI.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/MotherRabbit/PlayerGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/NPC/NPC.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

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
		if (CurrentTimer > 0)
		{
			CurrentTimer -= (TimerRate * InDeltaTime);
			Timer->SetText(FText::AsNumber(static_cast<int>(CurrentTimer)));
		}
		else
		{
			NPC = Cast<ANPC>(Player->CurrentInteractNPC);
			if (NPC)
			{
				if (APlayerController* PlayerController = Cast<APlayerController>(Player->GetController()))
				{
					UUserWidget* Widget = CreateWidget<UUserWidget>(PlayerController, FailureUI);
					Widget->AddToViewport();
				}

				FTransform ResetPlace = NPC->GetPlayerResetPlacement();
				Player->SetActorTransform(ResetPlace);
				bStartTimer = false;
				CurrentTimer = NPC->GetObjectiveTimer();
			}
		}
	}
}

void UGameplayHUDUI::OnFinishedObjective()
{
	bStartTimer = false;
	OnFinishedObjectiveEvent();

	Player->NumberOfLives = 3;
}