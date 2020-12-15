// Copyright 1998-2019 David Morasz All Rights Reserved.

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

USpaceMouseConfig* FSpaceMouseModule::Settings;

bool FSpaceMouseModule::HandleSettingsSaved()
{
	Settings = GetMutableDefault<USpaceMouseConfig>();
	Settings->SaveConfig();
	return true;
}

void FSpaceMouseModule::RegisterSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		// Create the new category
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Editor");

		SettingsContainer->DescribeCategory("SpaceMouse",
			LOCTEXT("RuntimeWDCategoryName", "SpaceMouse"),
			LOCTEXT("RuntimeWDCategoryDescription", "Configure SpaceMice for the editor"));

		Settings = GetMutableDefault<USpaceMouseConfig>();
		// Register the settings
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Editor", "SpaceMouse", "General",
			LOCTEXT("RuntimeGeneralSettingsName", "General"),
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
		SettingsModule->UnregisterSettings("Editor", "SpaceMouse", "General");
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