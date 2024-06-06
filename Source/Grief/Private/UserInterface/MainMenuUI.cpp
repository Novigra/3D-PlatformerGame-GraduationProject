// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/MainMenuUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Debug/Debug.h"


UMainMenuUI::UMainMenuUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BtnNewGame = nullptr;
	BtnLoadGame = nullptr;
	BtnExitGame = nullptr;

	BtnArrIndex = 0;
	Temp = 0;
	bLastKeyboardInput = true;
}

void UMainMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (AMotherRabbit* Player = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<AMotherRabbit>())
	{
		PrintScreen(false, 10.0f, FColor::Blue, "Got The Player!!!");

		Player->OnPressingNavigationAction.AddDynamic(this, &UMainMenuUI::NavigateToNextButton);
		Player->OnPressingEnterAction.AddDynamic(this, &UMainMenuUI::Interact);
	}

	SetupButtons();
}

void UMainMenuUI::SetupButtons()
{
	// Check if Buttons and animations are assigned
	for (int32 i = 0; i != BtnArr.Num(); ++i)
	{
		check(BtnArr[i] != nullptr && BtnAnimationArr[i] != nullptr);
	}

	// Bind so when the player uses the mouse and click on the button, it calls the functions
	BtnArr[0]->OnClicked.AddDynamic(this, &UMainMenuUI::NewGame);
	BtnArr[1]->OnClicked.AddDynamic(this, &UMainMenuUI::LoadGame);
	BtnArr[2]->OnClicked.AddDynamic(this, &UMainMenuUI::ExitGame);

	BtnArr[0]->OnHovered.AddDynamic(this, &UMainMenuUI::OnHoveredNewGameButton);
	BtnArr[1]->OnHovered.AddDynamic(this, &UMainMenuUI::OnHoveredLoadGameButton);
	BtnArr[2]->OnHovered.AddDynamic(this, &UMainMenuUI::OnHoveredExitGameButton);

	for (int32 i = 0; i < BtnArr.Num(); ++i)
	{
		BtnArr[i]->OnUnhovered.AddDynamic(this, &UMainMenuUI::OnUnHoveredButton);
	}

	// Bind so when the player uses the keyboard and hit enter, it calls the functions
	BtnAction.Add(0, FButtonAction::CreateUObject(this, &UMainMenuUI::NewGame));
	BtnAction.Add(1, FButtonAction::CreateUObject(this, &UMainMenuUI::LoadGame));
	BtnAction.Add(2, FButtonAction::CreateUObject(this, &UMainMenuUI::ExitGame));

	BtnArr[0]->SetKeyboardFocus();
	PlayAnimation(BtnAnimationArr[0]);
}

void UMainMenuUI::Interact()
{
	if (BtnAction[BtnArrIndex].IsBound())
	{
		BtnAction[BtnArrIndex].Execute();
	}
}

void UMainMenuUI::NewGame()
{
	PrintScreen(false, 15.0f, FColor::Green, "New Game Function Is Working!!!");

	OnCloseAction.Broadcast();
}

void UMainMenuUI::LoadGame()
{
	PrintScreen(false, 15.0f, FColor::Red, "Load Game Function Is Working!!!");
}

void UMainMenuUI::ExitGame()
{
	PrintScreen(false, 15.0f, FColor::Yellow, "Exit Game Function Is Working!!!");

	FWindowsPlatformMisc::RequestExit(false);
}

