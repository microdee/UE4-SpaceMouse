// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadingMethod/DataReadingMethod.h"

#include "MovementState.h"
#include "ProcessedDeviceOutput.h"
#include "Curves/RichCurve.h"


FDataReadingMethod::FDataReadingMethod()
{
}

FDataReadingMethod::~FDataReadingMethod()
{
}

namespace SmDataReadingDetails
{
    template<typename TResult>
    void ApplyMovement(float fx, float fy, float fz, float DeltaSecs, const FMovementSettings& Settings, TResult& Output, TResult& NormOutput)
    {
        FVector xmap = Settings.XAxisMap;
        FVector ymap = Settings.YAxisMap;
        FVector zmap = Settings.ZAxisMap;

        fx = FDataReadingMethod::GetCurvedFloat(Settings.Curve, fx);
        fy = FDataReadingMethod::GetCurvedFloat(Settings.Curve, fy);
        fz = FDataReadingMethod::GetCurvedFloat(Settings.Curve, fz);

        NormOutput = TResult(
            fx * xmap.X + fy * xmap.Y + fz * xmap.Z,
            fx * ymap.X + fy * ymap.Y + fz * ymap.Z,
            fx * zmap.X + fy * zmap.Y + fz * zmap.Z
        );
        
        Output = NormOutput * Settings.UnitsPerSec * DeltaSecs;
    }
}

float FDataReadingMethod::GetCurvedFloat(const FRichCurve* curve, float ff)
{
    if(curve && FMath::Abs(ff) > SMALL_NUMBER)
        return curve->Eval(FMath::Abs(ff)) * FMath::Sign(ff);
    else return ff;
}

void FDataReadingMethod::Tick(FDataReadingOutput& Output, float DeltaSecs)
{
    Output.MovementState->PreTick();
}

void FDataReadingMethod::TickMovementState(FDataReadingOutput& Output, float DeltaSecs)
{
    Output.MovementState->Tick(Output.Settings.MovementTimeTolerance, DeltaSecs);
}

void FDataReadingMethod::ApplyTranslation(FDataReadingOutput& Output, float fx, float fy, float fz, float DeltaSecs)
{
    SmDataReadingDetails::ApplyMovement(
        fx, fy, fz,
        DeltaSecs,
        Output.Settings.Translation,
        Output.ProcessedData->Translation,
        Output.NormData->Translation
    );
}

void FDataReadingMethod::ApplyRotation(FDataReadingOutput& Output, float fp, float fy, float fr, float DeltaSecs)
{
    SmDataReadingDetails::ApplyMovement(
        fp, fy, fr,
        DeltaSecs,
        Output.Settings.Rotation,
        Output.ProcessedData->Rotation,
        Output.NormData->Rotation
    );
}