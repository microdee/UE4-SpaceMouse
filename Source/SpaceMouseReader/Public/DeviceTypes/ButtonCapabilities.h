// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

#include "SmButtons.h"
#include "ProcessedDeviceOutput.h"

/**
 * 
 */
class SPACEMOUSEREADER_API FSmButtonCapabilities
{
public:
    virtual ~FSmButtonCapabilities() = default;

    TSet<EV3DCmd> SupportedButtons;

    // Source of info: https://github.com/blender/blender/blob/594f47ecd2d5367ca936cf6fc6ec8168c2b360d0/intern/ghost/intern/GHOST_NDOFManager.cpp#L91
    static FButtonBits MapModernButtons(FButtonBits HIDButtons);

    static FButtonBits MapButtons(FButtonBits HIDButtons, const TArray<EV3DCmd>& ToV3DCmd);
    
    virtual void TransformRawData(TSharedPtr<FSmProcessedDeviceOutput> Data) {}
};

