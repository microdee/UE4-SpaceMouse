// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ConvexVolume.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SPACEMOUSE_API SDebugVpNavlib : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SDebugVpNavlib)
    {
    }

    SLATE_ATTRIBUTE(FMatrix, SceneViewTr)
    SLATE_ATTRIBUTE(FMatrix, LocRotTr)
    SLATE_ATTRIBUTE(FMatrix, ProjTr)
	SLATE_ATTRIBUTE(FVector, PivotPos)
	SLATE_ATTRIBUTE(FVector, HitPos)
	SLATE_ATTRIBUTE(FVector, PointerPos)
	SLATE_ATTRIBUTE(FVector, HitLookfrom)
	SLATE_ATTRIBUTE(FVector, HitDirection)
	SLATE_ATTRIBUTE(FConvexVolume, Frustum)

    SLATE_END_ARGS()

    /** Constructs this widget with InArgs */
    void Construct(const FArguments& InArgs);
};
