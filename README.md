## SpaceMouse camera controller for UE4 editor viewports

**Compatible with UE 4.22 and probably below**  
# [DOWNLOAD](https://github.com/microdee/UE4-SpaceMouse/releases/latest)

Demo video: https://youtu.be/Qibig0gQWvE

You can control any 3D editor viewport currently in focus (user clicked on it). Controls are 6DOF flying camera movement type, no orbit type yet. See the picture for the default transition and rotation axis (although you can change it in Editor Preferences):

![Alt text](/ReadmeMedia/coordinates.jpg?raw=true "Coordinates")

Transition speed is controllable via the camera speed setting and the camera speed scalar of the viewport. Button 0 and 1 can be also used to decrease or increase the camera speed setting. Multiple devices are supported however their data is merged together into a global context.

On default speeds (speed setting = 4) transition velocity is 1000 units/sec and rotation speed is 270°/sec. Rotation speed is not affected by camera speed settings. You can change these in the **Editor Preference** under SpaceMouse section.

![Alt text](/ReadmeMedia/settings.png?raw=true "Coordinates")

**Axis mappings** are conversions between the space of spacemice and the space of UE4. You can invert rotations and translations here by flipping the sign. The default values are my subjective preferences (as you can see in the coordinate system image above). **Display Debug Information** prints HID data onto the viewport. You don't need to change **Max Hid Read Operations Per Frame**. Just ignore it.

This plugin works with the HID device directly so no 3DxWare service is needed to run (similar how Blender does it). And I highly recommend to disable said service because it's a big pile of steaming hot garbage imo. You might still need to install 3DxWare for drivers. However it shouldn't interfere with a running 3DxWare service in case you need it for other less fortunate programs.

[Discussion at UE4 forum](https://forums.unrealengine.com/unreal-engine/feedback-for-epic/437-support-for-space-navigator-3d-mouse?p=1609440#post1609440)

## Would be nice to have:

* Add ability to remap buttons to different actions, so one can potentially use all the buttons on their SpaceMouse Pro
* Add feature to lock camera roll.
* Add Orbit mode (and figure out how to solve its interaction with the world) (probably ain't gonna happen)

## Known issues:

* ~~Upon exiting the editor the engine crashes. I know why it does that but I didn't figure it out quite yet how to prevent it.~~  
  FIXED
* Only free-fly mode is supported and every orbitting perspective viewport in focus is forced to be free-fly while any spacemice operates on them.
