// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PauseMenuUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Debug/Debug.h"

UPauseMenuUI::UPauseMenuUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BtnContinue = nullptr;
	BtnLoad		= nullptr;
	BtnMaps		= nullptr;
	BtnTools	= nullptr;
	BtnSettings = nullptr;
	BtnReturn	= nullptr;
	BtnQuit		= nullptr;

	BtnArrIndex = 0;
	bLastKeyboardInput = true;
}

void UPauseMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (AMotherRabbit* Player = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<AMotherRabbit>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Got The Player!!!"));

		Player->OnPressingNavigationAction.AddDynamic(this, &UPauseMenuUI::NavigateToNextButton);
		Player->OnPressingEnterAction.AddDynamic(this, &UPauseMenuUI::Interact);
	}

	SetupButtons();
}

void UPauseMenuUI::SetupButtons()
{
	// Check if Buttons and animations are assigned
	for (int32 i = 0; i != BtnArr.Num(); ++i)
	{
		check(BtnArr[i] != nullptr && BtnAnimationArr[i] != nullptr);
	}

	// Bind so when the player uses the mouse and click on the button, it calls the functions
	BtnArr[0]->OnClicked.AddDynamic(this, &UPauseMenuUI::Continue);
	BtnArr[1]->OnClicked.AddDynamic(this, &UPauseMenuUI::Load);
	BtnArr[2]->OnClicked.AddDynamic(this, &UPauseMenuUI::Maps);
	BtnArr[3]->OnClicked.AddDynamic(this, &UPauseMenuUI::Tools);
	BtnArr[4]->OnClicked.AddDynamic(this, &UPauseMenuUI::Settings);
	BtnArr[5]->OnClicked.AddDynamic(this, &UPauseMenuUI::Return);
	BtnArr[6]->OnClicked.AddDynamic(this, &UPauseMenuUI::Quit);


	// Bind so when the player uses the keyboard and hit enter, it calls the functions
	BtnAction.Add(0, FButtonAction::CreateUObject(this, &UPauseMenuUI::Continue));
	BtnAction.Add(1, FButtonAction::CreateUObject(this, &UPauseMenuUI::Load));
	BtnAction.Add(2, FButtonAction::CreateUObject(this, &UPauseMenuUI::Maps));
	BtnAction.Add(3, FButtonAction::CreateUObject(this, &UPauseMenuUI::Tools));
	BtnAction.Add(4, FButtonAction::CreateUObject(this, &UPauseMenuUI::Settings));
	BtnAction.Add(5, FButtonAction::CreateUObject(this, &UPauseMenuUI::Return));
	BtnAction.Add(6, FButtonAction::CreateUObject(this, &UPauseMenuUI::Quit));

	BtnArr[0]->SetKeyboardFocus();
	PlayAnimation(BtnAnimationArr[0]);
}

void UPauseMenuUI::Interact()
{
	if (BtnAction[BtnArrIndex].IsBound())
	{
		BtnAction[BtnArrIndex].Execute();
	}
}

void UPauseMenuUI::Continue()
{
	PrintScreen(15.0f, FColor::Green, "Continue Function Is Working!!!");
}

void UPauseMenuUI::Load()
{
	PrintScreen(15.0f, FColor::Green, "Load Function Is Working!!!");
}

void UPauseMenuUI::Maps()
{
	PrintScreen(15.0f, FColor::Green, "Maps Function Is Working!!!");
}

void UPauseMenuUI::Tools()
{
	PrintScreen(15.0f, FColor::Green, "Tools Function Is Working!!!");
}

void UPauseMenuUI::Settings()
{
	PrintScreen(15.0f, FColor::Green, "Settings Function Is Working!!!");
}

void UPauseMenuUI::Return()
{
	PrintScreen(15.0f, FColor::Green, "Return Function Is Working!!!");
}

void UPauseMenuUI::Quit()
{
	PrintScreen(15.0f, FColor::Green, "Quit Function Is Working!!!");
}

// TODO: Create a UObject for the navigation, instead of writing the same code for every widget (Keep in mind can't hard code index and you need to use the length of an array)
void UPauseMenuUI::NavigateToNextButton(float ActionValue)
{
	if (BtnArr.IsValidIndex(BtnArrIndex))
	{
		check(BtnArr[BtnArrIndex] != nullptr && BtnAnimationArr[BtnArrIndex] != nullptr);

		if (ActionValue < 0.0f && (BtnArrIndex != 6)) // Go to next button (Down)
		{
			BtnArr[++BtnArrIndex]->SetKeyboardFocus();

			if (BtnArr[BtnArrIndex]->HasKeyboardFocus())
			{
				if (IsAnimationPlaying(BtnAnimationArr[BtnArrIndex - 1]))
					ReverseAnimation(BtnAnimationArr[BtnArrIndex - 1]);
				else if (!IsAnimationPlaying(BtnAnimationArr[BtnArrIndex - 1]) && (bLastKeyboardInput == true))
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
				else if (!IsAnimationPlaying(BtnAnimationArr[BtnArrIndex + 1]))
					PlayAnimation(BtnAnimationArr[BtnArrIndex + 1], 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);

				PlayAnimation(BtnAnimationArr[BtnArrIndex]);
			}
		}
		else if (ActionValue < 0.0f && (BtnArrIndex == 6)) // First element, so set the index to the last element
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

			BtnArrIndex = 6;
			BtnArr[BtnArrIndex]->SetKeyboardFocus();
			PlayAnimation(BtnAnimationArr[BtnArrIndex]);
		}
	}
}