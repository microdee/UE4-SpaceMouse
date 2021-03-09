// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"


#include "Buttons.h"
#include "ProcessedDeviceOutput.h"
#include "UserSettings.h"
#include "Containers/StaticBitArray.h"

class FSmDevice;
class FMovementState;

class SPACEMOUSEREADER_API FSpaceMouseManager
{
protected:

    FProcessedDeviceOutput PrevAccumulatedData;
    FProcessedDeviceOutput AccumulatedData;
    FProcessedDeviceOutput NormalizedData;
    TArray<TSharedPtr<FSmDevice>> Devices;

    virtual FUserSettings GetUserSettings() = 0;

public:
    virtual ~FSpaceMouseManager() = default;

    FVector FORCEINLINE GetTranslation() const { return AccumulatedData.Translation; }
    FRotator FORCEINLINE GetRotation() const { return AccumulatedData.Rotation; }
    TStaticBitArray<64> FORCEINLINE GetButtons() const { return AccumulatedData.Buttons; }
    
    TSharedPtr<FMovementState> MovementState;

    bool Enabled = false;
    virtual void Tick(float DeltaSecs);
    virtual void Initialize();

    int LastErrorCode;
    bool DeviceOpened;

    bool ButtonDownFrame(EV3DCmd Button);
    bool ButtonUpFrame(EV3DCmd Button);
};
