// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcessedDeviceOutput.h"

FProcessedDeviceOutput FProcessedDeviceOutput::operator+(const FProcessedDeviceOutput& other)
{
    return {
        Translation + other.Translation,
        Rotation + other.Rotation,
        Buttons | other.Buttons
    };
}
