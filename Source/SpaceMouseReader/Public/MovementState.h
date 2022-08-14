// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"

DECLARE_MULTICAST_DELEGATE(FSmMovementEvent)

/**
 * Class storing movement state of a SpaceMouse device
 */
class SPACEMOUSEREADER_API FSmMovementState
{
public:
    FSmMovementState();
    ~FSmMovementState();

    FSmMovementEvent OnMovementStarted;
    FSmMovementEvent OnMovementEnded;
    
    bool bOnMovementStartedFrame = false;
    bool bOnMovementEndedFrame = false;
    bool bMoving = false;

    void Move();
    void PreTick();
    void Tick(float MovementTimeTolerance, float DeltaSeconds);
    void AccumulationReset();
    void Accumulate(const FSmMovementState& Other);
    void Accumulate(TSharedPtr<FSmMovementState> Other);
    
private:
    bool bPrevMoving = false;
    float MovementTimed = 0.0f;
    
};
