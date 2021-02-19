// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

#define SPACEMOUSE_BUTTONCOUNT 48
#define SPACEMOUSE_AXIS_RESOLUTION 350

struct hid_device_;
struct FRichCurve;
typedef struct hid_device_ hid_device;

struct hid_device_info;

class SPACEMOUSEREADER_API FSpaceMouseDevice
{
protected:
    bool PrevMoving = false;

    FString dr0 {};
    FString dr1 {};
    FString dr2 {};
    FString dr3 {};

    float MovementTimed = 0.0f;
public:

    bool bPrintDebug = false;

    int MaxReads = 2048;
    float MovementTimeTolerance = 0.25;
    float TranslationUnitsPerSec = 1000;
    FVector XTranslationAxisMap {0, -1,  0};
    FVector YTranslationAxisMap {1,  0,  0};
    FVector ZTranslationAxisMap {0,  0, -1};
    const FRichCurve* TranslationCurve = nullptr;
    
    float RotationDegreesPerSec = 270;
    FVector PitchAxisMap {1,  0,  0};
    FVector YawAxisMap   {0,  0,  1};
    FVector RollAxisMap  {0, -1,  0};
    const FRichCurve* RotationCurve = nullptr;

    int InternalID = 0;
    hid_device* Device = nullptr;
    hid_device_info* DeviceInfo = nullptr;

    bool DeviceOpened = false;
    unsigned char OutputBuffer[80];

    FVector Translation {0,0,0};
    FRotator Rotation {0,0,0};
    TArray<bool> Buttons;

    bool OnMovementStartedFrame = false;
    bool OnMovementEndedFrame = false;
    bool Moving = false;

    FString FriendlyDeviceName {};

    static float GetCurvedFloat(const FRichCurve* curve, float ff);

    virtual TSharedPtr<FSpaceMouseDevice> NewDevice();

    virtual int GetReportSize() { return 7; }

    virtual void Tick(float DeltaSecs);

    virtual void PrintDebugInfo(FString dreport);

    void Initialize(hid_device_info* dev, int iid);

    FSpaceMouseDevice() { }
    //FSpaceMouseDevice( FSpaceMouseDevice& other ) { };

    virtual ~FSpaceMouseDevice()
    {
        /*if(DeviceOpened)
            hid_close(Device);*/
    }
};

class SPACEMOUSEREADER_API FSingleReportPosRotSmDevice : public FSpaceMouseDevice
{
    virtual TSharedPtr<FSpaceMouseDevice> NewDevice() override;

    virtual int GetReportSize() override { return 13; }

    virtual void Tick(float DeltaSecs) override;
};

class SPACEMOUSEREADER_API FTestSmDevice : public FSpaceMouseDevice
{
    virtual TSharedPtr<FSpaceMouseDevice> NewDevice() override { return MakeShared<FTestSmDevice>(); }

    virtual int GetReportSize() override
    {
        return 7;
    }

    virtual void Tick(float DeltaSecs) override;
};