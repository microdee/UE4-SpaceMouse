// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "SmUserSettings.h"

class FSmMovementState;
class FSmDebugInfoPrinter;
class FSmDataReadingMethod;
class FSmButtonCapabilities;
class FActiveHidSmDevice;
struct FSmProcessedDeviceOutput;

/**
 * Used to pass dynamic data to 
 */
struct SPACEMOUSEREADER_API FSmDeviceInstantiation
{
    int InternalID = 0;
    TSharedPtr<FActiveHidSmDevice> HidDevice;
    TFunction<FSmUserSettings()> UserSettings;
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
        const TSharedPtr<FSmButtonCapabilities> Buttons,
        const TSharedPtr<FSmDataReadingMethod> DataReadingMethod,
        const FSmDeviceInstantiation& InstanceData
    );
    ~FSmDevice();

    FString DeviceName;
    ESmModelConfidence ModelConfidence;
    int InternalID;
    TFunction<FSmUserSettings()> UserSettings;
    TSharedPtr<FSmButtonCapabilities> Buttons;
    TSharedPtr<FSmDataReadingMethod> DataReadingMethod;
    TSharedPtr<FActiveHidSmDevice> HidDevice;
    TSharedPtr<FSmProcessedDeviceOutput> NormData;
    TSharedPtr<FSmProcessedDeviceOutput> ProcessedData;
    TSharedPtr<FSmMovementState> MovementState;
    TSharedPtr<FSmDebugInfoPrinter> DebugInfoPrinter;

    void Tick(float DeltaSeconds);

private:

    bool bInited = false;
    void TickInit();
};
