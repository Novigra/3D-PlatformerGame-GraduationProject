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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<class UUserWidget> StartupHUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD)
	class UUserWidget* CurrentHUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD)
	class AMotherRabbit* MyPlayer;

private:
	void SetHUDStartup();

	UFUNCTION()
	void SwitchHUDOverlay();

	UFUNCTION()
	void CloseHUDOverlay();

protected:
	virtual void BeginPlay() override;
};
