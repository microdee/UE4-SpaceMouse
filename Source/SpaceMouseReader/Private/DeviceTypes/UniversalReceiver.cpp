// Fill out your copyright notice in the Description page of Project Settings.


#include "DeviceTypes/UniversalReceiver.h"

void FUniversalReceiver::TransformRawData(TSharedPtr<FProcessedDeviceOutput> Data)
{
    // TODO: assumption, so far all universal receiver compatible device have the same HID protocol
    // TODO: detect device types through the universal receiver
    Data->Buttons = MapModernButtons(Data->Buttons);
}
