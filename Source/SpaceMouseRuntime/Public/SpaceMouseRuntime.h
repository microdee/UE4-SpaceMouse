// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "TimerManager.h"

//General Log
DECLARE_LOG_CATEGORY_EXTERN(SpaceMouseEditor, Log, All);

#define SPACEMOUSE_BUTTONCOUNT 48

#define BUTTONDOWN(id) (Buttons[id] && !PrevButtons[id])

class FSpaceMouseRuntimeModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool SupportsDynamicReloading() override { return true; }
	
	class FSpaceMouseReaderModule* ReaderModule;
};