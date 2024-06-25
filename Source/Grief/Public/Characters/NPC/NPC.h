// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "NPC.generated.h"

UCLASS()
class GRIEF_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPCProperties")
	class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPCProperties")
	class USphereComponent* PlayerResetPlacement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPCProperties")
	class UArrowComponent* DialogueCameraPlacementArrow;

	UPROPERTY()
	class AMotherRabbit* Player;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool bStartCameraTransition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool bStartReverseCameraTransition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float CameraTransitionSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	TSubclassOf<class UUserWidget> DialogueMenuUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|DialogueDetails")
	FText NPCName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|DialogueDetails")
	TArray<FText> NameHeader;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|DialogueDetails")
	TMap<int32, FText> Dialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|DialogueDetails")
	int32 DialogueIndex;

	// Decide who starts the conversation between the player and the NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|DialogueDetails")
	bool bStartConversation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	bool bCanInteract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|ObjectiveDetails")
	int32 CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|ObjectiveDetails")
	FText CurrentObjective;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|ObjectiveDetails")
	float ObjectiveTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|ObjectiveDetails")
	bool bIsObjectiveComplete;

	// Decide whether to spawn or destroy any actor associated to the npc
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|ObjectiveDetails")
	bool bSpawnSubActor;

	// Called when the game starts or when spa.wned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void StartDialogue();

	UFUNCTION()
	void CameraTransition(float DeltaTime);

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay|ObjectiveDetails")
	int32 NumberOfCompletedSubObjectives;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OnFinishDialogue();

	UFUNCTION(BlueprintCallable)
	void OnFinishObjective();

	FORCEINLINE void SetSpawnSubActor(bool bEnable) { bSpawnSubActor = bEnable; }
	FORCEINLINE bool GetSpawnSubActor() { return bSpawnSubActor; }
	FORCEINLINE void SetStartConversation(bool bEnable) { bStartConversation = bEnable; }
	FORCEINLINE bool GetStartConversation() { return bStartConversation; }
	FORCEINLINE FText GetNPCName() { return NPCName; }
	/*
	* Used for the dialogue menu where the player interacts with the NPC.
	* @param Index: Indicates which line should be shown
	* @param bIsPlayer: indicates who is the speaker. The player or the NPC?
	*/
	//FORCEINLINE FText GetDialogue(int32 Index, bool bIsPlayer) { return bIsPlayer ? *PlayerDialogue.Find(Index) : *NPCDialogue.Find(Index); }
	FORCEINLINE void SetDialogueIndex(int32 Index) { DialogueIndex = Index; }
	FORCEINLINE int32 GetDialogueIndex() { return DialogueIndex; }
	FORCEINLINE FText GetDialogue(int32 Index) { return *Dialogue.Find(Index); }
	FORCEINLINE FText GetNameHeader(int32 Index) { return NameHeader[Index]; }
	FORCEINLINE bool SetNPCInteractionAvailability(bool bEnable) { return bCanInteract = bEnable; }
	FORCEINLINE bool GetNPCInteractionAvailability() { return bCanInteract; }
	FORCEINLINE void SetCameraSceneState(bool bEnable) { bStartCameraTransition = bEnable; }
	FORCEINLINE void SetCameraToOriginalState(bool bEnable) { bStartReverseCameraTransition = bEnable; }
	FORCEINLINE int32 GetNPCCurrentLevel() { return CurrentLevel; }
	FORCEINLINE FText GetCurrentObjective() { return CurrentObjective; }
	FORCEINLINE float GetObjectiveTimer() { return ObjectiveTimer; }
	FORCEINLINE void SetObjectiveComplete(bool Value) { bIsObjectiveComplete = Value; }
	FORCEINLINE bool GetObjectiveComplete() { return bIsObjectiveComplete; }
	FORCEINLINE FTransform GetPlayerResetPlacement() { return PlayerResetPlacement->GetComponentTransform(); }
};
