// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorDelegates.h"
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
    
	TSet<FName> RegisteredPropertyTypes;
	void RegisterPropertyTypeCustomizations();
	void RegisterCustomPropertyTypeLayout(FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate );

public:

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    virtual bool SupportsDynamicReloading() override { return true; }
    
    FSmEditorManager SmManager;
    class FSpaceMouseReaderModule* ReaderModule;
};
