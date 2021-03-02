// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#include "SpaceMouseDevice.h"
#include "Curves/CurveFloat.h"
//#include "App.h"

#include "EngineGlobals.h"
#include "Engine/Engine.h"

#include "hidapi.h"

namespace SmDevDetails
{
    template<typename TResult>
    void ApplyMovement(FSpaceMouseDevice* Self, float fx, float fy, float fz, float DeltaSecs, const FMovementSettings& Settings, TResult& Output)
    {
        Self->Moving = true;

        FVector xmap = Settings.XAxisMap;
        FVector ymap = Settings.YAxisMap;
        FVector zmap = Settings.ZAxisMap;

        fx = FSpaceMouseDevice::GetCurvedFloat(Settings.Curve, fx);
        fy = FSpaceMouseDevice::GetCurvedFloat(Settings.Curve, fy);
        fz = FSpaceMouseDevice::GetCurvedFloat(Settings.Curve, fz);

        auto NewTrl = TResult(
            fx * xmap.X + fy * xmap.Y + fz * xmap.Z,
            fx * ymap.X + fy * ymap.Y + fz * ymap.Z,
            fx * zmap.X + fy * zmap.Y + fz * zmap.Z
        ) * Settings.UnitsPerSec * DeltaSecs;

#if USE_MOST_SIGNIFICANT_AXES_ONLY
        if(NewTrl.Size() > Translation.Size())
#endif
        {
            Output = NewTrl;
        }
    }
}

// SpacePilot Pro had troubles with filtering only the most significant axis data for a frame
// So disabling first with a preprocessor in the hope that it won't cause trouble in other devices either.
#define USE_MOST_SIGNIFICANT_AXES_ONLY 0

float FSpaceMouseDevice::GetCurvedFloat(const FRichCurve* curve, float ff)
{
    if(curve && FMath::Abs(ff) > SMALL_NUMBER)
        return curve->Eval(FMath::Abs(ff)) * FMath::Sign(ff);
    else return ff;
}

TSharedPtr<FSpaceMouseDevice> FSpaceMouseDevice::NewDevice()
{
    auto res = MakeShared<FSpaceMouseDevice>();
    res->FriendlyDeviceName = FriendlyDeviceName;
    return res;
}

#define CHECK_AXES() \
    (  xx <= SPACEMOUSE_AXIS_RESOLUTION \
    && yy <= SPACEMOUSE_AXIS_RESOLUTION \
    && zz <= SPACEMOUSE_AXIS_RESOLUTION \
    && -xx >= -SPACEMOUSE_AXIS_RESOLUTION \
    && -yy >= -SPACEMOUSE_AXIS_RESOLUTION \
    && -zz >= -SPACEMOUSE_AXIS_RESOLUTION \
    )

void FSpaceMouseDevice::Tick(float DeltaSecs)
{
    if (!DeviceOpened) return;

    uint8* pOutput = &OutputBuffer[0];
    int ctr = 0;

    PrevMoving = MovementTimed > 0;
    Moving = false;

    bool dReceived = false;
    FString dReport;

#if USE_MOST_SIGNIFICANT_AXES_ONLY
    Translation = {0,0,0};
    Rotation = {0,0,0};
#endif

    while (hid_read(Device, pOutput, GetReportSize() * 4) > 0 && ctr < UserSettings.MaxReads)
    {
        dReceived = true;
        if(UserSettings.bPrintDebug)
        {
            dReport += FString::FromHexBlob(pOutput, GetReportSize());
        }
        uint8* pCurrentReport = pOutput;
        for (int i = 0; i < 4; i++)
        {
            const uint8 report = *pCurrentReport;

            int16 xx = *reinterpret_cast<int16*>(pCurrentReport + 1);
            int16 yy = *reinterpret_cast<int16*>(pCurrentReport + 3);
            int16 zz = *reinterpret_cast<int16*>(pCurrentReport + 5);

            float fx = static_cast<float>(xx) / SPACEMOUSE_AXIS_RESOLUTION;
            float fy = static_cast<float>(yy) / SPACEMOUSE_AXIS_RESOLUTION;
            float fz = static_cast<float>(zz) / SPACEMOUSE_AXIS_RESOLUTION;

            if (report == 0 && UserSettings.bPrintDebug)
            {
                dr0 = FString::FromHexBlob(pCurrentReport, 7);
            }

            if (report == 1 && CHECK_AXES())
            {
                ApplyTranslation(fx, fy, fz, DeltaSecs);
#if USE_MOST_SIGNIFICANT_AXES_ONLY
                if(NewTrl.Size() > Translation.Size())
#endif
                {
                    if(UserSettings.bPrintDebug) dr1 = FString::FromHexBlob(pCurrentReport, GetReportSize());
                }
            }
            if (report == 2 && CHECK_AXES())
            {
                ApplyRotation(fx, fy, fz, DeltaSecs);

#if USE_MOST_SIGNIFICANT_AXES_ONLY
                if(NewRot.Euler().Size() > Rotation.Euler().Size())
#endif
                {
                    if (UserSettings.bPrintDebug) dr2 = FString::FromHexBlob(pCurrentReport, GetReportSize());
                }
            }
            if (report == 3)
            {
                ApplyButtons(pCurrentReport);
            }
            pCurrentReport += GetReportSize();
        }
        ctr++;
    }

#if WITH_EDITOR
    if (UserSettings.bPrintDebug && dReceived)
    {
        PrintDebugInfo(dReport);
    }
#endif
    TickMovementState(DeltaSecs);
}

