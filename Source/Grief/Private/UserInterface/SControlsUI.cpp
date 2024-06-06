// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/SControlsUI.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/MotherRabbit/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "Debug/Debug.h"
#include "Engine/Texture2D.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

USControlsUI::USControlsUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BtnArrIndex = 0;
	LastVisitedIndex = 0;

	bLastKeyboardInput = true;
	bEditKey = false;

	ActionType = EActionType::EAT_NONE;

	// Remove Controls once you are done with debugging
	CurrentControls.MovementForwardLockedKey = EKeys::W;
	CurrentControls.MovementBackwardLockedKey = EKeys::S;
	CurrentControls.MovementRightLockedKey = EKeys::D;
	CurrentControls.MovementLeftLockedKey = EKeys::A;
	CurrentControls.JumpLockedKey = EKeys::SpaceBar;
}

void USControlsUI::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerRef = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<AMotherRabbit>();
	PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	//MoveForwardBtn->SetKeyboardFocus();


	if (PlayerRef)
	{
		PlayerRef->OnPressingNavigationAction.AddDynamic(this, &USControlsUI::NavigateToNextButton);
		PlayerRef->OnPressingEnterAction.AddDynamic(this, &USControlsUI::Interact);
	}

	SetupButtons();
}

void USControlsUI::SetupButtons()
{
	// Check if Buttons and animations are assigned
	for (int32 i = 0; i != BtnArr.Num(); ++i)
	{
		check(BtnArr[i] != nullptr && BtnAnimationArr[i] != nullptr);
	}

	// Bind so when the player uses the mouse and click on the button, it calls the functions
	BtnArr[0]->OnClicked.AddDynamic(this, &USControlsUI::MoveForwardOption);
	BtnArr[1]->OnClicked.AddDynamic(this, &USControlsUI::MoveBackwardOption);
	BtnArr[2]->OnClicked.AddDynamic(this, &USControlsUI::MoveRightOption);
	BtnArr[3]->OnClicked.AddDynamic(this, &USControlsUI::MoveLeftOption);
	BtnArr[4]->OnClicked.AddDynamic(this, &USControlsUI::JumpOption);


	// Bind so when the player uses the keyboard and hit enter, it calls the functions
	BtnAction.Add(0, FButtonAction::CreateUObject(this, &USControlsUI::MoveForwardOption));
	BtnAction.Add(1, FButtonAction::CreateUObject(this, &USControlsUI::MoveBackwardOption));
	BtnAction.Add(2, FButtonAction::CreateUObject(this, &USControlsUI::MoveRightOption));
	BtnAction.Add(3, FButtonAction::CreateUObject(this, &USControlsUI::MoveLeftOption));
	BtnAction.Add(4, FButtonAction::CreateUObject(this, &USControlsUI::JumpOption));

	BtnArr[0]->SetKeyboardFocus();
	PlayAnimation(BtnAnimationArr[0]);
}

void USControlsUI::Interact()
{
	if (BtnAction[BtnArrIndex].IsBound())
	{
		BtnAction[BtnArrIndex].Execute();
	}
}

FReply USControlsUI::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	
	if (bEditKey)
	{
		CurrentKey = InKeyEvent.GetKey();

		if (CurrentKey == EKeys::P)
		{
			CloseChildUI();
			bEditKey = false;
		}
		else if (ActionType == EActionType::EAT_Movement)
		{
			UpdateKeyBindings(PlayerRef->MovementMappingContext, PlayerRef->MovementAction, EditKey);
		}
		else if (ActionType == EActionType::EAT_Jump)
		{
			UpdateKeyBindings(PlayerRef->MovementMappingContext, PlayerRef->JumpAction, EditKey);
		}
		//PrintScreen(10.0f, FColor::Red, "Pressed Key: %s", *CurrentKey.ToString());

		return FReply::Handled();
	}
	//PrintScreen(10.0f, FColor::Red, "Pressed Key: %s", *CurrentKey.ToString());

	return FReply::Unhandled();
}

void USControlsUI::MoveForwardOption()
{
	if (PlayerRef)
	{
		bEditKey = true;
		EditKey = CurrentControls.MovementForwardLockedKey;
		ActionType = EActionType::EAT_Movement;

		OpenChildUI();
		PrintScreen(false, 10.0f, FColor::Red, "Please Enter A Key(MoveForward)");
	}
}

void USControlsUI::MoveBackwardOption()
{
	if (PlayerRef)
	{
		bEditKey = true;
		EditKey = CurrentControls.MovementBackwardLockedKey;
		ActionType = EActionType::EAT_Movement;

		OpenChildUI();
		PrintScreen(false, 10.0f, FColor::Red, "Please Enter A Key(MoveBackward)");
	}
}

void USControlsUI::MoveRightOption()
{
	if (PlayerRef)
	{
		bEditKey = true;
		EditKey = CurrentControls.MovementRightLockedKey;
		ActionType = EActionType::EAT_Movement;

		OpenChildUI();
		PrintScreen(false, 10.0f, FColor::Red, "Please Enter A Key(MoveRight)");
	}
}

void USControlsUI::MoveLeftOption()
{
	if (PlayerRef)
	{
		bEditKey = true;
		EditKey = CurrentControls.MovementLeftLockedKey;
		ActionType = EActionType::EAT_Movement;

		OpenChildUI();
		PrintScreen(false, 10.0f, FColor::Red, "Please Enter A Key(MoveLeft)");
	}
}

