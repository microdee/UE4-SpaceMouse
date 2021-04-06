// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInputDevice.h"
#include "Buttons.h"
#include "InputCoreTypes.h"

class FGenericApplicationMessageHandler;
class FSmRuntimeManager;

/**
 * 
 */
class SPACEMOUSERUNTIME_API FSmInputDevice : public IInputDevice
{
public:
    static TSharedPtr<FSmRuntimeManager> Manager;
    static TMap<FKey, EV3DCmd> KeyToSmButtonMap;
    
    static FKey TranslationX;
    static FKey TranslationY;
    static FKey TranslationZ;
    
    static FKey RotationPitch;
    static FKey RotationYaw;
    static FKey RotationRoll;
    
    FSmInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler);
    ~FSmInputDevice();

    static FKey GetKeyFrom(EV3DCmd SmButton);
    static EV3DCmd GetButtonFrom(FKey InKey);
    static FKeyDetails GetKeyDetailsFrom(EV3DCmd SmButton);
    static void RegisterSmButtons();
    
    virtual void Tick(float DeltaTime) override;
    virtual void SendControllerEvents() override;
    virtual void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;
    virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;
    virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues &values) override;
    virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;
    
private:
    /* Message handler */
    TSharedRef<FGenericApplicationMessageHandler> MessageHandler;
};