void UMainMenuUI::NavigateToNextButton(float ActionValue)
{
	if (BtnArr.IsValidIndex(BtnArrIndex))
	{
		check(BtnArr[BtnArrIndex] != nullptr && BtnAnimationArr[BtnArrIndex] != nullptr);
		//Temp = BtnArrIndex;

		if (ActionValue < 0.0f && (BtnArrIndex != 2)) // Go to next button (Down)
		{
			BtnArr[++BtnArrIndex]->SetKeyboardFocus();

			if (BtnArr[BtnArrIndex]->HasKeyboardFocus())
			{
				if(IsAnimationPlaying(BtnAnimationArr[BtnArrIndex - 1]))
					ReverseAnimation(BtnAnimationArr[BtnArrIndex - 1]);
				else if(!IsAnimationPlaying(BtnAnimationArr[BtnArrIndex - 1]) && (bLastKeyboardInput == true))
					PlayAnimation(BtnAnimationArr[BtnArrIndex - 1], 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);
				
				PlayAnimation(BtnAnimationArr[BtnArrIndex]);
			}
		}
		else if (ActionValue > 0.0f && (BtnArrIndex != 0)) // Go to previous button (Up)
		{
			BtnArr[--BtnArrIndex]->SetKeyboardFocus();

			if (BtnArr[BtnArrIndex]->HasKeyboardFocus())
			{
				if (IsAnimationPlaying(BtnAnimationArr[BtnArrIndex + 1]))
					ReverseAnimation(BtnAnimationArr[BtnArrIndex + 1]);
				else if(!IsAnimationPlaying(BtnAnimationArr[BtnArrIndex + 1]))
					PlayAnimation(BtnAnimationArr[BtnArrIndex + 1], 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);

				PlayAnimation(BtnAnimationArr[BtnArrIndex]);
			}
		}
		else if (ActionValue < 0.0f && (BtnArrIndex == 2)) // First element, so set the index to the last element
		{
			if (IsAnimationPlaying(BtnAnimationArr[BtnArrIndex]))
				ReverseAnimation(BtnAnimationArr[BtnArrIndex]);
			else if (!IsAnimationPlaying(BtnAnimationArr[BtnArrIndex]))
				PlayAnimation(BtnAnimationArr[BtnArrIndex], 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);

			BtnArrIndex = 0;
			BtnArr[BtnArrIndex]->SetKeyboardFocus();
			PlayAnimation(BtnAnimationArr[BtnArrIndex]);
		}
		else // Last element, so set the index to the first element
		{
			if (IsAnimationPlaying(BtnAnimationArr[BtnArrIndex]))
				ReverseAnimation(BtnAnimationArr[BtnArrIndex]);
			else if (!IsAnimationPlaying(BtnAnimationArr[BtnArrIndex]))
				PlayAnimation(BtnAnimationArr[BtnArrIndex], 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);

			BtnArrIndex = 2;
			BtnArr[BtnArrIndex]->SetKeyboardFocus();
			PlayAnimation(BtnAnimationArr[BtnArrIndex]);
		}

		//bLastKeyboardInput = true;
	}
}

void UMainMenuUI::OnHoveredNewGameButton()
{
	if (IsAnimationPlaying(BtnAnimationArr[BtnArrIndex]))
		ReverseAnimation(BtnAnimationArr[BtnArrIndex]);
	else
		PlayAnimation(BtnAnimationArr[BtnArrIndex], 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);

	BtnArrIndex = 0;
	bLastKeyboardInput = false;
	PrintScreen(false, 15.0f, FColor::Green, "Current Active Button Index = %d", BtnArrIndex);

	BtnArr[BtnArrIndex]->SetKeyboardFocus();
	PlayAnimation(BtnAnimationArr[BtnArrIndex]);
}

void UMainMenuUI::OnHoveredLoadGameButton()
{
	if (IsAnimationPlaying(BtnAnimationArr[BtnArrIndex]))
		ReverseAnimation(BtnAnimationArr[BtnArrIndex]);
	else
		PlayAnimation(BtnAnimationArr[BtnArrIndex], 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);

	BtnArrIndex = 1;
	bLastKeyboardInput = false;
	PrintScreen(false, 15.0f, FColor::Red, "Current Active Button Index = %d", BtnArrIndex);

	BtnArr[BtnArrIndex]->SetKeyboardFocus();
	PlayAnimation(BtnAnimationArr[BtnArrIndex]);
}

void UMainMenuUI::OnHoveredExitGameButton()
{
	if (IsAnimationPlaying(BtnAnimationArr[BtnArrIndex]))
		ReverseAnimation(BtnAnimationArr[BtnArrIndex]);
	else
		PlayAnimation(BtnAnimationArr[BtnArrIndex], 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);

	BtnArrIndex = 2;
	bLastKeyboardInput = false;
	PrintScreen(false, 15.0f, FColor::Yellow, "Current Active Button Index = %d", BtnArrIndex);

	BtnArr[BtnArrIndex]->SetKeyboardFocus();
	PlayAnimation(BtnAnimationArr[BtnArrIndex]);
}

void UMainMenuUI::OnUnHoveredButton()
{
	

	//Temp = BtnArrIndex;
	//BtnArrIndex = 0;
	//BtnArr[0]->SetKeyboardFocus();
}

FReply UMainMenuUI::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::K)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Pressed the button K"));

		return FReply::Handled();
	}

	return FReply::Unhandled();
}