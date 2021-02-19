// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

#include "UserSettings.h"

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

    FUserSettings UserSettings {};

    int InternalID = 0;
    hid_device* Device = nullptr;
    hid_device_info* DeviceInfo = nullptr;

    bool DeviceOpened = false;
    uint8 OutputBuffer[80];

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
    void TickMovementState(float DeltaSecs);

    virtual void PrintDebugInfo(FString dreport);

    void ApplyTranslation(float fx, float fy, float fz, float DeltaSecs);
    void ApplyRotation(float fp, float fy, float fr, float DeltaSecs);
    void ApplyButtons(uint8* Report);

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