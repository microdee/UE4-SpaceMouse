// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#include "SpaceMouse.h"
#include "Editor.h"
#include "SEditorViewport.h"
//#include "Runtime/Core/Public/Misc/App.h"
//#include "Object.h"
#include "SpaceMouseReader.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"

//#define DEBUG_SM_VALUES 1

#define LOCTEXT_NAMESPACE "FSpaceMouseModule"

//General Log
DEFINE_LOG_CATEGORY(SpaceMouseEditor);

bool FSpaceMouseModule::HandleSettingsSaved()
{
    auto Settings = GetMutableDefault<USpaceMouseConfig>();
    Settings->SaveConfig();
    return true;
}

void FSpaceMouseModule::RegisterSettings()
{
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        auto Settings = GetMutableDefault<USpaceMouseConfig>();

        ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Editor", "Plugins", "SpaceMouse",
            LOCTEXT("RuntimeGeneralSettingsName", "SpaceMouse"),
            LOCTEXT("RuntimeGeneralSettingsDescription", "Configure SpaceMice for the editor"),
            Settings
        );

        // Register the save handler to your settings, you might want to use it to
        // validate those or just act to settings changes.
        if (SettingsSection.IsValid())
        {
            SettingsSection->OnModified().BindRaw(this, &FSpaceMouseModule::HandleSettingsSaved);
        }
    }
}

void FSpaceMouseModule::UnregisterSettings()
{
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->UnregisterSettings("Editor", "Plugins", "SpaceMouse");
    }
}

void FSpaceMouseModule::StartupModule()
{
    RegisterSettings();

    if(FModuleManager::Get().IsModuleLoaded("SpaceMouseReader"))
        ReaderModule = FModuleManager::GetModulePtr<FSpaceMouseReaderModule>("SpaceMouseReader");
    else
    {
        ReaderModule = FModuleManager::LoadModulePtr<FSpaceMouseReaderModule>("SpaceMouseReader");
        //ReaderModule->StartupModule();
    }
    
    SmManager.Initialize();
    SmManager.Start();
}

void FSpaceMouseModule::ShutdownModule()
{
    if(UObjectInitialized())
    {
        UnregisterSettings();
    }
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FSpaceMouseModule, SpaceMouse)