// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#include "SpaceMouseReader.h"

#include "hidapi.h"

DEFINE_LOG_CATEGORY(LogSmReader);

void FSpaceMouseReaderModule::StartupModule()
{
    hid_init();
}

void FSpaceMouseReaderModule::ShutdownModule()
{
    hid_exit();
}

IMPLEMENT_MODULE(FSpaceMouseReaderModule, SpaceMouseReader)
