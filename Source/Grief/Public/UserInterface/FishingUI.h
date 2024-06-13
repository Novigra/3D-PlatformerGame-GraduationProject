// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FishingUI.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	EMS_Left		UMETA(DisplayName = "Left"),
	EMS_Right		UMETA(DisplayName = "Right")
};

UCLASS()
class GRIEF_API UFishingUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFishingUI(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	class AMotherRabbit* PlayerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* NeedleProgressBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class USlider* ArrowHeadSlider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TimerNumLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic")
	EMovementState MovementState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameLogic|NeedleSpeed")
	float NeedleProgressNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|NeedleSpeed")
	float NeedleProgressSpeedRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|NeedleSpeed")
	float DefaultSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|NeedleSpeed")
	float SpeedUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|NeedleSpeed")
	float SpeedDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|Timers")
	float MovementChangeDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|Timers")
	float Timer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|Timers")
	float TimerRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|CatchProperties")
	float SuccessRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|CatchProperties")
	float SuccessGoal;

	/*
	* Levels indicate how fast the success rate should grow
	* 
	* Level0 -> The highest range
	* Level1 -> The medium range
	* Level2 -> The lowest range
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|CatchProperties|Levels|Level0")
	float MinLevel0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|CatchProperties|Levels|Level0")
	float MaxLevel0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|CatchProperties|Levels|Level0")
	float SpeedLevel0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|CatchProperties|Levels|Level1")
	float MinLevel1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|CatchProperties|Levels|Level1")
	float MaxLevel1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|CatchProperties|Levels|Level1")
	float SpeedLevel1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|CatchProperties|Levels|Level2")
	float MinLevel2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|CatchProperties|Levels|Level2")
	float MaxLevel2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic|CatchProperties|Levels|Level2")
	float SpeedLevel2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameLogic")
	TSubclassOf<class UUserWidget> SuccessMenuUI;

	UPROPERTY()
	FTimerHandle TimerHandle;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void ChangeMovement();

	UFUNCTION()
	void ControlNeedle(float ActionValue);

	UFUNCTION()
	void CalculateSuccess(float DeltaTime);

	UFUNCTION()
	void CalculateTimer(float DeltaTime);
};
