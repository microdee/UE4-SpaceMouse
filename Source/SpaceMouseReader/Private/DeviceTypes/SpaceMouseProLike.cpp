// Fill out your copyright notice in the Description page of Project Settings.


#include "DeviceTypes/SpaceMouseProLike.h"

void FSpaceMouseProLike::TransformRawData(TSharedPtr<FProcessedDeviceOutput> Data)
{
    Data->Buttons = MapModernButtons(Data->Buttons);
}
