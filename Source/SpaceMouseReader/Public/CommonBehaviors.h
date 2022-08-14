// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CommonBehaviors.generated.h"

/**
 * 
 */
UCLASS()
class SPACEMOUSEREADER_API USmCommonBehaviors : public UBlueprintFunctionLibrary
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
