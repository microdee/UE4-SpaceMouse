// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

struct hid_device_;
typedef struct hid_device_ hid_device;
struct hid_device_info;

/**
 * 
 */
class SPACEMOUSEREADER_API FActiveHidSmDevice
{
public:
    FActiveHidSmDevice(hid_device_info* DeviceInfo);
    ~FActiveHidSmDevice();
    
    int Read(uint8* data, size_t length) const;
    
    hid_device* Device = nullptr;
    hid_device_info* DeviceInfo = nullptr;
    bool bDeviceOpened = false;
};
