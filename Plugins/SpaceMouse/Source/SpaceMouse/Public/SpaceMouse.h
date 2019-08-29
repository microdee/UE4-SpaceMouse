// Copyright 1998-2019 David Morasz All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "TimerManager.h"
#include "SmEditorManager.h"
#include "LevelEditorViewport.h"
#include "SpaceMouseConfig.h"

//General Log
DECLARE_LOG_CATEGORY_EXTERN(SpaceMouseEditor, Log, All);

class FSpaceMouseModule : public IModuleInterface
{
private:

	bool HandleSettingsSaved();
	void RegisterSettings();
	void UnregisterSettings();

public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool SupportsDynamicReloading() override { return true; }
	
	FSmEditorManager SmManager;
	class FSpaceMouseReaderModule* ReaderModule;

	static USpaceMouseConfig* Settings;
};
