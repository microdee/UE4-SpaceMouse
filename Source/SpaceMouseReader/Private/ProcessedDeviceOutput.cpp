// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE


#include "ProcessedDeviceOutput.h"

FSmProcessedDeviceOutput FSmProcessedDeviceOutput::operator+(const FSmProcessedDeviceOutput& other) const
{
    return {
        Translation + other.Translation,
        Rotation + other.Rotation,
        Buttons | other.Buttons
    };
}

FSmProcessedDeviceOutput FSmProcessedDeviceOutput::operator+(TSharedPtr<FSmProcessedDeviceOutput> other) const
{
    return {
        Translation + other->Translation,
        Rotation + other->Rotation,
        Buttons | other->Buttons
    };
}

FSmProcessedDeviceOutput&& FSmProcessedDeviceOutput::operator+=(const FSmProcessedDeviceOutput& other)
{
    Translation += other.Translation;
    Rotation += other.Rotation;
    Buttons |= other.Buttons;
    return MoveTemp(*this);
}

FSmProcessedDeviceOutput&& FSmProcessedDeviceOutput::operator+=(TSharedPtr<FSmProcessedDeviceOutput> other)
{
    Translation += other->Translation;
    Rotation += other->Rotation;
    Buttons |= other->Buttons;
    return MoveTemp(*this);
}
