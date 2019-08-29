// Copyright 1998-2019 David Morasz All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define SPACEMOUSE_BUTTONCOUNT 48
#define SPACEMOUSE_AXIS_RESOLUTION 350

struct hid_device_;
typedef struct hid_device_ hid_device;

struct hid_device_info;

class SPACEMOUSEREADER_API FSpaceMouseDevice
{
protected:
	bool PrevMoving;

	FString dr0;
	FString dr1;
	FString dr2;
	FString dr3;
public:

    bool bPrintDebug = false;

    int MaxReads = 2048;
    float TranslationUnitsPerSec = 1000;
    FVector XTranslationAxisMap = FVector(0, -1,  0);
    FVector YTranslationAxisMap = FVector(1,  0,  0);
    FVector ZTranslationAxisMap = FVector(0,  0, -1);
    
    float RotationDegreesPerSec = 270;
    FVector PitchAxisMap = FVector(1,  0,  0);
    FVector YawAxisMap   = FVector(0,  0,  1);
    FVector RollAxisMap  = FVector(0, -1,  0);

	int InternalID = 0;
	hid_device* Device;
	hid_device_info* DeviceInfo;

	bool DeviceOpened;
	unsigned char OutputBuffer[80];

	FVector Translation;
	FRotator Rotation;
	TArray<bool> Buttons;

	bool OnMovementStartedFrame = false;
	bool OnMovementEndedFrame = false;
	bool Moving = false;

	virtual FSpaceMouseDevice* NewDevice() { return new FSpaceMouseDevice(); }

	virtual int GetReportSize() { return 7; }

	virtual void Tick(float DeltaSecs);

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
	virtual FSpaceMouseDevice* NewDevice() override { return new FSingleReportPosRotSmDevice(); }

	virtual int GetReportSize() override { return 13; }

	virtual void Tick(float DeltaSecs) override;
};