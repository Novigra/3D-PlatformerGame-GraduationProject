// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayHUDUI.generated.h"

/**
 * 
 */
UCLASS()
class GRIEF_API UGameplayHUDUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UGameplayHUDUI(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Timer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CurrentObjective;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Heart1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Heart2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Heart3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool bStartTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float CurrentTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float TimerRate;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay|Characters")
	class AMotherRabbit* Player;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay|Characters")
	class ANPC* NPC;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UWidgetAnimation* TimerAnimOpen;*/

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ObjectiveAnimationPrep"))
	void ObjectiveAnimEvent();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnFinishedObjectiveEvent"))
	void OnFinishedObjectiveEvent();

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	UFUNCTION(BlueprintCallable)
	void OnFinishedObjective();
};
