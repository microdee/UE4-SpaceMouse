// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "SmUserSettings.generated.h"

struct FRichCurve;

USTRUCT(BlueprintType)
struct FSmMovementSettings
{
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    FVector XAxisMap {0, -1,  0}; // Pitch
    
    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    FVector YAxisMap {1,  0,  0}; // Yaw
    
    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    FVector ZAxisMap {0,  0, -1}; // Roll
    
    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    float UnitsPerSec = 1000;
    
    const FRichCurve* Curve = nullptr;
    
};

USTRUCT(BlueprintType)
struct SPACEMOUSEREADER_API FSmUserSettings
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    bool bPrintDebug = false;
    
    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    int MaxReads = 2048;
    
    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    float MovementTimeTolerance = 0.25;

    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    FSmMovementSettings Translation
    {
        {0, -1,  0},
        {1,  0,  0},
        {0,  0, -1},
        1000.0f
    };

    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    FSmMovementSettings Rotation
    {
        {1,  0,  0},
        {0,  0,  1},
        {0, -1,  0},
        270.0f
    };
};
