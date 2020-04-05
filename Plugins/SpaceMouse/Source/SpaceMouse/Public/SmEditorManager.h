// Copyright 1998-2019 David Morasz All Rights Reserved.

#pragma once

#include "SpaceMouseManager.h"
#include "Misc/App.h"
#include "TimerManager.h"

class FEditorViewportClient;

class SPACEMOUSE_API FSmEditorManager : public FSpaceMouseManager
{
private:

	FTimerDelegate OnTickDel;

	bool bWasOrbitCamera = false;
	bool bWasRealtime = false;

	FEditorViewportClient* ActiveViewportClient = nullptr;
	FString focusedVpType = "";

	static bool UseForceSetView(FEditorViewportClient* cvp);

public:

	static bool bStarted;

	int LastErrorCode = 0;

	FSmEditorManager() : FSpaceMouseManager() { }

	virtual void Initialize() override
	{
		FSpaceMouseManager::Initialize();

		OnTickDel = OnTickDel.CreateLambda([this]()
		{
			Tick(FApp::GetDeltaTime());
		});
		bWasOrbitCamera = false;
		bWasRealtime = false;
	}

	virtual void Tick(float DeltaSecs) override;
	void Start();
	void ManageActiveViewport();
	void MoveActiveViewport(FVector trans, FRotator rot);
	const bool IsActiveViewportInvalid(const TArray<FEditorViewportClient*>& AllViewportClients);
};
