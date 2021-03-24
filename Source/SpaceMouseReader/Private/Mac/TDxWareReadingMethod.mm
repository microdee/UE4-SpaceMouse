// Fill out your copyright notice in the Description page of Project Settings.


#include "Mac/TDxWareReadingMethod.h"

#if PLATFORM_MAC

#include "SpaceMouseReader.h"

// connection to driver
// grabbed from https://github.com/blender/blender/blob/594f47ecd2d5367ca936cf6fc6ec8168c2b360d0/intern/ghost/intern/GHOST_NDOFManagerCocoa.mm

#include <dlfcn.h>
#include <stdint.h>

static uint16_t clientID = 0;

static TSharedPtr<FTDyDataProvider> StaticDataProvider;

static bool driver_loaded = false;
static bool has_old_driver = false; // 3Dconnexion drivers before 10 beta 4 are "old", not all buttons will work
static bool has_new_driver = false; // drivers >= 10.2.2 are "new", and can process events on a separate thread

// replicate just enough of the 3Dx API for our uses, not everything the driver provides

#define kConnexionClientModeTakeOver 1
#define kConnexionMaskAll 0x3fff
#define kConnexionMaskAllButtons 0xffffffff
#define kConnexionCmdHandleButtons 2
#define kConnexionCmdHandleAxis 3
#define kConnexionCmdAppSpecific 10
#define kConnexionMsgDeviceState '3dSR'
#define kConnexionCtlGetDeviceID '3did'

// callback functions:
typedef void (*AddedHandler)(uint32_t);
typedef void (*RemovedHandler)(uint32_t);
typedef void (*MessageHandler)(uint32_t, uint32_t msg_type, void *msg_arg);

// driver functions:
typedef int16_t (*SetConnexionHandlers_ptr)(MessageHandler, AddedHandler, RemovedHandler, bool);
typedef int16_t (*InstallConnexionHandlers_ptr)(MessageHandler, AddedHandler, RemovedHandler);
typedef void (*CleanupConnexionHandlers_ptr)();

typedef uint16_t (*RegisterConnexionClient_ptr)(
    uint32_t signature,
    const char *name,
    uint16_t mode,
    uint32_t mask
);

typedef void (*SetConnexionClientButtonMask_ptr)(uint16_t clientID, uint32_t buttonMask);
typedef void (*UnregisterConnexionClient_ptr)(uint16_t clientID);

typedef int16_t (*ConnexionClientControl_ptr)(
    uint16_t clientID,
    uint32_t message,
    int32_t param,
    int32_t *result
);

#define DECLARE_FUNC(name) name##_ptr name = NULL

DECLARE_FUNC(SetConnexionHandlers);
DECLARE_FUNC(InstallConnexionHandlers);
DECLARE_FUNC(CleanupConnexionHandlers);
DECLARE_FUNC(RegisterConnexionClient);
DECLARE_FUNC(SetConnexionClientButtonMask);
DECLARE_FUNC(UnregisterConnexionClient);
DECLARE_FUNC(ConnexionClientControl);

static void *load_func(void *module, const char *func_name)
{
    void *func = dlsym(module, func_name);
    FString FuncName {func_name};
    if(func)
    {
        UE_LOG(LogSmReader, Display, TEXT("3DxWare function loaded: %s"), *FuncName);
    }
    else
    {
        FString DlError {dlerror()};
        UE_LOG(LogSmReader, Error, TEXT("Couldn't load 3DxWare function: %s (%s)"), *FuncName, *DlError);
    }
    return func;
}

#define LOAD_FUNC(name) name = (name##_ptr)load_func(module, #name)

static void *module;  // handle to the whole driver

static bool load_driver_functions()
{
    if (driver_loaded) {
        return true;
    }

    // TODO: should we use local instead? It's supposedly already installed on the user's mac
    module = dlopen("/Library/Frameworks/3DconnexionClient.framework/3DconnexionClient", RTLD_LAZY | RTLD_LOCAL);

    if (module) {
        LOAD_FUNC(SetConnexionHandlers);

        if (SetConnexionHandlers != NULL) {
            driver_loaded = true;
            has_new_driver = true;
        }
        else {
            LOAD_FUNC(InstallConnexionHandlers);

            driver_loaded = (InstallConnexionHandlers != NULL);
        }

        if (driver_loaded) {
            LOAD_FUNC(CleanupConnexionHandlers);
            LOAD_FUNC(RegisterConnexionClient);
            LOAD_FUNC(SetConnexionClientButtonMask);
            LOAD_FUNC(UnregisterConnexionClient);
            LOAD_FUNC(ConnexionClientControl);

            has_old_driver = (SetConnexionClientButtonMask == NULL);
        }
    }

    return driver_loaded;
}

static void unload_driver()
{
    dlclose(module);
}

static void DeviceAdded(uint32_t unused)
{
    // determine exactly which device is plugged in
    int32_t result;
    ConnexionClientControl(clientID, kConnexionCtlGetDeviceID, 0, &result);
    int16_t vendorID = result >> 16;
    int16_t productID = result & 0xffff;
    
    UE_LOG(LogSmReader, Display, TEXT("A device got connected."));

    StaticDataProvider->SeenDevices.Add({vendorID, productID});
}

static void DeviceRemoved(uint32_t unused)
{
    UE_LOG(LogSmReader, Display, TEXT("A device got removed."));
}

static void DeviceEvent(uint32_t unused, uint32_t msg_type, void *msg_arg)
{
    if (msg_type == kConnexionMsgDeviceState) {
        ConnexionDeviceState *s = (ConnexionDeviceState *)msg_arg;

        // device state is broadcast to all clients; only react if sent to us
        if (s->client == clientID) {
            // TODO: is s->time compatible with GHOST timestamps? if so use that instead.
            GHOST_TUns64 now = ghost_system->getMilliSeconds();

            switch (s->command) {
                case kConnexionCmdHandleAxis: {
                    // convert to blender view coordinates
                    const int t[3] = {s->axis[0], -(s->axis[2]), s->axis[1]};
                    const int r[3] = {-(s->axis[3]), s->axis[5], -(s->axis[4])};

                    ndof_manager->updateTranslation(t, now);
                    ndof_manager->updateRotation(r, now);

                    ghost_system->notifyExternalEventProcessed();
                    break;
                }
                case kConnexionCmdHandleButtons: {
                    int button_bits = has_old_driver ? s->buttons8 : s->buttons;
                    ndof_manager->updateButtons(button_bits, now);
                    ghost_system->notifyExternalEventProcessed();
                    break;
                }
#if DEBUG_NDOF_DRIVER
                case kConnexionCmdAppSpecific:
                    printf("ndof: app-specific command, param = %hd, value = %d\n", s->param, s->value);
                    break;

                default:
                    printf("ndof: mystery device command %d\n", s->command);
#endif
            }
        }
    }
}

FTDxWareReadingMethod::FTDxWareReadingMethod()
{
    
}

#endif