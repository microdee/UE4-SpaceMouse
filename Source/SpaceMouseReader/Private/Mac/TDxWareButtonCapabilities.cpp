
#include "Mac/TDxWareButtonCapabilities.h"

void FTDxWareButtonCapabilities::TransformRawData(TSharedPtr<FProcessedDeviceOutput> Data)
{
    // TODO: assumption, so far all universal receiver compatible device have the same HID protocol
    // TODO: detect device types through the universal receiver
    Data->Buttons = MapModernButtons(Data->Buttons);
}