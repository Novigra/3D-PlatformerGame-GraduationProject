// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MotherRabbit/MyPlayerController.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/MotherRabbit/PlayerGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

AMyPlayerController::AMyPlayerController()
{
	NumberOfOpenChildren = 0;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetHUDStartup();
}

void AMyPlayerController::SetHUDStartup()
{
	MyPlayer = Cast<AMotherRabbit>(GetCharacter());
	
	// What menu to show at the beginning of the game (MainMenuUI)
	if (StartupHUD)
	{
		CurrentHUD = CreateWidget<UUserWidget>(this, StartupHUD);
		CurrentHUD->AddToViewport();

		MyPlayer->OnPressingBackAction.AddDynamic(this, &AMyPlayerController::CloseHUDOverlay);

		SetInputMode(FInputModeGameAndUI());
		SetShowMouseCursor(true);
	}

	// TODO: the StartupHUD is not set, so use this for (debug only). Deal with it after fully finishing UI system :)
	MyPlayer->OnPressingClosingAction.AddDynamic(this, &AMyPlayerController::CloseHUDOverlay);
}

void AMyPlayerController::SwitchHUDOverlay()
{

}

void AMyPlayerController::CloseHUDOverlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Closing Widget %s ..."), *CurrentHUD->GetClass()->GetName()));

	CurrentHUD->RemoveFromRoot();
	//CurrentHUD->RemoveFromParent();
	CurrentHUD->RemoveFromViewport();

	MyPlayer->RemovePlayerAllMappingContexts();
	MyPlayer->SetPlayerMappingContext(MyPlayer->MovementMappingContext, 0);
	SetInputMode(FInputModeGameOnly());
	SetShowMouseCursor(false);
}