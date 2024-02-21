// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/MainMenuUI.h"
#include "Components/Button.h"

UMainMenuUI::UMainMenuUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BtnNewGame = nullptr;
	BtnLoadGame = nullptr;
	BtnExitGame = nullptr;
}

void UMainMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (BtnNewGame)
		BtnNewGame->OnClicked.AddDynamic(this, &UMainMenuUI::NewGame);
}

void UMainMenuUI::NewGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("New Game Function Is Working!!!"));
}

void UMainMenuUI::LoadGame()
{

}

void UMainMenuUI::ExitGame()
{

}