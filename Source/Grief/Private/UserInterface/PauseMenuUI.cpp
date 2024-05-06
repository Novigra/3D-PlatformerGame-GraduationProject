// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PauseMenuUI.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/MotherRabbit/MyPlayerController.h"
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
	Diamond_Overlay = nullptr;

	BtnArrIndex = 0;
	LastVisitedIndex = 0;
	TransformLocation = 100.0f;
	TargetLocation.Translation.Set(0.0f, 0.0f);
	InterpSpeed = 20.0f;
	bCanTransform = false;
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

void UPauseMenuUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bCanTransform && (Diamond_Overlay->GetRenderTransform().Translation != TargetLocation.Translation))
	{
		FVector2D CurrentLocation = FMath::Vector2DInterpTo(Diamond_Overlay->GetRenderTransform().Translation, TargetLocation.Translation, InDeltaTime, InterpSpeed);
		Diamond_Overlay->SetRenderTranslation(CurrentLocation);

		PrintScreen(10.0f, FColor::Red, "Overlay Current Location: X = %f  Y = %f", CurrentLocation.X, CurrentLocation.Y);
	}
	else if (Diamond_Overlay->GetRenderTransform().Translation == TargetLocation.Translation)
	{
		bCanTransform = false;
	}
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

	BtnArr[0]->OnHovered.AddDynamic(this, &UPauseMenuUI::OnHoveredContinueButton);
	BtnArr[1]->OnHovered.AddDynamic(this, &UPauseMenuUI::OnHoveredLoadButton);
	BtnArr[2]->OnHovered.AddDynamic(this, &UPauseMenuUI::OnHoveredMapsButton);
	BtnArr[3]->OnHovered.AddDynamic(this, &UPauseMenuUI::OnHoveredToolsButton);
	BtnArr[4]->OnHovered.AddDynamic(this, &UPauseMenuUI::OnHoveredSettingsButton);
	BtnArr[5]->OnHovered.AddDynamic(this, &UPauseMenuUI::OnHoveredReturnButton);
	BtnArr[6]->OnHovered.AddDynamic(this, &UPauseMenuUI::OnHoveredQuitButton);


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

	if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		PlayerController->CloseHUDOverlay();
	}
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
		else if (ActionValue > 0.0f && (BtnArrIndex != 0)) // Go to previous button (Up)
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
		else if (ActionValue < 0.0f && (BtnArrIndex == 6)) // First element, so set the index to the last element
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

			BtnArrIndex = 6;
			BtnArr[BtnArrIndex]->SetKeyboardFocus();
			PlayAnimation(BtnAnimationArr[BtnArrIndex]);
		}

		ButtonIndicator();
	}
}

void UPauseMenuUI::OnHoveredContinueButton()
{
	ReverseButtonAnimation(0);
}

void UPauseMenuUI::OnHoveredLoadButton()
{
	ReverseButtonAnimation(1);
}

void UPauseMenuUI::OnHoveredMapsButton()
{
	ReverseButtonAnimation(2);
}

void UPauseMenuUI::OnHoveredToolsButton()
{
	ReverseButtonAnimation(3);
}

void UPauseMenuUI::OnHoveredSettingsButton()
{
	ReverseButtonAnimation(4);
}

void UPauseMenuUI::OnHoveredReturnButton()
{
	ReverseButtonAnimation(5);
}

void UPauseMenuUI::OnHoveredQuitButton()
{
	ReverseButtonAnimation(6);
}

void UPauseMenuUI::ReverseButtonAnimation(int32 Index)
{
	if (IsAnimationPlaying(BtnAnimationArr[BtnArrIndex]))
		ReverseAnimation(BtnAnimationArr[BtnArrIndex]);
	else
		PlayAnimation(BtnAnimationArr[BtnArrIndex], 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);

	LastVisitedIndex = BtnArrIndex;
	BtnArrIndex = Index;
	bLastKeyboardInput = false;
	PrintScreen(15.0f, FColor::Green, "Current Active Button Index = %d", BtnArrIndex);

	BtnArr[BtnArrIndex]->SetKeyboardFocus();
	ButtonIndicator();
	PlayAnimation(BtnAnimationArr[BtnArrIndex]);
}

void UPauseMenuUI::ButtonIndicator()
{
	int32 Difference = BtnArrIndex - LastVisitedIndex;
	TargetLocation = Diamond_Overlay->GetRenderTransform();

	if (Difference > 0)
	{
		TargetLocation.Translation.Y += TransformLocation * FMath::Abs(Difference);
	}
	else
	{
		TargetLocation.Translation.Y -= TransformLocation * FMath::Abs(Difference);
	}

	bCanTransform = true;
}