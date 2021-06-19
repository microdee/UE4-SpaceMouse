// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#include "SmNavContext.h"
#include "Navlib/TDxNavContext.h"

FSmNavContextInternal::FSmNavContextInternal(TWeakObjectPtr<USmNavContext> InAssociatedNavCtx)
    : FTDxNavContext()
    , AssociatedNavCtx(InAssociatedNavCtx)
{ }

void FSmNavContextInternal::OnPostOpen()
{
    FTDxNavContext::OnPostOpen();
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnPostOpen();
}

FString FSmNavContextInternal::GetProfileName()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->GetProfileName();
    return TEXT("Unnamed Unreal Engine Runtime Navigation Context");
}


bool FSmNavContextInternal::IsActiveAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsActiveAvailable();
    return false;
}

void FSmNavContextInternal::OnActiveGet(FActiveProperty& InValue)
{
    bool Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnActiveGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnActiveSet(const FActiveProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnActiveSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsFocusAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsFocusAvailable();
    return false;
}

void FSmNavContextInternal::OnFocusGet(FFocusProperty& InValue)
{
    bool Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnFocusGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnFocusSet(const FFocusProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnFocusSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsMotionAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsMotionAvailable();
    return false;
}

void FSmNavContextInternal::OnMotionGet(FMotionProperty& InValue)
{
    bool Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnMotionGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnMotionSet(const FMotionProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnMotionSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsDevicePresentAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsDevicePresentAvailable();
    return false;
}

void FSmNavContextInternal::OnDevicePresentGet(FDevicePresentProperty& InValue)
{
    bool Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnDevicePresentGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnDevicePresentSet(const FDevicePresentProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnDevicePresentSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsEventsKeyPressAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsEventsKeyPressAvailable();
    return false;
}

void FSmNavContextInternal::OnEventsKeyPressGet(FEventsKeyPressProperty& InValue)
{
    int Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnEventsKeyPressGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnEventsKeyPressSet(const FEventsKeyPressProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnEventsKeyPressSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsEventsKeyReleaseAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsEventsKeyReleaseAvailable();
    return false;
}

void FSmNavContextInternal::OnEventsKeyReleaseGet(FEventsKeyReleaseProperty& InValue)
{
    int Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnEventsKeyReleaseGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnEventsKeyReleaseSet(const FEventsKeyReleaseProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnEventsKeyReleaseSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsTransactionAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsTransactionAvailable();
    return false;
}

void FSmNavContextInternal::OnTransactionGet(FTransactionProperty& InValue)
{
    int Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnTransactionGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnTransactionSet(const FTransactionProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnTransactionSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsViewAffineAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsViewAffineAvailable();
    return false;
}

void FSmNavContextInternal::OnViewAffineGet(FViewAffineProperty& InValue)
{
    FMatrix Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnViewAffineGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnViewAffineSet(const FViewAffineProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnViewAffineSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsViewConstructionPlaneAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsViewConstructionPlaneAvailable();
    return false;
}

void FSmNavContextInternal::OnViewConstructionPlaneGet(FViewConstructionPlaneProperty& InValue)
{
    FPlane Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnViewConstructionPlaneGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnViewConstructionPlaneSet(const FViewConstructionPlaneProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnViewConstructionPlaneSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsViewExtentsAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsViewExtentsAvailable();
    return false;
}

void FSmNavContextInternal::OnViewExtentsGet(FViewExtentsProperty& InValue)
{
    FBox Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnViewExtentsGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnViewExtentsSet(const FViewExtentsProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnViewExtentsSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsViewFovAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsViewFovAvailable();
    return false;
}

void FSmNavContextInternal::OnViewFovGet(FViewFovProperty& InValue)
{
    float Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnViewFovGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnViewFovSet(const FViewFovProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnViewFovSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsViewFrustumAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsViewFrustumAvailable();
    return false;
}

void FSmNavContextInternal::OnViewFrustumGet(FViewFrustumProperty& InValue)
{
    FMatrix Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnViewFrustumGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnViewFrustumSet(const FViewFrustumProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnViewFrustumSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsViewPerspectiveAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsViewPerspectiveAvailable();
    return false;
}

void FSmNavContextInternal::OnViewPerspectiveGet(FViewPerspectiveProperty& InValue)
{
    bool Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnViewPerspectiveGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnViewPerspectiveSet(const FViewPerspectiveProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnViewPerspectiveSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsViewRotatableAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsViewRotatableAvailable();
    return false;
}

void FSmNavContextInternal::OnViewRotatableGet(FViewRotatableProperty& InValue)
{
    bool Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnViewRotatableGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnViewRotatableSet(const FViewRotatableProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnViewRotatableSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsViewTargetAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsViewTargetAvailable();
    return false;
}

void FSmNavContextInternal::OnViewTargetGet(FViewTargetProperty& InValue)
{
    FVector Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnViewTargetGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnViewTargetSet(const FViewTargetProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnViewTargetSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsViewsFrontAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsViewsFrontAvailable();
    return false;
}

void FSmNavContextInternal::OnViewsFrontGet(FViewsFrontProperty& InValue)
{
    FMatrix Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnViewsFrontGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnViewsFrontSet(const FViewsFrontProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnViewsFrontSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsPivotPositionAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsPivotPositionAvailable();
    return false;
}

void FSmNavContextInternal::OnPivotPositionGet(FPivotPositionProperty& InValue)
{
    FVector Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnPivotPositionGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnPivotPositionSet(const FPivotPositionProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnPivotPositionSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsPivotUserAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsPivotUserAvailable();
    return false;
}

void FSmNavContextInternal::OnPivotUserGet(FPivotUserProperty& InValue)
{
    bool Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnPivotUserGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnPivotUserSet(const FPivotUserProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnPivotUserSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsPivotVisibleAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsPivotVisibleAvailable();
    return false;
}

void FSmNavContextInternal::OnPivotVisibleGet(FPivotVisibleProperty& InValue)
{
    bool Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnPivotVisibleGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnPivotVisibleSet(const FPivotVisibleProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnPivotVisibleSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsHitLookfromAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsHitLookfromAvailable();
    return false;
}

void FSmNavContextInternal::OnHitLookfromGet(FHitLookfromProperty& InValue)
{
    FVector Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnHitLookfromGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnHitLookfromSet(const FHitLookfromProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnHitLookfromSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsHitDirectionAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsHitDirectionAvailable();
    return false;
}

void FSmNavContextInternal::OnHitDirectionGet(FHitDirectionProperty& InValue)
{
    FVector Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnHitDirectionGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnHitDirectionSet(const FHitDirectionProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnHitDirectionSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsHitApertureAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsHitApertureAvailable();
    return false;
}

void FSmNavContextInternal::OnHitApertureGet(FHitApertureProperty& InValue)
{
    float Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnHitApertureGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnHitApertureSet(const FHitApertureProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnHitApertureSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsHitLookatAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsHitLookatAvailable();
    return false;
}

void FSmNavContextInternal::OnHitLookatGet(FHitLookatProperty& InValue)
{
    FVector Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnHitLookatGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnHitLookatSet(const FHitLookatProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnHitLookatSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsHitSelectionOnlyAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsHitSelectionOnlyAvailable();
    return false;
}

void FSmNavContextInternal::OnHitSelectionOnlyGet(FHitSelectionOnlyProperty& InValue)
{
    bool Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnHitSelectionOnlyGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnHitSelectionOnlySet(const FHitSelectionOnlyProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnHitSelectionOnlySet(InValue.GetUE());
}

bool FSmNavContextInternal::IsSelectionAffineAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsSelectionAffineAvailable();
    return false;
}

void FSmNavContextInternal::OnSelectionAffineGet(FSelectionAffineProperty& InValue)
{
    FMatrix Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnSelectionAffineGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnSelectionAffineSet(const FSelectionAffineProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnSelectionAffineSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsSelectionEmptyAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsSelectionEmptyAvailable();
    return false;
}

void FSmNavContextInternal::OnSelectionEmptyGet(FSelectionEmptyProperty& InValue)
{
    bool Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnSelectionEmptyGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnSelectionEmptySet(const FSelectionEmptyProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnSelectionEmptySet(InValue.GetUE());
}

bool FSmNavContextInternal::IsSelectionExtentsAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsSelectionExtentsAvailable();
    return false;
}

void FSmNavContextInternal::OnSelectionExtentsGet(FSelectionExtentsProperty& InValue)
{
    FBox Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnSelectionExtentsGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnSelectionExtentsSet(const FSelectionExtentsProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnSelectionExtentsSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsModelExtentsAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsModelExtentsAvailable();
    return false;
}

void FSmNavContextInternal::OnModelExtentsGet(FModelExtentsProperty& InValue)
{
    FBox Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnModelExtentsGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnModelExtentsSet(const FModelExtentsProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnModelExtentsSet(InValue.GetUE());
}

bool FSmNavContextInternal::IsPointerPositionAvailable()
{
    if(AssociatedNavCtx.IsValid())
        return AssociatedNavCtx->IsPointerPositionAvailable();
    return false;
}

void FSmNavContextInternal::OnPointerPositionGet(FPointerPositionProperty& InValue)
{
    FVector Output {};
    if(AssociatedNavCtx.IsValid())
    {
        AssociatedNavCtx->OnPointerPositionGet(Output);
        InValue.SetUE(Output);
    }
}

void FSmNavContextInternal::OnPointerPositionSet(const FPointerPositionProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnPointerPositionSet(InValue.GetUE());
}


void USmNavContext::PostLoad()
{
    NavlibCtx = MakeUnique<FSmNavContextInternal>(this);
}

FString USmNavContext::GetProfileName_Implementation()
{
    return TEXT("Unnamed Unreal Engine Runtime Navigation Context");
}

void USmNavContext::Open()
{
    if(NavlibCtx) NavlibCtx->Open();
}

void USmNavContext::OnPostOpen_Implementation() { }


bool USmNavContext::IsActiveAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnActiveGet_Implementation(bool& Output) { }
void USmNavContext::OnActiveSet_Implementation(bool Input) { }

bool USmNavContext::IsFocusAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnFocusGet_Implementation(bool& Output) { }
void USmNavContext::OnFocusSet_Implementation(bool Input) { }

bool USmNavContext::IsMotionAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnMotionGet_Implementation(bool& Output) { }
void USmNavContext::OnMotionSet_Implementation(bool Input) { }

bool USmNavContext::IsDevicePresentAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnDevicePresentGet_Implementation(bool& Output) { }
void USmNavContext::OnDevicePresentSet_Implementation(bool Input) { }

bool USmNavContext::IsEventsKeyPressAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnEventsKeyPressGet_Implementation(int& Output) { }
void USmNavContext::OnEventsKeyPressSet_Implementation(int Input) { }

bool USmNavContext::IsEventsKeyReleaseAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnEventsKeyReleaseGet_Implementation(int& Output) { }
void USmNavContext::OnEventsKeyReleaseSet_Implementation(int Input) { }

bool USmNavContext::IsTransactionAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnTransactionGet_Implementation(int& Output) { }
void USmNavContext::OnTransactionSet_Implementation(int Input) { }

bool USmNavContext::IsViewAffineAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnViewAffineGet_Implementation(FMatrix& Output) { }
void USmNavContext::OnViewAffineSet_Implementation(FMatrix Input) { }

bool USmNavContext::IsViewConstructionPlaneAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnViewConstructionPlaneGet_Implementation(FPlane& Output) { }
void USmNavContext::OnViewConstructionPlaneSet_Implementation(FPlane Input) { }

bool USmNavContext::IsViewExtentsAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnViewExtentsGet_Implementation(FBox& Output) { }
void USmNavContext::OnViewExtentsSet_Implementation(FBox Input) { }

bool USmNavContext::IsViewFovAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnViewFovGet_Implementation(float& Output) { }
void USmNavContext::OnViewFovSet_Implementation(float Input) { }

bool USmNavContext::IsViewFrustumAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnViewFrustumGet_Implementation(FMatrix& Output) { }
void USmNavContext::OnViewFrustumSet_Implementation(FMatrix Input) { }

bool USmNavContext::IsViewPerspectiveAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnViewPerspectiveGet_Implementation(bool& Output) { }
void USmNavContext::OnViewPerspectiveSet_Implementation(bool Input) { }

bool USmNavContext::IsViewRotatableAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnViewRotatableGet_Implementation(bool& Output) { }
void USmNavContext::OnViewRotatableSet_Implementation(bool Input) { }

bool USmNavContext::IsViewTargetAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnViewTargetGet_Implementation(FVector& Output) { }
void USmNavContext::OnViewTargetSet_Implementation(FVector Input) { }

bool USmNavContext::IsViewsFrontAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnViewsFrontGet_Implementation(FMatrix& Output) { }
void USmNavContext::OnViewsFrontSet_Implementation(FMatrix Input) { }

bool USmNavContext::IsPivotPositionAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnPivotPositionGet_Implementation(FVector& Output) { }
void USmNavContext::OnPivotPositionSet_Implementation(FVector Input) { }

bool USmNavContext::IsPivotUserAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnPivotUserGet_Implementation(bool& Output) { }
void USmNavContext::OnPivotUserSet_Implementation(bool Input) { }

bool USmNavContext::IsPivotVisibleAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnPivotVisibleGet_Implementation(bool& Output) { }
void USmNavContext::OnPivotVisibleSet_Implementation(bool Input) { }

bool USmNavContext::IsHitLookfromAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnHitLookfromGet_Implementation(FVector& Output) { }
void USmNavContext::OnHitLookfromSet_Implementation(FVector Input) { }

bool USmNavContext::IsHitDirectionAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnHitDirectionGet_Implementation(FVector& Output) { }
void USmNavContext::OnHitDirectionSet_Implementation(FVector Input) { }

bool USmNavContext::IsHitApertureAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnHitApertureGet_Implementation(float& Output) { }
void USmNavContext::OnHitApertureSet_Implementation(float Input) { }

bool USmNavContext::IsHitLookatAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnHitLookatGet_Implementation(FVector& Output) { }
void USmNavContext::OnHitLookatSet_Implementation(FVector Input) { }

bool USmNavContext::IsHitSelectionOnlyAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnHitSelectionOnlyGet_Implementation(bool& Output) { }
void USmNavContext::OnHitSelectionOnlySet_Implementation(bool Input) { }

bool USmNavContext::IsSelectionAffineAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnSelectionAffineGet_Implementation(FMatrix& Output) { }
void USmNavContext::OnSelectionAffineSet_Implementation(FMatrix Input) { }

bool USmNavContext::IsSelectionEmptyAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnSelectionEmptyGet_Implementation(bool& Output) { }
void USmNavContext::OnSelectionEmptySet_Implementation(bool Input) { }

bool USmNavContext::IsSelectionExtentsAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnSelectionExtentsGet_Implementation(FBox& Output) { }
void USmNavContext::OnSelectionExtentsSet_Implementation(FBox Input) { }

bool USmNavContext::IsModelExtentsAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnModelExtentsGet_Implementation(FBox& Output) { }
void USmNavContext::OnModelExtentsSet_Implementation(FBox Input) { }

bool USmNavContext::IsPointerPositionAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnPointerPositionGet_Implementation(FVector& Output) { }
void USmNavContext::OnPointerPositionSet_Implementation(FVector Input) { }
