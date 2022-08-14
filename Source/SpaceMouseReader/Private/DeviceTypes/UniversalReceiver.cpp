// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE


#include "DeviceTypes/UniversalReceiver.h"

void FUniversalReceiver::TransformRawData(TSharedPtr<FSmProcessedDeviceOutput> Data)
{
    // TODO: assumption, so far all universal receiver compatible device have the same HID protocol
    // TODO: detect device types through the universal receiver
    Data->Buttons = MapModernButtons(Data->Buttons);
}
