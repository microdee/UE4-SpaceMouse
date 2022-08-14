// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

#include "Containers/StaticArray.h"

struct hid_device_info;

/**
 * 
 */
class SPACEMOUSEREADER_API FSmDebugInfoPrinter
{
public:

    static inline const int ReportCount = 4;
    
    FSmDebugInfoPrinter();
    ~FSmDebugInfoPrinter();

    TStaticArray<FString, ReportCount> Reports;
    FString ReportAll {};
    
    void Print(FString FriendlyDeviceName, const hid_device_info* DeviceInfo, int InternalID, bool bEnabled);
    void AppendReport(const uint8* Report, uint32 Size);
    void SetReport(int Index, const uint8* Report, uint32 Size);
};
