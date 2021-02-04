// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#include "SpaceMouseDevice.h"
#include "Curves/CurveFloat.h"
//#include "App.h"

#if WITH_EDITOR
#include "EngineGlobals.h"
#include "Engine/Engine.h"
#endif

#include "hidapi.h"

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

    unsigned char* pOutput = (unsigned char*)&OutputBuffer;
    int ctr = 0;

    PrevMoving = MovementTimed > 0;
    Moving = false;

    bool drecieved = false;
    FString dreport;

    Translation = {0,0,0};
    Rotation = {0,0,0};

    while (hid_read(Device, pOutput, GetReportSize() * 4) > 0 && ctr < MaxReads)
    {
        drecieved = true;
        if(bPrintDebug)
        {
            dreport += FString::FromHexBlob(pOutput, GetReportSize());
        }
        unsigned char* pCurr = pOutput;
        for (int i = 0; i < 4; i++)
        {
            unsigned char report = *pCurr;
            /*int16 xx = *(pCurr + 1) | (uint16)(*(pCurr + 2)) << 8;
            int16 yy = *(pCurr + 3) | (uint16)(*(pCurr + 4)) << 8;
            int16 zz = *(pCurr + 5) | (uint16)(*(pCurr + 6)) << 8;*/

            int16 xx = *(int16*)(pCurr + 1);
            int16 yy = *(int16*)(pCurr + 3);
            int16 zz = *(int16*)(pCurr + 5);

            float fx = (float)xx / SPACEMOUSE_AXIS_RESOLUTION;
            float fy = (float)yy / SPACEMOUSE_AXIS_RESOLUTION;
            float fz = (float)zz / SPACEMOUSE_AXIS_RESOLUTION;

            if (report == 0 && bPrintDebug)
            {
                dr0 = FString::FromHexBlob(pCurr, 7);
            }

            if (report == 1 && CHECK_AXES())
            {
                Moving = true;

                FVector xmap = XTranslationAxisMap;
                FVector ymap = YTranslationAxisMap;
                FVector zmap = ZTranslationAxisMap;

                fx = GetCurvedFloat(TranslationCurve, fx);
                fy = GetCurvedFloat(TranslationCurve, fy);
                fz = GetCurvedFloat(TranslationCurve, fz);

                auto NewTrl = FVector(
                    fx * xmap.X + fy * xmap.Y + fz * xmap.Z,
                    fx * ymap.X + fy * ymap.Y + fz * ymap.Z,
                    fx * zmap.X + fy * zmap.Y + fz * zmap.Z
                ) * TranslationUnitsPerSec * DeltaSecs;

                if(NewTrl.Size() > Translation.Size())
                {
                    Translation = NewTrl;
                    if(bPrintDebug) dr1 = FString::FromHexBlob(pCurr, GetReportSize());
                }
            }
            if (report == 2 && CHECK_AXES())
            {
                Moving = true;

                FVector xmap = PitchAxisMap;
                FVector ymap = YawAxisMap;
                FVector zmap = RollAxisMap;

                fx = GetCurvedFloat(RotationCurve, fx);
                fy = GetCurvedFloat(RotationCurve, fy);
                fz = GetCurvedFloat(RotationCurve, fz);
                
                auto NewRot = FRotator(
                    fx * xmap.X + fy * xmap.Y + fz * xmap.Z,
                    fx * ymap.X + fy * ymap.Y + fz * ymap.Z,
                    fx * zmap.X + fy * zmap.Y + fz * zmap.Z
                ) * RotationDegreesPerSec * DeltaSecs;

                if(NewRot.Euler().Size() > Rotation.Euler().Size())
                {
                    Rotation = NewRot;
                    if (bPrintDebug) dr2 = FString::FromHexBlob(pCurr, GetReportSize());
                }
            }
            if (report == 3)
            {
                int ii = 0;
                for (int j = 0; j < 6; j++)
                {
                    for (int k = 0; k < 8; k++)
                    {
                        Buttons[ii] = (1 << k & (unsigned char)*(pCurr + 1 + j)) > 0;
                        ii++;
                    }
                }

                if (bPrintDebug) dr3 = FString::FromHexBlob(pCurr, GetReportSize());
            }
            pCurr += GetReportSize();
        }
        ctr++;
    }

#if WITH_EDITOR
    if (bPrintDebug && drecieved)
    {
        PrintDebugInfo(dreport);
    }
