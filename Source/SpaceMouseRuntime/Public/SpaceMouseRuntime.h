// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "IInputDeviceModule.h"

//General Log
DECLARE_LOG_CATEGORY_EXTERN(SpaceMouseRuntime, Log, All);

class FSpaceMouseRuntimeModule : public IInputDeviceModule
{
public:

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    virtual bool SupportsDynamicReloading() override { return true; }
    
    virtual TSharedPtr< class IInputDevice > CreateInputDevice(const TSharedRef< class FGenericApplicationMessageHandler >& InMessageHandler) override;
};