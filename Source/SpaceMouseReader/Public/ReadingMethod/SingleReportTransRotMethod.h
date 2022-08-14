// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "HidDataReadingMethod.h"

/**
 * This HID data format has the translation and rotation in a single report
 */
class SPACEMOUSEREADER_API FSingleReportTransRotMethod : public FHidDataReadingMethod
{
public:
    FSingleReportTransRotMethod();
    ~FSingleReportTransRotMethod();
    
    virtual void ReadData(FSmDataReadingOutput& Output, float DeltaSecs, uint8* Report) override;
    virtual int GetReportSize() override { return 13; }
};
