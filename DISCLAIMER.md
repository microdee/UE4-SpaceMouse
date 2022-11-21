## Disclaimer about the relationship to the new official plugin provided by 3DConnexion

After I released this plugin to the marketplace it came to my knowledge that 3D connexion also released their own plugin for UE4 editor (dubbed `TDxUnrealEditor`). I have no affiliation with 3DConnexion and 3DConnexion of course were not involved in any way during the development of this plugin (SpaceMouse for UE). We had no knowledge about each other's work regarding the Unreal Engine implementation.

TDxUnrealEditor is installed automatically when you install or update the official drivers. Functionality-wise it matches this plugin. When both plugins are installed at the same time the behavior is undefined and I cannot guarantee that both would work as expected. Probably the simultaneous presence of both plugin would cause many interaction glitches. Here's how they compare to each-other:

| TDxUnrealEditor | SpaceMouse for UE |
| - | - |
| Not open-source, not even the UE4 specific part <sup>[1](#f1)</sup> | Fully open source, including the HID implementation (HIDAPI) |
| Full 3DxWare feature support <sup>[2](#f2)</sup> (obviously) | Doesn't know about 3DxWare |
| Unified control scheme for all apps implementing 3Dx Navlib | Custom navigation scheme requires Unreal specific configuration |
| It can control any 3D viewport in the editor | It can control any 3D viewport in the editor <sup>[3](#f3)</sup> |
| Better orbit/object mode implementation | Orbit/object mode is more barebones |
| Supports Windows and Mac | Supports Windows and Linux |
| Configurable via 3DxWare | Configurable from UE4 Editor Preferences |
| 3DxWare can bind Unreal Editor functions to buttons | SpaceMouse buttons are bindable to editor functions in Unreal |
| Speed is configurable via 3DxWare | Reads and modifies camera speed set for the viewport |
| No curvature or deadzone configuration <sup>[4](#f4)</sup> | Configure deadzone or curvature from Editor Preferences |
| Controls ortho viewports too? Maybe? | Controls ortho viewports too |
| They're working in piloting actors | Can pilot actors |
| Only functions in Editor | Functions both in Editor and Runtime via a BP node |

* This is not a complete list, and it might change with updates
* <a name="f1">1</a> because of this I couldn't compare implementation differences
* <a name="f2">2</a> This also allows you to sync your preferences accross multiple applications, SpaceMouse for UE obviously cannot provide or read that.
* <a name="f3">3</a> Including skeletal and static mesh editors, material preview, niagara editors, or really anything which provides a camera to control
* <a name="f4">4</a> Not to my knowledge anyway.
