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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UButton*> BtnArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UWidgetAnimation*> BtnAnimationArr;

	UPROPERTY(BlueprintReadWrite)
	int32 BtnArrIndex;

	TMap<int32, FButtonAction> BtnAction;

	UPROPERTY(BlueprintReadWrite)
	bool bLastKeyboardInput;

protected:
	virtual void NativeConstruct() override;

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
	void NavigateToNextButton(float ActionValue);
};
