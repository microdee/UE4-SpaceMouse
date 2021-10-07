// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

#include "SmUserSettings.h"

class FMovementState;
struct FRichCurve;
struct FProcessedDeviceOutput;
class FDebugInfoPrinter;
class FActiveHidSmDevice;

DECLARE_MULTICAST_DELEGATE(FDataReadEvent)

struct SPACEMOUSEREADER_API FDataReadingOutput
{
    TSharedPtr<FProcessedDeviceOutput> ProcessedData;
    TSharedPtr<FProcessedDeviceOutput> NormData;
    TSharedPtr<FDebugInfoPrinter> Debug;
    TSharedPtr<FActiveHidSmDevice> HidDevice;
    TSharedPtr<FMovementState> MovementState;
    FUserSettings Settings;
};

/**
 * Base class to encapsulate and configure input data to be used by the device
 */
class SPACEMOUSEREADER_API FDataReadingMethod
{
public:
    FDataReadingMethod();
    virtual ~FDataReadingMethod();
    
    FDataReadEvent OnDataReceived;
    
    virtual int GetAxisResolution() { return 350; }
    static float GetCurvedFloat(const FRichCurve* curve, float ff);
    
    virtual void Tick(FDataReadingOutput& Output, float DeltaSecs);

protected:

    static void TickMovementState(FDataReadingOutput& Output, float DeltaSecs);

    static void ApplyTranslation(FDataReadingOutput& Output, float fx, float fy, float fz, float DeltaSecs);
    static void ApplyRotation(FDataReadingOutput& Output, float fp, float fy, float fr, float DeltaSecs);
};
