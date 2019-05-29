// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SpaceMouse.h"
#include "Editor.h"
#include "SEditorViewport.h"
#include "App.h"
#include "Object.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"

//#define DEBUG_SM_VALUES 1

#define LOCTEXT_NAMESPACE "FSpaceMouseModule"

//General Log
DEFINE_LOG_CATEGORY(SpaceMouseEditor);

void FSpaceMouseDevice::Tick()
{
	if (!DeviceOpened) return;

	unsigned char* pOutput = (unsigned char*)&OutputBuffer;
	int ctr = 0;

	PrevMoving = Moving;
	Moving = false;

	int maxreads = FSpaceMouseModule::Settings->MaxHidReadOperationsPerFrame;

	bool printdebug = FSpaceMouseModule::Settings->DisplayDebugInformation;
	bool drecieved = false;
	FString dreport;

	while (hid_read(Device, pOutput, 28) > 0 && ctr < maxreads)
	{
		drecieved = true;
		if(printdebug)
		{
			dreport += FString::FromHexBlob(pOutput, 7);
		}
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

			float fx = (float)xx / FSpaceMouseModule::gResolution;
			float fy = (float)yy / FSpaceMouseModule::gResolution;
			float fz = (float)zz / FSpaceMouseModule::gResolution;

			if (report == 0 && printdebug)
			{
				dr0 = FString::FromHexBlob(pCurr, 7);
			}

			if (report == 1)
			{
				Moving = true;

				FVector xmap = FSpaceMouseModule::Settings->XTranslationAxisMap;
				FVector ymap = FSpaceMouseModule::Settings->YTranslationAxisMap;
				FVector zmap = FSpaceMouseModule::Settings->ZTranslationAxisMap;

				Translation = FVector(
					fx * xmap.X + fy * xmap.Y + fz * xmap.Z,
					fx * ymap.X + fy * ymap.Y + fz * ymap.Z,
					fx * zmap.X + fy * zmap.Y + fz * zmap.Z
				) * FSpaceMouseModule::Settings->TranslationUnitsPerSec * FApp::GetDeltaTime();

				if(printdebug) dr1 = FString::FromHexBlob(pCurr, 7);
			}
			else if (report == 2)
			{
				Moving = true;

				FVector xmap = FSpaceMouseModule::Settings->PitchAxisMap;
				FVector ymap = FSpaceMouseModule::Settings->YawAxisMap;
				FVector zmap = FSpaceMouseModule::Settings->RollAxisMap;
				Rotation = FRotator(
					fx * xmap.X + fy * xmap.Y + fz * xmap.Z,
					fx * ymap.X + fy * ymap.Y + fz * ymap.Z,
					fx * zmap.X + fy * zmap.Y + fz * zmap.Z
				) * FSpaceMouseModule::Settings->RotationDegreesPerSec * FApp::GetDeltaTime();

				if (printdebug) dr2 = FString::FromHexBlob(pCurr, 7);
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

				if (printdebug) dr3 = FString::FromHexBlob(pCurr, 7);
			}
			pCurr += 7;
		}
		ctr++;
	}
	if (printdebug && drecieved)
	{
		FString message = "Device: ";
		message += "Serial: " + FString(DeviceInfo->serial_number) + "\n";
		message += "VID: " + FString::FromInt(DeviceInfo->vendor_id) + "\n";
		message += "PID: " + FString::FromInt(DeviceInfo->product_id) + "\n";
		message += "Report:\n    ";
		message += dreport + "\n";
		message += "Sorted:\n    " + dr0 + "\n    " + dr1 + "\n    " + dr2 + "\n    " + dr3;
		GEngine->AddOnScreenDebugMessage(2010 + InternalID, 10.0, FColor::Orange, message);
	}

	OnMovementStartedFrame = Moving && !PrevMoving;
}

float FSpaceMouseModule::gResolution;
USpaceMouseConfig* FSpaceMouseModule::Settings;

