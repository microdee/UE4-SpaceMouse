// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ButtonCapabilities.h"

/**
 * 
 */
class SPACEMOUSEREADER_API FSpaceNavigatorLike : public FButtonCapabilities
{
public:
    FSpaceNavigatorLike()
    {
        SupportedButtons.Add(FSmButton::FromID(0));
        SupportedButtons.Add(FSmButton::FromID(1));
    }
};
