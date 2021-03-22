// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadingMethod/HidDataReadingMethod.h"
#include "ReadingMethod/ActiveHidSmDevice.h"
#include "Buttons.h"
#include "DebugInfoPrinter.h"
#include "MovementState.h"
#include "ProcessedDeviceOutput.h"
#include "Curves/RichCurve.h"


FHidDataReadingMethod::FHidDataReadingMethod()
{
}

FHidDataReadingMethod::~FHidDataReadingMethod()
{
}

// SpacePilot Pro had troubles with filtering only the most significant axis data for a frame

namespace SmDataReadingDetails
{
    template<typename TResult>
    void ApplyMovement(float fx, float fy, float fz, float DeltaSecs, const FMovementSettings& Settings, TResult& Output, TResult& NormOutput)
    {
        FVector xmap = Settings.XAxisMap;
        FVector ymap = Settings.YAxisMap;
        FVector zmap = Settings.ZAxisMap;

        fx = FHidDataReadingMethod::GetCurvedFloat(Settings.Curve, fx);
        fy = FHidDataReadingMethod::GetCurvedFloat(Settings.Curve, fy);
        fz = FHidDataReadingMethod::GetCurvedFloat(Settings.Curve, fz);

        NormOutput = TResult(
            fx * xmap.X + fy * xmap.Y + fz * xmap.Z,
            fx * ymap.X + fy * ymap.Y + fz * ymap.Z,
            fx * zmap.X + fy * zmap.Y + fz * zmap.Z
        );
        
        Output = NormOutput * Settings.UnitsPerSec * DeltaSecs;
    }
}

void FHidDataReadingMethod::Tick(FDataReadingOutput& Output, float DeltaSecs)
{
    uint8* Report = &OutputBuffer[0];
    int Ctr = 0;

    Output.MovementState->PreTick();

    bool Received = false;
    
    while (Output.HidDevice->Read(Report, GetReportSize() * GetReportCount()) > 0 && Ctr < Output.Settings.MaxReads)
    {
        Received = true;
        ReadData(Output, DeltaSecs, Report);
        Ctr++;
    }
    if(Received) OnDataReceived.Broadcast();

    TickMovementState(Output, DeltaSecs);
}

float FHidDataReadingMethod::GetCurvedFloat(const FRichCurve* curve, float ff)
{
    if(curve && FMath::Abs(ff) > SMALL_NUMBER)
        return curve->Eval(FMath::Abs(ff)) * FMath::Sign(ff);
    else return ff;
}

void FHidDataReadingMethod::TickMovementState(FDataReadingOutput& Output, float DeltaSecs)
{
    Output.MovementState->Tick(Output.Settings.MovementTimeTolerance, DeltaSecs);
}

void FHidDataReadingMethod::ApplyTranslation(FDataReadingOutput& Output, float fx, float fy, float fz, float DeltaSecs)
{
    SmDataReadingDetails::ApplyMovement(
        fx, fy, fz,
        DeltaSecs,
        Output.Settings.Translation,
        Output.ProcessedData->Translation,
        Output.NormData->Translation
    );
}

void FHidDataReadingMethod::ApplyRotation(FDataReadingOutput& Output, float fp, float fy, float fr, float DeltaSecs)
{
    SmDataReadingDetails::ApplyMovement(
        fp, fy, fr,
        DeltaSecs,
        Output.Settings.Rotation,
        Output.ProcessedData->Rotation,
        Output.NormData->Rotation
    );
}

void FHidDataReadingMethod::ApplyButtons(FDataReadingOutput& Output, uint8* Report, int ReportID)
{
    FMemory::Memcpy(&Output.ProcessedData->Buttons, Report + 1, GetReportSize() - 1);
    FMemory::Memcpy(&Output.NormData->Buttons, Report + 1, GetReportSize() - 1);
    
    Output.Debug->SetReport(ReportID, Report, GetReportSize());
}
