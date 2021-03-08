// Fill out your copyright notice in the Description page of Project Settings.


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
