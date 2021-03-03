// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class SOverlay;
class SViewport;
class STextBlock;
class FEditorViewportClient;
/**
 * Object managing the lifespan of orbiting information over the active viewport
 */
class SPACEMOUSE_API FSmViewportOverlay
{
public:
    FSmViewportOverlay(FEditorViewportClient* VpClient);
    ~FSmViewportOverlay();

    void Draw(FVector Pivot, float PivotDistance);
    
private:
    FEditorViewportClient* ViewportClient = nullptr;
    TSharedPtr<STextBlock> DistanceText;
    TSharedPtr<SViewport> Viewport;
    TSharedPtr<SOverlay> Overlay;

    static TSharedPtr<SWidget> GetChildWidgetOfType(TSharedPtr<SWidget> InWidget, FName InType);
};
