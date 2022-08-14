// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

#include "SmUserSettings.h"

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
class SPACEMOUSEREADER_API FSmDeviceFactory
{
public:
    FSmDeviceFactory();
    ~FSmDeviceFactory();

    TMap<uint32 /* vid, pid */, FSmDeviceCreator> KnownModels;
    void AddModel(uint16 Vid, uint16 Pid, FSmDeviceCreator Creator);

    void OpenConnectedDevices(const TFunction<FSmUserSettings()>& Settings, TArray<TSharedPtr<FSmDevice>>& Output);
};
