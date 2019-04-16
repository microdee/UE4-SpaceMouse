// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SpaceMouse.h"
#include "Editor.h"
#include "SWidget.h"
#include "SEditorViewport.h"
#include "SceneViewport.h"

//#define DEBUG_SM_VALUES 1

#define LOCTEXT_NAMESPACE "FSpaceMouseModule"

//General Log
DEFINE_LOG_CATEGORY(SpaceMouseEditor);

void FSpaceMouseModule::OnTick()
{
	if (DeviceOpened)
	{
		AllViewportClients = GEditor->GetAllViewportClients();

		for(auto cvpi = AllViewportClients.CreateConstIterator(); cvpi; ++cvpi)
		{
			FEditorViewportClient* cvp = *cvpi;
			if(cvp->GetEditorViewportWidget().Get()->HasAnyUserFocusOrFocusedDescendants())
			{
				ActiveViewportClient = cvp;
			}
		}

		unsigned char* pOutput = (unsigned char*)&OutputBuffer;
		int ctr = 0;

		while(hid_read(Device, pOutput, 28) > 0 && ctr < 64)
		{
			unsigned char* pCurr = pOutput;
			for (int i = 0; i < 4; i++)
			{
				unsigned char report = *pCurr;
				/*int16 xx = *(pCurr + 1) | (uint16)(*(pCurr + 2)) << 8;
				int16 yy = *(pCurr + 3) | (uint16)(*(pCurr + 4)) << 8;
				int16 zz = *(pCurr + 5) | (uint16)(*(pCurr + 6)) << 8;*/

				int16 xx = *(int16*)(pCurr + 1);
				int16 yy = *(int16*)(pCurr + 3);
				int16 zz = *(int16*)(pCurr + 5);
#if defined(DEBUG_SM_VALUES)
				GEngine->AddOnScreenDebugMessage(
					2000 + report,
					1.0,
					FColor::Yellow,
					FString::FromHexBlob((uint8*)pCurr, 28)
				);
#endif

				if (report == 1)
				{
#if defined(DEBUG_SM_VALUES)
					GEngine->AddOnScreenDebugMessage(3002, 1.0, FColor::Cyan, "tx " + FString::FromInt(xx));
					GEngine->AddOnScreenDebugMessage(3003, 1.0, FColor::Cyan, "ty " + FString::FromInt(yy));
					GEngine->AddOnScreenDebugMessage(3004, 1.0, FColor::Cyan, "tz " + FString::FromInt(zz));
#endif
					Translation = FVector(
						(float)yy / -Resolution,
						(float)xx / Resolution,
						(float)zz / -Resolution
					) * TransSpeed;
				}
				else if (report == 2)
				{

#if defined(DEBUG_SM_VALUES)
					GEngine->AddOnScreenDebugMessage(3006, 1.0, FColor::Cyan, "rx " + FString::FromInt(xx));
					GEngine->AddOnScreenDebugMessage(3007, 1.0, FColor::Cyan, "ry " + FString::FromInt(yy));
					GEngine->AddOnScreenDebugMessage(3008, 1.0, FColor::Cyan, "rz " + FString::FromInt(zz));
#endif
					Rotation = FRotator(
						(float)xx / Resolution,
						(float)zz / Resolution,
						(float)yy / -Resolution
					) * RotSpeed;
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
			ctr++;
		}

		if (ActiveViewportClient)
		{
			FRotator currRot = ActiveViewportClient->GetViewRotation();
			FVector currPos = ActiveViewportClient->GetViewLocation();
			currPos += currRot.RotateVector(Translation * ActiveViewportClient->GetCameraSpeed());
			currRot = FRotator(FQuat(currRot) * FQuat(Rotation));
			ActiveViewportClient->SetViewLocation(currPos);
			ActiveViewportClient->SetViewRotation(currRot);

#if defined(DEBUG_SM_VALUES)
			GEngine->AddOnScreenDebugMessage(
				2200,
				1.0,
				FColor::Yellow,
				FString::SanitizeFloat(ActiveViewportClient->GetCameraSpeed())
			);
#endif
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