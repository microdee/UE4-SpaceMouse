// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE


#include "SpaceMouseReader/Public/CommonBehaviors.h"

FVector USmCommonBehaviors::GetOrbitingTranslationDelta(
    FVector Pivot,
    FRotator CurrentRotation,
    FRotator RotationDelta,
    float Distance,
    bool bWithRoll
) {
    if (!bWithRoll)
    {
        const float YawCorr = FMath::Abs(FMath::Cos(FMath::DegreesToRadians(CurrentRotation.Pitch)));
        RotationDelta.Yaw *= YawCorr;
    }

    const FMatrix OrbitTr = FTransform(Pivot).ToMatrixWithScale()
        * FTransform(RotationDelta).ToMatrixWithScale()
        * FTransform(FVector(-Distance, 0, 0)).ToMatrixWithScale();

    FVector Ret = OrbitTr.TransformPosition(FVector::ZeroVector);
    Ret.X = 0;
    return Ret;
}
