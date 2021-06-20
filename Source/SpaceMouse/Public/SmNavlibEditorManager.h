// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmEditorManagerBase.h"
#include "TickableEditorObject.h"

class FViewportNavContext;

/**
 * 
 */
class SPACEMOUSE_API FSmNavlibEditorManager : public FSmEditorManagerBase
{
public:
    FSmNavlibEditorManager();
    virtual ~FSmNavlibEditorManager() override;
protected:
    virtual void TickManager(float DeltaSecs) override;

    virtual void OnEnumerateViewport(FEditorViewportClient* Current) override;
    virtual void OnActiveViewportChanged(FEditorViewportClient* Current, FEditorViewportClient* Previous) override;
private:
    
    TMap<FEditorViewportClient*, TSharedPtr<FViewportNavContext>> AllNavContexts;
};
