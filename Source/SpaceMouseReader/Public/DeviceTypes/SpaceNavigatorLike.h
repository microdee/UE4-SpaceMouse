// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ButtonCapabilities.h"

/**
 * 
 */
class SPACEMOUSEREADER_API FSpaceNavigatorLike : FButtonCapabilities
{
public:
    FSpaceNavigatorLike()
    {
        SupportedButtons.Add(FSmButton::FromButtonID(0));
        SupportedButtons.Add(FSmButton::FromButtonID(1));
    }
    ~FSpaceNavigatorLike();
};
