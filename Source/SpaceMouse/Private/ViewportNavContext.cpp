// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewportNavContext.h"
#include "EditorViewportClient.h"
#include "SEditorViewport.h"
#include "Engine/Selection.h"

#if WITH_3DX_NAVLIB

FViewportNavContext::FViewportNavContext(FEditorViewportClient* InAssociatedViewport)
    : FTDxNavContext()
    , AssociatedVp(InAssociatedViewport)
{
}

FViewportNavContext::~FViewportNavContext()
{
    FCoreDelegates::OnEndFrame.Remove(EndFrame);
}

FSceneView* FViewportNavContext::GetSceneView()
{
    if(!ViewCached)
    {
        FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
            AssociatedVp->Viewport,
            AssociatedVp->GetScene(),
            AssociatedVp->EngineShowFlags
        ));
        ViewCached = AssociatedVp->CalcSceneView(&ViewFamily);
    }
    return ViewCached;
}

void FViewportNavContext::OnPostOpen()
{
    FTDxNavContext::OnPostOpen();
    Active.Set(AssociatedVp->IsVisible());
    PrevVisible = AssociatedVp->IsVisible();
    
    EndFrame = FCoreDelegates::OnEndFrame.AddLambda([this]()
    {
        ViewCached = nullptr;
        bHitFrame = false;
        bSelectionBoundsFrame = false;
        PrevMotion = Motion.Get();
    });
    PivotUser.Set(false);
}

void FViewportNavContext::Tick(float DeltaSeconds)
{
    if(IsMotionStartedFrame())
    {
        bWasRealtime = AssociatedVp->IsRealtime();
        bWasOrbitCamera = AssociatedVp->ShouldOrbitCamera();

        AssociatedVp->SetRealtime(true);
        AssociatedVp->ToggleOrbitCamera(false);
    }
    if(IsMotionFinishedFrame())
    {
        AssociatedVp->SetRealtime(bWasRealtime);
        AssociatedVp->ToggleOrbitCamera(bWasOrbitCamera);
    }

    if(AssociatedVp->IsVisible() && (AssociatedVp->IsVisible() ^ PrevVisible))
    {
        Active.Set(true);
    }

    if(PrevVisible && (AssociatedVp->IsVisible() ^ PrevVisible))
    {
        Active.Set(false);
    }

    PrevVisible = AssociatedVp->IsVisible();
}

bool FViewportNavContext::IsMotionStartedFrame() const
{
    const bool CurrMotion = Motion.Get(); 
    return CurrMotion && (CurrMotion ^ PrevMotion);
}

bool FViewportNavContext::IsMotionFinishedFrame() const
{
    const bool CurrMotion = Motion.Get(); 
    return PrevMotion && (CurrMotion ^ PrevMotion);
}

void FViewportNavContext::OnNavlibEndFrame()
{
    if(Motion.Get())
    {
        if(AllowPerspectiveCameraMoveEvent())
        {
            // This is important to trigger PerspectiveCameraMoved event from outside.
            AssociatedVp->MoveViewportCamera(FVector::ZeroVector, FRotator::ZeroRotator);
        }
        AssociatedVp->Viewport->InvalidateHitProxy();
    }
}

void FViewportNavContext::OnViewPerspectiveSet(const FViewPerspectiveProperty& InValue)
{
    AssociatedVp->SetViewportType(InValue.Get() ? LVT_Perspective : LVT_OrthoFreelook);
}

void FViewportNavContext::OnViewPerspectiveGet(FViewPerspectiveProperty& InValue)
{
    InValue.Set(AssociatedVp->IsPerspective());
}

void FViewportNavContext::OnViewRotatableGet(FViewRotatableProperty& InValue)
{
    InValue.Set(
        AssociatedVp->GetViewportType() == LVT_Perspective
        || AssociatedVp->GetViewportType() == LVT_OrthoFreelook
    );
}

bool FViewportNavContext::IsViewExtentsAvailable()
{
    return AssociatedVp->IsOrtho();
}

