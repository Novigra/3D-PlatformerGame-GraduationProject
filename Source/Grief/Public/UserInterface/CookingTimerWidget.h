// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "CookingTimerWidget.generated.h"

/**
 * 
 */
UCLASS()
class GRIEF_API UCookingTimerWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Timer;
	
public:
	FORCEINLINE void SetTimerText(int CurrentTimer) { Timer->SetText(FText::AsNumber(CurrentTimer)); }
};
