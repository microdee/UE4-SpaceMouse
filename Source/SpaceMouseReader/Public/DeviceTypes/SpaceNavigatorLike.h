// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

#include "ButtonCapabilities.h"

/**
 * 
 */
class SPACEMOUSEREADER_API FSpaceNavigatorLike : public FSmButtonCapabilities
{
public:
    FSpaceNavigatorLike()
    {
        SupportedButtons.Add(FSmButton::FromID(0));
        SupportedButtons.Add(FSmButton::FromID(1));
    }
};
