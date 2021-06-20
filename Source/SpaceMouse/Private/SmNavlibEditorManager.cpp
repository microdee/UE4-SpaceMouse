// Fill out your copyright notice in the Description page of Project Settings.


#include "SmNavlibEditorManager.h"

#include "EditorViewportClient.h"
#include "ViewportNavContext.h"


FSmNavlibEditorManager::FSmNavlibEditorManager()
    : FSmEditorManagerBase()
{
}

FSmNavlibEditorManager::~FSmNavlibEditorManager()
{
}

void FSmNavlibEditorManager::TickManager(float DeltaSecs)
{
    FSmEditorManagerBase::TickManager(DeltaSecs);

    TArray<FEditorViewportClient*> InvalidViewports;
    for(auto Vp : AllNavContexts)
    {
        if(IsViewportValid(Vp.Key)) continue;
        InvalidViewports.Add(Vp.Key);
    }
    for(auto InvalidVp : InvalidViewports)
    {
        AllNavContexts.Remove(InvalidVp);
    }
    
    for(auto Vp : AllNavContexts)
    {
        Vp.Value->Tick(DeltaSecs);
    }
}

void FSmNavlibEditorManager::OnEnumerateViewport(FEditorViewportClient* Current)
{
    if(!AllNavContexts.Contains(Current))
    {
        auto NewVp = MakeShared<FViewportNavContext>(Current);
        NewVp->Open();
        AllNavContexts.Add(Current, NewVp);
    }
}

void FSmNavlibEditorManager::OnActiveViewportChanged(FEditorViewportClient* Current, FEditorViewportClient* Previous)
{
    if(Current) AllNavContexts[Current]->Focus.Set(true);
    if(Previous) AllNavContexts[Previous]->Focus.Set(false);
}
