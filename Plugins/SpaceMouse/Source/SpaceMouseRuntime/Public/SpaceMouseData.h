// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "TimerManager.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpaceMouseManager.h"
#include "Misc/App.h"

#include "SpaceMouseData.generated.h"

/**
 * 
 */
UCLASS()
class SPACEMOUSERUNTIME_API USpaceMouseData : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static bool bFrameRequested;

	static FTimerDelegate OnTickDel;

	static FSpaceMouseManager Manager;

	UFUNCTION(BlueprintPure, Category="SpaceMouse", meta=(WorldContext="WorldContextObj"))
	static void GetSpaceMouseData(
		UObject* WorldContextObj,

		FVector& DeltaTranslation,
		FRotator& DeltaRotation,
		TArray<bool>& Buttons
	);
};
