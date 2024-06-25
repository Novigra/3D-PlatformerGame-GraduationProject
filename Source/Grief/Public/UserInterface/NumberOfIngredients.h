// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "NumberOfIngredients.generated.h"

/**
 * 
 */
UCLASS()
class GRIEF_API UNumberOfIngredients : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Number;

public:
	FORCEINLINE void SetNumberText(int32 CurrentNumber) { Number->SetText(FText::AsNumber(CurrentNumber)); }
};
