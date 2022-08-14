// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

#include "DataReadingMethod.h"
#include "SmUserSettings.h"

/**
 * Class encapsulating a method to convert raw HID input into usable data
 */
class SPACEMOUSEREADER_API FHidDataReadingMethod : public FSmDataReadingMethod
{
public:
    FHidDataReadingMethod();
    virtual ~FHidDataReadingMethod();
    
    virtual int GetReportSize() { return 7; }
    virtual int GetReportCount() { return 4; }

    virtual void Tick(FSmDataReadingOutput& Output, float DeltaSecs) override;
    virtual void ReadData(FSmDataReadingOutput& Output, float DeltaSecs, uint8* Report) = 0;

protected:
    
    uint8 OutputBuffer[80];
    
    void ApplyButtons(FSmDataReadingOutput& Output, uint8* Report, int ReportID = 3);
};