void FSpaceMouseDevice::TickMovementState(float DeltaSecs)
{
    if(Moving) MovementTimed = UserSettings.MovementTimeTolerance;
    OnMovementStartedFrame = MovementTimed > 0 && !PrevMoving;
    MovementTimed -= DeltaSecs;
    OnMovementEndedFrame = MovementTimed <= 0 && PrevMoving;
}

void FSpaceMouseDevice::PrintDebugInfo(FString dreport)
{
    auto message = FString::Printf(
        TEXT("Device: %s\n")
        TEXT("  Serial: %s\n")
        TEXT("  VID: 0x%04x\n")
        TEXT("  PID: 0x%04x\n")
        TEXT("  Report:\n")
        TEXT("    %s\n")
        TEXT("  Sorted:\n")
        TEXT("    %s\n")
        TEXT("    %s\n")
        TEXT("    %s\n")
        TEXT("    %s\n"),
        *FriendlyDeviceName,
        DeviceInfo->serial_number,
        DeviceInfo->vendor_id,
        DeviceInfo->product_id,
        *dreport,
        *dr0, *dr1, *dr2, *dr3
    );
    GEngine->AddOnScreenDebugMessage(2010 + InternalID, 10.0, FColor::Orange, message);
}

void FSpaceMouseDevice::ApplyTranslation(float fx, float fy, float fz, float DeltaSecs)
{
    SmDevDetails::ApplyMovement(this, fx, fy, fz, DeltaSecs, UserSettings.Translation, Translation);
}

void FSpaceMouseDevice::ApplyRotation(float fp, float fy, float fr, float DeltaSecs)
{
    SmDevDetails::ApplyMovement(this, fp, fy, fr, DeltaSecs, UserSettings.Rotation, Rotation);
}

void FSpaceMouseDevice::ApplyButtons(uint8* Report)
{
    int ii = 0;
    for (int j = 0; j < 6; j++)
    {
        for (int k = 0; k < 8; k++)
        {
            Buttons[ii] = (1 << k & static_cast<uint8>(*(Report + 1 + j))) > 0;
            ii++;
        }
    }

    if (UserSettings.bPrintDebug) dr3 = FString::FromHexBlob(Report, GetReportSize());
}

#undef CHECK_AXES

void FSpaceMouseDevice::Initialize(hid_device_info* dev, int iid)
{
    Translation = FVector::ZeroVector;
    Rotation = FRotator::ZeroRotator;

    InternalID = iid;
    PrevMoving = false;
    Moving = false;
    OnMovementStartedFrame = false;
    DeviceInfo = dev;
    Device = hid_open_path(dev->path);
    DeviceOpened = Device != nullptr;

    Buttons.Empty(SPACEMOUSE_BUTTONCOUNT);
    Buttons.AddZeroed(SPACEMOUSE_BUTTONCOUNT);

    if (DeviceOpened) hid_set_nonblocking(Device, 1);
}

#define CHECK_AXES() \
    (  xx <= SPACEMOUSE_AXIS_RESOLUTION \
    && yy <= SPACEMOUSE_AXIS_RESOLUTION \
    && zz <= SPACEMOUSE_AXIS_RESOLUTION \
    && rxx <= SPACEMOUSE_AXIS_RESOLUTION \
    && ryy <= SPACEMOUSE_AXIS_RESOLUTION \
    && rzz <= SPACEMOUSE_AXIS_RESOLUTION \
    && -xx >= -SPACEMOUSE_AXIS_RESOLUTION \
    && -yy >= -SPACEMOUSE_AXIS_RESOLUTION \
    && -zz >= -SPACEMOUSE_AXIS_RESOLUTION \
    && -rxx >= -SPACEMOUSE_AXIS_RESOLUTION \
    && -ryy >= -SPACEMOUSE_AXIS_RESOLUTION \
    && -rzz >= -SPACEMOUSE_AXIS_RESOLUTION \
    )

