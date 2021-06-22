// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SDebugVpNavlib.h"

#include "SlateOptMacros.h"
#include "Widgets/SCanvas.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "Widgets/SMatrixDisplay.h"
#include "Widgets/Layout/SGridPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
#define LOCTEXT_NAMESPACE "NavlibVpDebug"

void SDebugVpNavlib::Construct(const FArguments& InArgs)
{
    ChildSlot
    [
        SNew(SConstraintCanvas)
        + SConstraintCanvas::Slot()
        . Anchors(FAnchors(1, 0))
        . Offset(FMargin(-20, 50))
        . AutoSize(true)
        . Alignment(FVector2D(1, 0))
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
    ];
}

#undef LOCTEXT_NAMESPACE
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
