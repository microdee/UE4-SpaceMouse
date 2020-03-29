
#include "SmEditorManager.h"
#include "SpaceMouse.h"
#include "Editor.h"
#include "SEditorViewport.h"
#include "EditorViewportClient.h"
//#include "Runtime/Core/Public/Misc/App.h"
//#include "Object.h"

void FSmEditorManager::Tick(float DeltaSecs)
{
	bPrintDebug = FSpaceMouseModule::Settings->DisplayDebugInformation;
	for (auto sm : Devices)
	{
        sm->bPrintDebug = FSpaceMouseModule::Settings->DisplayDebugInformation;
        sm->MaxReads = FSpaceMouseModule::Settings->MaxHidReadOperationsPerFrame;

        sm->TranslationUnitsPerSec = FSpaceMouseModule::Settings->TranslationUnitsPerSec;
        sm->XTranslationAxisMap = FSpaceMouseModule::Settings->XTranslationAxisMap;
        sm->YTranslationAxisMap = FSpaceMouseModule::Settings->YTranslationAxisMap;
        sm->ZTranslationAxisMap = FSpaceMouseModule::Settings->ZTranslationAxisMap;

        sm->RotationDegreesPerSec = FSpaceMouseModule::Settings->RotationDegreesPerSec;
        sm->PitchAxisMap = FSpaceMouseModule::Settings->PitchAxisMap;
        sm->YawAxisMap = FSpaceMouseModule::Settings->YawAxisMap;
        sm->RollAxisMap = FSpaceMouseModule::Settings->RollAxisMap;
	}
    FSpaceMouseManager::Tick(DeltaSecs);

	ManageActiveViewport();
	MoveActiveViewport(Translation, Rotation);
    
	if(Enabled) GEditor->GetTimerManager().Get().SetTimerForNextTick(OnTickDel);
}

bool FSmEditorManager::bStarted = false;

void FSmEditorManager::Start()
{
	if (!bStarted)
	{
		bStarted = true;
		GEditor->GetTimerManager().Get().SetTimerForNextTick(OnTickDel);
	}
}

void FSmEditorManager::ManageActiveViewport()
{
	TArray<FEditorViewportClient*> AllViewportClients = GEditor->GetAllViewportClients();

	if (IsActiveViewportInvalid(AllViewportClients)) ActiveViewportClient = nullptr;

	for (FEditorViewportClient* cvp : AllViewportClients)
	{
		if (!cvp) continue;
		if (!cvp->GetEditorViewportWidget().Get()) continue;
		if (cvp->GetEditorViewportWidget().Get()->HasAnyUserFocusOrFocusedDescendants())
		{
			if(cvp == ActiveViewportClient) break;
			if (cvp->IsVisible() && cvp->IsPerspective())
			{
				if (cvp != ActiveViewportClient)
				{
					if (ActiveViewportClient)
					{
						ActiveViewportClient->ToggleOrbitCamera(bWasOrbitCamera);
						ActiveViewportClient->SetRealtime(bWasRealtime);
					}
					bWasOrbitCamera = cvp->ShouldOrbitCamera();
					bWasRealtime = cvp->IsRealtime();
					cvp->ToggleOrbitCamera(false);
					cvp->SetRealtime(true);
					ActiveViewportClient = cvp;
					break;
				}
			}
		}
	}
}

void FSmEditorManager::MoveActiveViewport(FVector trans, FRotator rot)
{
	if (OnMovementStartedFrame && ActiveViewportClient)
	{
		bWasRealtime = ActiveViewportClient->IsRealtime();
		ActiveViewportClient->ToggleOrbitCamera(false);
		ActiveViewportClient->SetRealtime(true);
	}

	/*if (OnMovementEndedFrame && ActiveViewportClient)
	{
		ActiveViewportClient->SetRealtime(bWasRealtime);
	}*/

	if (ActiveViewportClient && Enabled)
	{
		if (ActiveViewportClient->IsVisible())
		{
			if (ActiveViewportClient->IsPerspective())
			{
				float camspeed = ActiveViewportClient->GetCameraSpeedSetting();
				if (BUTTONDOWN(FSpaceMouseModule::Settings->DecreaseSpeedButtonID))
				{
					ActiveViewportClient->SetCameraSpeedSetting(camspeed - 1);
					UE_LOG(LogTemp, Display, TEXT("Speed --"));
				}
				if (BUTTONDOWN(FSpaceMouseModule::Settings->IncreaseSpeedButtonID))
				{
					ActiveViewportClient->SetCameraSpeedSetting(camspeed + 1);
					UE_LOG(LogTemp, Display, TEXT("Speed ++"));
				}
				if (BUTTONDOWN(FSpaceMouseModule::Settings->ResetSpeedButtonID))
				{
					ActiveViewportClient->SetCameraSpeedSetting(4);
				}

				float speedexp = FMath::Max(ActiveViewportClient->GetCameraSpeedSetting() - 8, 0);
				speedexp += FMath::Min(ActiveViewportClient->GetCameraSpeedSetting(), 0);
				float speedmul = FMath::Pow(2, speedexp);

				FRotator currRot = ActiveViewportClient->GetViewRotation();
				FVector currPos = ActiveViewportClient->GetViewLocation();
				currPos += currRot.RotateVector(trans * ActiveViewportClient->GetCameraSpeed()) * speedmul;
				currRot = FRotator(FQuat(currRot) * FQuat(rot));
				ActiveViewportClient->SetViewLocation(currPos);
				ActiveViewportClient->SetViewRotation(currRot);
			}
		}
	}
}

const bool FSmEditorManager::IsActiveViewportInvalid(const TArray<FEditorViewportClient*>& AllViewportClients)
{
	bool activeViewportInvalid = true;
	for (FEditorViewportClient* cvp : AllViewportClients)
	{
		if (cvp == ActiveViewportClient) return false;
	}
	return true;
}