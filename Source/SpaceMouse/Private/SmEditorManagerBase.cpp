// Fill out your copyright notice in the Description page of Project Settings.


#include "SmEditorManagerBase.h"

#include "Editor.h"
#include "EditorViewportClient.h"
#include "SEditorViewport.h"
#include "SpaceMouseConfig.h"
#include "Framework/Commands/InputBindingManager.h"


FSmEditorManagerBase::FSmEditorManagerBase()
    : FTickableEditorObject()
{
}

FUserSettings FSmEditorManagerBase::GetUserSettings()
{
    return GetMutableDefault<USpaceMouseConfig>()->GetUserSettings();
}

TArray<FEditorViewportClient*> FSmEditorManagerBase::GetAllViewports()
{
#if UE_VERSION >= MAKE_UE_VERSION(4, 22)
    return GEditor->GetAllViewportClients();
#else
    return GEditor->AllViewportClients;
#endif
}

bool FSmEditorManagerBase::IsViewportValid(FEditorViewportClient* InVp)
{
    for (FEditorViewportClient* Cvp : GetAllViewports())
    {
        if (Cvp == InVp) return true;
    }
    return false;
}

bool FSmEditorManagerBase::IsActiveViewportInvalid() const
{
    return !IsViewportValid(ActiveViewportClient);
}

void FSmEditorManagerBase::Initialize()
{
    FSpaceMouseManager::Initialize();
    
    auto& Ibm = FInputBindingManager::Get();
    Ibm.SaveInputBindings();
}

void FSmEditorManagerBase::TickManager(float DeltaSecs)
{
    FSpaceMouseManager::TickManager(DeltaSecs);
    ManageActiveViewport();
}

void FSmEditorManagerBase::Tick(float DeltaTime)
{
    TickManager(DeltaTime);
}

void FSmEditorManagerBase::ManageActiveViewport()
{
    auto AllViewportClients = GetAllViewports();
    if(IsActiveViewportInvalid())
    {
        ActiveViewportClient = nullptr;
        OnActiveViewportClosed();
    }
    
    for (FEditorViewportClient* Cvp : AllViewportClients)
    {
        if (!Cvp) continue;
        if (!Cvp->GetEditorViewportWidget().Get()) continue;
        
        OnEnumerateViewport(Cvp);
        
        if (Cvp->GetEditorViewportWidget().Get()->HasAnyUserFocusOrFocusedDescendants())
        {
            if(Cvp == ActiveViewportClient) break;
            if (Cvp->IsVisible() /* && Cvp->IsPerspective() */)
            {
                OnActiveViewportChanged(Cvp, ActiveViewportClient);
                ActiveViewportClient = Cvp;
                break;
            }
        }
    }
}