#endif

    if(Moving) MovementTimed = MovementTimeTolerance;
    OnMovementStartedFrame = MovementTimed > 0 && !PrevMoving;
    OnMovementEndedFrame = MovementTimed <= 0 && PrevMoving;
    MovementTimed -= DeltaSecs;
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

    unsigned char* pOutput = (unsigned char*)&OutputBuffer;
    int ctr = 0;

    PrevMoving = MovementTimed > 0;
    Moving = false;

    bool drecieved = false;
    FString dreport;

    Translation = { 0,0,0 };
    Rotation = { 0,0,0 };

    while (hid_read(Device, pOutput, GetReportSize() * 4) > 0 && ctr < MaxReads)
    {
        drecieved = true;
        if (bPrintDebug)
        {
            dreport += FString::FromHexBlob(pOutput, GetReportSize());
        }
        unsigned char* pCurr = pOutput;
        for (int i = 0; i < 4; i++)
        {
            unsigned char report = *pCurr;
            /*int16 xx = *(pCurr + 1) | (uint16)(*(pCurr + 2)) << 8;
            int16 yy = *(pCurr + 3) | (uint16)(*(pCurr + 4)) << 8;
            int16 zz = *(pCurr + 5) | (uint16)(*(pCurr + 6)) << 8;*/

            int16 xx = *(int16*)(pCurr + 1);
            int16 yy = *(int16*)(pCurr + 3);
            int16 zz = *(int16*)(pCurr + 5);
            int16 rxx = *(int16*)(pCurr + 7);
            int16 ryy = *(int16*)(pCurr + 9);
            int16 rzz = *(int16*)(pCurr + 11);

            float fx = GetCurvedFloat(TranslationCurve, (float)xx / SPACEMOUSE_AXIS_RESOLUTION);
            float fy = GetCurvedFloat(TranslationCurve, (float)yy / SPACEMOUSE_AXIS_RESOLUTION);
            float fz = GetCurvedFloat(TranslationCurve, (float)zz / SPACEMOUSE_AXIS_RESOLUTION);
            float rfx = GetCurvedFloat(RotationCurve, (float)rxx / SPACEMOUSE_AXIS_RESOLUTION);
            float rfy = GetCurvedFloat(RotationCurve, (float)ryy / SPACEMOUSE_AXIS_RESOLUTION);
            float rfz = GetCurvedFloat(RotationCurve, (float)rzz / SPACEMOUSE_AXIS_RESOLUTION);

            if (report == 0 && bPrintDebug)
            {
                dr0 = FString::FromHexBlob(pCurr, GetReportSize());
            }

            if (report == 1 && CHECK_AXES())
            {
                Moving = true;

                FVector xmap = XTranslationAxisMap;
                FVector ymap = YTranslationAxisMap;
                FVector zmap = ZTranslationAxisMap;

                auto NewTrl = FVector(
                    fx * xmap.X + fy * xmap.Y + fz * xmap.Z,
                    fx * ymap.X + fy * ymap.Y + fz * ymap.Z,
                    fx * zmap.X + fy * zmap.Y + fz * zmap.Z
                ) * TranslationUnitsPerSec * DeltaSecs;

                if (NewTrl.Size() > Translation.Size())
                {
                    Translation = NewTrl;
                    if (bPrintDebug) dr1 = FString::FromHexBlob(pCurr, GetReportSize());
                }

                xmap = PitchAxisMap;
                ymap = YawAxisMap;
                zmap = RollAxisMap;

                auto NewRot = FRotator(
                    rfx * xmap.X + rfy * xmap.Y + rfz * xmap.Z,
                    rfx * ymap.X + rfy * ymap.Y + rfz * ymap.Z,
                    rfx * zmap.X + rfy * zmap.Y + rfz * zmap.Z
                ) * RotationDegreesPerSec * DeltaSecs;


                if (NewRot.Euler().Size() > Rotation.Euler().Size())
                {
                    Rotation = NewRot;
                    if (bPrintDebug) dr2 = FString::FromHexBlob(pCurr, GetReportSize());
                }
            }
            else if (report == 3)
            {
                int ii = 0;
                for (int j = 0; j < 6; j++)
                {
                    for (int k = 0; k < 8; k++)
                    {
                        Buttons[ii] = (1 << k & (unsigned char)*(pCurr + 1 + j)) > 0;
                        ii++;
                    }
                }

                if (bPrintDebug) dr3 = FString::FromHexBlob(pCurr, GetReportSize());
            }
            pCurr += GetReportSize();
        }
        ctr++;
    }

#if WITH_EDITOR
    if (bPrintDebug && drecieved)
    {
        PrintDebugInfo(dreport);
    }
#endif

    if (Moving) MovementTimed = MovementTimeTolerance;
    OnMovementStartedFrame = MovementTimed > 0 && !PrevMoving;
    OnMovementEndedFrame = MovementTimed <= 0 && PrevMoving;
    MovementTimed -= DeltaSecs;
}

#undef CHECK_AXES

void FTestSmDevice::Tick(float DeltaSecs)
{
    FSpaceMouseDevice::Tick(DeltaSecs);

#if WITH_EDITOR
    GEngine->AddOnScreenDebugMessage(2010 + InternalID, 10.0, FColor::Orange, TEXT("TESTING DEVICE TYPE"));
#endif
}
