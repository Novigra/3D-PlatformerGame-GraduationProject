// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class GRIEF_API UDialogueMenuUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UDialogueMenuUI(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Speaker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Dialogue;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay|Characters")
	class AMotherRabbit* Player;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay|Characters")
	class ANPC* NPC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|Characters")
	int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	TSubclassOf<class UUserWidget> MissionIndicationUI;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void NextDialogueText();
};
