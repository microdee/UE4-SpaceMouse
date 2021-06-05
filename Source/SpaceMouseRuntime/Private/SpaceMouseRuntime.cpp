// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#include "SpaceMouseRuntime.h"
//#include "App.h"
//#include "Object.h"
#include "SmInputDevice.h"
#include "Modules/ModuleManager.h"
#include "TimerManager.h"
#include "SpaceMouseReader.h"
#include "SpaceMouseData.h"


#define LOCTEXT_NAMESPACE "FSpaceMouseRuntimeModule"

//General Log
DEFINE_LOG_CATEGORY(SpaceMouseRuntime);

void FSpaceMouseRuntimeModule::StartupModule()
{
    IModularFeatures::Get().RegisterModularFeature(GetModularFeatureName(), this);
}

void FSpaceMouseRuntimeModule::ShutdownModule()
{
    IModularFeatures::Get().UnregisterModularFeature(GetModularFeatureName(), this);
}

TSharedPtr<IInputDevice> FSpaceMouseRuntimeModule::CreateInputDevice(
    const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
    return MakeShared<FSmInputDevice>(InMessageHandler);
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FSpaceMouseRuntimeModule, SpaceMouseRuntime)