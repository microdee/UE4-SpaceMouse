# UE4-SpaceMouse Build Guide for Linux

This guide will help you get up and running with the UE4-SpaceMouse plugin on Linux.

## Compatibility

The installation process detailed in this guide has been validated to work on the following system configurations:

| Operating System | Engine                  |
|------------------|-------------------------|
| Linux Mint 21.2  | UE 5.2.1 (pre-compiled) |

## Prerequisites

This guide assumes that you've installed a compatible Unreal Engine version – however, it's likely that other versions will be fine as well. If the guide works for you with any other mix of OS and/or engine version, feel free to add your configuration to the compatibility table.

Unreal Engine is distributed with the necessary dependencies to package your games and build your plugins, however it's possible to use local installations of compilers and additional dependencies instead. **This guide assumes you're using the bundled toolchain**.

After installation, take note of your installation directory – you'll need it later.

If you intend to use your SpaceMouse for any other software you should consider installing the `spacenavd` driver (daemon) for additional support.

## Building

UE4-SpaceMouse doesn't currently provide a pre-built plugin for Linux, so we have to build our own release before installation.

Download the plugin source code from the [release page](https://github.com/microdee/UE4-SpaceMouse/releases) or clone the repository:

```
git clone --recurse-submodules https://github.com/microdee/UE4-SpaceMouse.git
```

UE4-SpaceMouse includes additional submodules as dependencies, so it's important to clone these as well.

Build the plugin using the `RunUAT.sh` script bundled with the engine. Use the following command. Don't forget to completing each path with your local installation directory:

```
Engine/Build/BatchFiles/RunUAT.sh BuildPlugin \
-Plugin="UE4-SpaceMouse/SpaceMouse.uplugin" \
-Package="UE4-SpaceMouse/Out/Linux"
```

After completion you will find the compiled plugin in the `UE4-SpaceMouse/Out/Linux` directory.

### Troubleshooting

When you try to build the plugin you might get an error saying `"libudev.h not found"`. If that's the case, install the `libudev-dev` package from your package manager and try again.

If you've installed local toolchains for C/C++ development using system packages such as `build-essential` (Debian, Ubuntu, etc.) you could experience issues with compiling the plugin. This was resolved by removing the installed packages, but for many that won't be a possibility. For now there's no documented way to resolve these issues.

## Installation

After building the plugin copy the `UE4-SpaceMouse/Out/Linux` folder into your project's `Plugins` directory, changing the name in the process to `SpaceMouse`.

Start the Unreal Editor and verify that the plugin is enabled in **Edit > Plugins > Input Devices**. Then check that plugin settings are available in **Edit > Editor Preferences > Plugins > SpaceMouse**.

Your'e now ready to use your 3DConnexion hardware! Review the [README](README.md) for additional configuration options and how to use the plugin.

### Troubleshooting

After installation, if you can't use your SpaceMouse to navigate any editor viewports it's possible that your local user account doesn't have access to the HID device. This can be solved by adding the following `udev` rules ([source](https://github.com/prusa3d/PrusaSlicer/blob/master/resources/udev/90-3dconnexion.rules)) which should set permissions to allow any user read/write access to most 3DConnexion devices.

Copy the following content and save it in a file named `90-3dconnexion.rules` in the `/usr/lib/udev/rules.d` directory. **This will require root privileges!**

```
# 3D Connexion vendor devices
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c603", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c605", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c606", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c621", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c623", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c625", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c626", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c627", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c628", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c629", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c62b", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c62e", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c62f", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c631", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c632", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c633", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c635", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c636", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c640", MODE="0666"
KERNEL=="hidraw*", ATTRS{idVendor}=="256f", ATTRS{idProduct}=="c652", MODE="0666"
```

Restart your computer and you should now be able to use your SpaceMouse in Unreal Engine.
