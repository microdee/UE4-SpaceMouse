// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#include "SpaceMouseData.h"
#include "Engine/World.h"

bool USpaceMouseData::bFrameRequested = false;

FTimerDelegate USpaceMouseData::OnTickDel;
FSmRuntimeManager USpaceMouseData::Manager;

void USpaceMouseData::LazyInit(UObject* WorldContextObj)
{
    if (!bFrameRequested)
    {
        OnTickDel = OnTickDel.CreateLambda([WorldContextObj]()
        {
            if (!bFrameRequested) return;
            USpaceMouseData::Manager.Tick(FApp::GetDeltaTime());
            USpaceMouseData::bFrameRequested = false;
        });
        //Manager.Initialize();

        USpaceMouseData::bFrameRequested = true;
        WorldContextObj->GetWorld()->GetTimerManager().SetTimerForNextTick(USpaceMouseData::OnTickDel);
    }
}

void USpaceMouseData::GetSpaceMouseAxes(UObject* WorldContextObj, FVector& DeltaTranslation, FRotator& DeltaRotation)
{
    LazyInit(WorldContextObj);

    DeltaTranslation = Manager.GetTranslation();
    DeltaRotation = Manager.GetRotation();
}

bool USpaceMouseData::GetSpaceMouseButtonState(UObject* WorldContextObj, int Id)
{
    LazyInit(WorldContextObj);
    return Manager.GetButtons()[Id];
}

bool USpaceMouseData::GetSpaceMouseButtonDown(UObject* WorldContextObj, int Id)
{
    LazyInit(WorldContextObj);
    return Manager.ButtonDownFrame(FSmButton::FromID(Id));
}

bool USpaceMouseData::GetSpaceMouseButtonUp(UObject* WorldContextObj, int Id)
{
    LazyInit(WorldContextObj);
    return Manager.ButtonUpFrame(FSmButton::FromID(Id));
}
