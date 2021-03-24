// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DeviceTypes/ButtonCapabilities.h"

/**
 * 
 */
class SPACEMOUSEREADER_API FTDxWareButtonCapabilities : public FButtonCapabilities
{
public:
    FTDxWareButtonCapabilities()
    {
        // TODO: detect actual device and use those buttons
    }

    virtual void TransformRawData(TSharedPtr<FProcessedDeviceOutput> Data) override;
};
