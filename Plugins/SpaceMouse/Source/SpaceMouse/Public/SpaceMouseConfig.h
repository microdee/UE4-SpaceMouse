// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Curves/CurveFloat.h"

#include "SpaceMouseConfig.generated.h"

UENUM()
enum class ESpaceMouseCameraBehavior : uint8
{
	CameraDeltaWithRoll,
	CameraDeltaNoRoll,
	OrbittingWithRoll,
	OrbittingNoRoll
};

UCLASS(Config=Editor, defaultconfig)
class USpaceMouseConfig : public UObject
{
	GENERATED_BODY()
public:
	USpaceMouseConfig(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Config, Category = "Behavior")
		bool ActiveInBackground = false;

	UPROPERTY(EditAnywhere, Config, Category = "Behavior")
		ESpaceMouseCameraBehavior CameraBehavior = ESpaceMouseCameraBehavior::CameraDeltaWithRoll;

	UPROPERTY(EditAnywhere, Config, Category = "Behavior")
		bool OrbittingMovesObject = false;

	UPROPERTY(EditAnywhere, Config, Category = "Behavior")
		bool OrbittingRotatesObject = false;

	UPROPERTY(EditAnywhere, Config, Category = "Behavior", meta = (InlineEditConditionToggle))
		bool OrbittingAtFixedPivot = false;

	UPROPERTY(EditAnywhere, Config, Category = "Behavior", meta = (EditCondition = "OrbittingAtFixedPivot"))
		float OrbittingAtFixedPivotDistance = 300;
	
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

	UPROPERTY(config, EditAnywhere, Category = "Translation", meta = (
		XAxisName = "Push/Pull",
		YAxisName = "Scale"))
		FRuntimeFloatCurve TranslationCurve;

	UPROPERTY(EditAnywhere, Config, Category = "Rotation")
		FVector PitchAxisMap = FVector(1, 0, 0);

	UPROPERTY(EditAnywhere, Config, Category = "Rotation")
		FVector YawAxisMap = FVector(0, 0, 1);

	UPROPERTY(EditAnywhere, Config, Category = "Rotation")
		FVector RollAxisMap = FVector(0, -1, 0);

	UPROPERTY(config, EditAnywhere, Category = "Rotation", meta = (
		XAxisName = "Push/Pull",
		YAxisName = "Scale"))
		FRuntimeFloatCurve RotationCurve;

	UPROPERTY(EditAnywhere, Config, Category = HID)
		int MaxHidReadOperationsPerFrame = 2048;

	UPROPERTY(EditAnywhere, Config, Category = HID)
		bool DisplayDebugInformation = false;

	UPROPERTY(EditAnywhere, Category = "ButtonMapping", meta = (InlineEditConditionToggle))
		bool LearnIncreaseSpeed = false;

	UPROPERTY(EditAnywhere, Config, Category = "ButtonMapping", meta = (EditCondition = "LearnIncreaseSpeed", ToolTip = "Press button to map when enabled."))
		int IncreaseSpeedButtonID = 1;

	UPROPERTY(EditAnywhere, Category = "ButtonMapping", meta = (InlineEditConditionToggle))
		bool LearnDecreaseSpeed = false;

	UPROPERTY(EditAnywhere, Config, Category = "ButtonMapping", meta = (EditCondition = "LearnDecreaseSpeed", ToolTip = "Press button to map when enabled."))
		int DecreaseSpeedButtonID = 0;

	UPROPERTY(EditAnywhere, Category = "ButtonMapping", meta = (InlineEditConditionToggle))
		bool LearnResetSpeed = false;

	UPROPERTY(EditAnywhere, Config, Category = "ButtonMapping", meta = (EditCondition = "LearnResetSpeed", ToolTip = "Press button to map when enabled."))
		int ResetSpeedButtonID = 2;

	UPROPERTY(EditAnywhere, Category = "ButtonMapping", meta = (InlineEditConditionToggle))
		bool LearnResetRoll = false;

	UPROPERTY(EditAnywhere, Config, Category = "ButtonMapping", meta = (EditCondition = "LearnResetRoll", ToolTip = "Press button to map when enabled."))
		int ResetRollButtonID = 3;
};
