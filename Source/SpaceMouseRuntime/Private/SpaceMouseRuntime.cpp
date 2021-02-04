// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#include "SpaceMouseRuntime.h"
//#include "App.h"
//#include "Object.h"
#include "SpaceMouseReader.h"
#include "SpaceMouseData.h"

//#define DEBUG_SM_VALUES 1

//#define LOCTEXT_NAMESPACE "FSpaceMouseRuntimeModule"

//General Log
//DEFINE_LOG_CATEGORY(SpaceMouseRuntime);

void FSpaceMouseRuntimeModule::StartupModule()
{
    if(FModuleManager::Get().IsModuleLoaded("SpaceMouseReader"))
        ReaderModule = FModuleManager::GetModulePtr<FSpaceMouseReaderModule>("SpaceMouseReader");
    else
    {
        ReaderModule = FModuleManager::LoadModulePtr<FSpaceMouseReaderModule>("SpaceMouseReader");
        //ReaderModule->StartupModule();
    }

    USpaceMouseData::Manager.Initialize();
}

void FSpaceMouseRuntimeModule::ShutdownModule()
{
}

//#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FSpaceMouseRuntimeModule, SpaceMouseRuntime)