## SpaceMouse camera controller for UE4 editor viewports

**Compatible with UE 4.22 and probably below**  
**Download plugin from releases**

Demo video: https://youtu.be/Qibig0gQWvE

You can control any 3D editor viewport currently in focus (user clicked on it). Controls are 6DOF camera movement type, no orbit type yet. See the picture for the transition and rotation axis:

![Alt text](/ReadmeMedia/coordinates.jpg?raw=true "Coordinates")

Transition speed is controllable via the camera speed setting and the camera speed scalar of the viewport. Button 0 and 1 can be also used to decrease or increase the camera speed setting. Multiple devices are supported however their data is merged together into a global context.

On default speeds (speed setting = 4) transition velocity is 1000 units/sec and rotation speed is 180°/sec. Rotation speed is not affected by camera speed settings. These are currently hard coded, I'm planning to make these into plugin settings.

This plugin works with the HID device directly so no 3DxWare service is needed to run (similar how Blender does it). And I highly recommend to disable said service because it's a big pile of steaming hot garbage imo. You might still need to install 3DxWare for drivers. However it shouldn't interfere with a running 3DxWare service in case you need it for other less fortunate programs.

## Known issues:

* Upon exiting the editor the engine crashes. I know why it does that but I didn't figure it out quite yet how to prevent it.
