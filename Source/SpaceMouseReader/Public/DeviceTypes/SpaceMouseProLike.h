// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ButtonCapabilities.h"

/**
 * 
 */
class SPACEMOUSEREADER_API FSpaceMouseProLike : public FButtonCapabilities
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
};
