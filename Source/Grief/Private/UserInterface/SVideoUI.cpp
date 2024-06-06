// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/SVideoUI.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Debug/Debug.h"

USVideoUI::USVideoUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void USVideoUI::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerRef = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<AMotherRabbit>();

	if (PlayerRef)
	{
		PlayerRef->OnPressingEnterAction.AddDynamic(this, &USVideoUI::Interact);
	}

	SetupButtons();
}

void USVideoUI::SetupButtons()
{
	// Check if Buttons and animations are assigned
	for (int32 i = 0; i != BtnArr.Num(); ++i)
	{
		check(BtnArr[i] != nullptr && BtnAnimationArr[i] != nullptr);
	}

	// Bind so when the player uses the mouse and click on the button, it calls the functions
	BtnArr[0]->OnClicked.AddDynamic(this, &USVideoUI::SyncOption);


	// Bind so when the player uses the keyboard and hit enter, it calls the functions
	BtnAction.Add(0, FButtonAction::CreateUObject(this, &USVideoUI::SyncOption));

	BtnArr[0]->SetKeyboardFocus();
	PlayAnimation(BtnAnimationArr[0]);
}

void USVideoUI::Interact()
{
	if (BtnAction[BtnArrIndex].IsBound())
	{
		BtnAction[BtnArrIndex].Execute();
	}
}

void USVideoUI::SyncOption()
{
	if (PlayerRef)
	{
		PrintScreen(false, 10.0f, FColor::Red, "Yes, buttons are working");
	}
}