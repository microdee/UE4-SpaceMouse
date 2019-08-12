// Copyright 1998-2019 David Morasz All Rights Reserved.

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