// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadingMethod/SeparateReportTransRotMethod.h"

#include "DebugInfoPrinter.h"


FSeparateReportTransRotMethod::FSeparateReportTransRotMethod()
{
}

FSeparateReportTransRotMethod::~FSeparateReportTransRotMethod()
{
}

#define CHECK_AXES() \
    (  xx <= GetAxisResolution() \
    && yy <= GetAxisResolution() \
    && zz <= GetAxisResolution() \
    && -xx >= -GetAxisResolution() \
    && -yy >= -GetAxisResolution() \
    && -zz >= -GetAxisResolution() \
    )

void FSeparateReportTransRotMethod::ReadData(FDataReadingOutput& Output, float DeltaSecs, uint8* Report)
{
    Output.Debug->AppendReport(Report, GetReportSize());
    
    for (int i = 0; i < GetReportCount(); i++)
    {
        const uint8 ReportID = *Report;

        int16 xx = *reinterpret_cast<int16*>(Report + 1);
        int16 yy = *reinterpret_cast<int16*>(Report + 3);
        int16 zz = *reinterpret_cast<int16*>(Report + 5);

        float fx = static_cast<float>(xx) / GetAxisResolution();
        float fy = static_cast<float>(yy) / GetAxisResolution();
        float fz = static_cast<float>(zz) / GetAxisResolution();

        if (ReportID == 0 && UserSettings.bPrintDebug)
        {
            Output.Debug->SetReport(ReportID, Report, GetReportSize());
        }

        if (ReportID == 1 && CHECK_AXES())
        {
            ApplyTranslation(Output, fx, fy, fz, DeltaSecs);
            Output.Debug->SetReport(ReportID, Report, GetReportSize());
            Output.MovementState->Move();
        }
        if (ReportID == 2 && CHECK_AXES())
        {
            ApplyRotation(Output, fx, fy, fz, DeltaSecs);
            Output.Debug->SetReport(ReportID, Report, GetReportSize());
            Output.MovementState->Move();
        }
        if (ReportID == 3)
        {
            ApplyButtons(Output, Report);
        }
        Report += GetReportSize();
    }
}

#undef CHECK_AXES
