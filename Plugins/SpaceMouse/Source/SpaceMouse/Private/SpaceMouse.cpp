// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SpaceMouse.h"
#include "Editor.h"

#define LOCTEXT_NAMESPACE "FSpaceMouseModule"

void FSpaceMouseModule::OnTick()
{
	if (DeviceOpened)
	{
		unsigned char* pOutput = (unsigned char*)&OutputBuffer;
		unsigned char* pCurr = pOutput;
		if(hid_read(Device, pOutput, 28))
		{
			for (int i = 0; i < 4; i++)
			{
				unsigned char report = *pCurr;
				short xx = *(pCurr + 1);
				short yy = *(pCurr + 3);
				short zz = *(pCurr + 5);
				if (report == 1)
				{
					Translation = FVector(
						(float)xx / Resolution,
						(float)yy / Resolution,
						(float)zz / Resolution
					);
				}
				else if (report == 2)
				{
					Rotation = FVector(
						(float)xx / Resolution,
						(float)yy / Resolution,
						(float)zz / Resolution
					);
				}
				else if (report == 3)
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
				}
				pCurr += 7;
			}

			auto avc = static_cast<FLevelEditorViewportClient*>(GEditor->GetActiveViewport()->GetClient());
			if (avc) ActiveViewportClient = avc;

			if (ActiveViewportClient)
			{
				FVector currpos = ActiveViewportClient->GetViewLocation();
				currpos += Translation * ActiveViewportClient->GetCameraSpeed();
				ActiveViewportClient->SetViewLocation(currpos);
			}
		}
	}
	GEditor->GetTimerManager().Get().SetTimerForNextTick(OnTickDel);
};

void FSpaceMouseModule::StartupModule()
{
	OnTickDel = OnTickDel.CreateLambda([this]() { OnTick(); });

	hid_init();
	Device = hid_open(0x46D, 0xC62B, nullptr);
	DeviceOpened = Device != nullptr;
	if (DeviceOpened) hid_set_nonblocking(Device, 1);
	GEditor->GetTimerManager().Get().SetTimerForNextTick(OnTickDel);
}

void FSpaceMouseModule::ShutdownModule()
{
	//hid_free_enumeration(DeviceInfos);
	hid_close(Device);
	hid_exit();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSpaceMouseModule, SpaceMouse)