// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#include "SpaceMouseConfig.h"

// Add default functionality here for any ISpaceMouseConfig functions that are not pure virtual.
USpaceMouseConfig::USpaceMouseConfig(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    TranslationCurve.GetRichCurve()->AddKey(0.0, 0.0);
    TranslationCurve.GetRichCurve()->AddKey(1.0, 1.0);
    RotationCurve.GetRichCurve()->AddKey(0.0, 0.0);
    RotationCurve.GetRichCurve()->AddKey(1.0, 1.0);
}
