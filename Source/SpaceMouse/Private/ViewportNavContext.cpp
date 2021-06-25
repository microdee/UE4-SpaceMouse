// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewportNavContext.h"
#include "EditorViewportClient.h"
#include "SEditorViewport.h"
#include "Engine/Selection.h"
#include "Widgets/SDebugVpNavlib.h"

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
    if(!AssociatedVp->IsVisible()) return nullptr;
    if(AssociatedVp->Viewport->GetSizeXY().X <= 0 || AssociatedVp->Viewport->GetSizeXY().Y <= 0)
        return nullptr;
    
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

    if(auto VpOverlay = GetOverlayWidgetOfVp())
    {
        auto GetProj = [=]() -> FMatrix
        {
            if(auto View = GetSceneView())
            {
                return View->ViewMatrices.ComputeInvProjectionNoAAMatrix();
            }
            return FMatrix::Identity;
        };
        auto GetFrustum = [=]() -> navlib::frustum_t
        {
            if(auto View = GetSceneView())
            {
                return navlib::TUnreal<navlib::frustum_t>::To(GetProj());
            }
            return {};
        };
        VpOverlay->AddSlot()
            . HAlign(HAlign_Fill)
            . VAlign(VAlign_Fill)
            [
                SAssignNew(DebugUI, SDebugVpNavlib)
                . SceneViewTr_Lambda([this]
                {
                    if(auto View = GetSceneView())
                    {
                        return View->ViewMatrices.GetInvViewMatrix();
                    }
                    return FMatrix::Identity;
                })
                . ProjTr_Lambda([=] { return GetProj(); })
                . LocRotTr_Lambda([this]
                {
                    FTransform ViewTr(
                        AssociatedVp->GetViewRotation(),
                        AssociatedVp->GetViewLocation()
                    );
                    return FMatrix(
                        {0, 1, 0, 0},
                        {0, 0, 1, 0},
                        {1, 0, 0, 0},
                        {0, 0, 0, 1}
                    ) * ViewTr.ToMatrixNoScale();
                })
                . PivotPos_Lambda([this]{ return PivotPosition.GetCachedUE(); })
                . PointerPos_Lambda([this]{ return PointerPosition.GetCachedUE(); })
                . HitPos_Lambda([this]{ CalcHitTest(); return HitPosition; })
                . HitLookfrom_Lambda([this]{ return HitLookfrom.GetCachedUE(); })
                . HitDirection_Lambda([this]{ return HitDirection.GetCachedUE(); })
            ];
    }
}

void FViewportNavContext::Tick(float DeltaSeconds)
{
    OnFrameTimeGet(FrameTime);
    if(IsMotionStartedFrame())
    {
        bWasRealtime = AssociatedVp->IsRealtime();
        bWasOrbitCamera = AssociatedVp->ShouldOrbitCamera();

        AssociatedVp->SetRealtime(true);
        AssociatedVp->ToggleOrbitCamera(false);
    }
    if(IsMotionFinishedFrame())
    {
        //AssociatedVp->SetRealtime(bWasRealtime);
        //AssociatedVp->ToggleOrbitCamera(bWasOrbitCamera);
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

FString FViewportNavContext::GetProfileName()
{
    auto VpType = AssociatedVp->GetEditorViewportWidget()->GetType().ToString();
    return FString::Printf(TEXT("Unreal Engine (%s)"), *VpType);
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
    FTransform ViewTr(
        AssociatedVp->GetViewRotation(),
        AssociatedVp->GetViewLocation()
    );
    InValue.SetUE(ViewTr.ToMatrixNoScale());
}

void FViewportNavContext::OnViewAffineSet(const FViewAffineProperty& InValue)
{
    FTransform InTr(InValue.GetUE());
    AssociatedVp->SetViewLocation(InTr.GetLocation());
    AssociatedVp->SetViewRotation(FRotator(InTr.GetRotation()));
}

void FViewportNavContext::OnViewFrustumGet(FViewFrustumProperty& InValue)
{
    if(auto View = GetSceneView())
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
    return VpType == FName("SLevelViewport");
}

void FViewportNavContext::CalcHitTest()
{
    if(bHitFrame) return;
    if(!GetSceneView()) return;
    
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

void FViewportNavContext::DebugMatrix(uint64 Line, const TCHAR* Label, FMatrix $)
{
    GEngine->AddOnScreenDebugMessage(
        reinterpret_cast<uint64>(this) ^ Line, 100.0f, FColor::Purple,
        FString::Printf(
            TEXT("%s:\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n"),
            Label,
            $.M[0][0], $.M[0][1], $.M[0][2], $.M[0][3],
            $.M[1][0], $.M[1][1], $.M[1][2], $.M[1][3],
            $.M[2][0], $.M[2][1], $.M[2][2], $.M[2][3],
            $.M[3][0], $.M[3][1], $.M[3][2], $.M[3][3]
        )
    );
}

TSharedPtr<SWidget> FViewportNavContext::GetChildWidgetOfType(TSharedPtr<SWidget> InWidget, FName InType)
{
    if(InWidget->GetType() == InType) return InWidget;
    auto Children = InWidget->GetChildren();

    for(int i=0; i<Children->Num(); i++)
    {
        auto CurrChild = GetChildWidgetOfType(
            Children->GetChildAt(i),
            InType
        );
        if(CurrChild.IsValid()) return CurrChild;
    }
    return {};
}

TSharedPtr<SOverlay> FViewportNavContext::GetOverlayWidgetOfVp()
{
    auto VpRootWidget = AssociatedVp->GetEditorViewportWidget();
    auto Viewport = StaticCastSharedPtr<SViewport>(GetChildWidgetOfType(VpRootWidget, TEXT("SViewport")));
    if(!Viewport) return {};
    return StaticCastSharedRef<SOverlay>(Viewport->GetChildren()->GetChildAt(0));
}

#endif
