// Copyright 1998-2019 David Morasz All Rights Reserved.


#include "SpaceMouseConfig.h"

// Add default functionality here for any ISpaceMouseConfig functions that are not pure virtual.
USpaceMouseConfig::USpaceMouseConfig(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TranslationCurve.GetRichCurve()->AddKey(0.0, 0.0);
	TranslationCurve.GetRichCurve()->AddKey(1.0, 1.0);
	RotationCurve.GetRichCurve()->AddKey(0.0, 0.0);
	RotationCurve.GetRichCurve()->AddKey(1.0, 1.0);
}
