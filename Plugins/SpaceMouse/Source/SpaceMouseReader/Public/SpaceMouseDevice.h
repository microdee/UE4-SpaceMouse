// Copyright 1998-2019 David Morasz All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hid.h"

#define SPACEMOUSE_BUTTONCOUNT 48
#define SPACEMOUSE_AXIS_RESOLUTION 350

class SPACEMOUSEREADER_API FSpaceMouseDevice
{
private:
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

	virtual void Tick();

    void Initialize(hid_device_info* dev, int iid)
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

	FSpaceMouseDevice() { }
    //FSpaceMouseDevice( FSpaceMouseDevice& other ) { };

	virtual ~FSpaceMouseDevice()
	{
		/*if(DeviceOpened)
			hid_close(Device);*/
	}
};