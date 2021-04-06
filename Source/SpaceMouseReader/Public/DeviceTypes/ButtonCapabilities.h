// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Buttons.h"
#include "ProcessedDeviceOutput.h"

/**
 * 
 */
class SPACEMOUSEREADER_API FButtonCapabilities
{
public:
    virtual ~FButtonCapabilities() = default;

    TSet<EV3DCmd> SupportedButtons;

    // Source of info: https://github.com/blender/blender/blob/594f47ecd2d5367ca936cf6fc6ec8168c2b360d0/intern/ghost/intern/GHOST_NDOFManager.cpp#L91
    static FButtonBits MapModernButtons(FButtonBits HIDButtons);

    static FButtonBits MapButtons(FButtonBits HIDButtons, const TArray<EV3DCmd>& ToV3DCmd);
    
    virtual void TransformRawData(TSharedPtr<FProcessedDeviceOutput> Data) {}
};

