// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Hid.h"
#include "Modules/ModuleManager.h"
#include "Editor.h"
#include "Engine.h"
#include "Editor/EditorEngine.h"
#include "Editor/UnrealEdEngine.h"
#include "UnrealClient.h"
#include "TimerManager.h"
#include "GenericPlatformMisc.h"

class FSpaceMouseModule : public IModuleInterface
{
private:
	void OnTick();
	FTimerHandle TickTimerHandle;
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	hid_device * Device;
	bool DeviceOpened;
	//hid_device_info * DeviceInfos;
};
