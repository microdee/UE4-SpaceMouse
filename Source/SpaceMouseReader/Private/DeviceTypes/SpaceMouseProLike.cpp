// Fill out your copyright notice in the Description page of Project Settings.


#include "DeviceTypes/SpaceMouseProLike.h"


union FButtonUnion
{
    FButtonBits BitArray;
    uint16 Data[sizeof(FButtonBits) / 2];
};

void FSpaceMouseProLike::TransformRawData(TSharedPtr<FProcessedDeviceOutput> Data)
{
    FButtonUnion Conv {Data->Buttons};
    Conv.Data[1] = Conv.Data[1] << 2;
    Conv.Data[2] = Conv.Data[2] << 2;
    Data->Buttons = Conv.BitArray;
}
