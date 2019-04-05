// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SpaceMouse.h"

#define LOCTEXT_NAMESPACE "FSpaceMouseModule"

void FSpaceMouseModule::OnTick()
{
	GEditor->GetTimerManager().Get()->SetTimerForNextTick(OnTick);
}

void FSpaceMouseModule::StartupModule()
{
	hid_init();
	Device = hid_open(0x46D, 0xC62B, nullptr);
	DeviceOpened = Device != nullptr;
	GEditor->GetTimerManager().Get()->SetTimerForNextTick(OnTick);
}

void FSpaceMouseModule::ShutdownModule()
{
	//hid_free_enumeration(DeviceInfos);
	hid_close(Device);
	hid_exit();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSpaceMouseModule, SpaceMouse)