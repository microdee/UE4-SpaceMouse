// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Buttons.h"

/**
 * 
 */
class SPACEMOUSEREADER_API FButtonCapabilities
{
public:
    FButtonCapabilities();
    ~FButtonCapabilities();
    
    TSet<EV3DCmd> SupportedButtons;
};
