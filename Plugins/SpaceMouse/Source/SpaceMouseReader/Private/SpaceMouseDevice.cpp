// Copyright 1998-2019 David Morasz All Rights Reserved.

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

	PrevMoving = Moving;
	Moving = false;

	bool drecieved = false;
	FString dreport;

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

				Translation = FVector(
					fx * xmap.X + fy * xmap.Y + fz * xmap.Z,
					fx * ymap.X + fy * ymap.Y + fz * ymap.Z,
					fx * zmap.X + fy * zmap.Y + fz * zmap.Z
				) * TranslationUnitsPerSec * DeltaSecs;

				if(bPrintDebug) dr1 = FString::FromHexBlob(pCurr, GetReportSize());
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
				
				Rotation = FRotator(
					fx * xmap.X + fy * xmap.Y + fz * xmap.Z,
					fx * ymap.X + fy * ymap.Y + fz * ymap.Z,
					fx * zmap.X + fy * zmap.Y + fz * zmap.Z
				) * RotationDegreesPerSec * DeltaSecs;

				if (bPrintDebug) dr2 = FString::FromHexBlob(pCurr, GetReportSize());
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
		FString message = "Device: ";
		message += "Serial: " + FString(DeviceInfo->serial_number) + "\n";
		message += "VID: " + FString::FromInt(DeviceInfo->vendor_id) + "\n";
		message += "PID: " + FString::FromInt(DeviceInfo->product_id) + "\n";
		message += "Report:\n    ";
		message += dreport + "\n";
		message += "Sorted:\n    " + dr0 + "\n    " + dr1 + "\n    " + dr2 + "\n    " + dr3;
		GEngine->AddOnScreenDebugMessage(2010 + InternalID, 10.0, FColor::Orange, message);
	}
#endif

	OnMovementStartedFrame = Moving && !PrevMoving;
	OnMovementEndedFrame = !Moving && PrevMoving;
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

void FSingleReportPosRotSmDevice::Tick(float DeltaSecs)
{
	if (!DeviceOpened) return;

	unsigned char* pOutput = (unsigned char*)& OutputBuffer;
	int ctr = 0;

	PrevMoving = Moving;
	Moving = false;

	bool drecieved = false;
	FString dreport;

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

				Translation = FVector(
					fx * xmap.X + fy * xmap.Y + fz * xmap.Z,
					fx * ymap.X + fy * ymap.Y + fz * ymap.Z,
					fx * zmap.X + fy * zmap.Y + fz * zmap.Z
				) * TranslationUnitsPerSec * DeltaSecs;

				if (bPrintDebug) dr1 = FString::FromHexBlob(pCurr, GetReportSize());

				xmap = PitchAxisMap;
				ymap = YawAxisMap;
				zmap = RollAxisMap;

				Rotation = FRotator(
					rfx * xmap.X + rfy * xmap.Y + rfz * xmap.Z,
					rfx * ymap.X + rfy * ymap.Y + rfz * ymap.Z,
					rfx * zmap.X + rfy * zmap.Y + rfz * zmap.Z
				) * RotationDegreesPerSec * DeltaSecs;

				if (bPrintDebug) dr2 = FString::FromHexBlob(pCurr, GetReportSize());
			}
			else if (report == 3)
			{
				int ii = 0;
				for (int j = 0; j < 6; j++)
				{
					for (int k = 0; k < 8; k++)
					{
						Buttons[ii] = (1 << k & (unsigned char) * (pCurr + 1 + j)) > 0;
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
		FString message = "Device: ";
		message += "Serial: " + FString(DeviceInfo->serial_number) + "\n";
		message += "VID: " + FString::FromInt(DeviceInfo->vendor_id) + "\n";
		message += "PID: " + FString::FromInt(DeviceInfo->product_id) + "\n";
		message += "Report:\n    ";
		message += dreport + "\n";
		message += "Sorted:\n    " + dr0 + "\n    " + dr1 + "\n    " + dr2 + "\n    " + dr3;
		GEngine->AddOnScreenDebugMessage(2010 + InternalID, 10.0, FColor::Orange, message);
	}
#endif

	OnMovementStartedFrame = Moving && !PrevMoving;
	OnMovementEndedFrame = !Moving && PrevMoving;
}

#undef CHECK_AXES

void FTestSmDevice::Tick(float DeltaSecs)
{
	FSpaceMouseDevice::Tick(DeltaSecs);

#if WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(2010 + InternalID, 10.0, FColor::Orange, "TESTING DEVICE TYPE");
#endif
}
