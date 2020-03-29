// Copyright 1998-2019 David Morasz All Rights Reserved.

#include "SpaceMouseManager.h"
#include "SpaceMouseReader.h"

#include "Hid.h"

#if WITH_EDITOR
#include "EngineGlobals.h"
#include "Engine/Engine.h"
#endif

void FSpaceMouseManager::Initialize()
{
	Translation = FVector::ZeroVector;
	Rotation = FRotator::ZeroRotator;

	Buttons.Empty(SPACEMOUSE_BUTTONCOUNT);
	Buttons.AddZeroed(SPACEMOUSE_BUTTONCOUNT);
	PrevButtons.Empty(SPACEMOUSE_BUTTONCOUNT);
	PrevButtons.AddZeroed(SPACEMOUSE_BUTTONCOUNT);

    DeviceInfos = hid_enumerate(0, 0);
    hid_device_info* cinfo = DeviceInfos;

    int ii = 0;
    while (cinfo)
    {
        for(auto& elem : FSpaceMouseReaderModule::Prototypes)
        {
			uint32 vidpid = JOIN_VIDPID(static_cast<uint32>(cinfo->vendor_id), static_cast<uint32>(cinfo->product_id));
            if(elem.Key == vidpid)
            {
                auto smdevice = elem.Value->NewDevice();
                smdevice->Initialize(cinfo, ii);
                Devices.Add(smdevice);
                if (smdevice->DeviceOpened)
                    DeviceOpened = true;
                break;
            }
        }
        cinfo = cinfo->next;
        ii++;
    }
    Enabled = true;
}

void FSpaceMouseManager::Tick(float DeltaSecs)
{
	//Translation = FVector::ZeroVector;
	//Rotation = FRotator::ZeroRotator;
	FVector trans = FVector::ZeroVector;
	FRotator rot = FRotator::ZeroRotator;
    
	for (int i = 0; i < SPACEMOUSE_BUTTONCOUNT; i++)
	{
		PrevButtons[i] = Buttons[i];
		Buttons[i] = false;
	}
    
	OnMovementStartedFrame = false;
	OnMovementEndedFrame = false;
    
	for (auto sm : Devices)
	{
        sm->bPrintDebug = bPrintDebug;
		sm->Tick(DeltaSecs);
		trans += sm->Translation;
		rot += sm->Rotation;
		OnMovementStartedFrame = OnMovementStartedFrame || sm->OnMovementStartedFrame;
		OnMovementEndedFrame = OnMovementEndedFrame || sm->OnMovementEndedFrame;

		for (int i = 0; i < SPACEMOUSE_BUTTONCOUNT; i++)
			Buttons[i] = Buttons[i] || sm->Buttons[i];
	}
	Translation = trans;
	Rotation = rot;

#if WITH_EDITOR
	if (bPrintDebug)
	{
		GEngine->AddOnScreenDebugMessage(
			2000, 1.0, FColor::Cyan,
			"Connected SpaceMice: " + FString::FromInt(Devices.Num())
		);
	}
#endif
}