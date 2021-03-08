// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

#include "SmRuntimeManager.h"
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
    static FSmRuntimeManager Manager;
    
    static void LazyInit(UObject* WorldContextObj);

    UFUNCTION(
        BlueprintPure,
        Category = "SpaceMouse",
        meta = ( WorldContext = "WorldContextObj" )
    )
    static void GetSpaceMouseAxes(
        UObject* WorldContextObj,
        FVector& DeltaTranslation,
        FRotator& DeltaRotation
    );

    UFUNCTION(
        BlueprintPure,
        Category = "SpaceMouse",
        meta = ( WorldContext = "WorldContextObj" )
    )
    static bool GetSpaceMouseButtonState(UObject* WorldContextObj, int Id);

    UFUNCTION(
        BlueprintPure,
        Category = "SpaceMouse",
        meta = ( WorldContext = "WorldContextObj" )
    )
    static bool GetSpaceMouseButtonDown(UObject* WorldContextObj, int Id);

    UFUNCTION(
        BlueprintPure,
        Category = "SpaceMouse",
        meta = ( WorldContext = "WorldContextObj" )
    )
    static bool GetSpaceMouseButtonUp(UObject* WorldContextObj, int Id);
};
