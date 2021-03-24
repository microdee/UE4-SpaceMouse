// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#if PLATFORM_MAC

#include "CoreMinimal.h"
#include "ReadingMethod/DataReadingMethod.h"

class SPACEMOUSEREADER_API FTDxWareReadingMethod : public FDataReadingMethod
{
public:
    FTDxWareReadingMethod();
}

#endif