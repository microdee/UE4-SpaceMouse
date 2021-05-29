// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <navlib/navlib_types.h>


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
    template<typename TNavlibType>
    struct TUnreal
    {
    };

    DECLARE_TO_UNREAL(
        point_t, FVector,
        ({$.x, $.y, $.z}),
        ({$.X, $.Y, $.Z})
    );

    DECLARE_TO_UNREAL(
        vector_t, FVector,
        ({$.x, $.y, $.z}),
        ({$.X, $.Y, $.Z})
    );

    DECLARE_TO_UNREAL(
        plane_t, FPlane,
        ({$.x, $.y, $.z, $.d}),
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
                -($.farVal + $.nearVal) / ($.farVal-$.nearVal),
                0.0f,
                0.0f,
                -2.0f * $.nearVal * $.farVal / ($.farVal-$.nearVal)
            },
            {
                ($.right+$.left) / ($.right - $.left),
                2.0f * $.nearVal / ($.right - $.left),
                0.0f,
                0.0f
            },
            {
                ($.top + $.bottom) / ($.top - $.bottom),
                0.0f,
                2.0f * $.nearVal / ($.top - $.bottom),
                0.0f
            },
            {1.0f, 0.0f, 0.0f, 0.0f}
        }),
        ([&](){
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
            {$.m00, $.m01, $.m02, $.m03},
            {$.m10, $.m11, $.m12, $.m13},
            {$.m20, $.m21, $.m22, $.m23},
            {$.m30, $.m31, $.m32, $.m33}
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
        ({TCHAR_TO_ANSI(*$), $.Len()})
    );

    DECLARE_TO_UNREAL(
        cstr_t, FString,
        (FString($.length, ANSI_TO_TCHAR($.p))),
        ({TCHAR_TO_ANSI(*$), $.Len()})
    );
}