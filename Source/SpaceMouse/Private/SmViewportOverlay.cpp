// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE


#include "SmViewportOverlay.h"
#include "Editor.h"
#include "SEditorViewport.h"
#include "EditorViewportClient.h"
#include "Widgets/SViewport.h"
#include "Widgets/Text/STextBlock.h"


FSmViewportOverlay::FSmViewportOverlay(FEditorViewportClient* VpClient)
    : ViewportClient(VpClient)
{
    auto VpRootWidget = VpClient->GetEditorViewportWidget();
    Viewport = StaticCastSharedPtr<SViewport>(GetChildWidgetOfType(VpRootWidget, TEXT("SViewport")));
    if(!Viewport) return;
    Overlay = StaticCastSharedRef<SOverlay>(Viewport->GetChildren()->GetChildAt(0));

    Overlay->AddSlot()
        . HAlign(HAlign_Left)
        . VAlign(VAlign_Top)
        [
            SAssignNew(DistanceText, STextBlock)
            . SimpleTextMode(true)
            . ColorAndOpacity(FLinearColor::Yellow)
            . ShadowOffset(FVector2D(2, 2))
            . ShadowColorAndOpacity(FLinearColor::Black)
        ];
}

FSmViewportOverlay::~FSmViewportOverlay()
{
    if(Overlay)
        Overlay->RemoveSlot(DistanceText.ToSharedRef());
}

void FSmViewportOverlay::Draw(FVector Pivot, float PivotDistance)
{
    FSceneViewFamilyContext ViewFam({
        ViewportClient->Viewport,
        ViewportClient->GetScene(),
        ViewportClient->EngineShowFlags
    });
    auto DpiScale = ViewportClient->ShouldDPIScaleSceneCanvas() ? ViewportClient->GetDPIScale() : 1.0f;
    auto SceneView = ViewportClient->CalcSceneView(&ViewFam);
    FVector2D Pos2;
    auto VpSize = ViewportClient->Viewport->GetSizeXY();
    SceneView->ProjectWorldToScreen(
        Pivot,
        FIntRect({0, 0}, VpSize),
        SceneView->ViewMatrices.GetViewProjectionMatrix(),
        Pos2
    );
    
    
    DistanceText->SetText(
        FText::FromString(FString::Printf(TEXT("%.2f cm"), PivotDistance))
    );

    Pos2 /= DpiScale;
    Pos2 -= DistanceText->GetDesiredSize() / 2.0f;
    DistanceText->SetRenderTransform(FSlateRenderTransform(Pos2));
}

TSharedPtr<SWidget> FSmViewportOverlay::GetChildWidgetOfType(TSharedPtr<SWidget> InWidget, FName InType)
{
    if(InWidget->GetType() == InType) return InWidget;
    auto Children = InWidget->GetChildren();

    for(int i=0; i<Children->Num(); i++)
    {
        auto CurrChild = GetChildWidgetOfType(
            Children->GetChildAt(i),
            InType
        );
        if(CurrChild.IsValid()) return CurrChild;
    }
    return {};
}

