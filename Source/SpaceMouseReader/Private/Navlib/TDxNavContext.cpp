// Fill out your copyright notice in the Description page of Project Settings.


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
    
    Connection = MakeUnique<FTDxNavConnection>();
    TArray<accessor_t> Accessors;

    REGISTER_PROP(bool, motion_k,
        $.Setter.BindRaw(this, &FTDxNavContext::OnMotion);
    );
    REGISTER_PROP(matrix_t, coordinate_system_k,
        $.Getter.BindRaw(this, &FTDxNavContext::SetCoordinateSystem);
    );
    REGISTER_PROP(long, events_keyPress_k,
        $.Setter.BindRaw(this, &FTDxNavContext::OnEventsKeyPress);
    );
    REGISTER_PROP(long, events_keyRelease_k,
        $.Setter.BindRaw(this, &FTDxNavContext::OnEventsKeyRelease);
    );
    REGISTER_PROP(long, transaction_k,
        $.Setter.BindRaw(this, &FTDxNavContext::OnTransaction);
    );
    REGISTER_PROP(double, frame_time_k,
        $.Getter.BindRaw(this, &FTDxNavContext::SetFrameTime);
    );
    REGISTER_PROP(long, frame_timing_source_k,
        $.Getter.BindRaw(this, &FTDxNavContext::SetFrameTimingSource);
    );
    REGISTER_PROP(matrix_t, view_affine_k,
        $.Setter.BindRaw(this, &FTDxNavContext::OnViewAffine);
        $.Getter.BindRaw(this, &FTDxNavContext::SetViewAffine);
    );
    REGISTER_PROP(plane_t, view_constructionPlane_k,
        $.Getter.BindRaw(this, &FTDxNavContext::SetViewConstructionPlane);
    );
    REGISTER_PROP(box_t, view_extents_k,
        $.Setter.BindRaw(this, &FTDxNavContext::OnViewExtents);
        $.Getter.BindRaw(this, &FTDxNavContext::SetViewExtents);
    );
    REGISTER_PROP(float, view_fov_k,
        $.Setter.BindRaw(this, &FTDxNavContext::OnViewFov);
        $.Getter.BindRaw(this, &FTDxNavContext::SetViewFov);
    );
    REGISTER_PROP(frustum_t, view_constructionPlane_k,
        $.Getter.BindRaw(this, &FTDxNavContext::SetViewFrustum);
    );
    REGISTER_PROP(bool, view_perspective_k,
        $.Getter.BindRaw(this, &FTDxNavContext::SetViewPerspective);
    );
    REGISTER_PROP(bool, view_rotatable_k,
        $.Getter.BindRaw(this, &FTDxNavContext::SetViewRotatable);
    );
    REGISTER_PROP(point_t, view_target_k,
        $.Getter.BindRaw(this, &FTDxNavContext::SetViewTarget);
    );
    REGISTER_PROP(matrix_t, views_front_k,
        $.Getter.BindRaw(this, &FTDxNavContext::SetViewsFront);
    );
    REGISTER_PROP(point_t, pivot_position_k,
        $.Setter.BindRaw(this, &FTDxNavContext::OnPivotPosition);
        $.Getter.BindRaw(this, &FTDxNavContext::SetPivotPosition);
    );
    REGISTER_PROP(bool, pivot_visible_k,
        $.Setter.BindRaw(this, &FTDxNavContext::OnPivotVisible);
    );
    REGISTER_PROP(point_t, hit_lookfrom_k,
        $.Setter.BindRaw(this, &FTDxNavContext::OnHitLookfrom);
    );
    REGISTER_PROP(vector_t, hit_direction_k,
        $.Setter.BindRaw(this, &FTDxNavContext::OnHitDirection);
    );
    REGISTER_PROP(float, hit_aperture_k,
        $.Setter.BindRaw(this, &FTDxNavContext::OnHitAperture);
    );
    REGISTER_PROP(point_t, hit_lookat_k,
        $.Getter.BindRaw(this, &FTDxNavContext::SetHitLookat);
    );
    REGISTER_PROP(bool, hit_selectionOnly_k,
        $.Setter.BindRaw(this, &FTDxNavContext::OnHitSelectionOnly);
    );
    REGISTER_PROP(matrix_t, selection_affine_k,
        $.Setter.BindRaw(this, &FTDxNavContext::OnSelectionAffine);
        $.Getter.BindRaw(this, &FTDxNavContext::SetSelectionAffine);
    );
    REGISTER_PROP(bool, selection_empty_k,
        $.Getter.BindRaw(this, &FTDxNavContext::SetSelectionEmpty);
    );
    REGISTER_PROP(box_t, selection_extents_k,
        $.Getter.BindRaw(this, &FTDxNavContext::SetSelectionExtents);
    );
    REGISTER_PROP(box_t, model_extents_k,
        $.Getter.BindRaw(this, &FTDxNavContext::SetModelExtents);
    );
    REGISTER_PROP(point_t, pointer_position_k,
        $.Getter.BindRaw(this, &FTDxNavContext::SetPointerPosition);
    );
    REGISTER_PROP(long, settings_changed_k,
        $.Setter.BindRaw(this, &FTDxNavContext::OnSettingsChanged);
    );

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