TSharedPtr<FSpaceMouseDevice> FSingleReportPosRotSmDevice::NewDevice()
{
    auto res = MakeShared<FSingleReportPosRotSmDevice>();
    res->FriendlyDeviceName = FriendlyDeviceName;
    return res;
}

void FSingleReportPosRotSmDevice::Tick(float DeltaSecs)
{
    if (!DeviceOpened) return;

    uint8* pOutput = &OutputBuffer[0];
    int ctr = 0;

    PrevMoving = MovementTimed > 0;
    Moving = false;

    bool dReceived = false;
    FString dReport;

#if USE_MOST_SIGNIFICANT_AXES_ONLY
    Translation = { 0,0,0 };
    Rotation = { 0,0,0 };
#endif

    while (hid_read(Device, pOutput, GetReportSize() * 4) > 0 && ctr < UserSettings.MaxReads)
    {
        dReceived = true;
        if (UserSettings.bPrintDebug)
        {
            dReport += FString::FromHexBlob(pOutput, GetReportSize());
        }
        uint8* pCurrentReport = pOutput;
        for (int i = 0; i < 4; i++)
        {
            const uint8 report = *pCurrentReport;
            /*int16 xx = *(pCurr + 1) | (uint16)(*(pCurr + 2)) << 8;
            int16 yy = *(pCurr + 3) | (uint16)(*(pCurr + 4)) << 8;
            int16 zz = *(pCurr + 5) | (uint16)(*(pCurr + 6)) << 8;*/

            int16 xx = *reinterpret_cast<int16*>(pCurrentReport + 1);
            int16 yy = *reinterpret_cast<int16*>(pCurrentReport + 3);
            int16 zz = *reinterpret_cast<int16*>(pCurrentReport + 5);
            int16 rxx = *reinterpret_cast<int16*>(pCurrentReport + 7);
            int16 ryy = *reinterpret_cast<int16*>(pCurrentReport + 9);
            int16 rzz = *reinterpret_cast<int16*>(pCurrentReport + 11);

            float fx = static_cast<float>(xx) / SPACEMOUSE_AXIS_RESOLUTION;
            float fy = static_cast<float>(yy) / SPACEMOUSE_AXIS_RESOLUTION;
            float fz = static_cast<float>(zz) / SPACEMOUSE_AXIS_RESOLUTION;
            float rfx = static_cast<float>(rxx) / SPACEMOUSE_AXIS_RESOLUTION;
            float rfy = static_cast<float>(ryy) / SPACEMOUSE_AXIS_RESOLUTION;
            float rfz = static_cast<float>(rzz) / SPACEMOUSE_AXIS_RESOLUTION;

            if (report == 0 && UserSettings.bPrintDebug)
            {
                dr0 = FString::FromHexBlob(pCurrentReport, GetReportSize());
            }

            if (report == 1 && CHECK_AXES())
            {
                Moving = true;

                ApplyTranslation(fx, fy, fz, DeltaSecs);
                
#if USE_MOST_SIGNIFICANT_AXES_ONLY
                if (NewTrl.Size() > Translation.Size())
#endif
                {
                    if (UserSettings.bPrintDebug) dr1 = FString::FromHexBlob(pCurrentReport, GetReportSize());
                }

                ApplyRotation(rfx, rfy, rfz, DeltaSecs);
                
#if USE_MOST_SIGNIFICANT_AXES_ONLY
                if (NewRot.Euler().Size() > Rotation.Euler().Size())
#endif
                {
                    if (UserSettings.bPrintDebug) dr2 = FString::FromHexBlob(pCurrentReport, GetReportSize());
                }
            }
            else if (report == 3)
            {
                ApplyButtons(pCurrentReport);
            }
            pCurrentReport += GetReportSize();
        }
        ctr++;
    }

#if WITH_EDITOR
    if (UserSettings.bPrintDebug && dReceived)
    {
        PrintDebugInfo(dReport);
    }
#endif

    TickMovementState(DeltaSecs);
}

#undef CHECK_AXES

void FTestSmDevice::Tick(float DeltaSecs)
{
    FSpaceMouseDevice::Tick(DeltaSecs);

#if WITH_EDITOR
    GEngine->AddOnScreenDebugMessage(2010 + InternalID, 10.0, FColor::Orange, TEXT("TESTING DEVICE TYPE"));
#endif
}
