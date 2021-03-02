// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CommonBehaviors.generated.h"

/**
 * 
 */
UCLASS()
class SPACEMOUSEREADER_API UCommonBehaviors : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:

    UFUNCTION(BlueprintPure, Category=SpaceMouse)
    static FVector GetOrbitingTranslationDelta(
        FVector Pivot,
        FRotator CurrentRotation,
        FRotator RotationDelta,
        float Distance,
        bool bWithRoll
    );
};
