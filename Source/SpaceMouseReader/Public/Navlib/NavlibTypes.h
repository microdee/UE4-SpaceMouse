// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Containers/StaticArray.h"

#if WITH_3DX_NAVLIB

#include "CoreMinimal.h"

#include <navlib/navlib_types.h>
#include <navlib/navlib.h>


#define DECLARE_TO_UNREAL_BODY(...) __VA_ARGS__
#define DECLARE_TO_UNREAL(MNavlib, MUnreal, FromBody, ToBody) \
    template<> \
    struct TUnreal<MNavlib> \
    { \
        typedef MUnreal FUnreal; \
        typedef MNavlib FNavlib; \
        static FUnreal From(const FNavlib& $) { return DECLARE_TO_UNREAL_BODY##FromBody; } \
        static FNavlib To(const FUnreal& $) { return DECLARE_TO_UNREAL_BODY##ToBody; } \
    }

namespace navlib
{
    template<typename T>
    FORCEINLINE float FCast(const T& $) { return static_cast<float>($); }
    
    template<typename TNavlibType>
    struct TUnreal
    {
        typedef TNavlibType FUnreal; \
        typedef TNavlibType FNavlib; \
    };

    DECLARE_TO_UNREAL(
        point_t, FVector,
        ({FCast($.x), FCast($.y), FCast($.z)}),
        ({$.X, $.Y, $.Z})
    );

    DECLARE_TO_UNREAL(
        vector_t, FVector,
        ({FCast($.x), FCast($.y), FCast($.z)}),
        ({$.X, $.Y, $.Z})
    );

    DECLARE_TO_UNREAL(
        plane_t, FPlane,
        ({FCast($.x), FCast($.y), FCast($.z), FCast($.d)}),
        ({$.X, $.Y, $.Z, $.W})
    );

    DECLARE_TO_UNREAL(
        box_t, FBox,
        ({TUnreal<point_t>::From($.min), TUnreal<point_t>::From($.max)}),
        ({$.Min.X, $.Min.Y, $.Min.Z, $.Max.X, $.Max.Y, $.Max.Z})
    );

    DECLARE_TO_UNREAL(
        frustum_t, FMatrix,
        ({
            {
                FCast(-($.farVal + $.nearVal) / ($.farVal-$.nearVal)),
                0.0f,
                0.0f,
                FCast(-2.0 * $.nearVal * $.farVal / ($.farVal-$.nearVal))
            },
            {
                FCast(($.right+$.left) / ($.right - $.left)),
                FCast(2.0 * $.nearVal / ($.right - $.left)),
                0.0f,
                0.0f
            },
            {
                FCast(($.top + $.bottom) / ($.top - $.bottom)),
                0.0f,
                FCast(2.0 * $.nearVal / ($.top - $.bottom)),
                0.0f
            },
            {1.0f, 0.0f, 0.0f, 0.0f}
        }),
        ([&]() -> frustum_t {
            FPlane L, R, T, B, N, F;
            if(!$.GetFrustumLeftPlane(L)) return {};
            if(!$.GetFrustumRightPlane(R)) return {};
            if(!$.GetFrustumTopPlane(T)) return {};
            if(!$.GetFrustumBottomPlane(B)) return {};
            if(!$.GetFrustumNearPlane(N)) return {};
            if(!$.GetFrustumFarPlane(F)) return {};

            // TODO: I'm 85% sure this is not correct here:
            return { L.W, R.W, B.W, T.W, N.W, F.W };
        }())
    );

    DECLARE_TO_UNREAL(
        matrix_t, FMatrix,
        ({
            {FCast($.m00), FCast($.m01), FCast($.m02), FCast($.m03)},
            {FCast($.m10), FCast($.m11), FCast($.m12), FCast($.m13)},
            {FCast($.m20), FCast($.m21), FCast($.m22), FCast($.m23)},
            {FCast($.m30), FCast($.m31), FCast($.m32), FCast($.m33)}
        }),
        ({
            $.M[0][0], $.M[0][1], $.M[0][2], $.M[0][3],
            $.M[1][0], $.M[1][1], $.M[1][2], $.M[1][3],
            $.M[2][0], $.M[2][1], $.M[2][2], $.M[2][3],
            $.M[3][0], $.M[3][1], $.M[3][2], $.M[3][3]
        })
    );

    DECLARE_TO_UNREAL(
        string_t, FString,
        (FString($.length, ANSI_TO_TCHAR($.p))),
        ({TCHAR_TO_ANSI(*$), static_cast<size_t>($.Len())})
    );

    DECLARE_TO_UNREAL(
        cstr_t, FString,
        (FString($.length, ANSI_TO_TCHAR($.p))),
        ({TCHAR_TO_ANSI(*$), static_cast<size_t>($.Len())})
    );
    
    enum class EProperty : uint8
    {
        Active,
        Focus,
        Motion,
        CoordinateSystem,
        DevicePresent,
        EventsKeyPress,
        EventsKeyRelease,
        Transaction,
        FrameTime,
        FrameTimingSource,
        ViewAffine,
        ViewConstructionPlane,
        ViewExtents,
        ViewFov,
        ViewFrustum,
        ViewPerspective,
        ViewRotatable,
        ViewTarget,
        ViewsFront,
        PivotPosition,
        PivotUser,
        PivotVisible,
        HitLookfrom,
        HitDirection,
        HitAperture,
        HitLookat,
        HitSelectionOnly,
        SelectionAffine,
        SelectionEmpty,
        SelectionExtents,
        ModelExtents,
        PointerPosition,
        CommandsTree,
        CommandsActiveSet,
        CommandsActiveCommand,
        Images,
        Settings,
        SettingsChanged
    };

    inline TArray GPropertyMap {
        active_k,
        focus_k,
        motion_k,
        coordinate_system_k,
        device_present_k,
        events_keyPress_k,
        events_keyRelease_k,
        transaction_k,
        frame_time_k,
        frame_timing_source_k,
        view_affine_k,
        view_constructionPlane_k,
        view_extents_k,
        view_fov_k,
        view_frustum_k,
        view_perspective_k,
        view_rotatable_k,
        view_target_k,
        views_front_k,
        pivot_position_k,
        pivot_user_k,
        pivot_visible_k,
        hit_lookfrom_k,
        hit_direction_k,
        hit_aperture_k,
        hit_lookat_k,
        hit_selectionOnly_k,
        selection_affine_k,
        selection_empty_k,
        selection_extents_k,
        model_extents_k,
        pointer_position_k,
        commands_tree_k,
        commands_activeSet_k,
        commands_activeCommand_k,
        images_k,
        settings_k,
        settings_changed_k
    };

    template<EProperty TProp>
    struct TPropType {};
    
#define NL_PROPERTY_TYPE(Type, Name) template<> struct TPropType<EProperty::Name> { typedef Type FType; }
    
    NL_PROPERTY_TYPE( bool              , Active );
    NL_PROPERTY_TYPE( bool              , Focus );
    NL_PROPERTY_TYPE( bool              , Motion );
    NL_PROPERTY_TYPE( matrix            , CoordinateSystem );
    NL_PROPERTY_TYPE( bool              , DevicePresent );
    NL_PROPERTY_TYPE( long              , EventsKeyPress );
    NL_PROPERTY_TYPE( long              , EventsKeyRelease );
    NL_PROPERTY_TYPE( long              , Transaction );
    NL_PROPERTY_TYPE( double            , FrameTime );
    NL_PROPERTY_TYPE( long              , FrameTimingSource );
    NL_PROPERTY_TYPE( matrix            , ViewAffine );
    NL_PROPERTY_TYPE( plane             , ViewConstructionPlane );
    NL_PROPERTY_TYPE( box               , ViewExtents );
    NL_PROPERTY_TYPE( float             , ViewFov );
    NL_PROPERTY_TYPE( frustum           , ViewFrustum );
    NL_PROPERTY_TYPE( bool              , ViewPerspective );
    NL_PROPERTY_TYPE( bool              , ViewRotatable );
    NL_PROPERTY_TYPE( point             , ViewTarget );
    NL_PROPERTY_TYPE( matrix            , ViewsFront );
    NL_PROPERTY_TYPE( point             , PivotPosition );
    NL_PROPERTY_TYPE( bool              , PivotUser );
    NL_PROPERTY_TYPE( bool              , PivotVisible );
    NL_PROPERTY_TYPE( point             , HitLookfrom );
    NL_PROPERTY_TYPE( vector            , HitDirection );
    NL_PROPERTY_TYPE( float             , HitAperture );
    NL_PROPERTY_TYPE( point             , HitLookat );
    NL_PROPERTY_TYPE( bool              , HitSelectionOnly );
    NL_PROPERTY_TYPE( matrix            , SelectionAffine );
    NL_PROPERTY_TYPE( bool              , SelectionEmpty );
    NL_PROPERTY_TYPE( box               , SelectionExtents );
    NL_PROPERTY_TYPE( box               , ModelExtents );
    NL_PROPERTY_TYPE( point             , PointerPosition );
    NL_PROPERTY_TYPE( SiActionNodeEx_t* , CommandsTree );
    NL_PROPERTY_TYPE( string_t          , CommandsActiveSet );
    NL_PROPERTY_TYPE( string_t          , CommandsActiveCommand );
    NL_PROPERTY_TYPE( imagearray_t      , Images );
    NL_PROPERTY_TYPE( string_t          , Settings );
    NL_PROPERTY_TYPE( long              , SettingsChanged );

    template<EProperty TProp>
    class TProperty
    {
    public:
        using FSelf = TProperty<TProp>;
        using FTypeNL = typename TPropType<TProp>::FType;
        using FConversion = TUnreal<FTypeNL>;
        using FTypeUE = typename FConversion::FUnreal;

        static FTypeNL FromUE(const FTypeUE& $) { return MoveTemp(FConversion::To($)); }
        static FTypeUE FromNL(const FTypeNL& $) { return MoveTemp(FConversion::From($)); }
        
        static property_t GetProperty()
        {
            return GPropertyMap[static_cast<uint8>(TProp)];
        }

        explicit TProperty(const nlHandle_t& InCtx) : Ctx(InCtx) {}
        
        FTypeNL GetCached() { return Cache; }
        FTypeUE GetCachedUE() { return FromNL(Cache); }
        void SetCached(const FTypeNL& InVal) { Cache = InVal; }
        void SetCachedUE(const FTypeUE& InVal) { Cache = FromUE(InVal); }

        FTypeNL Get()
        {
            value_t Val;
            if(NlReadValue(Ctx, GetProperty(), &Val))
            {
                return Cache;
            }

            FTypeNL TypedVal = Val;
            return Val;
        }

        FTypeUE GetUE() { return FromNL(Get()); }

        void Set(const FTypeNL& InVal)
        {
            SetCached(InVal);
            
            value_t Val(InVal);
            auto Result = NlWriteValue(Ctx, GetProperty(), &Val);

            check(!Result);
        }

        void SetUE(const FTypeUE& InVal) { Set(FromUE(InVal)); }
    
    private:
        nlHandle_t Ctx;
        FTypeNL Cache {};
    };
}

#endif