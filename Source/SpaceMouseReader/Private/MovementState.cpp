// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE


#include "MovementState.h"


FSmMovementState::FSmMovementState()
{
}

FSmMovementState::~FSmMovementState()
{
}

void FSmMovementState::Move()
{
    bMoving = true;
}

void FSmMovementState::PreTick()
{
    bPrevMoving = MovementTimed > 0;
    bMoving = false;
}

void FSmMovementState::Tick(float MovementTimeTolerance, float DeltaSeconds)
{
    if(bMoving) MovementTimed = MovementTimeTolerance;
    
    bOnMovementStartedFrame = MovementTimed > 0 && !bPrevMoving;
    if(bOnMovementStartedFrame) OnMovementStarted.Broadcast();
    
    MovementTimed -= DeltaSeconds;
    
    bOnMovementEndedFrame = MovementTimed <= 0 && bPrevMoving;
    if(bOnMovementEndedFrame) OnMovementEnded.Broadcast();
}

void FSmMovementState::AccumulationReset()
{
    bOnMovementStartedFrame = false;
    bOnMovementEndedFrame = false;
    bMoving = false;
}

void FSmMovementState::Accumulate(const FSmMovementState& Other)
{
    bMoving |= Other.bMoving;
    bOnMovementStartedFrame |= Other.bOnMovementStartedFrame;
    bOnMovementEndedFrame |= Other.bOnMovementEndedFrame;
    
    if(bOnMovementStartedFrame) OnMovementStarted.Broadcast();
    if(bOnMovementEndedFrame) OnMovementEnded.Broadcast();
}

void FSmMovementState::Accumulate(TSharedPtr<FSmMovementState> Other)
{
    Accumulate(*Other.Get());
}
