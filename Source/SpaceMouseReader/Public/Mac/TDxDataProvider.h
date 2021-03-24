// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#if PLATFORM_MAC

#include "CoreMinimal.h"

struct FTDxDeviceModel
{
    uint16 VID;
    uint16 PID;
}

#pragma pack(push, 2)  // just this struct
struct ConnexionDeviceState {
    uint16_t version;
    uint16_t client;
    uint16_t command;
    int16_t param;
    int32_t value;
    uint64_t time;
    uint8_t report[8];
    uint16_t buttons8;  // obsolete! (pre-10.x drivers)
    int16_t axis[6];    // tx, ty, tz, rx, ry, rz
    uint16_t address;
    uint32_t buttons;
};
#pragma pack(pop)

class SPACEMOUSEREADER_API FTDxDataProvider
{
	    TFunction<
    TArray<FTDxDeviceModel> SeenDevices;
    
    FTDxDataProvider();
}

#endif
