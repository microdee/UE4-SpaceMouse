// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#include "SpaceMouseReader.h"

#include "hidapi.h"

TMap<unsigned int, FSpaceMouseDevice*> FSpaceMouseReaderModule::Prototypes = TMap<unsigned int, FSpaceMouseDevice*>();

void FSpaceMouseReaderModule::StartupModule()
{
    // https://github.com/FreeSpacenav/spacenavd/blob/a9eccf34e7cac969ee399f625aef827f4f4aaec6/src/dev.c#L202
    // https://www.3dconnexion.fr/nc/service/faqs/faq/how-can-i-check-if-my-usb-3d-mouse-is-recognized-by-windows.html

    AddPrototype(0x046d, 0xc603, TEXT("Space Mouse plus XT"));
    AddPrototype(0x046d, 0xc605, TEXT("CAD Man"));
    AddPrototype(0x046d, 0xc606, TEXT("Space Mouse classic"));
    AddPrototype(0x046d, 0xc621, TEXT("SpaceBall 5000"));
    AddPrototype(0x046d, 0xc623, TEXT("Space Traveller"));
    AddPrototype(0x046d, 0xc625, TEXT("Space Pilot"));
    AddPrototype(0x046d, 0xc626, TEXT("Space Navigator"));
    AddPrototype(0x046d, 0xc627, TEXT("Space Explorer"));
    AddPrototype(0x046d, 0xc628, TEXT("Space Navigator for Notebooks"));
    AddPrototype(0x046d, 0xc629, TEXT("Space Pilot Pro"));
    AddPrototype(0x046d, 0xc62b, TEXT("Space Mouse Pro"));
    AddPrototype(0x046d, 0xc640, TEXT("nulooq"));
    AddPrototype<FSingleReportPosRotSmDevice>(0x256f, 0xc62e, TEXT("Space Mouse Wireless (USB cable)"));
    AddPrototype<FSingleReportPosRotSmDevice>(0x256f, 0xc62f, TEXT("Space Mouse Wireless (Receiver)"));
    AddPrototype<FSingleReportPosRotSmDevice>(0x256f, 0xc631, TEXT("Space Mouse Pro Wireless (USB cable)"));
    AddPrototype<FSingleReportPosRotSmDevice>(0x256f, 0xc632, TEXT("Space Mouse Pro Wireless (Receiver)"));
    AddPrototype<FSingleReportPosRotSmDevice>(0x256f, 0xc633, TEXT("Space Mouse Enterprise"));
    AddPrototype(0x256f, 0xc635, TEXT("Space Mouse Compact"));
    AddPrototype(0x256f, 0xc636, TEXT("Space Mouse Module"));
    AddPrototype<FSingleReportPosRotSmDevice>(0x256f, 0xc652, TEXT("Universal Receiver"));

    hid_init();
}

void FSpaceMouseReaderModule::ShutdownModule()
{
    Prototypes.Empty();
    hid_exit();
}

IMPLEMENT_MODULE(FSpaceMouseReaderModule, SpaceMouseReader)
