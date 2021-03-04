// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataReadingMethod.h"

/**
 * This HID data format has the translation and rotation in a single report
 */
class SPACEMOUSEREADER_API FSingleReportTransRotMethod : FDataReadingMethod
{
public:
    FSingleReportTransRotMethod();
    ~FSingleReportTransRotMethod();
    
    virtual void ReadData(FDataReadingOutput& Output, float DeltaSecs, uint8* Report) override;
    virtual int GetReportSize() override { return 13; }
};
