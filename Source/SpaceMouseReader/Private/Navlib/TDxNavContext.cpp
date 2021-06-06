// Fill out your copyright notice in the Description page of Project Settings.

#if WITH_3DX_NAVLIB

#include "Navlib/TDxNavContext.h"
#include "Navlib/NavlibAccessor.h"

#include "SpaceMouseReader.h"

FTDxNavContext::FTDxNavContext()
{
}

FTDxNavContext::~FTDxNavContext()
{
}

void FTDxNavContext::Open()
{
    using namespace navlib;

    TArray<accessor_t> Accessors;
    
    AddActiveAccessor(Accessors);
    AddFocusAccessor(Accessors);
    AddMotionAccessor(Accessors);
    AddCoordinateSystemAccessor(Accessors);
    AddDevicePresentAccessor(Accessors);
    AddEventsKeyPressAccessor(Accessors);
    AddEventsKeyReleaseAccessor(Accessors);
    AddTransactionAccessor(Accessors);
    AddFrameTimeAccessor(Accessors);
    AddFrameTimingSourceAccessor(Accessors);
    AddViewAffineAccessor(Accessors);
    AddViewConstructionPlaneAccessor(Accessors);
    AddViewExtentsAccessor(Accessors);
    AddViewFovAccessor(Accessors);
    AddViewFrustumAccessor(Accessors);
    AddViewPerspectiveAccessor(Accessors);
    AddViewRotatableAccessor(Accessors);
    AddViewTargetAccessor(Accessors);
    AddViewsFrontAccessor(Accessors);
    AddPivotPositionAccessor(Accessors);
    AddPivotUserAccessor(Accessors);
    AddPivotVisibleAccessor(Accessors);
    AddHitLookfromAccessor(Accessors);
    AddHitDirectionAccessor(Accessors);
    AddHitApertureAccessor(Accessors);
    AddHitLookatAccessor(Accessors);
    AddHitSelectionOnlyAccessor(Accessors);
    AddSelectionAffineAccessor(Accessors);
    AddSelectionEmptyAccessor(Accessors);
    AddSelectionExtentsAccessor(Accessors);
    AddModelExtentsAccessor(Accessors);
    AddPointerPositionAccessor(Accessors);
    AddCommandsTreeAccessor(Accessors);
    AddCommandsActiveSetAccessor(Accessors);
    AddCommandsActiveCommandAccessor(Accessors);
    AddImagesAccessor(Accessors);
    AddSettingsAccessor(Accessors);
    AddSettingsChangedAccessor(Accessors);

    OnPreOpen(Accessors);

    nlCreateOptions_t Options
    {
        sizeof(nlCreateOptions_t),
        true,
        nlOptions_t::none
    };

    if(auto CreationError = NlCreate(
        &Navlib,
        TCHAR_TO_ANSI(*GetProfileName()),
        Accessors.GetData(),
        Accessors.Num(),
        &Options
    )) {
        UE_LOG(LogSmReader, Error, TEXT("Could not connect to 3DxWare Navlib, %l"), CreationError)
        Navlib = {};
    }
}

#endif