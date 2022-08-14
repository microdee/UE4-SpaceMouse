// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"


#include "SmButtons.h"
#include "ProcessedDeviceOutput.h"
#include "SmUserSettings.h"
#include "Containers/StaticBitArray.h"

class FSmDevice;
class FSmMovementState;

class SPACEMOUSEREADER_API FSpaceMouseManager
{
protected:

    FSmProcessedDeviceOutput PrevAccumulatedData;
    FSmProcessedDeviceOutput AccumulatedData;
    FSmProcessedDeviceOutput NormalizedData;
    TArray<TSharedPtr<FSmDevice>> Devices;

    virtual FSmUserSettings GetUserSettings() = 0;

public:
    virtual ~FSpaceMouseManager() = default;

    FVector FORCEINLINE GetTranslation() const { return AccumulatedData.Translation; }
    FRotator FORCEINLINE GetRotation() const { return AccumulatedData.Rotation; }
    FVector FORCEINLINE GetNormalizedTranslation() const { return NormalizedData.Translation; }
    FRotator FORCEINLINE GetNormalizedRotation() const { return NormalizedData.Rotation; }
    FButtonBits FORCEINLINE GetButtons() const { return AccumulatedData.Buttons; }
    
    TSharedPtr<FSmMovementState> MovementState;

    bool Enabled = false;
    virtual void Tick(float DeltaSecs);
    virtual void Initialize();

    int LastErrorCode;
    bool DeviceOpened;

    bool ButtonDownFrame(EV3DCmd Button);
    bool ButtonUpFrame(EV3DCmd Button);
};
