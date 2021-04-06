// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UserSettings.h"

enum class ESmModelConfidence : uint8;
class FSmDevice;
struct FSmDeviceInstantiation;

typedef TFunction<TSharedPtr<FSmDevice>(const FSmDeviceInstantiation&)> FSmDeviceCreator;


#define JOIN_VIDPID(vid, pid) ((vid) | ((pid) << 16))
#define GET_VID(vidpid) ((vidpid) & 0x0000FFFF)
#define GET_PID(vidpid) (((vidpid) & 0xFFFF0000) >> 16)

/**
 * 
 */
class SPACEMOUSEREADER_API FDeviceFactory
{
public:
    FDeviceFactory();
    ~FDeviceFactory();

    TMap<uint32 /* vid, pid */, FSmDeviceCreator> KnownModels;
    void AddModel(uint16 Vid, uint16 Pid, FSmDeviceCreator Creator);

    void OpenConnectedDevices(const TFunction<FUserSettings()>& Settings, TArray<TSharedPtr<FSmDevice>>& Output);
};
