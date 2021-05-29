// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DeviceTypes/ButtonCapabilities.h"

#if WITH_3DX_NAVLIB

/**
 * 
 */
class SPACEMOUSEREADER_API FTDxNavlibButtonCapabilities : public FButtonCapabilities
{
public:
	FTDxNavlibButtonCapabilities()
	{
	}
    virtual void TransformRawData(TSharedPtr<FProcessedDeviceOutput> Data) override {}
};

#endif