void FSpaceMouseModule::OnTick()
{
	FSpaceMouseModule::gResolution = Resolution;

	Translation = FVector::ZeroVector;
	Rotation = FRotator::ZeroRotator;

	for (int i = 0; i < SPACEMOUSE_BUTTONCOUNT; i++)
	{
		PrevButtons[i] = Buttons[i];
		Buttons[i] = false;
	}

	bool onmovestarted = false;

	for (auto smi = Devices.CreateConstIterator(); smi; ++smi)
	{
		FSpaceMouseDevice* sm = *smi;
		sm->Tick();
		Translation += sm->Translation;
		Rotation += sm->Rotation;
		onmovestarted = onmovestarted || sm->OnMovementStartedFrame;

		for (int i = 0; i < SPACEMOUSE_BUTTONCOUNT; i++)
			Buttons[i] = Buttons[i] || sm->Buttons[i];
	}

	bool printdebug = Settings->DisplayDebugInformation;
	if (printdebug)
	{
		//FString message = "Connected SpaceMice: " + FString::FromInt(Devices.Num());
		GEngine->AddOnScreenDebugMessage(
			2000, 1.0, FColor::Cyan,
			"Connected SpaceMice: " + FString::FromInt(Devices.Num())
		);
	}

	AllViewportClients = GEditor->GetAllViewportClients();

	for (auto cvpi = AllViewportClients.CreateConstIterator(); cvpi; ++cvpi)
	{
		FEditorViewportClient* cvp = *cvpi;
		if (cvp->GetEditorViewportWidget().Get()->HasAnyUserFocusOrFocusedDescendants())
		{
			if(cvp->IsVisible() && cvp->IsPerspective())
			{
				if(cvp != ActiveViewportClient)
				{
					if(ActiveViewportClient)
					{
						ActiveViewportClient->ToggleOrbitCamera(bWasOrbitCamera);
					}
					bWasOrbitCamera = cvp->ShouldOrbitCamera();
					cvp->ToggleOrbitCamera(false);
				}
				ActiveViewportClient = cvp;
			}
		}
	}

	if(onmovestarted && ActiveViewportClient)
	{
		ActiveViewportClient->ToggleOrbitCamera(false);
	}

	try
	{
		if (ActiveViewportClient != nullptr && Enabled)
		{
			if(ActiveViewportClient->IsVisible())
			{
				if(ActiveViewportClient->IsPerspective())
				{
					float camspeed = ActiveViewportClient->GetCameraSpeedSetting();
					if (BUTTONDOWN(Settings->DecreaseSpeedButtonID))
					{
						ActiveViewportClient->SetCameraSpeedSetting(camspeed - 1);
					}
					if (BUTTONDOWN(Settings->IncreaseSpeedButtonID))
					{
						ActiveViewportClient->SetCameraSpeedSetting(camspeed + 1);
					}
					if(BUTTONDOWN(Settings->ResetSpeedButtonID))
					{
						ActiveViewportClient->SetCameraSpeedSetting(4);
					}

					float speedexp = FMath::Max(ActiveViewportClient->GetCameraSpeedSetting() - 8, 0);
					speedexp += FMath::Min(ActiveViewportClient->GetCameraSpeedSetting(), 0);
					float speedmul = FMath::Pow(2, speedexp);

					FRotator currRot = ActiveViewportClient->GetViewRotation();
					FVector currPos = ActiveViewportClient->GetViewLocation();
					currPos += currRot.RotateVector(Translation * ActiveViewportClient->GetCameraSpeed()) * speedmul;
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
		}
	}
	catch (int exc) { LastErrorCode = exc; }
	if(Enabled) GEditor->GetTimerManager().Get().SetTimerForNextTick(OnTickDel);
}

bool FSpaceMouseModule::HandleSettingsSaved()
{
	Settings = GetMutableDefault<USpaceMouseConfig>();
	Settings->SaveConfig();
	return true;
}

void FSpaceMouseModule::RegisterSettings()
{

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		// Create the new category
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Editor");

		SettingsContainer->DescribeCategory("SpaceMouse",
			LOCTEXT("RuntimeWDCategoryName", "SpaceMouse"),
			LOCTEXT("RuntimeWDCategoryDescription", "Configure SpaceMice for the editor"));

		Settings = GetMutableDefault<USpaceMouseConfig>();
		// Register the settings
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Editor", "SpaceMouse", "General",
			LOCTEXT("RuntimeGeneralSettingsName", "General"),
			LOCTEXT("RuntimeGeneralSettingsDescription", "Configure SpaceMice for the editor"),
			Settings
		);

		// Register the save handler to your settings, you might want to use it to
		// validate those or just act to settings changes.
		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FSpaceMouseModule::HandleSettingsSaved);
		}
	}
}

void FSpaceMouseModule::UnregisterSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Editor", "SpaceMouse", "General");
	}
}

void FSpaceMouseModule::StartupModule()
{
	OnTickDel = OnTickDel.CreateLambda([this]() { OnTick(); });

	RegisterSettings();
	bWasOrbitCamera = false;

	hid_init();
	DeviceInfos = hid_enumerate(0x46D, 0);
	hid_device_info* cinfo = DeviceInfos;

	for (int i = 0; i < SPACEMOUSE_BUTTONCOUNT; i++)
	{
		PrevButtons[i] = false;
		Buttons[i] = false;
	}

	int ii = 0;
	while (cinfo)
	{
		auto manfstr = FString((TCHAR*)cinfo->manufacturer_string);
		if(manfstr.Contains("3Dconnexion", ESearchCase::IgnoreCase, ESearchDir::FromStart))
		{
			auto smdevice = new FSpaceMouseDevice(cinfo, ii);
			Devices.Add(smdevice);
			if (smdevice->DeviceOpened)
				DeviceOpened = true;
		}
		cinfo = cinfo->next;
		ii++;
	}

	Enabled = true;
	GEditor->GetTimerManager().Get().SetTimerForNextTick(OnTickDel);
}

void FSpaceMouseModule::ShutdownModule()
{
	//hid_free_enumeration(DeviceInfos);

	if(UObjectInitialized())
	{
		UnregisterSettings();
	}

	Enabled = false;
	Devices.Empty();
	hid_exit();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSpaceMouseModule, SpaceMouse)