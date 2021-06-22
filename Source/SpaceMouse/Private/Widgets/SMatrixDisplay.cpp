// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SMatrixDisplay.h"

#include "SlateOptMacros.h"
#include "Brushes/SlateColorBrush.h"
#include "Components/VerticalBox.h"
#include "Widgets/Input/SVectorInputBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SGridPanel.h"
#include "Widgets/Text/STextBlock.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

FText SMatrixDisplay::FormatFloat(float $)
{
    return FText::FromString(
        FString::Printf(TEXT("%.2f"), $)
    );
}

FText SMatrixDisplay::FormatMatrixComp(const FArguments& InArgs, int Row, int Col)
{
    return FormatFloat(InArgs._InMatrix.Get().M[Row][Col]);
}

#define LOCTEXT_NAMESPACE "MatrixDisplay"

void SMatrixDisplay::Construct(const FArguments& InArgs)
{
    PersistArgs = InArgs;

    auto GetPosition = [=]
    {
        return FTransform(
            InArgs._InMatrix.Get()
        ).GetLocation();
    };

    auto GetRotation = [=]
    {
        return FTransform(
            InArgs._InMatrix.Get()
        ).GetRotation().Rotator();
    };

    BackgroundBrush = MakeShared<FSlateColorBrush>(
        FLinearColor(0.3f, 0.3f, 0.3f, 0.6f)
    );
    
    ChildSlot
    [
        SNew(SBorder)
        . Padding(3)
        . BorderImage(BackgroundBrush.Get())
        . BorderBackgroundColor(FSlateColor({0.3f, 0.3f, 0.3f, 0.8f}))
        [
            SNew(SVerticalBox)
            + SVerticalBox::Slot() // Label
            . AutoHeight()
            [
                SNew(STextBlock)
                . SimpleTextMode(true)
                . ColorAndOpacity(FLinearColor::White)
                . Text(InArgs._Label)
            ]
            + SVerticalBox::Slot() // Matrix grid
            . AutoHeight()
            [
                SAssignNew(MainGrid, SGridPanel)
            ]
            + SVerticalBox::Slot() // Position
            . AutoHeight()
            [
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot()
                [
                    SNew(SVectorInputBox)
                    . X_Lambda([=]{ return GetPosition().X; })
                    . Y_Lambda([=]{ return GetPosition().Y; })
                    . Z_Lambda([=]{ return GetPosition().Z; })
                ]
                + SHorizontalBox::Slot()
                [
                    SNew(STextBlock)
                    . SimpleTextMode(true)
                    . ColorAndOpacity(FLinearColor::White)
                    . Text(LOCTEXT("PositionLabel", "Position"))
                ]
            ]
            + SVerticalBox::Slot() // Rotation
            . AutoHeight()
            [
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot()
                [
                    SNew(SVectorInputBox)
                    . X_Lambda([=]{ return GetRotation().Pitch; })
                    . Y_Lambda([=]{ return GetRotation().Yaw; })
                    . Z_Lambda([=]{ return GetRotation().Roll; })
                ]
                + SHorizontalBox::Slot()
                [
                    SNew(STextBlock)
                    . SimpleTextMode(true)
                    . ColorAndOpacity(FLinearColor::White)
                    . Text(LOCTEXT("RotationLabel", "Rotation"))
                ]
            ]
        ]
    ];

    auto MatrixComponent = [=](SGridPanel::FSlot& TargetSlot, int Row, int Col)
    {
        TargetSlot
        . Padding(2)
        [
            SNew(SBorder)
            . Padding(3)
            . BorderImage(BackgroundBrush.Get())
            . BorderBackgroundColor(FSlateColor({0.3f, 0.3f, 0.3f, 0.8f}))
            [
                SNew(STextBlock)
                . SimpleTextMode(true)
                . ColorAndOpacity(FLinearColor::White)
                . Text_Lambda([=]
                {
                    return FormatMatrixComp(InArgs, Row, Col);
                })
            ]
        ];
    };
    for(int r = 0; r < 4; r++)
        for(int c = 0; c < 4; c++)
        {
            MatrixComponent(MainGrid->AddSlot(c, r), r, c);
        }
}

#undef LOCTEXT_NAMESPACE
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
