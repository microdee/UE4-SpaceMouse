// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

#include "ButtonCapabilities.h"

/**
 * 
 */
class SPACEMOUSEREADER_API FSpaceMouseProLike : public FSmButtonCapabilities
{
public:
    FSpaceMouseProLike()
    {
        // sides
        SupportedButtons.Add(EV3DCmd::MenuOptions);
        SupportedButtons.Add(EV3DCmd::ViewFit);

        // left
        SupportedButtons.Add(EV3DCmd::KeyCtrl);
        SupportedButtons.Add(EV3DCmd::KeyAlt);
        SupportedButtons.Add(EV3DCmd::KeyShift);
        SupportedButtons.Add(EV3DCmd::KeyEsc);

        // right
        SupportedButtons.Add(EV3DCmd::ViewRollCW); // ?
        SupportedButtons.Add(EV3DCmd::ViewTop);
        SupportedButtons.Add(EV3DCmd::ViewRight);
        SupportedButtons.Add(EV3DCmd::ViewFront);
        SupportedButtons.Add(EV3DCmd::FilterRotate); // ?

        // front
        SupportedButtons.Add(EV3DCmd::KeyF1);
        SupportedButtons.Add(EV3DCmd::KeyF2);
        SupportedButtons.Add(EV3DCmd::KeyF3);
        SupportedButtons.Add(EV3DCmd::KeyF4);
    }
    
    virtual void TransformRawData(TSharedPtr<FSmProcessedDeviceOutput> Data) override;
};
