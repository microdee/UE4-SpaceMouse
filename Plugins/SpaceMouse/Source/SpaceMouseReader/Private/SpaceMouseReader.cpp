// Copyright 1998-2019 David Morasz All Rights Reserved.

#include "SpaceMouseReader.h"

TMap<unsigned int, FSpaceMouseDevice> FSpaceMouseReaderModule::Prototypes = TMap<unsigned int, FSpaceMouseDevice>();

void FSpaceMouseReaderModule::StartupModule()
{
    // https://github.com/FreeSpacenav/spacenavd/blob/a9eccf34e7cac969ee399f625aef827f4f4aaec6/src/dev.c#L202

    ADD_PROTOTYPE(0x046d, 0xc603); // spacemouse plus XT
    ADD_PROTOTYPE(0x046d, 0xc605); // cadman
    ADD_PROTOTYPE(0x046d, 0xc606); // spacemouse classic
    ADD_PROTOTYPE(0x046d, 0xc621); // spaceball 5000
    ADD_PROTOTYPE(0x046d, 0xc623); // space traveller
    ADD_PROTOTYPE(0x046d, 0xc625); // space pilot
    ADD_PROTOTYPE(0x046d, 0xc626); // space navigator
    ADD_PROTOTYPE(0x046d, 0xc627); // space explorer
    ADD_PROTOTYPE(0x046d, 0xc628); // space navigator for notebooks
    ADD_PROTOTYPE(0x046d, 0xc629); // space pilot pro
    ADD_PROTOTYPE(0x046d, 0xc62b); // space mouse pro
    ADD_PROTOTYPE(0x046d, 0xc640); // nulooq
    ADD_PROTOTYPE(0x256f, 0xc603); // spacemouse wireless (USB cable)
    ADD_PROTOTYPE(0x256f, 0xc603); // spacemouse wireless (receiver)
    ADD_PROTOTYPE(0x256f, 0xc603); // spacemouse pro wireless (USB cable)
    ADD_PROTOTYPE(0x256f, 0xc603); // spacemouse pro wireless (receiver)
    ADD_PROTOTYPE(0x256f, 0xc603); // spacemouse enterprise
    ADD_PROTOTYPE(0x256f, 0xc603); // spacemouse compact
    ADD_PROTOTYPE(0x256f, 0xc636); // spacemouse module

	hid_init();
}

void FSpaceMouseReaderModule::ShutdownModule()
{
    hid_exit();
}

IMPLEMENT_MODULE(FSpaceMouseReaderModule, SpaceMouseReader)
