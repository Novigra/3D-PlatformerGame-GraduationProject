// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUI.generated.h"

/**
 * 
 */
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

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void NewGame();

	UFUNCTION()
	void LoadGame();

	UFUNCTION()
	void ExitGame();
};
