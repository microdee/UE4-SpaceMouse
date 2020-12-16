// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "SpaceMouseManager.h"

#define JOIN_VIDPID(vid, pid) ((vid) | ((pid) << 16))
#define GET_VID(vidpid) ((vidpid) & 0x0000FFFF)
#define GET_PID(vidpid) (((vidpid) & 0xFFFF0000) >> 16)

#define ADD_PROTOTYPE(vid, pid) Prototypes.Add(JOIN_VIDPID(vid, pid), new FSpaceMouseDevice())
#define ADD_PROTOTYPE_DERIV(vid, pid, devclass) Prototypes.Add(JOIN_VIDPID(vid, pid), new devclass())

#define BUTTONDOWN(id) (Buttons[id] && !PrevButtons[id])

class SPACEMOUSEREADER_API FSpaceMouseReaderModule : public IModuleInterface
{
public:

    static TMap<unsigned int, FSpaceMouseDevice*> Prototypes;

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool SupportsDynamicReloading() override { return true; }
};