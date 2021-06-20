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
    
    virtual bool IsFocusAvailable() override;
    virtual void OnFocusGet(FFocusProperty& InValue) override;
    
    
    
    virtual void OnMotionSet(const FMotionProperty& InValue) override;
    
    
    virtual void OnDevicePresentSet(const FDevicePresentProperty& InValue) override;
    
    
    virtual void OnEventsKeyPressSet(const FEventsKeyPressProperty& InValue) override;
    
    
    virtual void OnEventsKeyReleaseSet(const FEventsKeyReleaseProperty& InValue) override;
    
    
    virtual void OnTransactionSet(const FTransactionProperty& InValue) override;
    virtual bool IsViewAffineAvailable() override;
    virtual void OnViewAffineGet(FViewAffineProperty& InValue) override;
    virtual void OnViewAffineSet(const FViewAffineProperty& InValue) override;
    virtual bool IsViewConstructionPlaneAvailable() override;
    virtual void OnViewConstructionPlaneGet(FViewConstructionPlaneProperty& InValue) override;
    
    virtual bool IsViewExtentsAvailable() override;
    virtual void OnViewExtentsGet(FViewExtentsProperty& InValue) override;
    virtual void OnViewExtentsSet(const FViewExtentsProperty& InValue) override;
    virtual bool IsViewFovAvailable() override;
    virtual void OnViewFovGet(FViewFovProperty& InValue) override;
    virtual void OnViewFovSet(const FViewFovProperty& InValue) override;
    virtual bool IsViewFrustumAvailable() override;
    virtual void OnViewFrustumGet(FViewFrustumProperty& InValue) override;
    
    virtual bool IsViewPerspectiveAvailable() override;
    virtual void OnViewPerspectiveGet(FViewPerspectiveProperty& InValue) override;
    
    virtual bool IsViewRotatableAvailable() override;
    virtual void OnViewRotatableGet(FViewRotatableProperty& InValue) override;
    
    virtual bool IsViewTargetAvailable() override;
    virtual void OnViewTargetGet(FViewTargetProperty& InValue) override;
    
    virtual bool IsViewsFrontAvailable() override;
    virtual void OnViewsFrontGet(FViewsFrontProperty& InValue) override;
    
    virtual bool IsPivotPositionAvailable() override;
    virtual void OnPivotPositionGet(FPivotPositionProperty& InValue) override;
    virtual void OnPivotPositionSet(const FPivotPositionProperty& InValue) override;
    virtual bool IsPivotUserAvailable() override;
    virtual void OnPivotUserGet(FPivotUserProperty& InValue) override;
    
    
    
    virtual void OnPivotVisibleSet(const FPivotVisibleProperty& InValue) override;
    
    
    virtual void OnHitLookfromSet(const FHitLookfromProperty& InValue) override;
    
    
    virtual void OnHitDirectionSet(const FHitDirectionProperty& InValue) override;
    
    
    virtual void OnHitApertureSet(const FHitApertureProperty& InValue) override;
    virtual bool IsHitLookatAvailable() override;
    virtual void OnHitLookatGet(FHitLookatProperty& InValue) override;
    
    
    
    virtual void OnHitSelectionOnlySet(const FHitSelectionOnlyProperty& InValue) override;
    virtual bool IsSelectionAffineAvailable() override;
    virtual void OnSelectionAffineGet(FSelectionAffineProperty& InValue) override;
    virtual void OnSelectionAffineSet(const FSelectionAffineProperty& InValue) override;
    virtual bool IsSelectionEmptyAvailable() override;
    virtual void OnSelectionEmptyGet(FSelectionEmptyProperty& InValue) override;
    
    virtual bool IsSelectionExtentsAvailable() override;
    virtual void OnSelectionExtentsGet(FSelectionExtentsProperty& InValue) override;
    
    virtual bool IsModelExtentsAvailable() override;
    virtual void OnModelExtentsGet(FModelExtentsProperty& InValue) override;
    
    virtual bool IsPointerPositionAvailable() override;
    virtual void OnPointerPositionGet(FPointerPositionProperty& InValue) override;
    
    
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

    /** Return true if Active is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsActiveAvailable();

    /**
     * Specifies that the navigation instance is currently active.
     *
     * Clients that have multiple navigation instances open need to inform the navlib which of them is 
     * the target for 3D Mouse input. They do this by setting the active_k property of a navigation 
     * instance to true.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnActiveGet( UPARAM(ref) bool& Output );


    /** Return true if Focus is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsFocusAvailable();

    /**
     * Specifies that the application has keyboard focus.
     *
     * Clients that run in container applications via the NLServer proxy set this property to indicate
     * keyboard focus. This will set 3DMouse focus to the navlib connection.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnFocusGet( UPARAM(ref) bool& Output );



    /**
     * Specifies that a motion model is active.
     *
     * The motion_k property is set to true by the navlib to notify the client that it is executing a
     * motion model and will update the camera matrix regularly. This is useful for clients that need
     * to run an animation loop. When the navlib has finished navigating the camera position it will
     * set the property to false. By setting motion_k to false, a client may temporarily interrupt a
     * navigation communication and forces the Navlib to reinitialize the navigation.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnMotionSet( bool Input );


    /**
     * Specifies whether a device is present
     * Currently this always returns true.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnDevicePresentSet( bool Input );


    /**
     * V3DK press event.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnEventsKeyPressSet( int Input );


    /**
     * V3DK release event.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnEventsKeyReleaseSet( int Input );


    /**
     * Specifies the navigation transaction.
     *
     * The Navigation Library can set more than one client property for a single navigation frame. For 
     * example when navigating in an orthographic projection possibly both the view affine and extents 
     * will be modified depending on the 3DMouse input. The Navigation Library will set the 
     * transaction_k property to a value >0 at the beginning of a navigation frame and to 0 at the end. 
     * Clients that need to actively refresh the view can trigger the refresh when the value is set to 0.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnTransactionSet( int Input );

    /** Return true if ViewAffine is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewAffineAvailable();

    /**
     * Specifies the matrix of the camera in the view.
     *
     * This matrix specifies the camera to world transformation of the view. That is, multiplying this 
     * matrix on the right by the position (0, 0, 0) yields the position of the camera in world coordinates. 
     * The navlib will, generally, query this matrix at the beginning of a navigation action and then set 
     * the property per frame. The frame rate that the navlib attempts to achieve is related to the 3D 
     * mouse event rate and is about 60Hz.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewAffineGet( UPARAM(ref) FMatrix& Output );

    /**
     * Specifies the matrix of the camera in the view.
     *
     * This matrix specifies the camera to world transformation of the view. That is, multiplying this 
     * matrix on the right by the position (0, 0, 0) yields the position of the camera in world coordinates. 
     * The navlib will, generally, query this matrix at the beginning of a navigation action and then set 
     * the property per frame. The frame rate that the navlib attempts to achieve is related to the 3D 
     * mouse event rate and is about 60Hz.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewAffineSet( FMatrix Input );

    /** Return true if ViewConstructionPlane is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewConstructionPlaneAvailable();

    /**
     * Specifies the plane equation of the construction plane as a normal and a distance (general form 
     * of the equation of a plane).
     *
     * This property is used by the Navigation Library to distinguish views used for construction in an 
     * orthographic projection: typically the top, right left etc. views. The Navigation Library assumes 
     * that when the camera’s look-at axis is parallel to the plane normal the view should not be 
     * rotated.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewConstructionPlaneGet( UPARAM(ref) FPlane& Output );


    /** Return true if ViewExtents is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewExtentsAvailable();

    /**
     * Specifies the orthographic extents the view in camera coordinates
     *
     * This orthographic extents of the view are returned as a bounding box in camera/view 
     * coordinates. The navlib will only access this property if the view is orthographic.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewExtentsGet( UPARAM(ref) FBox& Output );

    /**
     * Specifies the orthographic extents the view in camera coordinates
     *
     * This orthographic extents of the view are returned as a bounding box in camera/view 
     * coordinates. The navlib will only access this property if the view is orthographic.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewExtentsSet( FBox Input );

    /** Return true if ViewFov is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewFovAvailable();

    /**
     * Specifies the field-of-view of a perspective camera/view in radians
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewFovGet( UPARAM(ref) float& Output );

    /**
     * Specifies the field-of-view of a perspective camera/view in radians
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewFovSet( float Input );

    /** Return true if ViewFrustum is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewFrustumAvailable();

    /**
     * Specifies the frustum of a perspective camera/view in camera coordinates
     *
     * The navlib uses this property to calculate the field-of-view of the perspective camera. The 
     * frustum is also used in algorithms that need to determine if the model is currently visible. The
     * navlib will not write to this property. Instead, if necessary, the navlib will write to the view_fov_k 
     * property and leave the client to change the frustum as it wishes.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewFrustumGet( UPARAM(ref) FMatrix& Output );


    /** Return true if ViewPerspective is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewPerspectiveAvailable();

    /**
     * Specifies the projection of the view/camera
     *
     * This property defaults to true. If the client does not supply a function for the navlib to query the 
     * view’s projection (which it will generally do at the onset of motion), then it must set the property 
     * in the navlib if the projection is orthographic or when it changes.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewPerspectiveGet( UPARAM(ref) bool& Output );


    /** Return true if ViewRotatable is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewRotatableAvailable();

    /**
     * Specifies whether the view can be rotated.
     *
     * This property is generally used to differentiate between orthographic 3D views and views that 
     * can only be panned and zoomed.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewRotatableGet( UPARAM(ref) bool& Output );


    /** Return true if ViewTarget is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewTargetAvailable();

    /**
     * Specifies the target constraint of the view/camera.
     *
     * The camera target is the point in space the camera is constrained to look at by a ‘lookat’
     * controller attached to the camera. The side effects of the controller are that panning the 
     * constrained camera will also result in a camera rotation due to the camera being constrained to 
     * keep the target position in the center of the view. Similarly panning the target will result in the 
     * camera rotating.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewTargetGet( UPARAM(ref) FVector& Output );


    /** Return true if ViewsFront is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsViewsFrontAvailable();

    /**
     * Specifies the orientation of the view designated as the front view.
     *
     * The Navigation Library will only query the value of this property when the connection is
     * created. It is used to orientate the model to one of the 'Front', 'Back', 'Right', 'Left' etc.
     * views in response to the respective pre-defined view commands. If the orientation of the front
     * view is redefined after the connection is opened by the user, the client application is required
     * to update the property to the new value.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnViewsFrontGet( UPARAM(ref) FMatrix& Output );


    /** Return true if PivotPosition is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsPivotPositionAvailable();

    /**
     * The pivot_position_k property specifies the center of rotation of the model in world coordinates.
     *
     * This property is normally set by the navlib. The application can manually override the navlib 
     * calculated pivot and set a specific pivot position that the navlib will use until it is cleared again 
     * by the application.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnPivotPositionGet( UPARAM(ref) FVector& Output );

    /**
     * The pivot_position_k property specifies the center of rotation of the model in world coordinates.
     *
     * This property is normally set by the navlib. The application can manually override the navlib 
     * calculated pivot and set a specific pivot position that the navlib will use until it is cleared again 
     * by the application.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnPivotPositionSet( FVector Input );

    /** Return true if PivotUser is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsPivotUserAvailable();

    /**
     * The pivot_user_k property specifies whether an application specified pivot is being used.
     *
     * To clear a pivot set by the application and to use the pivot algorithm in the navlib, the 
     * application sets this property to false. To override the navlib pivot algorithm the application can 
     * either set this property to true, which will cause the navlib to query the pivot position it should 
     * use, or the application can set the pivot position directly using the pivot_position_k property. The 
     * navlib’s pivot algorithm continues to be overridden until this property is set back to false.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnPivotUserGet( UPARAM(ref) bool& Output );



    /**
     * The pivot_visible_k property specifies whether the pivot widget should be displayed.
     *
     * In the default configuration this property is set by the navlib to true when the user starts to move 
     * the model and to false when the user has finished moving the model.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnPivotVisibleSet( bool Input );


    /**
     * Defines the origin of the ray used for hit-testing in world coordinates.
     *
     * This property is set by the navlib
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnHitLookfromSet( FVector Input );


    /**
     * Defines the direction of the ray used for hit-testing in world coordinates.
     *
     * This property is set by the navlib
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnHitDirectionSet( FVector Input );


    /**
     * Defines the diameter of the ray used for hit-testing.
     *
     * This property is set by the navlib
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnHitApertureSet( float Input );

    /** Return true if HitLookat is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsHitLookatAvailable();

    /**
     * Specifies the point of the model that is hit by the ray originating from the lookfrom position.
     *
     * This property is queried by the navlib. The navlib will generally calculate if it is possible to hit a 
     * part of the model from the model_extents_k and selection_extents_k properties before setting up 
     * the hit-test properties and querying this property.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnHitLookatGet( UPARAM(ref) FVector& Output );



    /**
     * Specifies whether the hit-testing is to be limited solely to the current selection set.
     *
     * This property is set by the navlib
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnHitSelectionOnlySet( bool Input );

    /** Return true if SelectionAffine is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsSelectionAffineAvailable();

    /**
     * Specifies the matrix of the selection.
     *
     * This matrix specifies the object to world transformation of the selection. That is, multiplying this 
     * matrix on the right by the position (0, 0, 0) yields the position of the selection in world 
     * coordinates. The navlib will, generally, query this matrix at the beginning of a navigation action
     * that involves moving the selection and then set the property per frame. The frame rate that the 
     * navlib attempts to achieve is related to the 3D mouse event rate and is about 60Hz.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnSelectionAffineGet( UPARAM(ref) FMatrix& Output );

    /**
     * Specifies the matrix of the selection.
     *
     * This matrix specifies the object to world transformation of the selection. That is, multiplying this 
     * matrix on the right by the position (0, 0, 0) yields the position of the selection in world 
     * coordinates. The navlib will, generally, query this matrix at the beginning of a navigation action
     * that involves moving the selection and then set the property per frame. The frame rate that the 
     * navlib attempts to achieve is related to the 3D mouse event rate and is about 60Hz.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnSelectionAffineSet( FMatrix Input );

    /** Return true if SelectionEmpty is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsSelectionEmptyAvailable();

    /**
     * When true, nothing is selected.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnSelectionEmptyGet( UPARAM(ref) bool& Output );


    /** Return true if SelectionExtents is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsSelectionExtentsAvailable();

    /**
     * Defines the bounding box of the selection in world coordinates
     *
     * This extents of the selection are returned as a bounding box in world coordinates. The navlib 
     * will only access this property if the selection_empty_k is false.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnSelectionExtentsGet( UPARAM(ref) FBox& Output );


    /** Return true if ModelExtents is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsModelExtentsAvailable();

    /**
     * Defines the bounding box of the model in world coordinates.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnModelExtentsGet( UPARAM(ref) FBox& Output );


    /** Return true if PointerPosition is currently available, and or makes sense */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    bool IsPointerPositionAvailable();

    /**
     * Defines the position of the mouse cursor on the projection plane in world coordinates.
     * The property is readonly.
     *
     * In OpenGL the position would typically be retrieved using gluUnProject with winZ set to 0.0.
     */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SpaceMouse")
    void OnPointerPositionGet( UPARAM(ref) FVector& Output );


};