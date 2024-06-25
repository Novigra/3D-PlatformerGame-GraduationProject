// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToolsMenuUI.generated.h"

USTRUCT(BlueprintType)
struct FItemStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDetails")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDetails")
	FString ItemDesc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDetails")
	FString ItemDetails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDetails")
	FString ItemLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDetails")
	float ItemCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDetails")
	bool bOwnItem;
};

UCLASS()
class GRIEF_API UToolsMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UToolsMenuUI(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<FItemStruct> Item;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* Btn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* CurrentCoins;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ItemUsage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	bool bCanAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	bool bSwitchAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anim")
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	class AMotherRabbit* PlayerRef;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void NavigateToNextButton(float ActionValue);

	UFUNCTION()
	void Purchase();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "UpdateItemUsage"))
	void UsageEvent();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "UpdatePurchaseUI"))
	void PurchaseEvent();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "UpdateNonPurchasedUI"))
	void NonPurchasedPlayEvent();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "UpdateNonPurchasedReverseUI"))
	void NonPurchasedReverseEvent();
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnNavigationChangeUI"))
	void OnNavigationChangeEvent();

	void UpdatePlayerData();

	void UpdateUI();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnLoadingGameSuccessUIUpdate"))
	void OnLoadingEvent();
};
