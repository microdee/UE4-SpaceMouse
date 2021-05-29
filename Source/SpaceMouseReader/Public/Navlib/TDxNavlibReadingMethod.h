// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ReadingMethod/DataReadingMethod.h"

#if WITH_3DX_NAVLIB

/**
 * 
 */
class SPACEMOUSEREADER_API FTDxNavlibReadingMethod : public FDataReadingMethod
{
public:
	FTDxNavlibReadingMethod();
	~FTDxNavlibReadingMethod();
	
	virtual int GetAxisResolution() override { return 350; }
	virtual void Tick(FDataReadingOutput& Output, float DeltaSecs) override;
};

#endif