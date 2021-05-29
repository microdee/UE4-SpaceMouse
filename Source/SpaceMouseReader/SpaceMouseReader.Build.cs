// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

using UnrealBuildTool;
using System.IO;

public class SpaceMouseReader : ModuleRules
{
    public SpaceMouseReader(ReadOnlyTargetRules Target) : base(Target)
    {
        PrecompileForTargets = PrecompileTargetsType.Any;
        PCHUsage = ModuleRules.PCHUsageMode.NoSharedPCHs;
        bEnableUndefinedIdentifierWarnings = false;
        CppStandard = CppStandardVersion.Cpp17;

        PublicDependencyModuleNames.AddRange(new []
        {
            "Core",
            "CoreUObject",
            "Engine",

            "HIDUE"
            // ... add other public dependencies that you statically link with here ...
        });
        
        var TDxWareDir = Path.Combine(PluginDirectory, "Source", "ThirdParty", "3DxWareSDK", Target.Platform.ToString());
        if(File.Exists(Path.Combine(TDxWareDir, "inc", "navlib", "navlib.h")))
        {
            PublicDefinitions.Add("WITH_3DX_NAVLIB=1");
            PublicSystemIncludePaths.Add(Path.Combine(TDxWareDir, "inc"));
            PublicAdditionalLibraries.AddRange(new []
            {
                Path.Combine(TDxWareDir, "lib", "x64", "TDxNavLib.lib")
            });
        }
        else
        {
            PublicDefinitions.Add("WITH_3DX_NAVLIB=0");
        }
    }
}
    
