// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

#include "SmButtons.h"
#include "Containers/StaticBitArray.h"

/**
 * 
 */
struct SPACEMOUSEREADER_API FProcessedDeviceOutput
{
    FVector Translation {0,0,0};
    FRotator Rotation {0,0,0};
    FButtonBits Buttons;

    FProcessedDeviceOutput operator+(const FProcessedDeviceOutput& other) const;
    FProcessedDeviceOutput operator+(TSharedPtr<FProcessedDeviceOutput> other) const;
    FProcessedDeviceOutput&& operator+=(const FProcessedDeviceOutput& other);
    FProcessedDeviceOutput&& operator+=(TSharedPtr<FProcessedDeviceOutput> other);
};
