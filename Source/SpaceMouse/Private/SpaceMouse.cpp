// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#include "SpaceMouse.h"
#include "Editor.h"
#include "SEditorViewport.h"
#include "SpaceMouseReader.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#include "SmKeyStructCustomization.h"

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
    auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    
    PropertyModule.RegisterCustomClassLayout(
        "SpaceMouseConfig",
        FOnGetDetailCustomizationInstance::CreateStatic(&FSpaceMouseConfigCustomization::MakeInstance)
    );

    PropertyModule.NotifyCustomizationModuleChanged();

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

        Settings->RegisterInputBindingNotification();
    }
}

void FSpaceMouseModule::UnregisterSettings()
{
    if(FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
    {
        auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

        PropertyModule.UnregisterCustomClassLayout("SpaceMouseConfig");
    }
    
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->UnregisterSettings("Editor", "Plugins", "SpaceMouse");
    }
}

void FSpaceMouseModule::RegisterPropertyTypeCustomizations()
{
    RegisterCustomPropertyTypeLayout(
        "SmKey",
        FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FSmKeyStructCustomization::MakeInstance)
    );
}

void FSpaceMouseModule::RegisterCustomPropertyTypeLayout(FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate)
{
    check(PropertyTypeName != NAME_None);

    RegisteredPropertyTypes.Add(PropertyTypeName);

    static FName PropertyEditor("PropertyEditor");
    FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(PropertyEditor);
    PropertyModule.RegisterCustomPropertyTypeLayout(PropertyTypeName, PropertyTypeLayoutDelegate);
}

void FSpaceMouseModule::StartupModule()
{
    if(FModuleManager::Get().IsModuleLoaded("SpaceMouseReader"))
        ReaderModule = FModuleManager::GetModulePtr<FSpaceMouseReaderModule>("SpaceMouseReader");
    else
    {
        ReaderModule = FModuleManager::LoadModulePtr<FSpaceMouseReaderModule>("SpaceMouseReader");
        //ReaderModule->StartupModule();
    }
    
    RegisterPropertyTypeCustomizations();
    RegisterSettings();
    
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