// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "SpaceMouseManager.h"
#include "TickableEditorObject.h"
#include "Misc/App.h"
#include "Input/Events.h"
#include "TimerManager.h"

struct FInputActionKeyMapping;
class FEditorViewportClient;
class FSmViewportOverlay;

class SPACEMOUSE_API FSmEditorManager : public FSpaceMouseManager, public FTickableEditorObject
{
private:

    bool bLearning = false;
    bool bFinishLearning = false;

    bool bWasOrbitCamera = false;
    bool bWasRealtime = false;
    float LastOrbitDistance = 0;
    FVector LastOrbitPivot = FVector::ZeroVector;
    FVector LastOrbitPivotView = FVector::ZeroVector;

    FEditorViewportClient* ActiveViewportClient = nullptr;
    FString FocusedVpType = "";

    TSharedPtr<FSmViewportOverlay> OrbitingOverlay;

    static FKeyEvent GetKeyEventFromKey(const FInputActionKeyMapping& mapping);
    static bool AllowPerspectiveCameraMoveEvent(FEditorViewportClient* cvp);
    FVector GetOrbitingPosDeltaOffset(FRotator rotDelta, float forwardDelta);

protected:
    virtual FUserSettings GetUserSettings() override;

public:

    FSmEditorManager() : FTickableEditorObject() {}
    
    void BeginLearning();
    void EndLearning();
    bool IsLearning() const { return bLearning; } 

    virtual void Initialize() override;
    virtual void TickManager(float DeltaSecs) override;
    virtual void Tick(float DeltaTime) override;
    
    void ManageOrbitingOverlay();
    void ManageActiveViewport();
    void TriggerCustomButtons();
    void MoveActiveViewport(FVector trans, FRotator rot);
    const bool IsActiveViewportInvalid(const TArray<FEditorViewportClient*>& AllViewportClients);
    
    virtual TStatId GetStatId() const override { return {}; }
};
