
#include "SmEditorManager.h"
#include "SpaceMouse.h"
#include "Editor.h"
#include "SEditorViewport.h"
#include "EditorViewportClient.h"
#include "CameraController.h"
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
	LearnButtonMappings();
    
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

void FSmEditorManager::LearnButtonMappings()
{
	if(FSpaceMouseModule::Settings->LearnDecreaseSpeed)
		LearnButtonMapping(FSpaceMouseModule::Settings->DecreaseSpeedButtonID);

	if (FSpaceMouseModule::Settings->LearnIncreaseSpeed)
		LearnButtonMapping(FSpaceMouseModule::Settings->IncreaseSpeedButtonID);

	if (FSpaceMouseModule::Settings->LearnResetSpeed)
		LearnButtonMapping(FSpaceMouseModule::Settings->ResetSpeedButtonID);
}

void FSmEditorManager::LearnButtonMapping(int& target)
{
	bool learnt = false;
	for(int i=0; i<Buttons.Num(); i++)
	{
		if(BUTTONDOWN(i))
		{
			target = i;
			learnt = true;
			break;
		}
	}
	if(learnt)
	{
		FSpaceMouseModule::Settings->SaveConfig();
	}
}

void FSmEditorManager::ManageActiveViewport()
{
#if ENGINE_MINOR_VERSION >= 22
	TArray<FEditorViewportClient*> AllViewportClients = GEditor->GetAllViewportClients();
#else
	TArray<FEditorViewportClient*> AllViewportClients = GEditor->AllViewportClients;
#endif

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

bool FSmEditorManager::UseForceSetView(FEditorViewportClient* cvp)
{
	static TSet<FName> ForceSetViewTable =
	{
		FName("SStaticMeshEditorViewport")
	};

	FName widgetType = cvp->GetEditorViewportWidget()->GetType();
	return ForceSetViewTable.Contains(widgetType);
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
					//UE_LOG(LogTemp, Display, TEXT("Speed --"));
				}
				if (BUTTONDOWN(FSpaceMouseModule::Settings->IncreaseSpeedButtonID))
				{
					ActiveViewportClient->SetCameraSpeedSetting(camspeed + 1);
					//UE_LOG(LogTemp, Display, TEXT("Speed ++"));
				}
				if (BUTTONDOWN(FSpaceMouseModule::Settings->ResetSpeedButtonID))
				{
					ActiveViewportClient->SetCameraSpeedSetting(4);
				}

				if(!trans.IsNearlyZero(SMALL_NUMBER) || !rot.IsNearlyZero(SMALL_NUMBER))
				{
					float speedexp = FMath::Max(ActiveViewportClient->GetCameraSpeedSetting() - 8, 0);
					speedexp += FMath::Min(ActiveViewportClient->GetCameraSpeedSetting(), 0);
					float speedmul = FMath::Pow(2, speedexp);
					
					FRotator currRot = ActiveViewportClient->GetViewRotation();
					FVector posDelta = currRot.RotateVector(trans * ActiveViewportClient->GetCameraSpeed()) * speedmul;

					if(UseForceSetView(ActiveViewportClient))
					{
						FVector currPos = ActiveViewportClient->GetViewLocation();
						currPos += posDelta;
						currRot = FRotator(FQuat(currRot) * FQuat(rot));
						ActiveViewportClient->SetViewLocation(currPos);
						ActiveViewportClient->SetViewRotation(currRot);
					}
					else
					{
						FRotator rotDelta = FRotator(FQuat(currRot) * FQuat(rot)) - currRot;
						ActiveViewportClient->MoveViewportCamera(posDelta, rotDelta);
					}
				}
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