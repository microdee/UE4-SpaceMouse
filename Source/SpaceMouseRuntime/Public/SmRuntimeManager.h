// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

#include "SpaceMouseManager.h"
#include "SmUserSettings.h"

class SPACEMOUSERUNTIME_API FSmRuntimeManager : public FSpaceMouseManager
{
protected:

    virtual FSmUserSettings GetUserSettings() override;
};
