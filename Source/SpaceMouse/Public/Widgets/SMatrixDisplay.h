// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

struct FSlateColorBrush;
class SGridPanel;

/**
 * 
 */
class SPACEMOUSE_API SMatrixDisplay : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SMatrixDisplay)
    {
    }

    SLATE_ATTRIBUTE(FMatrix, InMatrix)
    SLATE_ATTRIBUTE(FText, Label)

    SLATE_END_ARGS()

    static FText FormatFloat(float $);
    static FText FormatMatrixComp(const FArguments& InArgs, int Row, int Col);

    /** Constructs this widget with InArgs */
    void Construct(const FArguments& InArgs);

    FArguments PersistArgs;

    TSharedPtr<SGridPanel> MainGrid;
    TSharedPtr<FSlateColorBrush> BackgroundBrush;
};
