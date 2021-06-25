// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SDebugVpNavlib.h"

#include "SlateOptMacros.h"
#include "Components/VerticalBox.h"
#include "Widgets/SCanvas.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "Widgets/SMatrixDisplay.h"
#include "Widgets/Input/SVectorInputBox.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "Widgets/Layout/SGridPanel.h"
#include "Widgets/Layout/SScrollBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
#define LOCTEXT_NAMESPACE "NavlibVpDebug"

void SDebugVpNavlib::Construct(const FArguments& InArgs)
{
    auto VectorWidget = [=](TAttribute<FVector> InVector, TAttribute<FText> Label)
    {
        return SNew(SHorizontalBox)
        + SHorizontalBox::Slot()
        [
            SNew(SVectorInputBox)
            . X_Lambda([=]{ return InVector.Get().X; })
            . Y_Lambda([=]{ return InVector.Get().Y; })
            . Z_Lambda([=]{ return InVector.Get().Z; })
            ]
            + SHorizontalBox::Slot()
            [
                SNew(STextBlock)
                . SimpleTextMode(true)
                . ColorAndOpacity(FLinearColor::White)
                . Text(Label)
            ];
    };

    auto VectorRow = [=](TAttribute<FVector> InVector, TAttribute<FText> Label) -> SVerticalBox::FSlot&
    {
        return SVerticalBox::Slot()
            . HAlign(HAlign_Fill)
            . AutoHeight()
            [
                VectorWidget(InVector, Label)
            ];
    };
    
    ChildSlot
    [
        SNew(SConstraintCanvas)
        + SConstraintCanvas::Slot()
        . Anchors(FAnchors(1, 0, 1, 1))
        . Offset(FMargin(-20, 50, 600, 30))
        . AutoSize(false)
        . Alignment(FVector2D(1, 0))
        [
            SNew(SScrollBox)
            . Orientation(Orient_Vertical)
            . ConsumeMouseWheel(EConsumeMouseWheel::Always)
            . AnimateWheelScrolling(true)
            + SScrollBox::Slot()
            . HAlign(HAlign_Fill)
            . VAlign(VAlign_Fill)
            [
                SNew(SVerticalBox)
                + SVerticalBox::Slot()
                . AutoHeight()
                . HAlign(HAlign_Fill)
                [
                    SNew(SExpandableArea)
                    . AreaTitle(LOCTEXT("DebugViewTr", "Debug View Tr"))
                    . HeaderContent()
                    [
                        SNew(STextBlock)
                        . SimpleTextMode(true)
                        . ColorAndOpacity(FLinearColor::White)
                        . Text(LOCTEXT("DebugViewTr", "Debug View Tr"))
                    ]
                    . BodyContent()
                    [
                        SNew(SGridPanel)
                        + SGridPanel::Slot(1, 0)
                        [
                            SNew(SMatrixDisplay)
                            . Label(LOCTEXT("SceneViewTr", "Scene View"))
                            . InMatrix(InArgs._SceneViewTr)
                        ]
                        + SGridPanel::Slot(0, 0)
                        [
                            SNew(SMatrixDisplay)
                            . Label(LOCTEXT("LocRotTr", "Location Rotation Tr"))
                            . InMatrix(InArgs._LocRotTr)
                        ]
                        + SGridPanel::Slot(1, 1)
                        [
                            SNew(SMatrixDisplay)
                            . Label(LOCTEXT("ProjTr", "Projection"))
                            . InMatrix(InArgs._ProjTr)
                        ]
                    ]
                ]
                + SVerticalBox::Slot()
                . AutoHeight()
                . HAlign(HAlign_Fill)
                [
                    SNew(SExpandableArea)
                    . AreaTitle(LOCTEXT("DebugPositions", "Debug Positions"))
                    . HeaderContent()
                    [
                        SNew(STextBlock)
                        . SimpleTextMode(true)
                        . ColorAndOpacity(FLinearColor::White)
                        . Text(LOCTEXT("DebugPositions", "Debug Positions"))
                    ]
                    . BodyContent()
                    [
                        SNew(SVerticalBox)
                        + VectorRow(InArgs._PivotPos, LOCTEXT("PivotPos", "PivotPos"))
                        + VectorRow(InArgs._PointerPos, LOCTEXT("PointerPos", "PointerPos"))
                    ]
                ]
                + SVerticalBox::Slot()
                . AutoHeight()
                . HAlign(HAlign_Fill)
                [
                    SNew(SExpandableArea)
                    . AreaTitle(LOCTEXT("DebugFrustum", "Debug Frustum"))
                    . HeaderContent()
                    [
                        SNew(STextBlock)
                        . SimpleTextMode(true)
                        . ColorAndOpacity(FLinearColor::White)
                        . Text(LOCTEXT("DebugFrustum", "Debug Frustum"))
                    ]
                    . BodyContent()
                    [
                        SNew(SVerticalBox)
                        + SVerticalBox::Slot()
                        . HAlign(HAlign_Fill)
                        . AutoHeight()
                        [
                            SNew(STextBlock)
                            . ColorAndOpacity(FLinearColor::White)
                            . Text_Lambda([=]
                            {
                                auto Ft = InArgs._Frustum.Get();
                                static TArray<FString> PlaneNames {
                                    TEXT("Near"),
                                    TEXT("Left"),
                                    TEXT("Right"),
                                    TEXT("Top"),
                                    TEXT("Bottom"),
                                    TEXT("Far"),
                                };

                                FString Output = "";
                                for(int i=0; i<Ft.Planes.Num(); i++)
                                {
                                    Output += FString::Printf(
                                        TEXT("%.2f | %.2f | %.2f | %.2f | %s\n"),
                                        Ft.Planes[i].X, Ft.Planes[i].Y, Ft.Planes[i].Z, Ft.Planes[i].W,
                                        *PlaneNames[i]
                                    );
                                }
                                
                                return FText::FromString(Output);
                            })
                        ]
                    ]
                ]
                + SVerticalBox::Slot()
                . AutoHeight()
                . HAlign(HAlign_Fill)
                [
                    SNew(SExpandableArea)
                    . AreaTitle(LOCTEXT("DebugHittest", "Debug Hittest"))
                    . HeaderContent()
                    [
                        SNew(STextBlock)
                        . SimpleTextMode(true)
                        . ColorAndOpacity(FLinearColor::White)
                        . Text(LOCTEXT("DebugHittest", "Debug Hittest"))
                    ]
                    . BodyContent()
                    [
                        SNew(SVerticalBox)
                        + VectorRow(InArgs._HitPos, LOCTEXT("HitPos", "HitPos"))
                        + VectorRow(InArgs._HitLookfrom, LOCTEXT("HitLookfrom", "HitLookfrom"))
                        + VectorRow(InArgs._HitLookfrom, LOCTEXT("HitDirection", "HitDirection"))
                    ]
                ]
            ]
        ]
    ];
}

#undef LOCTEXT_NAMESPACE
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
