// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navlib/TDxNavContext.h"

#if WITH_3DX_NAVLIB

class FSceneView;
/**
 * 
 */
class SPACEMOUSE_API FViewportNavContext : public FTDxNavContext
{
public:
    FViewportNavContext(FEditorViewportClient* InAssociatedViewport);
    virtual ~FViewportNavContext() override;

    FSceneView* GetSceneView();
    virtual void OnPostOpen() override;
    void Tick(float DeltaSeconds);

    bool IsMotionStartedFrame() const;
    bool IsMotionFinishedFrame() const;

    virtual void OnNavlibEndFrame() override;

    virtual void OnViewPerspectiveSet(const FViewPerspectiveProperty& InValue) override;
    virtual void OnViewPerspectiveGet(FViewPerspectiveProperty& InValue) override;
    virtual void OnViewRotatableGet(FViewRotatableProperty& InValue) override;
    
    virtual bool IsViewExtentsAvailable() override;
    virtual void OnViewExtentsGet(FViewExtentsProperty& InValue) override;
    virtual void OnViewExtentsSet(const FViewExtentsProperty& InValue) override;

    virtual bool IsViewFovAvailable() override;
    virtual void OnViewFovGet(FViewFovProperty& InValue) override;
    virtual void OnViewFovSet(const FViewFovProperty& InValue) override;

    virtual void OnViewAffineGet(FViewAffineProperty& InValue) override;
    virtual void OnViewAffineSet(const FViewAffineProperty& InValue) override;
    virtual void OnViewFrustumGet(FViewFrustumProperty& InValue) override;

    // I'm not sure yet how restrictive this is according to its description
    virtual bool IsViewTargetAvailable() override { return false; }

    virtual void OnPivotPositionSet(const FPivotPositionProperty& InValue) override;

    virtual bool IsHitLookatAvailable() override;
    virtual void OnHitLookatGet(FHitLookatProperty& InValue) override;

    virtual void OnSelectionEmptyGet(FSelectionEmptyProperty& InValue) override;

    virtual bool IsSelectionAffineAvailable() override;
    virtual void OnSelectionAffineGet(FSelectionAffineProperty& InValue) override;
    virtual void OnSelectionAffineSet(const FSelectionAffineProperty& InValue) override;

    virtual bool IsSelectionExtentsAvailable() override;
    virtual void OnSelectionExtentsGet(FSelectionExtentsProperty& InValue) override;
    
    // TODO: treat mesh-editor and other single object editor viewports separately.
    virtual bool IsModelExtentsAvailable() override;

    virtual void OnPointerPositionGet(FPointerPositionProperty& InValue) override;
    
protected:
    FEditorViewportClient* AssociatedVp;
    bool AllowPerspectiveCameraMoveEvent() const;

    bool IsLevelEditorViewport();
    void CalcHitTest();
    void CalcSelectionBounds();
    bool IsSelectionAvailable();
    
    bool bWasRealtime = false;
    bool bWasOrbitCamera = false;
    
private:
    FSceneView* ViewCached = nullptr;
    FDelegateHandle EndFrame;

    bool PrevMotion;
    
    bool bHitFrame;
    bool bIsHitAvailable;
    FVector HitPosition;
    FVector Pivot;

    bool bSelectionBoundsFrame;
    FVector SelectionMin;
    FVector SelectionMax;
};

#endif
