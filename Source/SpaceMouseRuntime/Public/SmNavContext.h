// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "Navlib/TDxNavContext.h"

#include "SmNavContext.generated.h"

class USmNavContext;

class SPACEMOUSERUNTIME_API FSmNavContextInternal : public FTDxNavContext
{
public:
    FSmNavContextInternal(TWeakObjectPtr<USmNavContext> InAssociatedNavCtx);

    virtual void OnPostOpen() override;
    virtual FString GetProfileName() override;

    
    virtual bool IsActiveAvailable() override;
    virtual void OnActiveGet(FActiveProperty& InValue) override;
    virtual void OnActiveSet(const FActiveProperty& InValue) override;
    
    virtual bool IsFocusAvailable() override;
    virtual void OnFocusGet(FFocusProperty& InValue) override;
    virtual void OnFocusSet(const FFocusProperty& InValue) override;
    
    virtual bool IsMotionAvailable() override;
    virtual void OnMotionGet(FMotionProperty& InValue) override;
    virtual void OnMotionSet(const FMotionProperty& InValue) override;
    
    virtual bool IsDevicePresentAvailable() override;
    virtual void OnDevicePresentGet(FDevicePresentProperty& InValue) override;
    virtual void OnDevicePresentSet(const FDevicePresentProperty& InValue) override;
    
    virtual bool IsEventsKeyPressAvailable() override;
    virtual void OnEventsKeyPressGet(FEventsKeyPressProperty& InValue) override;
    virtual void OnEventsKeyPressSet(const FEventsKeyPressProperty& InValue) override;
    
    virtual bool IsEventsKeyReleaseAvailable() override;
    virtual void OnEventsKeyReleaseGet(FEventsKeyReleaseProperty& InValue) override;
    virtual void OnEventsKeyReleaseSet(const FEventsKeyReleaseProperty& InValue) override;
    
    virtual bool IsTransactionAvailable() override;
    virtual void OnTransactionGet(FTransactionProperty& InValue) override;
    virtual void OnTransactionSet(const FTransactionProperty& InValue) override;
    
    virtual bool IsViewAffineAvailable() override;
    virtual void OnViewAffineGet(FViewAffineProperty& InValue) override;
    virtual void OnViewAffineSet(const FViewAffineProperty& InValue) override;
    
    virtual bool IsViewConstructionPlaneAvailable() override;
    virtual void OnViewConstructionPlaneGet(FViewConstructionPlaneProperty& InValue) override;
    virtual void OnViewConstructionPlaneSet(const FViewConstructionPlaneProperty& InValue) override;
    
    virtual bool IsViewExtentsAvailable() override;
    virtual void OnViewExtentsGet(FViewExtentsProperty& InValue) override;
    virtual void OnViewExtentsSet(const FViewExtentsProperty& InValue) override;
    
    virtual bool IsViewFovAvailable() override;
    virtual void OnViewFovGet(FViewFovProperty& InValue) override;
    virtual void OnViewFovSet(const FViewFovProperty& InValue) override;
    
    virtual bool IsViewFrustumAvailable() override;
    virtual void OnViewFrustumGet(FViewFrustumProperty& InValue) override;
    virtual void OnViewFrustumSet(const FViewFrustumProperty& InValue) override;
    
    virtual bool IsViewPerspectiveAvailable() override;
    virtual void OnViewPerspectiveGet(FViewPerspectiveProperty& InValue) override;
    virtual void OnViewPerspectiveSet(const FViewPerspectiveProperty& InValue) override;
    
    virtual bool IsViewRotatableAvailable() override;
    virtual void OnViewRotatableGet(FViewRotatableProperty& InValue) override;
    virtual void OnViewRotatableSet(const FViewRotatableProperty& InValue) override;
    
    virtual bool IsViewTargetAvailable() override;
    virtual void OnViewTargetGet(FViewTargetProperty& InValue) override;
    virtual void OnViewTargetSet(const FViewTargetProperty& InValue) override;
    
    virtual bool IsViewsFrontAvailable() override;
    virtual void OnViewsFrontGet(FViewsFrontProperty& InValue) override;
    virtual void OnViewsFrontSet(const FViewsFrontProperty& InValue) override;
    
    virtual bool IsPivotPositionAvailable() override;
    virtual void OnPivotPositionGet(FPivotPositionProperty& InValue) override;
    virtual void OnPivotPositionSet(const FPivotPositionProperty& InValue) override;
    
    virtual bool IsPivotUserAvailable() override;
    virtual void OnPivotUserGet(FPivotUserProperty& InValue) override;
    virtual void OnPivotUserSet(const FPivotUserProperty& InValue) override;
    
    virtual bool IsPivotVisibleAvailable() override;
    virtual void OnPivotVisibleGet(FPivotVisibleProperty& InValue) override;
    virtual void OnPivotVisibleSet(const FPivotVisibleProperty& InValue) override;
    
    virtual bool IsHitLookfromAvailable() override;
    virtual void OnHitLookfromGet(FHitLookfromProperty& InValue) override;
    virtual void OnHitLookfromSet(const FHitLookfromProperty& InValue) override;
    
    virtual bool IsHitDirectionAvailable() override;
    virtual void OnHitDirectionGet(FHitDirectionProperty& InValue) override;
    virtual void OnHitDirectionSet(const FHitDirectionProperty& InValue) override;
    
    virtual bool IsHitApertureAvailable() override;
    virtual void OnHitApertureGet(FHitApertureProperty& InValue) override;
    virtual void OnHitApertureSet(const FHitApertureProperty& InValue) override;
    
