// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/FishingUI.h"
#include "Components/ProgressBar.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Characters/MotherRabbit/MotherRabbit.h"
#include "Characters/NPC/NPC.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/GameplayHUDUI.h"
#include "Debug/Debug.h"

UFishingUI::UFishingUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MovementState = EMovementState::EMS_Left;

	Timer = 10.0f;
	SuccessRate = 0.0f;
	SuccessGoal = 60.0f;
}

void UFishingUI::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerRef = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<AMotherRabbit>();
	if (PlayerRef)
	{
		PlayerRef->OnActivatingFishingAction.AddDynamic(this, &UFishingUI::ControlNeedle);
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UFishingUI::ChangeMovement, MovementChangeDelay, true);
}

void UFishingUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	switch (MovementState)
	{
	case EMovementState::EMS_Left:
		NeedleProgressNumber = FMath::Clamp(NeedleProgressNumber + (NeedleProgressSpeedRate * InDeltaTime), 0.0f, 1.0f);
		//NeedleProgressBar->SetPercent(NeedleProgressNumber);
		ArrowHeadSlider->SetValue(NeedleProgressNumber);
		break;
	case EMovementState::EMS_Right:
		NeedleProgressNumber = FMath::Clamp(NeedleProgressNumber - (NeedleProgressSpeedRate * InDeltaTime), 0.0f, 1.0f);
		//NeedleProgressBar->SetPercent(NeedleProgressNumber);
		ArrowHeadSlider->SetValue(NeedleProgressNumber);
		break;
	default:
		break;
	}

	//SuccessRate += NeedleProgressNumber;
	//PrintScreen(false, 2.0f, FColor::Green, "Success Rate = %f", SuccessRate);

	CalculateSuccess(InDeltaTime);
	CalculateTimer(InDeltaTime);
}

void UFishingUI::ChangeMovement()
{
	//int32 State = static_cast<int>(MovementState);
	int32 State = FMath::RandRange(0, 1);
	switch (State)
	{
	case 0:
		MovementState = EMovementState::EMS_Right;
		PrintScreen(true, 5.0f, FColor::Red, "Movement State = Right");
		break;
	case 1:
		MovementState = EMovementState::EMS_Left;
		PrintScreen(true, 5.0f, FColor::Red, "Movement State = Left");
		break;
	default:
		break;
	}
}

void UFishingUI::ControlNeedle(float ActionValue)
{
	if (ActionValue > 0.0f)
	{
		PrintScreen(false, 3.0f, FColor::Green, "Left = %f", ActionValue);

		switch (MovementState)
		{
		case EMovementState::EMS_Left:
			NeedleProgressSpeedRate = SpeedUp;
			break;
		case EMovementState::EMS_Right:
			NeedleProgressSpeedRate = -SpeedDown;
			break;
		default:
			break;
		}
	}
	else if (ActionValue < 0.0f)
	{
		PrintScreen(false, 3.0f, FColor::Green, "Right = %f", ActionValue);

		switch (MovementState)
		{
		case EMovementState::EMS_Left:
			NeedleProgressSpeedRate = -SpeedDown;
			break;
		case EMovementState::EMS_Right:
			NeedleProgressSpeedRate = SpeedUp;
			break;
		default:
			break;
		}
	}

	if (ActionValue == 0.0f)
	{
		PrintScreen(false, 3.0f, FColor::Green, "Stopped Pressing = %f", ActionValue);

		NeedleProgressSpeedRate = DefaultSpeed;
	}
}

void UFishingUI::CalculateSuccess(float DeltaTime)
{
	float Value = NeedleProgressNumber * 100;

	if (Value <= MaxLevel0 && Value >= MinLevel0)
	{
		SuccessRate += (SpeedLevel0 * DeltaTime);
		PrintScreen(false, 2.0f, FColor::Green, "Level0");
	}
	else if (Value <= MaxLevel1 && Value >= MinLevel1)
	{
		SuccessRate += (SpeedLevel1 * DeltaTime);
		PrintScreen(false, 2.0f, FColor::Orange, "Level1");
	}
	else if (Value <= MaxLevel2 && Value >= MinLevel2)
	{
		SuccessRate += (SpeedLevel2 * DeltaTime);
		PrintScreen(false, 2.0f, FColor::Red, "Level2");
	}

	PrintScreen(true, 2.0f, FColor::Green, "Success Rate = %f", SuccessRate);
}

void UFishingUI::CalculateTimer(float DeltaTime)
{
	if (Timer > 0.0f)
	{
		Timer -= (TimerRate * DeltaTime);
	}
	else
	{
		// Goal or failure-- catch or escape
		if (SuccessRate >= SuccessGoal)
		{
			APlayerController* PlayerController = Cast<APlayerController>(PlayerRef->GetController());
			if (PlayerController)
			{
				UUserWidget* Widget = CreateWidget<UUserWidget>(PlayerController, SuccessMenuUI);
				Widget->AddToViewport();
			}

			PlayerRef->ObjectiveActor->Destroy();
			PlayerRef->RemovePlayerAllMappingContexts();
			PlayerRef->SetPlayerMappingContext(PlayerRef->MovementMappingContext, 0);

			if (ANPC* NPC = Cast<ANPC>(PlayerRef->CurrentInteractNPC))
			{
				NPC->OnFinishObjective();
				NPC->SetObjectiveComplete(true);
			}

			UGameplayHUDUI* GameWidget = PlayerRef->GameplayHUDWidget;
			GameWidget->OnFinishedObjective();

			RemoveFromParent();
		}
	}
	
	TimerNumLabel->SetText(FText::AsNumber(static_cast<int>(Timer)));
}