## SpaceMouse camera controller for UE4 editor viewports

**Compatible with UE 4.26 and below**  
**Compiled for UE 4.23 .. 4.26.**

**[Download manually for free](https://github.com/microdee/UE4-SpaceMouse/releases/latest)**

**[Buy it via the Marketplace](https://www.unrealengine.com/marketplace/en-US/product/spacemouse-for-unreal-engine)**

Demo video: https://youtu.be/Qibig0gQWvE

## [Disclaimer about the new official plugin shipped by 3DConnexion](DISCLAIMER.md)

# About

You can control any 3D editor viewport currently in focus (user clicked on it). There are multiple control schemes, check below.

![Alt text](/ReadmeMedia/featured.png?raw=true "Coordinates")

Transition speed is controllable via the camera speed setting and the camera speed scalar of the viewport. Camera speed can be increased or decreased with configurable buttons on the spacemice. Multiple devices are supported however their data is merged together into a global context.

On default speeds (speed setting = 4) transition velocity is 1000 units/sec by default and rotation speed is 270°/sec by default. Rotation speed is not affected by camera speed settings. You can change these in the **Editor Preference** under SpaceMouse section.

![Alt text](/ReadmeMedia/settings.png?raw=true "Settings")

**Active in Background** When false, only control the camera of UE4 while the editor is the foreground application.

**Camera Behavior** Sets the mode of controlling the viewport camera. For all modes movement is always applied in current camera space.

* **Camera Delta with Roll**
  * SpaceMouse represents the Delta Movement of the camera in Free-flight/Helicopter fashion. All rotation is in current camera space.
* **Camera Delta with No Roll**
  * Same as above but roll is ignored and Yaw is always in World space (instead of current camera space))
* **Orbitting with Roll** (EXPERIMENTAL)
  * SpaceMouse represents the Delta Movement of the camera around "the object" OR the Delta movement of "the object" in front of the camera. The pivot of orbitting is either surface point in the center of the viewport, or a fixed distance if set in the settings.
* **Orbitting with No Roll** (EXPERIMENTAL)
  * Same as above but roll is ignored and Yaw is always in World space (instead of current camera space))

**Orbitting Moves/Rotates Object** When true, SpaceMouse represents the Delta movement of "the object" in front of the camera (meaning axes are inverted)

**Orbitting at Fixed Pivot Distance** When enabled, sets a fixed distance for the orbitting mode in UE4 units (usually cm).

**Orbitting Line Trace Length** is the maximum possible radius of the orbitting behavior in UE4 units (usually cm).

**Axis mappings** are conversions between the space of spacemice and the space of UE4. You can invert rotations and translations here by flipping the sign. The default values are my subjective preferences (as you can see in the coordinate system image above).

**Rotation/Translation Curve** are defining the 0..1 curvature from resting state to fully pushed/pulled state of the SpaceMouse puck. Dead-zone, clamping, exponent or other less useful transformations can be expressed with this. Default is 0..1 linear curve, which means no effect.

**Display Debug Information** prints HID data onto the viewport. You don't need to change **Max Hid Read Operations Per Frame**. Just ignore it.

With **Button mappings** one can remap some functionalities to SpaceMouse buttons. Activate the toggle button next to the property to learn the desired button mapping for said function.

* Increase, Decrease and Reset camera speed.
* Reset the roll of the camera
* Map SpaceMouse buttons to keyboard presses in UE4 editor, so if you have a SpaceMouse Pilot or Enterprise you can spare some hand lifts while working.

This plugin works with the HID device directly so no 3DxWare service is needed to run (similar how Blender does it). And I highly recommend to disable said service because it's a big pile of steaming hot garbage imo. It doesn't need you to install any drivers at all in theory. However it shouldn't interfere with a running 3DxWare service in case you need it for other less fortunate programs.

[Report bugs](https://github.com/microdee/UE4-SpaceMouse/issues)

[Have any feedback or ideas? Go to Discussions!](https://github.com/microdee/UE4-SpaceMouse/discussions)

[UE4 forum (please prefer Github Discussions)](https://forums.unrealengine.com/unreal-engine/feedback-for-epic/437-support-for-space-navigator-3d-mouse?p=1609440#post1609440)

## Major changes from version 1.1

Upon updating from prior versions please delete both HIDUE and SpaceMouse plugins from your Engine or Project plugins folder!

1. Editor settings is moved to Plugins -> SpaceMouse to follow conventions
2. HIDUE is now demoted to a module instead of an entire plugin
3. This repository now only contains the plugin itself which you can also directly submodule now in your code projects if you wish.

## Known issues:

* ~~"Focus selected" is broken while this plugin is loaded~~
  * FIXED
* ~~"Piloting" is not working with the SpaceMouse~~
  * FIXED
* ~~Upon exiting the editor the engine crashes. I know why it does that but I didn't figure it out quite yet how to prevent it.~~
  * FIXED
* Jumping forward periodically when leaning / going forward with the camera
  * This is most probably caused by the scroll-wheel emulation of 3DxWare. Disable it in the per-application settings, or uninstall it.
* If you install or update 3DxWare with their new plugin (TDxUnrealEditor), and you had this plugin before, you might experience undefined interaction glitches.
  * Remove either this or the 3DConnexion plugin (TDxUnrealEditor) according to your preference.

## Known nuances
* ~~Only free-fly mode is supported and every orbitting perspective viewport in focus is forced to be free-fly while any spacemice operates on them.~~
  * Now multiple camera behaviors are implemented
* Camera roll is not reset when one tries to navigate viewport with traditional methods
  * There's a mappable button now to reset roll
  * There are camera behaviors now which should not introduce roll
  * In case the SpaceMouse becomes unavailable Maya style Alt + Right-drag dollying resets camera roll

## Roadmap:

* Actively maintained cross platform support of HIDUE for MacOS and Linux (coming after mid-January)
* Default bindings for connected device and friendlier button name display (coming after mid-January)
* More intuitive and usable implementation of the Orbiting mode.

## Credits:

* [HIDAPI](https://github.com/libusb/hidapi)
* From UE4 forums:
  * **enzo_molinari** for the plugin icon
  * **adlord** for testing with wireless devices
