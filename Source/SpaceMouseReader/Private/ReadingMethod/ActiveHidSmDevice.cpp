// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE


#include "ReadingMethod/ActiveHidSmDevice.h"

#include "hidapi.h"


FActiveHidSmDevice::FActiveHidSmDevice(hid_device_info* DeviceInfo)
    : DeviceInfo(DeviceInfo)
{
    Device = hid_open_path(DeviceInfo->path);
    bDeviceOpened = Device != nullptr;
    if (bDeviceOpened) hid_set_nonblocking(Device, 1);
}

FActiveHidSmDevice::~FActiveHidSmDevice()
{
    if(Device) hid_close(Device);
}

int FActiveHidSmDevice::Read(uint8* data, size_t length) const
{
    return hid_read(Device, data, length);
}
