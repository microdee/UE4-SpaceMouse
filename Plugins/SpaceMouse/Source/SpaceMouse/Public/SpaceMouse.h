// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "TimerManager.h"
#include "LevelEditorViewport.h"
#include "Hid.h"

//General Log
DECLARE_LOG_CATEGORY_EXTERN(SpaceMouseEditor, Log, All);

class FSpaceMouseModule : public IModuleInterface
{
private:

	FTimerDelegate OnTickDel;
	void OnTick();
	unsigned char OutputBuffer[80];

	FVector Translation;
	FRotator Rotation;
	bool Buttons[48];

	TArray<FEditorViewportClient*> AllViewportClients;
	FEditorViewportClient* ActiveViewportClient;
	FString focusedVpType;

public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	float Resolution = 350.0;
	float RotSpeed = 3;
	float TransSpeed = 20;

	hid_device * Device;
	bool DeviceOpened;
	//hid_device_info * DeviceInfos;
};
