// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_MULTICAST_DELEGATE(FMovementEvent)

/**
 * Class storing movement state of a SpaceMouse device
 */
class SPACEMOUSEREADER_API FMovementState
{
public:
    FMovementState();
    ~FMovementState();

    FMovementEvent OnMovementStarted;
    FMovementEvent OnMovementEnded;
    
    bool bOnMovementStartedFrame = false;
    bool bOnMovementEndedFrame = false;
    bool bMoving = false;

    void Move();
    void PreTick();
    void Tick(float MovementTimeTolerance, float DeltaSeconds);
    
private:
    bool bPrevMoving = false;
    float MovementTimed = 0.0f;
    
};
