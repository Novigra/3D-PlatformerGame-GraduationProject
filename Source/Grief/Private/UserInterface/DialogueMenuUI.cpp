// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/DialogueMenuUI.h"
#include "UserInterface/GameplayHUDUI.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/MotherRabbit/PlayerGameModeBase.h"
#include "Characters/NPC/NPC.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Debug/Debug.h"

UDialogueMenuUI::UDialogueMenuUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Index = 0;
}

void UDialogueMenuUI::NativeConstruct()
{
	Player = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<AMotherRabbit>();
	NPC = Cast<ANPC>(Player->GetCurrentNPC());

	if (Player)
	{
		Player->OnProceedAction.AddDynamic(this, &UDialogueMenuUI::NextDialogueText);
	}

	Index = NPC->GetDialogueIndex();

	Speaker->SetText(NPC->GetNameHeader(Index));
	Dialogue->SetText(NPC->GetDialogue(Index++));
}

void UDialogueMenuUI::NextDialogueText()
{
	PrintScreen(false, 2.0f, FColor::Green, "Test E Dialogue");

	if (!NPC->GetNameHeader(Index).IsEmpty())
	{
		Speaker->SetText(NPC->GetNameHeader(Index));
		Dialogue->SetText(NPC->GetDialogue(Index));

		Index++;
	}
	else
	{
		NPC->SetDialogueIndex(++Index);
		NPC->OnFinishDialogue();

		Player->RemovePlayerAllMappingContexts();
		NPC->SetNPCInteractionAvailability(false);
		NPC->SetCameraSceneState(false);
		int32 Level = NPC->GetNPCCurrentLevel();
		Player->CollectedMaps[Level] = true;
		//NPC->SetCameraToOriginalState(true);
		Player->SetPlayerCameraTransform(Player->GetPlayerOriginalCameraTransform());
		Player->SetPlayerMappingContext(Player->MovementMappingContext, 0);

		if (!NPC->GetObjectiveComplete())
		{
			if (APlayerController* PlayerController = Cast<APlayerController>(Player->GetController()))
			{
				UUserWidget* Widget = CreateWidget<UUserWidget>(PlayerController, MissionIndicationUI);
				Widget->AddToViewport();
			}

			UGameplayHUDUI* GameWidget = Player->GameplayHUDWidget;
			GameWidget->Player = Player;
			GameWidget->NPC = NPC;
			GameWidget->CurrentTimer = NPC->GetObjectiveTimer();
			GameWidget->ObjectiveAnimEvent();
			GameWidget->Timer->SetText(FText::AsNumber(NPC->GetObjectiveTimer()));
			GameWidget->CurrentObjective->SetText(NPC->GetCurrentObjective());
			GameWidget->bStartTimer = true;
		}
		else
		{
			Player->CollectedKeys[Level] = true;
		}

		APlayerGameModeBase* GameMode = Player->GetPlayerGameMode();
		if (GameMode)
		{
			GameMode->SaveAllPlayerData(1);
		}

		RemoveFromParent();
	}
}