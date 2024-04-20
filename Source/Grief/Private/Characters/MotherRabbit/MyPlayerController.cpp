// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MotherRabbit/MyPlayerController.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/MotherRabbit/PlayerGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"


void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetHUDStartup();
}

void AMyPlayerController::SetHUDStartup()
{
	MyPlayer = Cast<AMotherRabbit>(GetCharacter());
	if (StartupHUD)
	{
		CurrentHUD = CreateWidget<UUserWidget>(this, StartupHUD);
		CurrentHUD->AddToViewport();

		MyPlayer->OnPressingBackAction.AddDynamic(this, &AMyPlayerController::CloseHUDOverlay);

		SetInputMode(FInputModeGameAndUI());
		SetShowMouseCursor(true);
	}
}

void AMyPlayerController::SwitchHUDOverlay()
{

}

void AMyPlayerController::CloseHUDOverlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Closing Widget %s ..."), *CurrentHUD->GetClass()->GetName()));

	CurrentHUD->RemoveFromRoot();
	CurrentHUD->RemoveFromViewport();

	MyPlayer->RemovePlayerAllMappingContexts();
	MyPlayer->SetPlayerMappingContext(MyPlayer->MovementMappingContext, 0);
}