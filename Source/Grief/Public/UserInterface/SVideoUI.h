// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SVideoUI.generated.h"

DECLARE_DELEGATE(FButtonAction);

UCLASS()
class GRIEF_API USVideoUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	USVideoUI(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	class AMotherRabbit* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UWidgetAnimation*> BtnAnimationArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UButton*> BtnArr;

	UPROPERTY(BlueprintReadWrite)
	int32 BtnArrIndex;

	TMap<int32, FButtonAction> BtnAction;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void SetupButtons();

	UFUNCTION()
	void SyncOption();
};
