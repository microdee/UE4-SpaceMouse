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
    if(IsActiveAvailable())
    {
        bool Output = AssociatedNavCtx->OnActiveGet();
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
    if(IsFocusAvailable())
    {
        bool Output = AssociatedNavCtx->OnFocusGet();
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
    if(IsViewAffineAvailable())
    {
        FMatrix Output = AssociatedNavCtx->OnViewAffineGet();
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
    if(IsViewConstructionPlaneAvailable())
    {
        FPlane Output = AssociatedNavCtx->OnViewConstructionPlaneGet();
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
    if(IsViewExtentsAvailable())
    {
        FBox Output = AssociatedNavCtx->OnViewExtentsGet();
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
    if(IsViewFovAvailable())
    {
        float Output = AssociatedNavCtx->OnViewFovGet();
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
    if(IsViewFrustumAvailable())
    {
        FMatrix Output = AssociatedNavCtx->OnViewFrustumGet();
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
    if(IsViewPerspectiveAvailable())
    {
        bool Output = AssociatedNavCtx->OnViewPerspectiveGet();
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
    if(IsViewRotatableAvailable())
    {
        bool Output = AssociatedNavCtx->OnViewRotatableGet();
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
    if(IsViewTargetAvailable())
    {
        FVector Output = AssociatedNavCtx->OnViewTargetGet();
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
    if(IsViewsFrontAvailable())
    {
        FMatrix Output = AssociatedNavCtx->OnViewsFrontGet();
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
    if(IsPivotPositionAvailable())
    {
        FVector Output = AssociatedNavCtx->OnPivotPositionGet();
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
    if(IsPivotUserAvailable())
    {
        bool Output = AssociatedNavCtx->OnPivotUserGet();
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
    if(IsHitLookatAvailable())
    {
        FVector Output = AssociatedNavCtx->OnHitLookatGet();
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
    if(IsSelectionAffineAvailable())
    {
        FMatrix Output = AssociatedNavCtx->OnSelectionAffineGet();
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
    if(IsSelectionEmptyAvailable())
    {
        bool Output = AssociatedNavCtx->OnSelectionEmptyGet();
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
    if(IsSelectionExtentsAvailable())
    {
        FBox Output = AssociatedNavCtx->OnSelectionExtentsGet();
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
    if(IsModelExtentsAvailable())
    {
        FBox Output = AssociatedNavCtx->OnModelExtentsGet();
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
    if(IsPointerPositionAvailable())
    {
        FVector Output = AssociatedNavCtx->OnPointerPositionGet();
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

bool USmNavContext::OnActiveGet_Implementation()
{
    return {};
}

bool USmNavContext::IsFocusAvailable_Implementation()
{
    return true;
}

bool USmNavContext::OnFocusGet_Implementation()
{
    return {};
}

void USmNavContext::OnMotionSet_Implementation(bool Input) { }

void USmNavContext::OnDevicePresentSet_Implementation(bool Input) { }

void USmNavContext::OnEventsKeyPressSet_Implementation(int Input) { }

void USmNavContext::OnEventsKeyReleaseSet_Implementation(int Input) { }

void USmNavContext::OnTransactionSet_Implementation(int Input) { }

bool USmNavContext::IsViewAffineAvailable_Implementation()
{
    return true;
}

FMatrix USmNavContext::OnViewAffineGet_Implementation()
{
    return {};
}
void USmNavContext::OnViewAffineSet_Implementation(FMatrix Input) { }

bool USmNavContext::IsViewConstructionPlaneAvailable_Implementation()
{
    return true;
}

FPlane USmNavContext::OnViewConstructionPlaneGet_Implementation()
{
    return {};
}

bool USmNavContext::IsViewExtentsAvailable_Implementation()
{
    return true;
}

FBox USmNavContext::OnViewExtentsGet_Implementation()
{
    return {};
}
void USmNavContext::OnViewExtentsSet_Implementation(FBox Input) { }

bool USmNavContext::IsViewFovAvailable_Implementation()
{
    return true;
}

float USmNavContext::OnViewFovGet_Implementation()
{
    return {};
}
void USmNavContext::OnViewFovSet_Implementation(float Input) { }

bool USmNavContext::IsViewFrustumAvailable_Implementation()
{
    return true;
}

FMatrix USmNavContext::OnViewFrustumGet_Implementation()
{
    return {};
}

bool USmNavContext::IsViewPerspectiveAvailable_Implementation()
{
    return true;
}

bool USmNavContext::OnViewPerspectiveGet_Implementation()
{
    return {};
}

bool USmNavContext::IsViewRotatableAvailable_Implementation()
{
    return true;
}

bool USmNavContext::OnViewRotatableGet_Implementation()
{
    return {};
}

bool USmNavContext::IsViewTargetAvailable_Implementation()
{
    return true;
}

FVector USmNavContext::OnViewTargetGet_Implementation()
{
    return {};
}

bool USmNavContext::IsViewsFrontAvailable_Implementation()
{
    return true;
}

FMatrix USmNavContext::OnViewsFrontGet_Implementation()
{
    return {};
}

bool USmNavContext::IsPivotPositionAvailable_Implementation()
{
    return true;
}

FVector USmNavContext::OnPivotPositionGet_Implementation()
{
    return {};
}
void USmNavContext::OnPivotPositionSet_Implementation(FVector Input) { }

bool USmNavContext::IsPivotUserAvailable_Implementation()
{
    return true;
}

bool USmNavContext::OnPivotUserGet_Implementation()
{
    return {};
}

void USmNavContext::OnPivotVisibleSet_Implementation(bool Input) { }

void USmNavContext::OnHitLookfromSet_Implementation(FVector Input) { }

void USmNavContext::OnHitDirectionSet_Implementation(FVector Input) { }

void USmNavContext::OnHitApertureSet_Implementation(float Input) { }

bool USmNavContext::IsHitLookatAvailable_Implementation()
{
    return true;
}

FVector USmNavContext::OnHitLookatGet_Implementation()
{
    return {};
}

void USmNavContext::OnHitSelectionOnlySet_Implementation(bool Input) { }

bool USmNavContext::IsSelectionAffineAvailable_Implementation()
{
    return true;
}

FMatrix USmNavContext::OnSelectionAffineGet_Implementation()
{
    return {};
}
void USmNavContext::OnSelectionAffineSet_Implementation(FMatrix Input) { }

bool USmNavContext::IsSelectionEmptyAvailable_Implementation()
{
    return true;
}

bool USmNavContext::OnSelectionEmptyGet_Implementation()
{
    return {};
}

bool USmNavContext::IsSelectionExtentsAvailable_Implementation()
{
    return true;
}

FBox USmNavContext::OnSelectionExtentsGet_Implementation()
{
    return {};
}

bool USmNavContext::IsModelExtentsAvailable_Implementation()
{
    return true;
}

FBox USmNavContext::OnModelExtentsGet_Implementation()
{
    return {};
}

bool USmNavContext::IsPointerPositionAvailable_Implementation()
{
    return true;
}

FVector USmNavContext::OnPointerPositionGet_Implementation()
{
    return {};
}
