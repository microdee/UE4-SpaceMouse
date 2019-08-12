// Copyright 1998-2019 David Morasz All Rights Reserved.

#include "SpaceMouseRuntime.h"
#include "App.h"
#include "Object.h"
#include "SpaceMouseReader.h"

//#define DEBUG_SM_VALUES 1

#define LOCTEXT_NAMESPACE "FSpaceMouseRuntimeModule"

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
}

void FSpaceMouseRuntimeModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSpaceMouseRuntimeModule, SpaceMouseRuntime)