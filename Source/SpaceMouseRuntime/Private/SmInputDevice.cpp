// Fill out your copyright notice in the Description page of Project Settings.


#include "SmInputDevice.h"

#include "MovementState.h"
#include "SmRuntimeManager.h"
#include "SpaceMouseData.h"

#define LOCTEXT_NAMESPACE "SpaceMouseRuntime"

TSharedPtr<FSmRuntimeManager> FSmInputDevice::Manager;
TMap<FKey, EV3DCmd> FSmInputDevice::KeyToSmButtonMap;
    
FKey FSmInputDevice::TranslationX;
FKey FSmInputDevice::TranslationY;
FKey FSmInputDevice::TranslationZ;
    
FKey FSmInputDevice::RotationPitch;
FKey FSmInputDevice::RotationYaw;
FKey FSmInputDevice::RotationRoll;

FSmInputDevice::FSmInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
    : MessageHandler(InMessageHandler)
{
    Manager = MakeShared<FSmRuntimeManager>();
    Manager->Initialize();
    RegisterSmButtons();
}

FSmInputDevice::~FSmInputDevice()
{
}

#define SM_KEY_PREFIX "SpaceMouseUE_"
#define SM_KEY_PREFIX_TEXT TEXT(SM_KEY_PREFIX)

FKey FSmInputDevice::GetKeyFrom(EV3DCmd SmButton)
{
    static FString GlobalPrefix = SM_KEY_PREFIX_TEXT;
    return FKey(*(GlobalPrefix + FSmButton::GetNameOf(SmButton).ToString()));
}

EV3DCmd FSmInputDevice::GetButtonFrom(FKey InKey)
{
    if(KeyToSmButtonMap.Contains(InKey)) return KeyToSmButtonMap[InKey];
    return EV3DCmd::Noop;
}

FKeyDetails FSmInputDevice::GetKeyDetailsFrom(EV3DCmd SmButton)
{
    FString LongDispName = TEXT("SpaceMouse ") + FSmButton::GetFriendlyNameOf(SmButton);
    return FKeyDetails(
        GetKeyFrom(SmButton),
        FText::FromString(LongDispName),
        FKeyDetails::GamepadKey,
        TEXT("SpaceMouse"),
        FText::FromString(FSmButton::GetFriendlyNameOf(SmButton))
    );
}

#define SM_AXIS_DETAIL(InName, InAxis) \
    FKeyDetails( \
        FKey(SM_KEY_PREFIX_TEXT TEXT(InName) TEXT(InAxis)), \
        LOCTEXT("SmInputDevice_Axis_" InName InAxis, "SpaceMouse " InName " " InAxis), \
        FKeyDetails::GamepadKey | FKeyDetails::Axis1D, \
        TEXT("SpaceMouse") \
    )

void FSmInputDevice::RegisterSmButtons()
{
    // register menu category
    EKeys::AddMenuCategoryDisplayInfo(
        TEXT("SpaceMouse"),
        LOCTEXT("SmInputDevice_InputMenuCategoryName", "SpaceMouse"),
        TEXT("GraphEditor.KeyEvent_16x") // TODO: make our own palette icon?
    );

    // register axes
    auto TrX = SM_AXIS_DETAIL("Translation", "Lateral");
    auto TrY = SM_AXIS_DETAIL("Translation", "Horizontal");
    auto TrZ = SM_AXIS_DETAIL("Translation", "Vertical");
    TranslationX = TrX.GetKey();
    TranslationY = TrY.GetKey();
    TranslationZ = TrZ.GetKey();
    EKeys::AddKey(TrX);
    EKeys::AddKey(TrY);
    EKeys::AddKey(TrZ);
    
    auto RotP = SM_AXIS_DETAIL("Rotation", "Pitch");
    auto RotY = SM_AXIS_DETAIL("Rotation", "Yaw");
    auto RotR = SM_AXIS_DETAIL("Rotation", "Roll");
    RotationPitch = RotP.GetKey();
    RotationYaw = RotY.GetKey();
    RotationRoll = RotR.GetKey();
    EKeys::AddKey(RotP);
    EKeys::AddKey(RotY);
    EKeys::AddKey(RotR);

    // register buttons
    for(auto SmButton : FAllSmButtons())
    {
        auto OutKey = GetKeyDetailsFrom(SmButton);
        EKeys::AddKey(OutKey);
        KeyToSmButtonMap.Add(OutKey.GetKey(), SmButton);
    }
}

void FSmInputDevice::Tick(float DeltaTime)
{
}

void FSmInputDevice::SendControllerEvents()
{
    Manager->Tick(FApp::GetDeltaTime());

    MessageHandler->OnControllerAnalog(
        SM_KEY_PREFIX_TEXT TEXT("TranslationLateral"), 0,
        Manager->GetNormalizedTranslation().X
    );
    MessageHandler->OnControllerAnalog(
        SM_KEY_PREFIX_TEXT TEXT("TranslationHorizontal"), 0,
        Manager->GetNormalizedTranslation().Y
    );
    MessageHandler->OnControllerAnalog(
        SM_KEY_PREFIX_TEXT TEXT("TranslationVertical"), 0,
        Manager->GetNormalizedTranslation().Z
    );
    
    MessageHandler->OnControllerAnalog(
        SM_KEY_PREFIX_TEXT TEXT("RotationPitch"), 0,
        Manager->GetNormalizedRotation().Pitch
    );
    MessageHandler->OnControllerAnalog(
        SM_KEY_PREFIX_TEXT TEXT("RotationYaw"), 0,
        Manager->GetNormalizedRotation().Yaw
    );
    MessageHandler->OnControllerAnalog(
        SM_KEY_PREFIX_TEXT TEXT("RotationRoll"), 0,
        Manager->GetNormalizedRotation().Roll
    );

    for(int i=0; i<Manager->GetButtons().Num(); ++i)
    {
        auto SmButton = FSmButton::FromID(i);
        if(Manager->ButtonDownFrame(SmButton))
        {
            MessageHandler->OnControllerButtonPressed(GetKeyFrom(SmButton).GetFName(), 0, false);
        }
        if(Manager->ButtonUpFrame(SmButton))
        {
            MessageHandler->OnControllerButtonReleased(GetKeyFrom(SmButton).GetFName(), 0, false);
        }
    }
}

void FSmInputDevice::SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
{
    MessageHandler = InMessageHandler;
}

void FSmInputDevice::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{
}

void FSmInputDevice::SetChannelValues(int32 ControllerId, const FForceFeedbackValues& values)
{
}

bool FSmInputDevice::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
    return false;
}

#undef LOCTEXT_NAMESPACE
