// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

#include "ButtonCapabilities.h"

/**
 * 
 */
class SPACEMOUSEREADER_API FSpaceExplorerLike : public FSmButtonCapabilities
{
public:
    FSpaceExplorerLike()
    {
        // Source of info: https://github.com/blender/blender/blob/594f47ecd2d5367ca936cf6fc6ec8168c2b360d0/intern/ghost/intern/GHOST_NDOFManager.cpp#L101
        SupportedButtons.Add(EV3DCmd::KeyF1);
        SupportedButtons.Add(EV3DCmd::KeyF2);
        SupportedButtons.Add(EV3DCmd::ViewTop);
        SupportedButtons.Add(EV3DCmd::ViewLeft);
        SupportedButtons.Add(EV3DCmd::ViewRight);
        SupportedButtons.Add(EV3DCmd::ViewFront);
        SupportedButtons.Add(EV3DCmd::KeyEsc);
        SupportedButtons.Add(EV3DCmd::KeyAlt);
        SupportedButtons.Add(EV3DCmd::KeyShift);
        SupportedButtons.Add(EV3DCmd::KeyCtrl);
        SupportedButtons.Add(EV3DCmd::ViewFit);
        SupportedButtons.Add(EV3DCmd::MenuOptions);
        SupportedButtons.Add(EV3DCmd::ScalePlus);
        SupportedButtons.Add(EV3DCmd::ScaleMinus);
        SupportedButtons.Add(EV3DCmd::FilterRotate);
    }

    virtual void TransformRawData(TSharedPtr<FSmProcessedDeviceOutput> Data) override;
};
