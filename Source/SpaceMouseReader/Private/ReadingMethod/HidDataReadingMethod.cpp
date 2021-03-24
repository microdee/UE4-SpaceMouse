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

void FHidDataReadingMethod::Tick(FDataReadingOutput& Output, float DeltaSecs)
{
    FDataReadingMethod::Tick(Output, DeltaSecs);
    uint8* Report = &OutputBuffer[0];
    int Ctr = 0;

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

void FHidDataReadingMethod::ApplyButtons(FDataReadingOutput& Output, uint8* Report, int ReportID)
{
    FMemory::Memcpy(&Output.ProcessedData->Buttons, Report + 1, GetReportSize() - 1);
    FMemory::Memcpy(&Output.NormData->Buttons, Report + 1, GetReportSize() - 1);
    
    Output.Debug->SetReport(ReportID, Report, GetReportSize());
}
