// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugInfoPrinter.h"

#include "hidapi.h"
#include "Engine/Engine.h"


FDebugInfoPrinter::FDebugInfoPrinter()
{
}

FDebugInfoPrinter::~FDebugInfoPrinter()
{
}

void FDebugInfoPrinter::Print(FString FriendlyDeviceName, const hid_device_info* DeviceInfo, int InternalID)
{
    auto message = FString::Printf(
        TEXT("Device: %s\n")
        TEXT("  Serial: %s\n")
        TEXT("  VID: 0x%04x\n")
        TEXT("  PID: 0x%04x\n")
        TEXT("  Report:\n")
        TEXT("    %s\n")
        TEXT("  Sorted:\n"),
        *FriendlyDeviceName,
        DeviceInfo->serial_number,
        DeviceInfo->vendor_id,
        DeviceInfo->product_id,
        *ReportAll
    );

    for(auto ReportLine : Reports)
    {
        message += TEXT("    ") + ReportLine + TEXT("\n");
    }
    GEngine->AddOnScreenDebugMessage(2010 + InternalID, 10.0, FColor::Orange, message);
    ReportAll.Empty();
}

void FDebugInfoPrinter::AppendReport(const uint8* Report, uint32 Size)
{
    ReportAll += FString::FromHexBlob(Report, Size);
}

void FDebugInfoPrinter::SetReport(int Index, const uint8* Report, uint32 Size)
{
    Reports[Index] = FString::FromHexBlob(Report, Size);
}
