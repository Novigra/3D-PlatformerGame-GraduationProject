// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GRIEF_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<class UUserWidget> StartupHUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD)
	class UUserWidget* CurrentHUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD)
	class AMotherRabbit* MyPlayer;

	// Calculate how many number of (Children) widgets are open
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	int32 NumberOfOpenChildren;

	UFUNCTION()
	void CloseHUDOverlay();

private:
	void SetHUDStartup();

	UFUNCTION()
	void SwitchHUDOverlay();

protected:
	virtual void BeginPlay() override;
};
