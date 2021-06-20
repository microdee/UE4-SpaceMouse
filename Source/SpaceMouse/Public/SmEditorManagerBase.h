// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceMouseManager.h"
#include "TickableEditorObject.h"

class FEditorViewportClient;

/**
 * 
 */
class SPACEMOUSE_API FSmEditorManagerBase : public FSpaceMouseManager, public FTickableEditorObject
{
public:
    FSmEditorManagerBase();
    
protected:
    
    FEditorViewportClient* ActiveViewportClient = nullptr;
    
    virtual FUserSettings GetUserSettings() override;

    static TArray<FEditorViewportClient*> GetAllViewports();
    static bool IsViewportValid(FEditorViewportClient* InVp);
    bool IsActiveViewportInvalid() const;

    virtual void OnActiveViewportChanged(FEditorViewportClient* Current, FEditorViewportClient* Previous) {}
    virtual void OnActiveViewportClosed() {}
    virtual void OnEnumerateViewport(FEditorViewportClient* Current) {}
    
public:
    
    virtual void Initialize() override;
    virtual void TickManager(float DeltaSecs) override;
    virtual void Tick(float DeltaTime) override;

    virtual void ManageActiveViewport();
    
    virtual TStatId GetStatId() const override { return {}; }
};