    virtual bool IsHitLookatAvailable() override;
    virtual void OnHitLookatGet(FHitLookatProperty& InValue) override;
    virtual void OnHitLookatSet(const FHitLookatProperty& InValue) override;
    
    virtual bool IsHitSelectionOnlyAvailable() override;
    virtual void OnHitSelectionOnlyGet(FHitSelectionOnlyProperty& InValue) override;
    virtual void OnHitSelectionOnlySet(const FHitSelectionOnlyProperty& InValue) override;
    
    virtual bool IsSelectionAffineAvailable() override;
    virtual void OnSelectionAffineGet(FSelectionAffineProperty& InValue) override;
    virtual void OnSelectionAffineSet(const FSelectionAffineProperty& InValue) override;
    
    virtual bool IsSelectionEmptyAvailable() override;
    virtual void OnSelectionEmptyGet(FSelectionEmptyProperty& InValue) override;
    virtual void OnSelectionEmptySet(const FSelectionEmptyProperty& InValue) override;
    
    virtual bool IsSelectionExtentsAvailable() override;
    virtual void OnSelectionExtentsGet(FSelectionExtentsProperty& InValue) override;
    virtual void OnSelectionExtentsSet(const FSelectionExtentsProperty& InValue) override;
    
    virtual bool IsModelExtentsAvailable() override;
    virtual void OnModelExtentsGet(FModelExtentsProperty& InValue) override;
    virtual void OnModelExtentsSet(const FModelExtentsProperty& InValue) override;
    
    virtual bool IsPointerPositionAvailable() override;
    virtual void OnPointerPositionGet(FPointerPositionProperty& InValue) override;
    virtual void OnPointerPositionSet(const FPointerPositionProperty& InValue) override;
    
    
protected:
    TWeakObjectPtr<USmNavContext> AssociatedNavCtx;
};

UCLASS(BlueprintType, Blueprintable, Abstract)
class SPACEMOUSERUNTIME_API USmNavContext : public UObject
{
    GENERATED_BODY()
protected:
    TUniquePtr<FSmNavContextInternal> NavlibCtx;

    virtual void PostLoad() override;

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    FString GetProfileName();

    UFUNCTION(BlueprintCallable, Category = "SpaceMouse")
    void Open();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnPostOpen();

    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsActiveAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnActiveGet( UPARAM(ref) bool& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnActiveSet( bool Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsFocusAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnFocusGet( UPARAM(ref) bool& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnFocusSet( bool Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsMotionAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnMotionGet( UPARAM(ref) bool& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnMotionSet( bool Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsDevicePresentAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnDevicePresentGet( UPARAM(ref) bool& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnDevicePresentSet( bool Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsEventsKeyPressAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnEventsKeyPressGet( UPARAM(ref) int& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnEventsKeyPressSet( int Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsEventsKeyReleaseAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnEventsKeyReleaseGet( UPARAM(ref) int& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnEventsKeyReleaseSet( int Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsTransactionAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnTransactionGet( UPARAM(ref) int& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnTransactionSet( int Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewAffineAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewAffineGet( UPARAM(ref) FMatrix& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewAffineSet( FMatrix Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewConstructionPlaneAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewConstructionPlaneGet( UPARAM(ref) FPlane& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewConstructionPlaneSet( FPlane Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewExtentsAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewExtentsGet( UPARAM(ref) FBox& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewExtentsSet( FBox Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewFovAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewFovGet( UPARAM(ref) float& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewFovSet( float Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewFrustumAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewFrustumGet( UPARAM(ref) FMatrix& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewFrustumSet( FMatrix Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewPerspectiveAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewPerspectiveGet( UPARAM(ref) bool& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewPerspectiveSet( bool Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewRotatableAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewRotatableGet( UPARAM(ref) bool& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewRotatableSet( bool Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewTargetAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewTargetGet( UPARAM(ref) FVector& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewTargetSet( FVector Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewsFrontAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewsFrontGet( UPARAM(ref) FMatrix& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewsFrontSet( FMatrix Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsPivotPositionAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnPivotPositionGet( UPARAM(ref) FVector& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnPivotPositionSet( FVector Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsPivotUserAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnPivotUserGet( UPARAM(ref) bool& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnPivotUserSet( bool Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsPivotVisibleAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnPivotVisibleGet( UPARAM(ref) bool& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnPivotVisibleSet( bool Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsHitLookfromAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnHitLookfromGet( UPARAM(ref) FVector& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnHitLookfromSet( FVector Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsHitDirectionAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnHitDirectionGet( UPARAM(ref) FVector& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnHitDirectionSet( FVector Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsHitApertureAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnHitApertureGet( UPARAM(ref) float& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnHitApertureSet( float Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsHitLookatAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnHitLookatGet( UPARAM(ref) FVector& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnHitLookatSet( FVector Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsHitSelectionOnlyAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnHitSelectionOnlyGet( UPARAM(ref) bool& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnHitSelectionOnlySet( bool Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsSelectionAffineAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnSelectionAffineGet( UPARAM(ref) FMatrix& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnSelectionAffineSet( FMatrix Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsSelectionEmptyAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnSelectionEmptyGet( UPARAM(ref) bool& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnSelectionEmptySet( bool Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsSelectionExtentsAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnSelectionExtentsGet( UPARAM(ref) FBox& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnSelectionExtentsSet( FBox Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsModelExtentsAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnModelExtentsGet( UPARAM(ref) FBox& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnModelExtentsSet( FBox Input );
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsPointerPositionAvailable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnPointerPositionGet( UPARAM(ref) FVector& Output );

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnPointerPositionSet( FVector Input );
    
};