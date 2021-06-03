// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#include "SmEditorManager.h"
#include "SmViewportOverlay.h"

#include "CameraController.h"
#include "CommonBehaviors.h"
#include "SpaceMouse.h"
#include "Editor.h"
#include "SEditorViewport.h"
#include "EditorViewportClient.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Framework/Application/SlateApplication.h"
//#include "Object.h"

void FSmEditorManager::Tick(float DeltaSecs)
{
    bPrintDebug = FSpaceMouseModule::Settings->DisplayDebugInformation;
    for (auto sm : Devices)
    {
        sm->UserSettings = FSpaceMouseModule::Settings->GetUserSettings();
    }
    FSpaceMouseManager::Tick(DeltaSecs);

    ManageActiveViewport();
    ManageOrbitingOverlay();
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

void FSmEditorManager::ManageOrbitingOverlay()
{
    
    if(OnMovementStartedFrame
        && ActiveViewportClient
        && FSpaceMouseModule::Settings->DisplayOrbittingPivot)
    {
        OrbitingOverlay = MakeShared<FSmViewportOverlay>(ActiveViewportClient);
    }
    if(OnMovementEndedFrame)
    {
        OrbitingOverlay.Reset();
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

    if (FSpaceMouseModule::Settings->LearnResetRoll)
        LearnButtonMapping(FSpaceMouseModule::Settings->ResetRollButtonID);

    for(auto& mapping : FSpaceMouseModule::Settings->CustomKeyMappings)
    {
        if(mapping.LearnSpaceMouseButtonID)
            LearnButtonMapping(mapping.SpaceMouseButtonID);
    }
}

void FSmEditorManager::LearnButtonMapping(int& target)
{
    static const FString DefaultEditorPath = FString::Printf(TEXT("%sDefaultEditor.ini"), *FPaths::SourceConfigDir());
    
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
        FSpaceMouseModule::Settings->SaveConfig(CPF_Config, *DefaultEditorPath);
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
                    //cvp->ToggleOrbitCamera(false);
                    //cvp->SetRealtime(true);
                    ActiveViewportClient = cvp;
                    break;
                }
            }
        }
    }
}

FVector FSmEditorManager::GetOrbitingPosDeltaOffset(FRotator rotDelta, float forwardDelta)
{
    if(OnMovementStartedFrame)
    {
        auto world = ActiveViewportClient->GetWorld();
        FHitResult hit;
        float traceLength = FSpaceMouseModule::Settings->OrbitingLineTraceLength;
        FVector startpoint = ActiveViewportClient->GetViewLocation();
        FVector endpoint = startpoint +
            ActiveViewportClient->GetViewRotation().RotateVector({1, 0, 0}) * traceLength;

        FCollisionQueryParams ColQuery;
        ColQuery.bTraceComplex = true;

        if(world->LineTraceSingleByChannel(hit, startpoint, endpoint, ECC_Visibility, ColQuery))
        {
            LastOrbitPivot = hit.ImpactPoint;
            LastOrbitDistance = hit.Distance;

            LastOrbitPivotView = LastOrbitPivot - ActiveViewportClient->GetViewLocation();
            LastOrbitPivotView = ActiveViewportClient->GetViewRotation().GetInverse().RotateVector(LastOrbitPivotView);
        }
        if(FMath::IsNearlyZero(LastOrbitDistance))
        {
            LastOrbitDistance = 300;
            LastOrbitPivotView = {LastOrbitDistance, 0, 0};

            LastOrbitPivot = ActiveViewportClient->GetViewLocation() +
                ActiveViewportClient->GetViewRotation().RotateVector(LastOrbitPivotView);
        }
    }
    
    LastOrbitDistance -= forwardDelta;
    LastOrbitPivotView.X -= forwardDelta;

    if(OrbitingOverlay) OrbitingOverlay->Draw(LastOrbitPivot, LastOrbitDistance);

    return UCommonBehaviors::GetOrbitingTranslationDelta(
        LastOrbitPivotView,
        ActiveViewportClient->GetViewRotation(),
        rotDelta,
        LastOrbitDistance,
        FSpaceMouseModule::Settings->CameraBehavior == ESpaceMouseCameraBehavior::OrbittingWithRoll
    );
}

FKeyEvent FSmEditorManager::GetKeyEventFromKey(const FInputActionKeyMapping& mapping)
{
    const uint32* kc;
    const uint32* cc;
    FInputKeyManager::Get().GetCodesFromKey(mapping.Key, kc, cc);
    
    return FKeyEvent(
        mapping.Key, FModifierKeysState(
            mapping.bShift, false,
            mapping.bCtrl, false,
            mapping.bAlt, false,
            mapping.bCmd, false,
            false
        ),
        0, false, cc ? *cc : 0, kc ? *kc : 0
    );
}

bool FSmEditorManager::AllowPerspectiveCameraMoveEvent(FEditorViewportClient* cvp)
{
    static TSet<FName> IncompatibleViewports =
    {
        FName("SStaticMeshEditorViewport")
    };

    FName widgetType = cvp->GetEditorViewportWidget()->GetType();
    return !IncompatibleViewports.Contains(widgetType);
}

