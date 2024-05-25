// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapsMenuUI.generated.h"

DECLARE_DELEGATE(FButtonAction);

UCLASS()
class GRIEF_API UMapsMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UMapsMenuUI(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnOne;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnTwo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnThree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnFour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UButton*> BtnArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UImage*> IMGArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UTextBlock*> TxtArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateColor HoveredColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateColor NormalColor;

	UPROPERTY(BlueprintReadWrite)
	int32 BtnArrIndex;

	UPROPERTY(BlueprintReadWrite)
	int32 LastVisitedIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TransformLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWidgetTransform TargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InterpAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InterpSpeed;

	TMap<int32, FButtonAction> BtnAction;

	UPROPERTY(BlueprintReadWrite)
	bool bLastKeyboardInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MapsHUD")
	bool bChildHudOpen;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MapsHUD")
	class UUserWidget* CurrentMapUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapsHUD")
	TSubclassOf<class UUserWidget> MapOneUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapsHUD")
	TSubclassOf<class UUserWidget> MapTwoUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapsHUD")
	TSubclassOf<class UUserWidget> MapThreeUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapsHUD")
	TSubclassOf<class UUserWidget> MapFourUI;

	UPROPERTY()
	class AMyPlayerController* PlayerController;

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetupButtons();

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void MapOne();

	UFUNCTION()
	void MapTwo();

	UFUNCTION()
	void MapThree();

	UFUNCTION()
	void MapFour();

	UFUNCTION()
	void OpenMap(TSubclassOf<class UUserWidget> Map);

	UFUNCTION()
	void CloseChildUI();

	UFUNCTION()
	void NavigateToNextButton(float ActionValue);

	UFUNCTION()
	void OnHoveredMapOneButton();

	UFUNCTION()
	void OnHoveredMapTwoButton();

	UFUNCTION()
	void OnHoveredMapThreeButton();

	UFUNCTION()
	void OnHoveredMapFourButton();

	void ReverseButtonAnimation(int32 Index);

	void ButtonIndicator();

	void InterpColor();
};
