// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE


#include "DeviceTypes/SmDevice.h"


#include "DebugInfoPrinter.h"
#include "MovementState.h"
#include "ProcessedDeviceOutput.h"
#include "DeviceTypes/ButtonCapabilities.h"
#include "ReadingMethod/ActiveHidSmDevice.h"
#include "ReadingMethod/DataReadingMethod.h"

FSmDevice::FSmDevice(
    const FString DeviceName,
    const ESmModelConfidence ModelConfidence,
    const TSharedPtr<FSmButtonCapabilities> Buttons,
    const TSharedPtr<FSmDataReadingMethod> DataReadingMethod,
    const FSmDeviceInstantiation& InstanceData
)   : DeviceName(DeviceName)
    , ModelConfidence(ModelConfidence)
    , InternalID(InstanceData.InternalID)
    , UserSettings(InstanceData.UserSettings)
    , Buttons(Buttons)
    , DataReadingMethod(DataReadingMethod)
    , HidDevice(InstanceData.HidDevice)
{
}

FSmDevice::~FSmDevice()
{
}

void FSmDevice::TickInit()
{
    if(!bInited)
    {
        bInited = true;
        ProcessedData = MakeShared<FSmProcessedDeviceOutput>();
        NormData = MakeShared<FSmProcessedDeviceOutput>();
        DebugInfoPrinter = MakeShared<FSmDebugInfoPrinter>();
        MovementState = MakeShared<FSmMovementState>();

        DataReadingMethod->OnDataReceived.AddLambda([this]()
        {
            DebugInfoPrinter->Print(
                DeviceName,
                HidDevice ? HidDevice->DeviceInfo : nullptr,
                InternalID,
                UserSettings().bPrintDebug
            );
        });
    }
}

void FSmDevice::Tick(float DeltaSeconds)
{
    TickInit();

    ProcessedData->Buttons = NormData->Buttons;
    FSmDataReadingOutput Output
    {
        ProcessedData,
        NormData,
        DebugInfoPrinter,
        HidDevice,
        MovementState,
        UserSettings()
    };
    DataReadingMethod->Tick(Output, DeltaSeconds);
    Buttons->TransformRawData(ProcessedData);
    // Buttons->TransformRawData(NormData); // NormData keeps the HID buttons from the device
}
