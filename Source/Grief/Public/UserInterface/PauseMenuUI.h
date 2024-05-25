// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuUI.generated.h"

DECLARE_DELEGATE(FButtonAction);

UCLASS()
class GRIEF_API UPauseMenuUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPauseMenuUI(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnContinue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnLoad;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnMaps;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnTools;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnSettings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnReturn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnQuit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UOverlay* Diamond_Overlay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UHorizontalBox* ChildUI_HorizontalBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UButton*> BtnArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UWidgetAnimation*> BtnAnimationArr;

	UPROPERTY(BlueprintReadWrite)
	int32 BtnArrIndex;

	UPROPERTY(BlueprintReadWrite)
	int32 LastVisitedIndex;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite)
	float TransformLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWidgetTransform TargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InterpSpeed;

	TMap<int32, FButtonAction> BtnAction;

	UPROPERTY(BlueprintReadWrite)
	bool bLastKeyboardInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	bool bChildHudOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD|ChildMenus")
	class UUserWidget* CurrentChildUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD|ChildMenus")
	TSubclassOf<class UUserWidget> MapMenuUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD|ChildMenus")
	TSubclassOf<class UUserWidget> ToolsMenuUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD|ChildMenus")
	TSubclassOf<class UUserWidget> SettingsMenuUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD|ChildMenus")
	TSubclassOf<class UUserWidget> ReturnMenuUI;

	class AMyPlayerController* PlayerController;

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetupButtons();

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void Continue();

	UFUNCTION()
	void Load();

	UFUNCTION()
	void Maps();

	UFUNCTION()
	void Tools();

	UFUNCTION()
	void Settings();

	UFUNCTION()
	void Return();

	UFUNCTION()
	void Quit();

	UFUNCTION()
	void OpenChildUI(TSubclassOf<class UUserWidget> Map);

	UFUNCTION()
	void NavigateToNextButton(float ActionValue);

	UFUNCTION()
	void OnHoveredContinueButton();

	UFUNCTION()
	void OnHoveredLoadButton();

	UFUNCTION()
	void OnHoveredMapsButton();

	UFUNCTION()
	void OnHoveredToolsButton();

	UFUNCTION()
	void OnHoveredSettingsButton();

	UFUNCTION()
	void OnHoveredReturnButton();

	UFUNCTION()
	void OnHoveredQuitButton();

	UFUNCTION()
	void CloseChildUI();

	void ReverseButtonAnimation(int32 Index);

	void ButtonIndicator();
};
