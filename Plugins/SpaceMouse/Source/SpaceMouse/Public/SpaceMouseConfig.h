// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpaceMouseConfig.generated.h"

UCLASS(Config=Editor, defaultconfig)
class USpaceMouseConfig : public UObject
{
	GENERATED_BODY()
public:
	USpaceMouseConfig(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Config, Category = Rotation)
		float RotationDegreesPerSec = 270;

	UPROPERTY(EditAnywhere, Config, Category = Translation)
		float TranslationUnitsPerSec = 1000;

	UPROPERTY(EditAnywhere, Config, Category = Translation)
		FVector XTranslationAxisMap = FVector(0, -1, 0);

	UPROPERTY(EditAnywhere, Config, Category = Translation)
		FVector YTranslationAxisMap = FVector(1, 0, 0);

	UPROPERTY(EditAnywhere, Config, Category = Translation)
		FVector ZTranslationAxisMap = FVector(0, 0, -1);

	UPROPERTY(EditAnywhere, Config, Category = Rotation)
		FVector PitchAxisMap = FVector(1, 0, 0);

	UPROPERTY(EditAnywhere, Config, Category = Rotation)
		FVector YawAxisMap = FVector(0, 0, 1);

	UPROPERTY(EditAnywhere, Config, Category = Rotation)
		FVector RollAxisMap = FVector(0, -1, 0);

	UPROPERTY(EditAnywhere, Config, Category = HID)
		int MaxHidReadOperationsPerFrame = 2048;

	UPROPERTY(EditAnywhere, Config, Category = HID)
		bool DisplayDebugInformation = false;
};
