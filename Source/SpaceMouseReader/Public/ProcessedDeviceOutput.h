// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

#include "SmButtons.h"
#include "Containers/StaticBitArray.h"

/**
 * 
 */
struct SPACEMOUSEREADER_API FSmProcessedDeviceOutput
{
    FVector Translation {0,0,0};
    FRotator Rotation {0,0,0};
    FButtonBits Buttons;

    FSmProcessedDeviceOutput operator+(const FSmProcessedDeviceOutput& other) const;
    FSmProcessedDeviceOutput operator+(TSharedPtr<FSmProcessedDeviceOutput> other) const;
    FSmProcessedDeviceOutput&& operator+=(const FSmProcessedDeviceOutput& other);
    FSmProcessedDeviceOutput&& operator+=(TSharedPtr<FSmProcessedDeviceOutput> other);
};
