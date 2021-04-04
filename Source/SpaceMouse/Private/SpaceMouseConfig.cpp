// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#include "SpaceMouseConfig.h"


#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "ISettingsModule.h"
#include "SmInputDevice.h"
#include "Modules/ModuleManager.h"
#include "Widgets/Input/SRichTextHyperlink.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "USpaceMouseConfig"

// Add default functionality here for any ISpaceMouseConfig functions that are not pure virtual.
USpaceMouseConfig::USpaceMouseConfig(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    TranslationCurve.GetRichCurve()->AddKey(0.0, 0.0);
    TranslationCurve.GetRichCurve()->AddKey(1.0, 1.0);
    RotationCurve.GetRichCurve()->AddKey(0.0, 0.0);
    RotationCurve.GetRichCurve()->AddKey(1.0, 1.0);

    IncreaseSpeedButton = FSmInputDevice::GetKeyFrom(EV3DCmd::KeyF2);
    DecreaseSpeedButton = FSmInputDevice::GetKeyFrom(EV3DCmd::KeyF1);
    ResetSpeedButton = FSmInputDevice::GetKeyFrom(EV3DCmd::KeyF3);
    ResetRollButton = FSmInputDevice::GetKeyFrom(EV3DCmd::FilterRotate);
}

FUserSettings USpaceMouseConfig::GetUserSettings()
{
    return
    {
        DisplayDebugInformation,
        MaxHidReadOperationsPerFrame,
        MovementSecondsTolerance,
        {
            XTranslationAxisMap,
            YTranslationAxisMap,
            ZTranslationAxisMap,
            TranslationUnitsPerSec,
            TranslationCurve.GetRichCurve()
        },
        {
            PitchAxisMap,
            YawAxisMap,
            RollAxisMap,
            RotationDegreesPerSec,
            RotationCurve.GetRichCurve()
        }
    };
}

TSharedRef<IDetailCustomization> FSpaceMouseConfigCustomization::MakeInstance()
{
    return MakeShared<FSpaceMouseConfigCustomization>();
}

void FSpaceMouseConfigCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
    auto PropertyInButtonMapping = DetailBuilder.GetProperty(
        GET_MEMBER_NAME_CHECKED(USpaceMouseConfig, ResetRollButton)
    );
    DetailBuilder.AddCustomRowToCategory(
        PropertyInButtonMapping,
        LOCTEXT("SmConfig_ButtonBindingNotice", "Button Binding Notice")
    )
    . WholeRowContent()
    [
        SNew(SVerticalBox)
        + SVerticalBox::Slot()
        . AutoHeight()
        . HAlign(EHorizontalAlignment::HAlign_Left)
        . VAlign(EVerticalAlignment::VAlign_Top)
        . Padding(0, 20, 0, 5)
        [
            SNew(STextBlock)
            . Text(LOCTEXT(
                "SmConfig_ButtonBindingNotice_Text",
                "Button bindings are now configurable via the 'Keyboard Shortcuts' section in Editor Preferences.\n"
                "When setting an action mapping, just press the desired button on your device to bind it to the selected action."
            ))
        ]
        + SVerticalBox::Slot()
        . AutoHeight()
        . HAlign(EHorizontalAlignment::HAlign_Left)
        . VAlign(EVerticalAlignment::VAlign_Bottom)
        . Padding(0, 0, 0, 20)
        [
            SNew(SHyperlink)
            . OnNavigate(FSimpleDelegate::CreateLambda([]()
            {
                ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
                SettingsModule->ShowViewer("Editor", "General", "InputBindings");
            }))
            . Text(LOCTEXT(
                "SmConfig_GoToKeyboardShortcuts",
                "Go to Keyboard Shortcuts"
            ))
        ]
    ];
}

#undef LOCTEXT_NAMESPACE