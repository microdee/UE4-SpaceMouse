// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadingMethod/DataReadingMethod.h"
#include "ActiveHidSmDevice.h"
#include "DebugInfoPrinter.h"
#include "ProcessedDeviceOutput.h"
#include "Curves/RichCurve.h"


FDataReadingMethod::FDataReadingMethod()
{
}

FDataReadingMethod::~FDataReadingMethod()
{
}

// SpacePilot Pro had troubles with filtering only the most significant axis data for a frame
// So disabling first with a preprocessor in the hope that it won't cause trouble in other devices either.
#define USE_MOST_SIGNIFICANT_AXES_ONLY 0

namespace SmDataReadingDetails
{
    template<typename TResult>
    void ApplyMovement(float fx, float fy, float fz, float DeltaSecs, const FMovementSettings& Settings, TResult& Output)
    {
        FVector xmap = Settings.XAxisMap;
        FVector ymap = Settings.YAxisMap;
        FVector zmap = Settings.ZAxisMap;

        fx = FDataReadingMethod::GetCurvedFloat(Settings.Curve, fx);
        fy = FDataReadingMethod::GetCurvedFloat(Settings.Curve, fy);
        fz = FDataReadingMethod::GetCurvedFloat(Settings.Curve, fz);

        auto NewTrl = TResult(
            fx * xmap.X + fy * xmap.Y + fz * xmap.Z,
            fx * ymap.X + fy * ymap.Y + fz * ymap.Z,
            fx * zmap.X + fy * zmap.Y + fz * zmap.Z
        ) * Settings.UnitsPerSec * DeltaSecs;
        
        Output = NewTrl;
    }
}

union FReportButtons
{
    uint16 Data[4];
    TStaticBitArray<64> BitArray;
};

void FDataReadingMethod::Tick(FDataReadingOutput& Output, float DeltaSecs)
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

float FDataReadingMethod::GetCurvedFloat(const FRichCurve* curve, float ff)
{
    if(curve && FMath::Abs(ff) > SMALL_NUMBER)
        return curve->Eval(FMath::Abs(ff)) * FMath::Sign(ff);
    else return ff;
}

void FDataReadingMethod::TickMovementState(FDataReadingOutput& Output, float DeltaSecs)
{
    Output.MovementState->Tick(Output.Settings.MovementTimeTolerance, DeltaSecs);
}

void FDataReadingMethod::ApplyTranslation(FDataReadingOutput& Output, float fx, float fy, float fz, float DeltaSecs)
{
    SmDataReadingDetails::ApplyMovement(fx, fy, fz, DeltaSecs, Output.Settings.Translation, Output.Data->Translation);
}

void FDataReadingMethod::ApplyRotation(FDataReadingOutput& Output, float fp, float fy, float fr, float DeltaSecs)
{
    SmDataReadingDetails::ApplyMovement(fp, fy, fr, DeltaSecs, Output.Settings.Rotation, Output.Data->Rotation);
}

void FDataReadingMethod::ApplyButtons(FDataReadingOutput& Output, uint8* Report, int ReportID)
{
    auto& Buttons = Output.Data->Buttons;
    FReportButtons Input {0, 0, 0, 0};
    uint16* DataPtr = reinterpret_cast<uint16*>(Report + 1);
    Input.Data[0] = DataPtr[0];
    Input.Data[1] = DataPtr[1];
    Input.Data[2] = DataPtr[2];

    Output.Data->Buttons = Input.BitArray;
    Output.Debug->SetReport(ReportID, Report, GetReportSize());
}
