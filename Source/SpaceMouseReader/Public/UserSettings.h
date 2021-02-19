// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UserSettings.generated.h"

USTRUCT(BlueprintType)
struct FMovementSettings
{
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    FVector XAxisMap {0, -1,  0};
    
    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    FVector YAxisMap {1,  0,  0};
    
    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    FVector ZAxisMap {0,  0, -1};
    
    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    float UnitsPerSec = 1000;
    
    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    const FRichCurve* Curve = nullptr;
    
};

USTRUCT(BlueprintType)
struct SPACEMOUSEREADER_API FUserSettings
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    bool bPrintDebug = false;
    
    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    int MaxReads = 2048;
    
    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    float MovementTimeTolerance = 0.25;

    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    FMovementSettings Translation
    {
        {0, -1,  0},
        {1,  0,  0},
        {0,  0, -1},
        1000.0f
    };

    UPROPERTY(BlueprintReadWrite, Category=SpaceMouse)
    FMovementSettings Rotation
    {
        {0, -1,  0},
        {1,  0,  0},
        {0,  0,  1},
        270.0f
    };
};