void FViewportNavContext::OnViewExtentsGet(FViewExtentsProperty& InValue)
{
    FBox Result({
        0.0f,
        -AssociatedVp->GetOrthoZoom() * 0.5f,
        -AssociatedVp->GetOrthoZoom() * 0.5f
    }, {
        AssociatedVp->GetFarClipPlaneOverride(),
        AssociatedVp->GetOrthoZoom() * 0.5f,
        AssociatedVp->GetOrthoZoom() * 0.5f
    });
    InValue.SetUE(Result);
}

void FViewportNavContext::OnViewExtentsSet(const FViewExtentsProperty& InValue)
{
    AssociatedVp->SetOrthoZoom(InValue.GetUE().GetSize().Y);
}

bool FViewportNavContext::IsViewFovAvailable()
{
    return AssociatedVp->IsPerspective();
}

void FViewportNavContext::OnViewFovGet(FViewFovProperty& InValue)
{
    InValue.Set(FMath::DegreesToRadians(AssociatedVp->ViewFOV));
}

void FViewportNavContext::OnViewFovSet(const FViewFovProperty& InValue)
{
    AssociatedVp->ViewFOV = InValue.Get();
}

void FViewportNavContext::OnViewAffineGet(FViewAffineProperty& InValue)
{
    auto View = GetSceneView();
    InValue.SetUE(View->ViewMatrices.GetViewMatrix());
}

void FViewportNavContext::OnViewAffineSet(const FViewAffineProperty& InValue)
{
    FTransform InTr(InValue.GetUE());
    AssociatedVp->SetViewLocation(InTr.GetLocation());
    AssociatedVp->SetViewRotation(FRotator(InTr.GetRotation()));
}

void FViewportNavContext::OnViewFrustumGet(FViewFrustumProperty& InValue)
{
    auto View = GetSceneView();
    InValue.SetUE(View->ViewMatrices.GetProjectionMatrix());
}

void FViewportNavContext::OnPivotPositionSet(const FPivotPositionProperty& InValue)
{
    Pivot = InValue.GetUE();
}

bool FViewportNavContext::IsHitLookatAvailable()
{
    CalcHitTest();
    return bIsHitAvailable;
}

void FViewportNavContext::OnHitLookatGet(FHitLookatProperty& InValue)
{
    CalcHitTest();
    InValue.SetUE(HitPosition);
}

void FViewportNavContext::OnSelectionEmptyGet(FSelectionEmptyProperty& InValue)
{
    InValue.Set(!IsSelectionAvailable());
}

bool FViewportNavContext::IsSelectionAffineAvailable()
{
    return IsSelectionAvailable();
}

void FViewportNavContext::OnSelectionAffineGet(FSelectionAffineProperty& InValue)
{
    auto Selected = GEditor->GetSelectedActors();
    if(Selected->Num() == 1)
    {
        auto SingleSelected = Selected->GetTop<AActor>();
        auto ActorTr = SingleSelected->GetTransform();
        InValue.SetUE(ActorTr.ToMatrixWithScale());
    }
    else if(Selected->Num() > 1)
    {
        CalcSelectionBounds();
        FTransform Result((SelectionMin + SelectionMax) * 0.5f);
        InValue.SetUE(Result.ToMatrixNoScale());
    }
}

void FViewportNavContext::OnSelectionAffineSet(const FSelectionAffineProperty& InValue)
{
    auto Selected = GEditor->GetSelectedActors();
    if(Selected->Num() == 1)
    {
        auto SingleSelected = Selected->GetTop<AActor>();
        SingleSelected->SetActorTransform(FTransform(InValue.GetUE()));
    }
    else if(Selected->Num() > 1)
    {
        TArray<AActor*> Actors;
        Selected->GetSelectedObjects<AActor>(Actors);
        for(auto Actor : Actors)
        {
            FMatrix ActorTr = Actor->GetTransform().ToMatrixWithScale();
            Actor->SetActorTransform(FTransform(ActorTr * InValue.GetUE()));
        }
    }
}

bool FViewportNavContext::IsSelectionExtentsAvailable()
{
    return IsSelectionAvailable();
}

