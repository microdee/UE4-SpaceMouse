// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceMouseData.h"
#include "Engine/World.h"

bool USpaceMouseData::bFrameRequested = false;

FTimerDelegate USpaceMouseData::OnTickDel;
FSpaceMouseManager USpaceMouseData::Manager;

void USpaceMouseData::GetSpaceMouseData(UObject* WorldContextObj, FVector& DeltaTranslation, FRotator& DeltaRotation, TArray<bool>& Buttons)
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

	DeltaTranslation = Manager.GetTranslation();
	DeltaRotation = Manager.GetRotation();
	Buttons = Manager.GetButtons();
}