void FSmEditorManager::MoveActiveViewport(FVector trans, FRotator rot)
{
    if(!FSpaceMouseModule::Settings->ActiveInBackground)
    {
        if(!FPlatformApplicationMisc::IsThisApplicationForeground()) return;
    }
    
    if (OnMovementStartedFrame && ActiveViewportClient)
    {
        bWasRealtime = ActiveViewportClient->IsRealtime();
        bWasOrbitCamera = ActiveViewportClient->ShouldOrbitCamera();
        ActiveViewportClient->ToggleOrbitCamera(false);
        ActiveViewportClient->SetRealtime(true);
    }

    if (OnMovementEndedFrame && ActiveViewportClient)
    {
        ActiveViewportClient->SetRealtime(bWasRealtime);
        //ActiveViewportClient->ToggleOrbitCamera(bWasOrbitCamera);
    }

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
                if (BUTTONDOWN(FSpaceMouseModule::Settings->ResetRollButtonID))
                {
                    ActiveViewportClient->RemoveCameraRoll();
                }
                
                for (const auto& mapping : FSpaceMouseModule::Settings->CustomKeyMappings)
                {
                    if(mapping.LearnSpaceMouseButtonID) continue;
                    if(BUTTONDOWN(mapping.SpaceMouseButtonID))
                    {
                        auto keyEvent = GetKeyEventFromKey(mapping.TargetKey);
                        FSlateApplication::Get().ProcessKeyDownEvent(keyEvent);
                    }
                    if(BUTTONUP(mapping.SpaceMouseButtonID))
                    {
                        auto keyEvent = GetKeyEventFromKey(mapping.TargetKey);
                        FSlateApplication::Get().ProcessKeyUpEvent(keyEvent);
                    }
                }

                if(!trans.IsNearlyZero(SMALL_NUMBER) || !rot.IsNearlyZero(SMALL_NUMBER))
                {
                    float speedexp = FMath::Max(ActiveViewportClient->GetCameraSpeedSetting() - 8, 0);
                    speedexp += FMath::Min(ActiveViewportClient->GetCameraSpeedSetting(), 0);
                    float speedmul = FMath::Pow(2, speedexp);
                    speedmul *= ActiveViewportClient->GetCameraSpeed();

                    bool orbitMovesObject = FSpaceMouseModule::Settings->OrbittingMovesObject;
                    bool orbitRotatesObject = FSpaceMouseModule::Settings->OrbittingRotatesObject;
                    FRotator currRot = ActiveViewportClient->GetViewRotation();

                    if(FSpaceMouseModule::Settings->CameraBehavior >= ESpaceMouseCameraBehavior::OrbittingWithRoll)
                    {
                        auto OrbRot = rot;
                        if(FSpaceMouseModule::Settings->CameraBehavior == ESpaceMouseCameraBehavior::OrbittingNoRoll)
                        {
                            OrbRot.Pitch *= currRot.Pitch > -80 && currRot.Pitch < 80;
                        }
                        auto orbitTrans = orbitMovesObject ? -trans : trans;
                        trans = GetOrbitingPosDeltaOffset(
                            orbitRotatesObject ? OrbRot : OrbRot.GetInverse(),
                            orbitTrans.X * speedmul
                        ) / speedmul + orbitTrans;
                    }
                    
                    FVector posDelta = currRot.RotateVector(trans) * speedmul;

                    FVector currPos = ActiveViewportClient->GetViewLocation();
                    currPos += posDelta;
                    switch (FSpaceMouseModule::Settings->CameraBehavior)
                    {
                    case ESpaceMouseCameraBehavior::CameraDeltaWithRoll:
                        currRot = FRotator(FQuat(currRot) * FQuat(rot));
                        break;
                        
                    case ESpaceMouseCameraBehavior::CameraDeltaNoRoll:
                        if (OnMovementStartedFrame)
                        {
                            ActiveViewportClient->RemoveCameraRoll();
                        }
                        currRot.Pitch = FMath::Clamp(currRot.Pitch, -80.0f, 80.0f);
                        currRot = FRotator(
                            FQuat(FRotator(0, rot.Yaw, 0)) *
                            FQuat(currRot) *
                            FQuat(FRotator(rot.Pitch, 0, 0))
                        );
                        currRot.Roll = 0;
                        break;
                        
                    case ESpaceMouseCameraBehavior::OrbittingWithRoll:
                        currRot = FRotator(FQuat(currRot) * (orbitRotatesObject ? FQuat(rot).Inverse() : FQuat(rot)));
                        break;
                        
                    case ESpaceMouseCameraBehavior::OrbittingNoRoll:
                        if (OnMovementStartedFrame)
                        {
                            ActiveViewportClient->RemoveCameraRoll();
                        }
                        currRot.Pitch = FMath::Clamp(currRot.Pitch, -80.0f, 80.0f);
                        currRot = FRotator(
                            FQuat(FRotator(0, orbitRotatesObject ? -rot.Yaw : rot.Yaw, 0)) *
                            FQuat(currRot) *
                            FQuat(FRotator(orbitRotatesObject ? -rot.Pitch : rot.Pitch, 0, 0))
                        );
                        currRot.Roll = 0;
                        break;
                    default: ;
                    }
                    ActiveViewportClient->SetViewLocation(currPos);
                    ActiveViewportClient->SetViewRotation(currRot);

                    if(AllowPerspectiveCameraMoveEvent(ActiveViewportClient))
                    {
                        // This is important to trigger PerspectiveCameraMoved event from outside.
                        ActiveViewportClient->MoveViewportCamera(FVector::ZeroVector, FRotator::ZeroRotator);
                        ActiveViewportClient->Viewport->InvalidateHitProxy();
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