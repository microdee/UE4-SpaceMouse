// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Containers/StaticArray.h"

struct hid_device_info;

/**
 * 
 */
class SPACEMOUSEREADER_API FDebugInfoPrinter
{
public:

    static inline const int ReportCount = 4;
    
    FDebugInfoPrinter();
    ~FDebugInfoPrinter();

    TStaticArray<FString, ReportCount> Reports;
    FString ReportAll {};
    
    void Print(FString FriendlyDeviceName, const hid_device_info* DeviceInfo, int InternalID, bool bEnabled);
    void AppendReport(const uint8* Report, uint32 Size);
    void SetReport(int Index, const uint8* Report, uint32 Size);
};
