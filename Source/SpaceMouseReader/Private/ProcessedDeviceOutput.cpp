// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE


#include "ProcessedDeviceOutput.h"

FProcessedDeviceOutput FProcessedDeviceOutput::operator+(const FProcessedDeviceOutput& other) const
{
    return {
        Translation + other.Translation,
        Rotation + other.Rotation,
        Buttons | other.Buttons
    };
}

FProcessedDeviceOutput FProcessedDeviceOutput::operator+(TSharedPtr<FProcessedDeviceOutput> other) const
{
    return {
        Translation + other->Translation,
        Rotation + other->Rotation,
        Buttons | other->Buttons
    };
}

FProcessedDeviceOutput&& FProcessedDeviceOutput::operator+=(const FProcessedDeviceOutput& other)
{
    Translation += other.Translation;
    Rotation += other.Rotation;
    Buttons |= other.Buttons;
    return MoveTemp(*this);
}

FProcessedDeviceOutput&& FProcessedDeviceOutput::operator+=(TSharedPtr<FProcessedDeviceOutput> other)
{
    Translation += other->Translation;
    Rotation += other->Rotation;
    Buttons |= other->Buttons;
    return MoveTemp(*this);
}
