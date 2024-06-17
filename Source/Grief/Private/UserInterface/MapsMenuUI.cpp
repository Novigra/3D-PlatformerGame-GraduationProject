// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/MapsMenuUI.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/MotherRabbit/MyPlayerController.h"
#include "Debug/Debug.h"

UMapsMenuUI::UMapsMenuUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BtnOne = nullptr;
	BtnTwo = nullptr;
	BtnThree = nullptr;
	BtnFour = nullptr;

	NormalColor = FSlateColor(FLinearColor::Black);
	HoveredColor = FSlateColor(FLinearColor::White);

	BtnArrIndex = 0;
	LastVisitedIndex = 0;
	TransformLocation = 100.0f;
	TargetLocation.Translation.Set(0.0f, 0.0f);
	InterpSpeed = 20.0f;
	bCanTransform = false;
	bLastKeyboardInput = true;
	bChildHudOpen = false;

	PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}

void UMapsMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	Player = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<AMotherRabbit>();
	if (Player)
	{
		PrintScreen(false, 10.0f, FColor::Blue, "Got The Player!!!");

		Player->OnPressingNavigationAction.AddDynamic(this, &UMapsMenuUI::NavigateToNextButton);
		Player->OnPressingEnterAction.AddDynamic(this, &UMapsMenuUI::Interact);
		Player->OnPressingBackAction.AddDynamic(this, &UMapsMenuUI::CloseChildUI);
	}

	SetupButtons();
}

void UMapsMenuUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	
}

void UMapsMenuUI::SetupButtons()
{
	// Check if Buttons and animations are assigned
	for (int32 i = 0; i != BtnArr.Num(); ++i)
	{
		check(BtnArr[i] != nullptr);
	}

	// Bind so when the player uses the mouse and click on the button, it calls the functions
	BtnArr[0]->OnClicked.AddDynamic(this, &UMapsMenuUI::MapOne);
	BtnArr[1]->OnClicked.AddDynamic(this, &UMapsMenuUI::MapTwo);
	BtnArr[2]->OnClicked.AddDynamic(this, &UMapsMenuUI::MapThree);
	BtnArr[3]->OnClicked.AddDynamic(this, &UMapsMenuUI::MapFour);

	BtnArr[0]->OnHovered.AddDynamic(this, &UMapsMenuUI::OnHoveredMapOneButton);
	BtnArr[1]->OnHovered.AddDynamic(this, &UMapsMenuUI::OnHoveredMapTwoButton);
	BtnArr[2]->OnHovered.AddDynamic(this, &UMapsMenuUI::OnHoveredMapThreeButton);
	BtnArr[3]->OnHovered.AddDynamic(this, &UMapsMenuUI::OnHoveredMapFourButton);


	// Bind so when the player uses the keyboard and hit enter, it calls the functions
	BtnAction.Add(0, FButtonAction::CreateUObject(this, &UMapsMenuUI::MapOne));
	BtnAction.Add(1, FButtonAction::CreateUObject(this, &UMapsMenuUI::MapTwo));
	BtnAction.Add(2, FButtonAction::CreateUObject(this, &UMapsMenuUI::MapThree));
	BtnAction.Add(3, FButtonAction::CreateUObject(this, &UMapsMenuUI::MapFour));

	BtnArr[0]->SetKeyboardFocus();
}

void UMapsMenuUI::Interact()
{
	if (BtnAction[BtnArrIndex].IsBound())
	{
		BtnAction[BtnArrIndex].Execute();
	}
}

void UMapsMenuUI::MapOne()
{
	if(Player->CollectedMaps[0])
		OpenMap(MapOneUI);
}

void UMapsMenuUI::MapTwo()
{
	if(Player->CollectedMaps[1])
		OpenMap(MapTwoUI);
}

void UMapsMenuUI::MapThree()
{
	if(Player->CollectedMaps[2])
		OpenMap(MapThreeUI);
}

void UMapsMenuUI::MapFour()
{
	if(Player->CollectedMaps[3])
		OpenMap(MapFourUI);
}

void UMapsMenuUI::OpenMap(TSubclassOf<class UUserWidget> Map)
{
	if (PlayerController && !(bChildHudOpen))
	{
		CurrentMapUI = CreateWidget<UUserWidget>(PlayerController, Map);
		CurrentMapUI->AddToViewport(1);

		PrintScreen(false, 5.0f, FColor::Red, "Map = %s", *CurrentMapUI->GetName());

		bChildHudOpen = true;

		PlayerController->NumberOfOpenChildren++;
	}
}

void UMapsMenuUI::CloseChildUI()
{
	if (CurrentMapUI)
	{
		//CurrentMapUI->RemoveFromViewport();
		CurrentMapUI->RemoveFromParent();
		CurrentMapUI = nullptr;
		PlayerController->NumberOfOpenChildren--;

		bChildHudOpen = false;
	}
}

// TODO: Create a UObject for the navigation, instead of writing the same code for every widget (Keep in mind can't hard code index and you need to use the length of an array)
void UMapsMenuUI::NavigateToNextButton(float ActionValue)
{
	if (BtnArr.IsValidIndex(BtnArrIndex) && !(bChildHudOpen))
	{
		check(BtnArr[BtnArrIndex] != nullptr);

		if (ActionValue < 0.0f && (BtnArrIndex != 3)) // Go to next button (Down)
		{
			LastVisitedIndex = BtnArrIndex;

			BtnArr[++BtnArrIndex]->SetKeyboardFocus();

			if (BtnArr[BtnArrIndex]->HasKeyboardFocus())
			{
				
			}
		}
		else if (ActionValue > 0.0f && (BtnArrIndex != 0)) // Go to previous button (Up)
		{
			LastVisitedIndex = BtnArrIndex;

			BtnArr[--BtnArrIndex]->SetKeyboardFocus();

			if (BtnArr[BtnArrIndex]->HasKeyboardFocus())
			{
				
			}
		}
		else if (ActionValue < 0.0f && (BtnArrIndex == 3)) // First element, so set the index to the last element
		{
			LastVisitedIndex = BtnArrIndex;

			

			BtnArrIndex = 0;
			BtnArr[BtnArrIndex]->SetKeyboardFocus();
		}
		else // Last element, so set the index to the first element
		{
			LastVisitedIndex = BtnArrIndex;

			

			BtnArrIndex = 3;
			BtnArr[BtnArrIndex]->SetKeyboardFocus();
		}

		ButtonIndicator();
		InterpAnim = 0.0f;
	}
}

void UMapsMenuUI::OnHoveredMapOneButton()
{
	ReverseButtonAnimation(0);
}

void UMapsMenuUI::OnHoveredMapTwoButton()
{
	ReverseButtonAnimation(1);
}

void UMapsMenuUI::OnHoveredMapThreeButton()
{
	ReverseButtonAnimation(2);
}

void UMapsMenuUI::OnHoveredMapFourButton()
{
	ReverseButtonAnimation(3);
}

void UMapsMenuUI::ReverseButtonAnimation(int32 Index)
{
	LastVisitedIndex = BtnArrIndex;
	BtnArrIndex = Index;
	bLastKeyboardInput = false;
	PrintScreen(false, 15.0f, FColor::Green, "Current Active Button Index = %d", BtnArrIndex);

	BtnArr[BtnArrIndex]->SetKeyboardFocus();
	ButtonIndicator();
}

void UMapsMenuUI::ButtonIndicator()
{
	int32 Difference = BtnArrIndex - LastVisitedIndex;

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