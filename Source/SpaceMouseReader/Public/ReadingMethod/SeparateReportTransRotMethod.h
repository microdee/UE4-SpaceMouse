// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "HidDataReadingMethod.h"

/**
 * This HID data format separates translation and rotation into separate reports
 */
class SPACEMOUSEREADER_API FSeparateReportTransRotMethod : public FHidDataReadingMethod
{
public:
    FSeparateReportTransRotMethod();
    ~FSeparateReportTransRotMethod();

    virtual void ReadData(FSmDataReadingOutput& Output, float DeltaSecs, uint8* Report) override;
};
