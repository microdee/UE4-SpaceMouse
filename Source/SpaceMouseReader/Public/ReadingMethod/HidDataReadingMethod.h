// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserSettings.h"

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
 * Class encapsulating a method to convert raw HID input into usable data
 */
class SPACEMOUSEREADER_API FHidDataReadingMethod
{
public:
    FHidDataReadingMethod();
    virtual ~FHidDataReadingMethod();
    
    FDataReadEvent OnDataReceived;
    
    virtual int GetReportSize() { return 7; }
    virtual int GetReportCount() { return 4; }
    virtual int GetAxisResolution() { return 350; }

    virtual void Tick(FDataReadingOutput& Output, float DeltaSecs);
    virtual void ReadData(FDataReadingOutput& Output, float DeltaSecs, uint8* Report) = 0;
    
    static float GetCurvedFloat(const FRichCurve* curve, float ff);

protected:
    
    uint8 OutputBuffer[80];

    static void TickMovementState(FDataReadingOutput& Output, float DeltaSecs);

    static void ApplyTranslation(FDataReadingOutput& Output, float fx, float fy, float fz, float DeltaSecs);
    static void ApplyRotation(FDataReadingOutput& Output, float fp, float fy, float fr, float DeltaSecs);
    void ApplyButtons(FDataReadingOutput& Output, uint8* Report, int ReportID = 3);
};