void FViewportNavContext::OnSelectionExtentsGet(FSelectionExtentsProperty& InValue)
{
    InValue.SetUE({SelectionMin, SelectionMax});
}

bool FViewportNavContext::IsModelExtentsAvailable()
{
    // TODO: treat mesh-editor and other single object editor viewports separately.
    return false;
}

void FViewportNavContext::OnPointerPositionGet(FPointerPositionProperty& InValue)
{
    auto WorldCursor = AssociatedVp->GetCursorWorldLocationFromMousePos();
    InValue.SetUE(WorldCursor.GetOrigin());
}

bool FViewportNavContext::AllowPerspectiveCameraMoveEvent() const
{
    static TSet<FName> IncompatibleViewports =
    {
        FName("SStaticMeshEditorViewport")
    };

    FName widgetType = AssociatedVp->GetEditorViewportWidget()->GetType();
    return !IncompatibleViewports.Contains(widgetType);
}

bool FViewportNavContext::IsLevelEditorViewport()
{
    auto VpType = AssociatedVp->GetEditorViewportWidget()->GetType();
    return VpType == FName("SLevelEditorViewport");
}

void FViewportNavContext::CalcHitTest()
{
    if(bHitFrame) return;
    
    const bool WithAperture = false;
    float TempLength = 10000;
    auto Start = HitLookfrom.GetUE();
    auto Dir = HitDirection.GetUE();
    auto World = AssociatedVp->GetWorld();

    // TODO: consider HitSelectionOnly

    if(WithAperture)
    {
        auto Aperture = HitAperture.GetUE();
        FLookFromMatrix LookFrom(Start, Dir, GetSceneView()->GetViewUp());
        TArray<FOverlapResult> Overlaps;
        FVector MiddlePoint = Start + Dir * TempLength * 0.5f;
        FQuat MiddleRot = FRotator(90.0f, 0.0f, 0.0f).Quaternion() * LookFrom.ToQuat();
        bIsHitAvailable = World->OverlapMultiByChannel(
            Overlaps,
            MiddlePoint, MiddleRot,
            ECC_Visibility,
            FCollisionShape::MakeCapsule(Aperture, TempLength * 0.5f),
            FCollisionQueryParams(true),
            FCollisionResponseParams(ECR_Overlap)
        );
        if(bIsHitAvailable)
        {
            // TODO: get closest overlap and other things
        }
    }
    else
    {
        FHitResult HitResult;
        bIsHitAvailable = World->LineTraceSingleByChannel(
            HitResult,
            Start,
            Start + Dir * TempLength,
            ECC_Visibility,
            FCollisionQueryParams(true)
        );
        if(bIsHitAvailable)
        {
            HitPosition = HitResult.Location;
        }
    }
    bHitFrame = true;
}

void FViewportNavContext::CalcSelectionBounds()
{
    if(bSelectionBoundsFrame) return;
    
    auto Selected = GEditor->GetSelectedActors();
    if(Selected->Num() == 1)
    {
        auto SingleSelected = Selected->GetTop<AActor>();
        FVector Center, Extent;
        SingleSelected->GetActorBounds(true, Center, Extent, true);
        SelectionMin = Center - Extent * 0.5f;
        SelectionMin = Center + Extent * 0.5f;
    }
    else if(Selected->Num() > 1)
    {
        FVector MinLocation({std::numeric_limits<float>::max()});
        FVector MaxLocation({std::numeric_limits<float>::min()});
        
        TArray<AActor*> Actors;
        Selected->GetSelectedObjects<AActor>(Actors);
        for(auto Actor : Actors)
        {
            FVector Center, Extent;
            Actor->GetActorBounds(true, Center, Extent, true);
            MinLocation = MinLocation.ComponentMin(Center - Extent * 0.5f);
            MaxLocation = MaxLocation.ComponentMax(Center + Extent * 0.5f);
        }
    }
    bSelectionBoundsFrame = true;
}

bool FViewportNavContext::IsSelectionAvailable()
{
    if(IsLevelEditorViewport())
    {
        auto Selected = GEditor->GetSelectedActors();
        return Selected->Num() > 0;
    }
    return false;
}

#endif
