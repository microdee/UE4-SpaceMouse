// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "SpaceMouseDevice.h"

#define BUTTONDOWN(id) (Buttons[id] && !PrevButtons[id])
#define BUTTONUP(id) (!Buttons[id] && PrevButtons[id])

class SPACEMOUSEREADER_API FSpaceMouseManager
{
protected:

	FVector Translation;
	FRotator Rotation;
	TArray<bool> PrevButtons;
	TArray<bool> Buttons;

	TArray<TSharedPtr<FSpaceMouseDevice>> Devices;
	hid_device_info * DeviceInfos;

public:

    FVector FORCEINLINE GetTranslation() { return Translation; }
    FRotator FORCEINLINE GetRotation() { return Rotation; }
	TArray<bool> FORCEINLINE GetButtons() { return Buttons; }
    
	bool OnMovementStartedFrame = false;
	bool OnMovementEndedFrame = false;

    bool bPrintDebug = false;

    FSpaceMouseManager() { }
	virtual ~FSpaceMouseManager()
	{
		Devices.Empty();
	}

	bool Enabled = false;
	virtual void Tick(float DeltaSecs);
    virtual void Initialize();

	int LastErrorCode;

	bool DeviceOpened;
};