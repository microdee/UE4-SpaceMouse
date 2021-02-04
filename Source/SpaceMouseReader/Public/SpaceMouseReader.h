// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "SpaceMouseManager.h"

#define JOIN_VIDPID(vid, pid) ((vid) | ((pid) << 16))
#define GET_VID(vidpid) ((vidpid) & 0x0000FFFF)
#define GET_PID(vidpid) (((vidpid) & 0xFFFF0000) >> 16)

#define BUTTONDOWN(id) (Buttons[id] && !PrevButtons[id])

class SPACEMOUSEREADER_API FSpaceMouseReaderModule : public IModuleInterface
{
public:

    static TMap<uint32, FSpaceMouseDevice*> Prototypes;

    template<typename TDevice = FSpaceMouseDevice>
    static void AddPrototype(uint32 vid, uint32 pid, FString DeviceName)
    {
        static_assert(
            std::is_convertible_v<TDevice*, FSpaceMouseDevice*>,
            "Given device type is not an FSpaceMouseDevice"
        );

        TDevice* res = new TDevice();
        res->FriendlyDeviceName = DeviceName;
        Prototypes.Add(JOIN_VIDPID(vid, pid), res);
    }

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    virtual bool SupportsDynamicReloading() override { return true; }
};