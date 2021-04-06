// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserSettings.h"

class FMovementState;
class FDebugInfoPrinter;
class FDataReadingMethod;
class FButtonCapabilities;
class FActiveHidSmDevice;
struct FProcessedDeviceOutput;

/**
 * Used to pass dynamic data to 
 */
struct SPACEMOUSEREADER_API FSmDeviceInstantiation
{
    int InternalID = 0;
    TSharedPtr<FActiveHidSmDevice> HidDevice;
    TFunction<FUserSettings()> UserSettings;
};

enum class ESmModelConfidence : uint8
{
    Tested,
    TestedViaFeedback,
    UntestedShouldWork,
    Unknown,
    Unsupported
};

/**
 * Root object for containing spacemouse components 
 */
class SPACEMOUSEREADER_API FSmDevice
{
public:
    FSmDevice(
        const FString DeviceName,
        const ESmModelConfidence ModelConfidence,
        const TSharedPtr<FButtonCapabilities> Buttons,
        const TSharedPtr<FDataReadingMethod> DataReadingMethod,
        const FSmDeviceInstantiation& InstanceData
    );
    ~FSmDevice();

    FString DeviceName;
    ESmModelConfidence ModelConfidence;
    int InternalID;
    TFunction<FUserSettings()> UserSettings;
    TSharedPtr<FButtonCapabilities> Buttons;
    TSharedPtr<FDataReadingMethod> DataReadingMethod;
    TSharedPtr<FActiveHidSmDevice> HidDevice;
    TSharedPtr<FProcessedDeviceOutput> NormData;
    TSharedPtr<FProcessedDeviceOutput> ProcessedData;
    TSharedPtr<FMovementState> MovementState;
    TSharedPtr<FDebugInfoPrinter> DebugInfoPrinter;

    void Tick(float DeltaSeconds);

private:

    bool bInited = false;
    void TickInit();
};
