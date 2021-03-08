// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#include "SpaceMouseManager.h"
#include "SpaceMouseReader.h"

#include "hidapi.h"
#include "MovementState.h"
#include "DeviceTypes/DeviceFactory.h"
#include "DeviceTypes/SmDevice.h"

#if WITH_EDITOR
#include "EngineGlobals.h"
#include "Engine/Engine.h"
#endif

void FSpaceMouseManager::Initialize()
{
    PrevAccumulatedData = AccumulatedData = {};
    MovementState = MakeShared<FMovementState>();

    Devices.Empty();
    FDeviceFactory Factory {};
    Factory.OpenConnectedDevices(GetUserSettings(), Devices);
    
    Enabled = true;
    DeviceOpened = Devices.Num() > 0;
}

void FSpaceMouseManager::Tick(float DeltaSecs)
{
    PrevAccumulatedData = AccumulatedData;
    AccumulatedData = {};

    MovementState->AccumulationReset();
    
    for (auto SmDevice : Devices)
    {
        SmDevice->Tick(DeltaSecs);
        AccumulatedData += SmDevice->Data;
        MovementState->Accumulate(SmDevice->MovementState);
    }

#if WITH_EDITOR
    if (GetUserSettings().bPrintDebug)
    {
        FString Message = TEXT("Connected SpaceMice: ") + FString::FromInt(Devices.Num());

        for (const auto SmDevice : Devices)
        {
            Message += TEXT("\n    Device: ") + SmDevice->DeviceName;
        }
        
        GEngine->AddOnScreenDebugMessage(
            2000, 1.0, FColor::Cyan,
            Message
        );
    }
#endif
}