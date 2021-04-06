// Fill out your copyright notice in the Description page of Project Settings.


#include "DeviceTypes/SpaceMouseEnterpriseLike.h"

void FSpaceMouseEnterpriseLike::TransformRawData(TSharedPtr<FProcessedDeviceOutput> Data)
{
    // Assumption, I'd need more proof
    Data->Buttons = MapModernButtons(Data->Buttons);
}
