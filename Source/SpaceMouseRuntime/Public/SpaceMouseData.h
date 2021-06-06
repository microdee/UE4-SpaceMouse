// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"
#include "TimerManager.h"
#include "Kismet/BlueprintFunctionLibrary.h"
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

    UFUNCTION(
        BlueprintPure,
        Category = "SpaceMouse"
    )
    static void GetSpaceMouseDeltaAxes(
        FVector& DeltaTranslation,
        FRotator& DeltaRotation
    );
    
    UFUNCTION(
        BlueprintPure,
        Category = "SpaceMouse"
    )
    static void GetSpaceMouseAxes(
        FVector& NormalizedTranslation,
        FRotator& NormalizedRotation
    );

    UFUNCTION(
        BlueprintPure,
        Category = "SpaceMouse"
    )
    static bool GetSpaceMouseButtonState(int Id);

    UFUNCTION(
        BlueprintPure,
        Category = "SpaceMouse"
    )
    static bool GetSpaceMouseButtonDown(int Id);

    UFUNCTION(
        BlueprintPure,
        Category = "SpaceMouse"
    )
    static bool GetSpaceMouseButtonUp(int Id);
};
