// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#include "SpaceMouseData.h"

#include "SmRuntimeManager.h"
#include "SmInputDevice.h"
#include "Engine/World.h"

bool USpaceMouseData::bFrameRequested = false;

FTimerDelegate USpaceMouseData::OnTickDel;

void USpaceMouseData::GetSpaceMouseDeltaAxes(FVector& DeltaTranslation, FRotator& DeltaRotation)
{
    DeltaTranslation = FSmInputDevice::Manager->GetTranslation();
    DeltaRotation = FSmInputDevice::Manager->GetRotation();
}

void USpaceMouseData::GetSpaceMouseAxes(FVector& NormalizedTranslation,
    FRotator& NormalizedRotation)
{
    
    NormalizedTranslation = FSmInputDevice::Manager->GetNormalizedTranslation();
    NormalizedRotation = FSmInputDevice::Manager->GetNormalizedRotation();
}

bool USpaceMouseData::GetSpaceMouseButtonState(int Id)
{
    return FSmInputDevice::Manager->GetButtons()[Id];
}

bool USpaceMouseData::GetSpaceMouseButtonDown(int Id)
{
    return FSmInputDevice::Manager->ButtonDownFrame(FSmButton::FromID(Id));
}

bool USpaceMouseData::GetSpaceMouseButtonUp(int Id)
{
    return FSmInputDevice::Manager->ButtonUpFrame(FSmButton::FromID(Id));
}
