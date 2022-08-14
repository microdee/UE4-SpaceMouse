// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE


#include "DeviceTypes/SpacePilotProLike.h"

void FSpacePilotProLike::TransformRawData(TSharedPtr<FSmProcessedDeviceOutput> Data)
{
    Data->Buttons = MapModernButtons(Data->Buttons);
}
