// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"

#define PrintScreen(bEnable, Duration, Color, Format, ...) \
    if (GEngine && bEnable) GEngine->AddOnScreenDebugMessage(-1, Duration, FColor::Color, FString::Printf(TEXT(Format), ##__VA_ARGS__))

/**
 * 
 */
class GRIEF_API Debug
{
public:

	// May or may not add complicated functionalities later on!
	Debug();
	~Debug();
};
