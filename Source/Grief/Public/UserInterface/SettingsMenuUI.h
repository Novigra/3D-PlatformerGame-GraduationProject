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

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	class AMotherRabbit* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Switcher")
	int32 Index;

	UPROPERTY(BlueprintReadOnly, Category = "Switcher")
	float Direction;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> TestWidgetSwitcherClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	class UUserWidget* TestWidgetSwitcher;*/

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void WidgetNavigation(float ActionValue);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "UpdateSwitcherVisuals"))
	void UpdateSwitcherEvent();
};
