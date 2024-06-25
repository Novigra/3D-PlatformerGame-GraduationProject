// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/ArrangeMapsWidgetUI.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Debug/Debug.h"

UArrangeMapsWidgetUI::UArrangeMapsWidgetUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BtnArrIndex = 0;
	ChoiceArrIndex = 0;
	LastVisitedIndex = 0;
	bLastKeyboardInput = true;
}

void UArrangeMapsWidgetUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (AMotherRabbit* Player = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<AMotherRabbit>())
	{
		PrintScreen(false, 10.0f, FColor::Blue, "Got The Player!!!");

		Player->OnPressingPageNavigationAction.AddDynamic(this, &UArrangeMapsWidgetUI::NavigateToNextButton);
		//Player->OnPressingNavigationAction.AddDynamic(this, &UPauseMenuUI::NavigateToNextButton);
		Player->OnPressingEnterAction.AddDynamic(this, &UArrangeMapsWidgetUI::Interact);

		Player->RemovePlayerMappingContext(Player->MovementMappingContext);
		Player->SetPlayerMappingContext(Player->UserInterfaceMappingContext, 0);
	}

	SetupButtons();
}

void UArrangeMapsWidgetUI::SetupButtons()
{
	// Bind so when the player uses the mouse and click on the button, it calls the functions
	BtnArr[0]->OnClicked.AddDynamic(this, &UArrangeMapsWidgetUI::MapOnePlacement);
	BtnArr[1]->OnClicked.AddDynamic(this, &UArrangeMapsWidgetUI::MapTwoPlacement);
	BtnArr[2]->OnClicked.AddDynamic(this, &UArrangeMapsWidgetUI::MapThreePlacement);
	BtnArr[3]->OnClicked.AddDynamic(this, &UArrangeMapsWidgetUI::MapFourPlacement);

	// Bind so when the player uses the keyboard and hit enter, it calls the functions
	BtnAction.Add(0, FButtonAction::CreateUObject(this, &UArrangeMapsWidgetUI::MapOnePlacement));
	BtnAction.Add(1, FButtonAction::CreateUObject(this, &UArrangeMapsWidgetUI::MapTwoPlacement));
	BtnAction.Add(2, FButtonAction::CreateUObject(this, &UArrangeMapsWidgetUI::MapThreePlacement));
	BtnAction.Add(3, FButtonAction::CreateUObject(this, &UArrangeMapsWidgetUI::MapFourPlacement));

	BtnArr[0]->SetKeyboardFocus();
	PlayAnimation(BtnAnimationArr[0]);
}

void UArrangeMapsWidgetUI::Interact()
{
	if (BtnAction[BtnArrIndex].IsBound())
	{
		BtnAction[BtnArrIndex].Execute();
	}
}

void UArrangeMapsWidgetUI::MapOnePlacement()
{
	FString Name = "MapOne";
	if (Name.Equals(ChoiceArr[ChoiceArrIndex]->GetName()))
	{
		PrintScreen(true, 2.0f, FColor::Green, "It works!!!!");
		ChoiceArrIndex++;

		OnUpdateEvent();
	}
	else
	{
		OnChoosingWrongEvent();
	}

	if (ChoiceArrIndex == 4)
	{
		OnDestroyWidget.Broadcast();
		RemoveFromParent();

		if (AMotherRabbit* Player = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<AMotherRabbit>())
		{
			Player->RemovePlayerMappingContext(Player->UserInterfaceMappingContext);
			Player->SetPlayerMappingContext(Player->MovementMappingContext, 0);
		}
	}
}

void UArrangeMapsWidgetUI::MapTwoPlacement()
{
	FString Name = "MapTwo";
	if (Name.Equals(ChoiceArr[ChoiceArrIndex]->GetName()))
	{
		PrintScreen(true, 2.0f, FColor::Green, "It works!!!!");
		ChoiceArrIndex++;

		OnUpdateEvent();
	}
	else
	{
		OnChoosingWrongEvent();
	}
}

void UArrangeMapsWidgetUI::MapThreePlacement()
{
	FString Name = "MapThree";
	if (Name.Equals(ChoiceArr[ChoiceArrIndex]->GetName()))
	{
		PrintScreen(true, 2.0f, FColor::Green, "It works!!!!");
		ChoiceArrIndex++;

		OnUpdateEvent();
	}
	else
	{
		OnChoosingWrongEvent();
	}
}

void UArrangeMapsWidgetUI::MapFourPlacement()
{
	FString Name = "MapFour";
	if (Name.Equals(ChoiceArr[ChoiceArrIndex]->GetName()))
	{
		PrintScreen(true, 2.0f, FColor::Green, "It works!!!!");
		ChoiceArrIndex++;

		OnUpdateEvent();
	}
	else
	{
		OnChoosingWrongEvent();
	}
}

void UArrangeMapsWidgetUI::NavigateToNextButton(float ActionValue)
{
	if (BtnArr.IsValidIndex(BtnArrIndex))
	{
		if (ActionValue > 0.0f && (BtnArrIndex != 3)) // Go to next button (Down)
		{
			LastVisitedIndex = BtnArrIndex;

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
		else if (ActionValue < 0.0f && (BtnArrIndex != 0)) // Go to previous button (Up)
		{
			LastVisitedIndex = BtnArrIndex;

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
		else if (ActionValue > 0.0f && (BtnArrIndex == 3)) // First element, so set the index to the last element
		{
			LastVisitedIndex = BtnArrIndex;

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
			LastVisitedIndex = BtnArrIndex;

			if (IsAnimationPlaying(BtnAnimationArr[BtnArrIndex]))
				ReverseAnimation(BtnAnimationArr[BtnArrIndex]);
			else if (!IsAnimationPlaying(BtnAnimationArr[BtnArrIndex]))
				PlayAnimation(BtnAnimationArr[BtnArrIndex], 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);

			BtnArrIndex = 3;
			BtnArr[BtnArrIndex]->SetKeyboardFocus();
			PlayAnimation(BtnAnimationArr[BtnArrIndex]);
		}
	}
}