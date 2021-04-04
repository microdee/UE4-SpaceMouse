// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#include "SmEditorManager.h"
#include "SmViewportOverlay.h"

#include "CameraController.h"
#include "CommonBehaviors.h"
#include "SpaceMouse.h"
#include "SmInputDevice.h"
#include "Editor.h"
#include "SEditorViewport.h"
#include "EditorViewportClient.h"
#include "MovementState.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Framework/Application/SlateApplication.h"
//#include "Object.h"

void FSmEditorManager::Initialize()
{
    FSpaceMouseManager::Initialize();

    OnTickDel = OnTickDel.CreateLambda([this]()
    {
        Tick(FApp::GetDeltaTime());
    });
    bWasOrbitCamera = false;
    bWasRealtime = false;
}

void FSmEditorManager::Tick(float DeltaSecs)
{
    auto Settings = GetMutableDefault<USpaceMouseConfig>();
    FSpaceMouseManager::Tick(DeltaSecs);

    ManageActiveViewport();
    ManageOrbitingOverlay();
    MoveActiveViewport(GetTranslation(), GetRotation());
    
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
    
    if(MovementState->bOnMovementStartedFrame && ActiveViewportClient)
    {
        OrbitingOverlay = MakeShared<FSmViewportOverlay>(ActiveViewportClient);
    }
    if(MovementState->bOnMovementEndedFrame)
    {
        OrbitingOverlay.Reset();
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

    for (FEditorViewportClient* Cvp : AllViewportClients)
    {
        if (!Cvp) continue;
        if (!Cvp->GetEditorViewportWidget().Get()) continue;
        if (Cvp->GetEditorViewportWidget().Get()->HasAnyUserFocusOrFocusedDescendants())
        {
            if(Cvp == ActiveViewportClient) break;
            if (Cvp->IsVisible() && Cvp->IsPerspective())
            {
                if (Cvp != ActiveViewportClient)
                {
                    if (ActiveViewportClient)
                    {
                        ActiveViewportClient->ToggleOrbitCamera(bWasOrbitCamera);
                        ActiveViewportClient->SetRealtime(bWasRealtime);
                    }
                    bWasOrbitCamera = Cvp->ShouldOrbitCamera();
                    bWasRealtime = Cvp->IsRealtime();
                    //cvp->ToggleOrbitCamera(false);
                    //cvp->SetRealtime(true);
                    ActiveViewportClient = Cvp;
                    break;
                }
            }
        }
    }
}

FVector FSmEditorManager::GetOrbitingPosDeltaOffset(FRotator rotDelta, float forwardDelta)
{
    auto Settings = GetMutableDefault<USpaceMouseConfig>();
    if(MovementState->bOnMovementStartedFrame)
    {
        auto world = ActiveViewportClient->GetWorld();
        FHitResult hit;
        float traceLength = Settings->OrbitingLineTraceLength;
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
        Settings->CameraBehavior == ESpaceMouseCameraBehavior::OrbittingWithRoll
    );
}

FUserSettings FSmEditorManager::GetUserSettings()
{
    return GetMutableDefault<USpaceMouseConfig>()->GetUserSettings();
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
    auto Settings = GetMutableDefault<USpaceMouseConfig>();
    if(!Settings->ActiveInBackground)
    {
        if(!FPlatformApplicationMisc::IsThisApplicationForeground()) return;
    }
    
    if (MovementState->bOnMovementStartedFrame && ActiveViewportClient)
    {
        bWasRealtime = ActiveViewportClient->IsRealtime();
        bWasOrbitCamera = ActiveViewportClient->ShouldOrbitCamera();
        ActiveViewportClient->ToggleOrbitCamera(false);
        ActiveViewportClient->SetRealtime(true);
    }

    if (MovementState->bOnMovementEndedFrame && ActiveViewportClient)
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
                if (ButtonDownFrame(FSmInputDevice::GetButtonFrom(Settings->DecreaseSpeedButton)))
                {
                    ActiveViewportClient->SetCameraSpeedSetting(camspeed - 1);
                    //UE_LOG(LogTemp, Display, TEXT("Speed --"));
                }
                if (ButtonDownFrame(FSmInputDevice::GetButtonFrom(Settings->IncreaseSpeedButton)))
                {
                    ActiveViewportClient->SetCameraSpeedSetting(camspeed + 1);
                    //UE_LOG(LogTemp, Display, TEXT("Speed ++"));
                }
                if (ButtonDownFrame(FSmInputDevice::GetButtonFrom(Settings->ResetSpeedButton)))
                {
                    ActiveViewportClient->SetCameraSpeedSetting(4);
                }
                if (ButtonDownFrame(FSmInputDevice::GetButtonFrom(Settings->ResetRollButton)))
                {
                    ActiveViewportClient->RemoveCameraRoll();
                }
                
                for (const auto& mapping : Settings->CustomKeyMappings)
                {
                    if(ButtonDownFrame(FSmInputDevice::GetButtonFrom(mapping.SpaceMouseButton)))
                    {
                        auto keyEvent = GetKeyEventFromKey(mapping.TargetKey);
                        FSlateApplication::Get().ProcessKeyDownEvent(keyEvent);
                    }
                    if(ButtonUpFrame(FSmInputDevice::GetButtonFrom(mapping.SpaceMouseButton)))
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

                    bool orbitMovesObject = Settings->OrbittingMovesObject;
                    bool orbitRotatesObject = Settings->OrbittingRotatesObject;
                    FRotator currRot = ActiveViewportClient->GetViewRotation();

                    if(Settings->CameraBehavior >= ESpaceMouseCameraBehavior::OrbittingWithRoll)
                    {
                        auto OrbRot = rot;
                        if(Settings->CameraBehavior == ESpaceMouseCameraBehavior::OrbittingNoRoll)
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
                    switch (Settings->CameraBehavior)
                    {
                    case ESpaceMouseCameraBehavior::CameraDeltaWithRoll:
                        currRot = FRotator(FQuat(currRot) * FQuat(rot));
                        break;
                        
                    case ESpaceMouseCameraBehavior::CameraDeltaNoRoll:
                        if (MovementState->bOnMovementStartedFrame)
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
                        if (MovementState->bOnMovementStartedFrame)
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
    bool bActiveViewportInvalid = true;
    for (FEditorViewportClient* Cvp : AllViewportClients)
    {
        if (Cvp == ActiveViewportClient) return false;
    }
    return true;
}