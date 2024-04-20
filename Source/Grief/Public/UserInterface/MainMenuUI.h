// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUI.generated.h"

DECLARE_DELEGATE(FButtonAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseAction);

UCLASS()
class GRIEF_API UMainMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainMenuUI(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnNewGame;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnLoadGame;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnExitGame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UButton*> BtnArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UWidgetAnimation*> BtnAnimationArr;

	UPROPERTY(BlueprintReadWrite)
	int32 BtnArrIndex;

	// Store previous BtnArrIndex
	int32 Temp;

	UPROPERTY(BlueprintReadWrite)
	bool bLastKeyboardInput;

	UPROPERTY(BlueprintAssignable)
	FOnCloseAction OnCloseAction;

	TMap<int32, FButtonAction> BtnAction;

protected:
	virtual void NativeConstruct() override;

	void SetupButtons();

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void NewGame();

	UFUNCTION()
	void LoadGame();

	UFUNCTION()
	void ExitGame();

	UFUNCTION()
	void NavigateToNextButton(float ActionValue);

	UFUNCTION()
	void OnHoveredNewGameButton();

	UFUNCTION()
	void OnHoveredLoadGameButton();

	UFUNCTION()
	void OnHoveredExitGameButton();

	UFUNCTION()
	void OnUnHoveredButton();

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
