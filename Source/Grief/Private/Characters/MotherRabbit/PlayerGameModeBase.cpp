// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MotherRabbit/PlayerGameModeBase.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/NPC/NPC.h"
#include "UserInterface/GameplayHUDUI.h"
#include "Data/SaveLocalPlayerGame.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Debug/Debug.h"

APlayerGameModeBase::APlayerGameModeBase()
{

}

void APlayerGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Player = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<AMotherRabbit>();
	PrintScreen(true, 5.0f, FColor::Green, "GameMode Is On...");
}

USaveLocalPlayerGame* APlayerGameModeBase::GetSaveGame()
{
	USaveLocalPlayerGame* DefaultSaveGame = Cast<USaveLocalPlayerGame>(UGameplayStatics::CreateSaveGameObject(USaveLocalPlayerGame::StaticClass()));
	return DefaultSaveGame;
}

void APlayerGameModeBase::LoadAllPlayerData()
{
	FString SaveSlotName = TEXT("DefaultSaveSlot");
	int32 UserIndex = 0;

	FAsyncLoadGameFromSlotDelegate LoadDelegate;
	LoadDelegate.BindUObject(this, &APlayerGameModeBase::LoadData);
	UGameplayStatics::AsyncLoadGameFromSlot(SaveSlotName, UserIndex, LoadDelegate);
}

void APlayerGameModeBase::SaveAllPlayerData(int32 SaveDataType)
{
	FString SaveSlotName = TEXT("DefaultSaveSlot");
	int32 UserIndex = 0;
	USaveLocalPlayerGame* SaveGameInstance;

	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
	{
		SaveGameInstance = Cast<USaveLocalPlayerGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	}
	else
	{
		SaveGameInstance = Cast<USaveLocalPlayerGame>(UGameplayStatics::CreateSaveGameObject(USaveLocalPlayerGame::StaticClass()));
	}

	if (SaveGameInstance && Player)
	{
		// Save player data
		SaveGameInstance->PlayerPosition	= Player->GetActorTransform();
		SaveGameInstance->Timer				= Player->LastTimerNumber;
		SaveGameInstance->Coins				= Player->CollectedCoins;
		SaveGameInstance->NumberOfLives		= Player->NumberOfLives;
		SaveGameInstance->CollectedKeys		= Player->CollectedKeys;
		SaveGameInstance->CollectedMaps		= Player->CollectedMaps;
		SaveGameInstance->LastMetNPC		= Player->CurrentInteractNPC;

		for (int32 Index = 0; Index < Player->PlayerItem.Num(); ++Index)
		{
			FPlayerOwnedItemStruct SavePlayerItem;
			SavePlayerItem.ItemName = Player->PlayerItem[Index].ItemName;
			SavePlayerItem.bOwnItem = Player->PlayerItem[Index].bOwnItem;

			SaveGameInstance->PlayerOwnedItems.Add(SavePlayerItem);
		}

		//Save NPC data
		if (ANPC* NPC = Cast<ANPC>(Player->CurrentInteractNPC))
		{
			SaveGameInstance->DialogueIndex			= NPC->GetDialogueIndex();
			SaveGameInstance->bStartConversation	= NPC->GetStartConversation();
			SaveGameInstance->bCanInteract			= NPC->GetNPCInteractionAvailability();
			SaveGameInstance->bIsObjectiveComplete	= NPC->GetObjectiveComplete();
			SaveGameInstance->bSpawnSubActor		= NPC->GetSpawnSubActor();
		}

		FAsyncSaveGameToSlotDelegate SaveDelegate;
		SaveDelegate.BindUObject(this, &APlayerGameModeBase::SaveResult);

		if (SaveDataType == 0)
		{
			UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex);
		}
		else
		{
			UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex, SaveDelegate);
		}
	}
}

void APlayerGameModeBase::LoadData(const FString& SaveSlotName, const int32 UserIndex, USaveGame* LoadGame)
{
	USaveLocalPlayerGame* LoadGameInstance = Cast<USaveLocalPlayerGame>(LoadGame);
	if (LoadGameInstance && Player)
	{
		Player->SetActorTransform(LoadGameInstance->PlayerPosition);
		Player->LastTimerNumber		= LoadGameInstance->Timer;
		Player->CollectedCoins		= LoadGameInstance->Coins;
		Player->NumberOfLives		= LoadGameInstance->NumberOfLives;
		Player->CollectedKeys		= LoadGameInstance->CollectedKeys;
		Player->CollectedMaps		= LoadGameInstance->CollectedMaps;
		Player->CurrentInteractNPC	= LoadGameInstance->LastMetNPC;

		for (int32 Index = 0; Index < LoadGameInstance->PlayerOwnedItems.Num(); ++Index)
		{
			FPlayerItemStruct LoadPlayerItem;
			LoadPlayerItem.ItemName = LoadGameInstance->PlayerOwnedItems[Index].ItemName;
			LoadPlayerItem.bOwnItem = LoadGameInstance->PlayerOwnedItems[Index].bOwnItem;

			Player->PlayerItem.Add(LoadPlayerItem);
		}

		if (ANPC* NPC = Cast<ANPC>(Player->CurrentInteractNPC))
		{
			NPC->SetDialogueIndex(LoadGameInstance->DialogueIndex);
			NPC->SetStartConversation(LoadGameInstance->bStartConversation);
			NPC->SetNPCInteractionAvailability(LoadGameInstance->bCanInteract);
			NPC->SetObjectiveComplete(LoadGameInstance->bIsObjectiveComplete);
			NPC->SetSpawnSubActor(LoadGameInstance->bSpawnSubActor);
			OnDestroyActors.Broadcast();

			if (!NPC->GetObjectiveComplete())
			{
				UGameplayHUDUI* GameWidget = Player->GameplayHUDWidget;
				GameWidget->CurrentTimer = NPC->GetObjectiveTimer();
				GameWidget->ObjectiveAnimEvent();
				GameWidget->Timer->SetText(FText::AsNumber(NPC->GetObjectiveTimer()));
				GameWidget->CurrentObjective->SetText(NPC->GetCurrentObjective());
				GameWidget->bStartTimer = true;
				GameWidget->AddToViewport();
			}
		}
	}
	else
	{
		PrintScreen(true, 5.0f, FColor::Red, "WARNING::FAILED TO LOAD DATA");
	}
}

void APlayerGameModeBase::TestCalling()
{
	PrintScreen(true, 5.0f, FColor::Green, "Player Called GameMode...");
}

void APlayerGameModeBase::SaveResult(const FString& SaveSlotName, const int32 UserIndex, bool bSuccess)
{
	if (bSuccess)
	{
		PrintScreen(true, 5.0f, FColor::Green, "Game Saved");
	}
	else
	{
		PrintScreen(true, 5.0f, FColor::Red, "WARNING::GAME FAILED TO SAVE");
	}
}