void USControlsUI::JumpOption()
{
	if (PlayerRef)
	{
		bEditKey = true;
		EditKey = CurrentControls.JumpLockedKey;
		ActionType = EActionType::EAT_Jump;

		OpenChildUI();
		PrintScreen(false, 10.0f, FColor::Red, "Please Enter A Key(Jump)");
	}
}

void USControlsUI::UpdateKeyBindings(UInputMappingContext* IMC, UInputAction* InputAction, FKey Key)
{
	if (CurrentKey.IsValid())
	{
		const TArray<FEnhancedActionKeyMapping>& Mapping = IMC->GetMappings();
		const FEnhancedActionKeyMapping* OldMapping = nullptr;
		for (const FEnhancedActionKeyMapping& i : Mapping)
		{
			if (i.Action == InputAction && (i.Key == Key))
			{
				OldMapping = &i;
				break;
			}
		}

		if (OldMapping == nullptr)
		{
			PrintScreen(false, 10.0f, FColor::Red, "WARNING::MAPPING DOESN'T EXIST");
			return;
		}

		TArray<TObjectPtr<UInputModifier>> Modifiers = OldMapping->Modifiers;
		TArray<TObjectPtr<UInputTrigger>> Triggers = OldMapping->Triggers;

		IMC->UnmapKey(InputAction, OldMapping->Key);

		IMC->MapKey(InputAction, CurrentKey).Modifiers = Modifiers;
		/*FEnhancedActionKeyMapping NewMapping = IMC->MapKey(InputAction, CurrentKey);
		
		NewMapping.Modifiers = Modifiers;
		NewMapping.Triggers = Triggers;*/

		UpdateKeyImage(CurrentKey);

		CloseChildUI();
		PrintScreen(false, 10.0f, FColor::Green, "Key has been edited");
		bEditKey = false;
	}
}

void USControlsUI::UpdateKeyImage(FKey Key)
{
	FString KeyName = Key.ToString();
	FString TexturePath = FString::Printf(TEXT("/Game/Blueprints/UI/Textures/Input/Dark/T_%s_Key_Dark"), *KeyName);

	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	UTexture2D* UpdatedKeyTexture = Cast<UTexture2D>(Streamable.LoadSynchronous(FSoftObjectPath(TexturePath)));

	if (UpdatedKeyTexture && CurrentKeyImage[BtnArrIndex])
	{
		CurrentKeyImage[BtnArrIndex]->SetBrushFromTexture(UpdatedKeyTexture);
		PrintScreen(false, 10.0f, FColor::Red, "Image Updated :)");
	}
}

void USControlsUI::OpenChildUI()
{
	if (PlayerController)
	{
		CurrentChildUI = CreateWidget<UUserWidget>(PlayerController, KeyChangeMenuUI);
		CurrentChildUI->AddToViewport();

		//PlayerController->NumberOfOpenChildren++;
	}
}

void USControlsUI::CloseChildUI()
{
	if (CurrentChildUI)
	{
		CurrentChildUI->RemoveFromViewport();
		CurrentChildUI = nullptr;
	}
}

// TODO: Create a UObject for the navigation, instead of writing the same code for every widget (Keep in mind can't hard code index and you need to use the length of an array)
void USControlsUI::NavigateToNextButton(float ActionValue)
{
	if (BtnArr.IsValidIndex(BtnArrIndex))
	{
		check(BtnArr[BtnArrIndex] != nullptr && BtnAnimationArr[BtnArrIndex] != nullptr);

		if (ActionValue < 0.0f && (BtnArrIndex != BtnArr.Num()-1)) // Go to next button (Down)
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

				PrintScreen(false, 10.0f, FColor::Red, "Ha, Down!!!");
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

				PrintScreen(false, 10.0f, FColor::Red, "Ha, Up!!!");
			}
		}
		else if (ActionValue < 0.0f && (BtnArrIndex == BtnArr.Num() - 1)) // First element, so set the index to the last element
		{
			LastVisitedIndex = BtnArrIndex;

			if (IsAnimationPlaying(BtnAnimationArr[BtnArrIndex]))
				ReverseAnimation(BtnAnimationArr[BtnArrIndex]);
			else if (!IsAnimationPlaying(BtnAnimationArr[BtnArrIndex]))
				PlayAnimation(BtnAnimationArr[BtnArrIndex], 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);

			BtnArrIndex = 0;
			BtnArr[BtnArrIndex]->SetKeyboardFocus();
			PlayAnimation(BtnAnimationArr[BtnArrIndex]);

			PrintScreen(false, 10.0f, FColor::Red, "Ha, Last!!!");
		}
		else // Last element, so set the index to the first element
		{
			LastVisitedIndex = BtnArrIndex;

			if (IsAnimationPlaying(BtnAnimationArr[BtnArrIndex]))
				ReverseAnimation(BtnAnimationArr[BtnArrIndex]);
			else if (!IsAnimationPlaying(BtnAnimationArr[BtnArrIndex]))
				PlayAnimation(BtnAnimationArr[BtnArrIndex], 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);

			BtnArrIndex = BtnArr.Num() - 1;
			BtnArr[BtnArrIndex]->SetKeyboardFocus();
			PlayAnimation(BtnAnimationArr[BtnArrIndex]);

			PrintScreen(false, 10.0f, FColor::Red, "Ha, First!!!");
		}

		UpdateScrollEvent();
	}
}