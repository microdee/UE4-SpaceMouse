## SpaceMouse camera controller for UE4 editor viewports

**Compatible with UE 4.25 and below**  
**Compiled for UE 4.21 .. 4.25.**
# [DOWNLOAD](https://github.com/microdee/UE4-SpaceMouse/releases/latest)

Demo video: https://youtu.be/Qibig0gQWvE

You can control any 3D editor viewport currently in focus (user clicked on it). There are multiple control schemes, check below. See the picture for the default transition and rotation axis (although you can change it in Editor Preferences):

![Alt text](/ReadmeMedia/coordinates.jpg?raw=true "Coordinates")

Transition speed is controllable via the camera speed setting and the camera speed scalar of the viewport. Camera speed can be increased or decreased with configurable buttons on the spacemice. Multiple devices are supported however their data is merged together into a global context.

On default speeds (speed setting = 4) transition velocity is 1000 units/sec by default and rotation speed is 270°/sec by default. Rotation speed is not affected by camera speed settings. You can change these in the **Editor Preference** under SpaceMouse section.

![Alt text](/ReadmeMedia/settings.png?raw=true "Coordinates")

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

[Have any feedback or ideas? Go to Discussions!](https://github.com/microdee/UE4-SpaceMouse/discussions)

[UE4 forum (please prefer Github Discussions)](https://forums.unrealengine.com/unreal-engine/feedback-for-epic/437-support-for-space-navigator-3d-mouse?p=1609440#post1609440)

## Known issues:

* ~~"Focus selected" is broken while this plugin is loaded~~
  * FIXED
* ~~"Piloting" is not working with the SpaceMouse~~
  * FIXED
* ~~Upon exiting the editor the engine crashes. I know why it does that but I didn't figure it out quite yet how to prevent it.~~
  * FIXED

## Known nuances
* ~~Only free-fly mode is supported and every orbitting perspective viewport in focus is forced to be free-fly while any spacemice operates on them.~~
  * Now multiple camera behaviors are implemented
* Camera roll is not reset when one tries to navigate viewport with traditional methods
  * There's a mappable button now to reset roll
  * There are camera behaviors now which should not introduce roll
  * In case the SpaceMouse becomes unavailable Maya style Alt + Right-drag dollying resets camera roll

## Would be nice to have:

* ~~Add ability to remap buttons to different actions, so one can potentially use all the buttons on their SpaceMouse Pro~~
  * ~~Implemented in Editor config, however it would be still nice to have a "learn button ID" button~~
    * SpaceMouse plugin can now learn buttons by just pushing them
* ~~Add feature to lock camera roll.~~
  * DONE!
* ~~Add Orbit mode~~
  * DONE!
* Marketplace release!

## Credits:

* [HIDAPI](https://github.com/libusb/hidapi)
* From UE4 forums:
  * **enzo_molinari** for the plugin icon
  * **adlord** for testing with wireless devices
