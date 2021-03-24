// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DataReadingMethod.h"
#include "UserSettings.h"

/**
 * Class encapsulating a method to convert raw HID input into usable data
 */
class SPACEMOUSEREADER_API FHidDataReadingMethod : public FDataReadingMethod
{
public:
    FHidDataReadingMethod();
    virtual ~FHidDataReadingMethod();
    
    FDataReadEvent OnDataReceived;
    
    virtual int GetReportSize() { return 7; }
    virtual int GetReportCount() { return 4; }

    virtual void Tick(FDataReadingOutput& Output, float DeltaSecs) override;
    virtual void ReadData(FDataReadingOutput& Output, float DeltaSecs, uint8* Report) = 0;

protected:
    
    uint8 OutputBuffer[80];
    
    void ApplyButtons(FDataReadingOutput& Output, uint8* Report, int ReportID = 3);
};
