// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SControlsUI.generated.h"

DECLARE_DELEGATE(FButtonAction);

UENUM(BlueprintType)
enum class EActionType : uint8
{
	EAT_Movement		UMETA(DisplayName = "MovementAction"),
	EAT_Jump			UMETA(DisplayName = "JumpAction"),
	EAT_NONE			UMETA(DisplayName = "None")
};

USTRUCT(BlueprintType)
struct FControls
{
	GENERATED_BODY()

	FKey MovementForwardLockedKey;
	FKey MovementBackwardLockedKey;
	FKey MovementRightLockedKey;
	FKey MovementLeftLockedKey;
	FKey JumpLockedKey;
};

UCLASS()
class GRIEF_API USControlsUI : public UUserWidget
{
	GENERATED_BODY()

public:
	USControlsUI(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	class AMotherRabbit* PlayerRef;

	UPROPERTY()
	class AMyPlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnMoveForward;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnMoveBackward;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnMoveRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnMoveLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TArray<class UImage*> CurrentKeyImage;

	UPROPERTY()
	FKey CurrentKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UButton*> BtnArr;

	UPROPERTY(BlueprintReadWrite)
	int32 BtnArrIndex;

	UPROPERTY(BlueprintReadWrite)
	int32 LastVisitedIndex;

	UPROPERTY(BlueprintReadWrite)
	bool bLastKeyboardInput;

	UPROPERTY(BlueprintReadWrite)
	bool bEditKey;

	UPROPERTY(BlueprintReadWrite)
	EActionType ActionType;

	UPROPERTY(BlueprintReadWrite)
	FControls CurrentControls;

	UPROPERTY(BlueprintReadWrite)
	FKey EditKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UWidgetAnimation*> BtnAnimationArr;

	TMap<int32, FButtonAction> BtnAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD|ChildMenu")
	class UUserWidget* CurrentChildUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD|ChildMenu")
	TSubclassOf<class UUserWidget> KeyChangeMenuUI;
	
protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UFUNCTION()
	void SetupButtons();

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void NavigateToNextButton(float ActionValue);

	UFUNCTION()
	void MoveForwardOption();

	UFUNCTION()
	void MoveBackwardOption();

	UFUNCTION()
	void MoveRightOption();

	UFUNCTION()
	void MoveLeftOption();

	UFUNCTION()
	void JumpOption();

	UFUNCTION()
	void UpdateKeyBindings(UInputMappingContext* IMC, UInputAction* InputAction, FKey Key);

	UFUNCTION()
	void UpdateKeyImage(FKey Key);

	UFUNCTION()
	void OpenChildUI();

	UFUNCTION()
	void CloseChildUI();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "UpdateScroll"))
	void UpdateScrollEvent();

};
