// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArrangeMapsWidgetUI.generated.h"

DECLARE_DELEGATE(FButtonAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestroyWidget);

UCLASS()
class GRIEF_API UArrangeMapsWidgetUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UArrangeMapsWidgetUI(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnMapOne;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnMapTwo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnMapThree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnMapFour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UButton*> BtnArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UButton*> ChoiceArr;

	UPROPERTY(BlueprintReadWrite)
	int32 ChoiceArrIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UWidgetAnimation*> BtnAnimationArr;

	UPROPERTY(BlueprintReadWrite)
	int32 BtnArrIndex;

	UPROPERTY(BlueprintReadWrite)
	int32 LastVisitedIndex;

	UPROPERTY(BlueprintReadWrite)
	bool bLastKeyboardInput;

	UPROPERTY(BlueprintAssignable)
	FOnDestroyWidget OnDestroyWidget;

	TMap<int32, FButtonAction> BtnAction;

protected:
	virtual void NativeConstruct() override;

	void SetupButtons();

	UFUNCTION()
	void MapOnePlacement();

	UFUNCTION()
	void MapTwoPlacement();

	UFUNCTION()
	void MapThreePlacement();

	UFUNCTION()
	void MapFourPlacement();

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void NavigateToNextButton(float ActionValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "Player")
	void OnUpdateEvent();

	UFUNCTION(BlueprintImplementableEvent, Category = "Player")
	void OnChoosingWrongEvent();
};
