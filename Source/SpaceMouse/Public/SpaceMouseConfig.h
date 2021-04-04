// Copyright 2018-2020 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UserSettings.h"
#include "Curves/CurveFloat.h"
#include "GameFramework/PlayerInput.h"

#include "SpaceMouseConfig.generated.h"

UENUM()
enum class ESpaceMouseCameraBehavior : uint8
{
    CameraDeltaWithRoll,
    CameraDeltaNoRoll,
    OrbittingWithRoll,
    OrbittingNoRoll
};

USTRUCT(BlueprintType)
struct FSpaceMouseKeyMapping
{
    GENERATED_BODY()
    
    UPROPERTY(
        EditAnywhere,
        Config,
        Category = "ButtonMapping",
        meta = (
            ToolTip = "Only SpaceMouse buttons regarded here."
        )
    )
    FKey SpaceMouseButton;

    UPROPERTY(EditAnywhere, Config, Category = "ButtonMapping")
    FInputActionKeyMapping TargetKey;
};

UCLASS(Config=Editor, defaultconfig)
class USpaceMouseConfig : public UObject
{
    GENERATED_BODY()
public:
    USpaceMouseConfig(const FObjectInitializer& ObjectInitializer);

    FUserSettings GetUserSettings();

    UPROPERTY(EditAnywhere, Config, Category = "Behavior")
    bool ActiveInBackground = false;

    UPROPERTY(EditAnywhere, Config, Category = "Behavior")
    ESpaceMouseCameraBehavior CameraBehavior = ESpaceMouseCameraBehavior::CameraDeltaWithRoll;

    UPROPERTY(EditAnywhere, Config, Category = "Behavior")
    bool OrbittingMovesObject = false;

    UPROPERTY(EditAnywhere, Config, Category = "Behavior")
    bool OrbittingRotatesObject = false;

    UPROPERTY(EditAnywhere, Config, Category = "Behavior")
    float MovementSecondsTolerance = 0.25;
    
    UPROPERTY(EditAnywhere, Config, Category = "Behavior")
    float OrbitingLineTraceLength = 200000; // 2 Km

    UPROPERTY(EditAnywhere, Config, Category = "Rotation")
    float RotationDegreesPerSec = 270;

    UPROPERTY(EditAnywhere, Config, Category = "Translation")
    float TranslationUnitsPerSec = 1000;

    UPROPERTY(EditAnywhere, Config, Category = "Translation")
    FVector XTranslationAxisMap = FVector(0, -1, 0);

    UPROPERTY(EditAnywhere, Config, Category = "Translation")
    FVector YTranslationAxisMap = FVector(1, 0, 0);

    UPROPERTY(EditAnywhere, Config, Category = "Translation")
    FVector ZTranslationAxisMap = FVector(0, 0, -1);

    UPROPERTY(
        config,
        EditAnywhere,
        Category = "Translation",
        meta = (
            XAxisName = "Push/Pull",
            YAxisName = "Scale"
        )
    )
    FRuntimeFloatCurve TranslationCurve;

    UPROPERTY(EditAnywhere, Config, Category = "Rotation")
    FVector PitchAxisMap = FVector(1, 0, 0);

    UPROPERTY(EditAnywhere, Config, Category = "Rotation")
    FVector YawAxisMap = FVector(0, 0, 1);

    UPROPERTY(EditAnywhere, Config, Category = "Rotation")
    FVector RollAxisMap = FVector(0, -1, 0);

    UPROPERTY(
        config,
        EditAnywhere,
        Category = "Rotation",
        meta = (
            XAxisName = "Push/Pull",
            YAxisName = "Scale"
        )
    )
    FRuntimeFloatCurve RotationCurve;

    UPROPERTY(EditAnywhere, Config, Category = HID)
    int MaxHidReadOperationsPerFrame = 2048;

    UPROPERTY(EditAnywhere, Config, Category = HID)
    bool DisplayDebugInformation = false;

    UPROPERTY(
        EditAnywhere,
        Config,
        Category = "ButtonMapping",
        meta = (
            ToolTip = "Only SpaceMouse buttons regarded here."
        )
    )
    FKey IncreaseSpeedButton;

    UPROPERTY(
        EditAnywhere,
        Config,
        Category = "ButtonMapping",
        meta = (
            ToolTip = "Only SpaceMouse buttons regarded here."
        )
    )
    FKey DecreaseSpeedButton;

    UPROPERTY(
        EditAnywhere,
        Config,
        Category = "ButtonMapping",
        meta = (
            ToolTip = "Only SpaceMouse buttons regarded here."
        )
    )
    FKey ResetSpeedButton;

    UPROPERTY(
        EditAnywhere,
        Config,
        Category = "ButtonMapping",
        meta = (
            ToolTip = "Only SpaceMouse buttons regarded here."
        )
    )
    FKey ResetRollButton;

    UPROPERTY(EditAnywhere, Config, Category = "ButtonMapping")
    TArray<FSpaceMouseKeyMapping> CustomKeyMappings;
};
