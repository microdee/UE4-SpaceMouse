// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE


#include "DeviceTypes/SpaceMouseEnterpriseLike.h"

void FSpaceMouseEnterpriseLike::TransformRawData(TSharedPtr<FSmProcessedDeviceOutput> Data)
{
    // Assumption, I'd need more proof
    Data->Buttons = MapModernButtons(Data->Buttons);
}
