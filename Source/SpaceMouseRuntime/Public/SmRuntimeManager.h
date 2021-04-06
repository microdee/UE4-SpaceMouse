// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SpaceMouseManager.h"
#include "UserSettings.h"

class SPACEMOUSERUNTIME_API FSmRuntimeManager : public FSpaceMouseManager
{
protected:

    virtual FUserSettings GetUserSettings() override;
};
