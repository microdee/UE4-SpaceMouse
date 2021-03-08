// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementState.h"


FMovementState::FMovementState()
{
}

FMovementState::~FMovementState()
{
}

void FMovementState::Move()
{
    bMoving = true;
}

void FMovementState::PreTick()
{
    bPrevMoving = MovementTimed > 0;
    bMoving = false;
}

void FMovementState::Tick(float MovementTimeTolerance, float DeltaSeconds)
{
    if(bMoving) MovementTimed = MovementTimeTolerance;
    
    bOnMovementStartedFrame = MovementTimed > 0 && !bPrevMoving;
    if(bOnMovementStartedFrame) OnMovementStarted.Broadcast();
    
    MovementTimed -= DeltaSeconds;
    
    bOnMovementEndedFrame = MovementTimed <= 0 && bPrevMoving;
    if(bOnMovementEndedFrame) OnMovementEnded.Broadcast();
}

void FMovementState::AccumulationReset()
{
    bOnMovementStartedFrame = false;
    bOnMovementEndedFrame = false;
    bMoving = false;
}

void FMovementState::Accumulate(const FMovementState& Other)
{
    bMoving |= Other.bMoving;
    bOnMovementStartedFrame |= Other.bOnMovementStartedFrame;
    bOnMovementEndedFrame |= Other.bOnMovementEndedFrame;
    
    if(bOnMovementStartedFrame) OnMovementStarted.Broadcast();
    if(bOnMovementEndedFrame) OnMovementEnded.Broadcast();
}
