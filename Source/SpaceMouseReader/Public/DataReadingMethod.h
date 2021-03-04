// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UserSettings.h"

struct FRichCurve;
struct FProcessedDeviceOutput;
struct FDebugInfoPrinter;

typedef struct hid_device_ hid_device;

DECLARE_MULTICAST_DELEGATE(FMovementEvent)
DECLARE_MULTICAST_DELEGATE(FDataReadEvent)

struct SPACEMOUSEREADER_API FDataReadingOutput
{
    TSharedPtr<FProcessedDeviceOutput> Data;
    TSharedPtr<FDebugInfoPrinter> Debug;
};

/**
 * Class encapsulating a method to convert raw HID input into usable data
 */
class SPACEMOUSEREADER_API FDataReadingMethod
{
public:
    FDataReadingMethod();
    virtual ~FDataReadingMethod();

    FMovementEvent OnMovementStarted;
    FMovementEvent OnMovementEnded;
    FDataReadEvent OnDataReceived;

    bool OnMovementStartedFrame = false;
    bool OnMovementEndedFrame = false;
    bool Moving = false;
    
    FUserSettings UserSettings {};
    
    virtual int GetReportSize() { return 7; }
    virtual int GetReportCount() { return 4; }
    virtual int GetAxisResolution() { return 350; }

    virtual void Tick(hid_device* Device, FDataReadingOutput& Output, float DeltaSecs);
    virtual void ReadData(FDataReadingOutput& Output, float DeltaSecs, uint8* Report) = 0;
    
    static float GetCurvedFloat(const FRichCurve* curve, float ff);

protected:
    
    uint8 OutputBuffer[80];
    bool PrevMoving = false;
    float MovementTimed = 0.0f;
    
    void TickMovementState(float DeltaSecs);
    
    void ApplyTranslation(FDataReadingOutput& Output, float fx, float fy, float fz, float DeltaSecs);
    void ApplyRotation(FDataReadingOutput& Output, float fp, float fy, float fr, float DeltaSecs);
    void ApplyButtons(FDataReadingOutput& Output, uint8* Report, int ReportID = 3);
};
