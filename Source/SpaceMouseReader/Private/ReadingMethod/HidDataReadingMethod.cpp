// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE


#include "ReadingMethod/HidDataReadingMethod.h"
#include "ReadingMethod/ActiveHidSmDevice.h"
#include "SmButtons.h"
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

void FHidDataReadingMethod::Tick(FSmDataReadingOutput& Output, float DeltaSecs)
{
    FSmDataReadingMethod::Tick(Output, DeltaSecs);
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

void FHidDataReadingMethod::ApplyButtons(FSmDataReadingOutput& Output, uint8* Report, int ReportID)
{
    FMemory::Memcpy(&Output.ProcessedData->Buttons, Report + 1, GetReportSize() - 1);
    FMemory::Memcpy(&Output.NormData->Buttons, Report + 1, GetReportSize() - 1);
    
    Output.Debug->SetReport(ReportID, Report, GetReportSize());
}
