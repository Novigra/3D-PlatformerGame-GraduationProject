// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/SettingsMenuUI.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetSwitcher.h"
#include "Debug/Debug.h"

USettingsMenuUI::USettingsMenuUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Index = 0;
}

void USettingsMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerRef = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<AMotherRabbit>();
	if (PlayerRef)
	{
		PlayerRef->OnPressingPageNavigationAction.AddDynamic(this, &USettingsMenuUI::WidgetNavigation);
	}
}

void USettingsMenuUI::WidgetNavigation(float ActionValue)
{
	if (ActionValue > 0.0f && (Index != 2))
	{
		WidgetSwitcher->SetActiveWidgetIndex(++Index);
	}
	else if (ActionValue < 0.0f && (Index != 0))
	{
		WidgetSwitcher->SetActiveWidgetIndex(--Index);
	}

	Direction = ActionValue;
	UpdateSwitcherEvent();
}