// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataReadingMethod.h"

/**
 * This HID data format separates translation and rotation into separate reports
 */
class SPACEMOUSEREADER_API FSeparateReportTransRotMethod : public FDataReadingMethod
{
public:
    FSeparateReportTransRotMethod();
    ~FSeparateReportTransRotMethod();

    virtual void ReadData(FDataReadingOutput& Output, float DeltaSecs, uint8* Report) override;
};
