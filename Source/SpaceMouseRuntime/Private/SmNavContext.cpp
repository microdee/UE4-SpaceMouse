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



void FSmNavContextInternal::OnMotionSet(const FMotionProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnMotionSet(InValue.GetUE());
}


void FSmNavContextInternal::OnDevicePresentSet(const FDevicePresentProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnDevicePresentSet(InValue.GetUE());
}


void FSmNavContextInternal::OnEventsKeyPressSet(const FEventsKeyPressProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnEventsKeyPressSet(InValue.GetUE());
}


void FSmNavContextInternal::OnEventsKeyReleaseSet(const FEventsKeyReleaseProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnEventsKeyReleaseSet(InValue.GetUE());
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



void FSmNavContextInternal::OnPivotVisibleSet(const FPivotVisibleProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnPivotVisibleSet(InValue.GetUE());
}


void FSmNavContextInternal::OnHitLookfromSet(const FHitLookfromProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnHitLookfromSet(InValue.GetUE());
}


void FSmNavContextInternal::OnHitDirectionSet(const FHitDirectionProperty& InValue)
{
    if(AssociatedNavCtx.IsValid())
        AssociatedNavCtx->OnHitDirectionSet(InValue.GetUE());
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

bool USmNavContext::IsFocusAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnFocusGet_Implementation(bool& Output) { }

void USmNavContext::OnMotionSet_Implementation(bool Input) { }

void USmNavContext::OnDevicePresentSet_Implementation(bool Input) { }

void USmNavContext::OnEventsKeyPressSet_Implementation(int Input) { }

void USmNavContext::OnEventsKeyReleaseSet_Implementation(int Input) { }

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

bool USmNavContext::IsViewPerspectiveAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnViewPerspectiveGet_Implementation(bool& Output) { }

bool USmNavContext::IsViewRotatableAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnViewRotatableGet_Implementation(bool& Output) { }

bool USmNavContext::IsViewTargetAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnViewTargetGet_Implementation(FVector& Output) { }

bool USmNavContext::IsViewsFrontAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnViewsFrontGet_Implementation(FMatrix& Output) { }

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

void USmNavContext::OnPivotVisibleSet_Implementation(bool Input) { }

void USmNavContext::OnHitLookfromSet_Implementation(FVector Input) { }

void USmNavContext::OnHitDirectionSet_Implementation(FVector Input) { }

void USmNavContext::OnHitApertureSet_Implementation(float Input) { }

bool USmNavContext::IsHitLookatAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnHitLookatGet_Implementation(FVector& Output) { }

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

bool USmNavContext::IsSelectionExtentsAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnSelectionExtentsGet_Implementation(FBox& Output) { }

bool USmNavContext::IsModelExtentsAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnModelExtentsGet_Implementation(FBox& Output) { }

bool USmNavContext::IsPointerPositionAvailable_Implementation()
{
    return true;
}

void USmNavContext::OnPointerPositionGet_Implementation(FVector& Output) { }
