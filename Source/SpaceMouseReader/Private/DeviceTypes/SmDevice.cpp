// Fill out your copyright notice in the Description page of Project Settings.


#include "DeviceTypes/SmDevice.h"


#include "DebugInfoPrinter.h"
#include "MovementState.h"
#include "ProcessedDeviceOutput.h"
#include "ReadingMethod/DataReadingMethod.h"

FSmDevice::FSmDevice(
    const FString DeviceName,
    const ESmModelConfidence ModelConfidence,
    const TSharedPtr<FButtonCapabilities> Buttons,
    const TSharedPtr<FDataReadingMethod> DataReadingMethod,
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
        ProcessedData = MakeShared<FProcessedDeviceOutput>();
        NormData = MakeShared<FProcessedDeviceOutput>();
        DebugInfoPrinter = MakeShared<FDebugInfoPrinter>();
        MovementState = MakeShared<FMovementState>();

        DataReadingMethod->OnDataReceived.AddLambda([this]()
        {
           DebugInfoPrinter->Print(DeviceName, HidDevice->DeviceInfo, InternalID, UserSettings().bPrintDebug); 
        });
    }
}

void FSmDevice::Tick(float DeltaSeconds)
{
    TickInit();
    
    FDataReadingOutput Output
    {
        ProcessedData,
        NormData,
        DebugInfoPrinter,
        HidDevice,
        MovementState,
        UserSettings()
    };
    DataReadingMethod->Tick(Output, DeltaSeconds);
}
