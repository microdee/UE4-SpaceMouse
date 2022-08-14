// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE


#include "ReadingMethod/DataReadingMethod.h"

#include "MovementState.h"
#include "ProcessedDeviceOutput.h"
#include "Curves/RichCurve.h"


FSmDataReadingMethod::FSmDataReadingMethod()
{
}

FSmDataReadingMethod::~FSmDataReadingMethod()
{
}

namespace SmDataReadingDetails
{
    template<typename TResult>
    void ApplyMovement(float fx, float fy, float fz, float DeltaSecs, const FSmMovementSettings& Settings, TResult& Output, TResult& NormOutput)
    {
        FVector xmap = Settings.XAxisMap;
        FVector ymap = Settings.YAxisMap;
        FVector zmap = Settings.ZAxisMap;

        fx = FSmDataReadingMethod::GetCurvedFloat(Settings.Curve, fx);
        fy = FSmDataReadingMethod::GetCurvedFloat(Settings.Curve, fy);
        fz = FSmDataReadingMethod::GetCurvedFloat(Settings.Curve, fz);

        NormOutput = TResult(
            fx * xmap.X + fy * xmap.Y + fz * xmap.Z,
            fx * ymap.X + fy * ymap.Y + fz * ymap.Z,
            fx * zmap.X + fy * zmap.Y + fz * zmap.Z
        );
        
        Output = NormOutput * Settings.UnitsPerSec * DeltaSecs;
    }
}

float FSmDataReadingMethod::GetCurvedFloat(const FRichCurve* curve, float ff)
{
    if(curve && FMath::Abs(ff) > SMALL_NUMBER)
        return curve->Eval(FMath::Abs(ff)) * FMath::Sign(ff);
    else return ff;
}

void FSmDataReadingMethod::Tick(FSmDataReadingOutput& Output, float DeltaSecs)
{
    Output.MovementState->PreTick();
}

void FSmDataReadingMethod::TickMovementState(FSmDataReadingOutput& Output, float DeltaSecs)
{
    Output.MovementState->Tick(Output.Settings.MovementTimeTolerance, DeltaSecs);
}

void FSmDataReadingMethod::ApplyTranslation(FSmDataReadingOutput& Output, float fx, float fy, float fz, float DeltaSecs)
{
    SmDataReadingDetails::ApplyMovement(
        fx, fy, fz,
        DeltaSecs,
        Output.Settings.Translation,
        Output.ProcessedData->Translation,
        Output.NormData->Translation
    );
}

void FSmDataReadingMethod::ApplyRotation(FSmDataReadingOutput& Output, float fp, float fy, float fr, float DeltaSecs)
{
    SmDataReadingDetails::ApplyMovement(
        fp, fy, fr,
        DeltaSecs,
        Output.Settings.Rotation,
        Output.ProcessedData->Rotation,
        Output.NormData->Rotation
    );
}