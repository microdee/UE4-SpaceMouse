// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "TimerManager.h"
#include "LevelEditorViewport.h"
#include "Hid.h"

class FSpaceMouseModule : public IModuleInterface
{
private:

	FTimerDelegate OnTickDel;
	void OnTick();
	unsigned char OutputBuffer[80];

	FVector Translation;
	FVector Rotation;
	bool Buttons[48];

	FEditorViewportClient* ActiveViewportClient;

public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	float Resolution = 350.0;

	hid_device * Device;
	bool DeviceOpened;
	//hid_device_info * DeviceInfos;
};
