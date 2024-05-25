// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/ToolsMenuUI.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Debug/Debug.h"

UToolsMenuUI::UToolsMenuUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Btn = nullptr;
	bCanAnim = false;
	bSwitchAnim = false;

	Index = 0;
	Direction = 0.0f;
}

void UToolsMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerRef = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<AMotherRabbit>();
	if (PlayerRef)
	{
		PlayerRef->OnPressingNavigationAction.AddDynamic(this, &UToolsMenuUI::NavigateToNextButton);
		PlayerRef->OnPressingEnterAction.AddDynamic(this, &UToolsMenuUI::Purchase);

		UpdateUI();
	}

	Btn->OnClicked.AddDynamic(this, &UToolsMenuUI::Purchase);
	Btn->SetKeyboardFocus();
}

void UToolsMenuUI::NavigateToNextButton(float ActionValue)
{
	if (ActionValue < 0.0f && (Index != Item.Num()-1))
	{
		Index++;

		if (Item[Index].bOwnItem != Item[Index-1].bOwnItem)
		{
			bSwitchAnim = true;
		}
	}
	else if (ActionValue > 0.0f && (Index != 0))
	{
		Index--;

		if (Item[Index].bOwnItem != Item[Index+1].bOwnItem)
		{
			bSwitchAnim = true;
		}
	}
	else if (ActionValue < 0.0f && (Index == Item.Num()-1))
	{
		Index = 0;

		if (Item[0].bOwnItem != Item[Item.Num() - 1].bOwnItem)
		{
			bSwitchAnim = true;
		}
	}
	else
	{
		Index = Item.Num()-1;

		if (Item[0].bOwnItem != Item[Item.Num() - 1].bOwnItem)
		{
			bSwitchAnim = true;
		}
	}
	Direction = ActionValue;
	bCanAnim = true;	

	if (!Item[Index].bOwnItem)
	{
		PrintScreen(15.0f, FColor::Blue, "Hi, Purchase from the function!!!");
		NonPurchasedPlayEvent();
	}
	else
	{
		PrintScreen(15.0f, FColor::Red, "Bye, Purchase from the function!!!");
		NonPurchasedReverseEvent();
	}

	OnNavigationChangeEvent();
}

void UToolsMenuUI::Purchase()
{
	int32 PlayerCoins = PlayerRef->GetCollectedCoins();

	if (PlayerCoins > Item[Index].ItemCost && !(Item[Index].bOwnItem))
	{
		PlayerRef->SetCollectedCoins(PlayerCoins - Item[Index].ItemCost);
		Item[Index].bOwnItem = true;

		UpdatePlayerData();
		PurchaseEvent();
		UpdateUI();

		PrintScreen(10.0f, FColor::Blue, "Purchased: %s", *Item[Index].ItemName);
	}
}

void UToolsMenuUI::UpdatePlayerData()
{
	FPlayerItemStruct PlayerItem;

	PlayerItem.ItemName = Item[Index].ItemName;
	PlayerItem.bOwnItem = Item[Index].bOwnItem;

	PlayerRef->PlayerItem.Add(PlayerItem);
}

void UToolsMenuUI::UpdateUI()
{
	CurrentCoins->SetText(FText::AsNumber(PlayerRef->GetCollectedCoins()));
	//ItemUsage->SetText(FText::FromString(TEXT("You Own This Item")));
	UsageEvent();
}