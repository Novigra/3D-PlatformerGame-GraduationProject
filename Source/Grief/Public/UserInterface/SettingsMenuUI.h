// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class GRIEF_API USettingsMenuUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	USettingsMenuUI(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> TestWidgetSwitcherClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	class UUserWidget* TestWidgetSwitcher;

protected:
	virtual void NativeConstruct() override;
};
