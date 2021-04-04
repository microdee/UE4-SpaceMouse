// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#include "SpaceMouseConfig.h"
#include "SmInputDevice.h"

// Add default functionality here for any ISpaceMouseConfig functions that are not pure virtual.
USpaceMouseConfig::USpaceMouseConfig(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    TranslationCurve.GetRichCurve()->AddKey(0.0, 0.0);
    TranslationCurve.GetRichCurve()->AddKey(1.0, 1.0);
    RotationCurve.GetRichCurve()->AddKey(0.0, 0.0);
    RotationCurve.GetRichCurve()->AddKey(1.0, 1.0);

    IncreaseSpeedButton = FSmInputDevice::GetKeyFrom(EV3DCmd::KeyF2);
    DecreaseSpeedButton = FSmInputDevice::GetKeyFrom(EV3DCmd::KeyF1);
    ResetSpeedButton = FSmInputDevice::GetKeyFrom(EV3DCmd::KeyF3);
    ResetRollButton = FSmInputDevice::GetKeyFrom(EV3DCmd::FilterRotate);
}

FUserSettings USpaceMouseConfig::GetUserSettings()
{
    return
    {
        DisplayDebugInformation,
        MaxHidReadOperationsPerFrame,
        MovementSecondsTolerance,
        {
            XTranslationAxisMap,
            YTranslationAxisMap,
            ZTranslationAxisMap,
            TranslationUnitsPerSec,
            TranslationCurve.GetRichCurve()
        },
        {
            PitchAxisMap,
            YawAxisMap,
            RollAxisMap,
            RotationDegreesPerSec,
            RotationCurve.GetRichCurve()
        }
    };
}
