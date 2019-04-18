// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "TimerManager.h"
#include "LevelEditorViewport.h"
#include "Hid.h"

//General Log
DECLARE_LOG_CATEGORY_EXTERN(SpaceMouseEditor, Log, All);

#define SPACEMOUSE_BUTTONCOUNT 48

class FSpaceMouseDevice
{
public:


	hid_device* Device;
	hid_device_info* DeviceInfo;

	bool DeviceOpened;
	unsigned char OutputBuffer[80];

	FVector Translation;
	FRotator Rotation;
	bool Buttons[SPACEMOUSE_BUTTONCOUNT];

	void Tick();

	explicit FSpaceMouseDevice(hid_device_info* dev)
	{
		DeviceInfo = dev;
		Device = hid_open_path(dev->path);
		DeviceOpened = Device != nullptr;
		if (DeviceOpened) hid_set_nonblocking(Device, 1);
	}

	~FSpaceMouseDevice()
	{
		hid_close(Device);
	}
};

class FSpaceMouseModule : public IModuleInterface
{
private:

	FTimerDelegate OnTickDel;
	void OnTick();
	bool Enabled = false;

	FVector Translation;
	FRotator Rotation;
	bool PrevButtons[SPACEMOUSE_BUTTONCOUNT];
	bool Buttons[SPACEMOUSE_BUTTONCOUNT];

	TArray<FSpaceMouseDevice*> Devices;
	TArray<FEditorViewportClient*> AllViewportClients;
	FEditorViewportClient* ActiveViewportClient;
	FString focusedVpType;

public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static float gResolution;
	static float gRotSpeed;
	static float gTransSpeed;

	float Resolution = 350.0;
	float RotSpeed = 180;
	float TransSpeed = 1000;

	bool DeviceOpened;
	hid_device_info * DeviceInfos;
};
