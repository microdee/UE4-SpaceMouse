// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <navlib/navlib.h>
#include <navlib/navlib_types.h>

/**
 * 
 */
class SPACEMOUSEREADER_API FTDxNavContext
{
    friend class FTDxNavConnection;
    
public:

    template<typename TVal>
    struct TResult
    {
        TVal Value {};
        long Result = 0;
        
        TResult()
            : Value({})
            , Result(navlib::make_result_code(navlib::navlib_errc::no_data_available))
        {}
        
        TResult(TVal InValue)
            : Value(InValue)
            , Result(0)
        {}
    private:
        explicit TResult(TVal InValue, long InResult)
            : Value(InValue)
            , Result(InResult)
        {}
    public:
        static TResult<TVal> Error(long InError)
        {
            return TResult(Value, navlib::make_result_code(InError));
        }

        operator TVal () { return Value; }
    };

protected:
    
    template<typename TVal>
    static TResult<TVal> Error(long InError)
    {
        return {{}, InError};
    }
    
public:
    
    FTDxNavContext();
    virtual ~FTDxNavContext();

    void Open();

    virtual void OnOpen(TArray<navlib::accessor_t>& Accessors) {}

    /** Name of this instance of a navigation context */
    virtual FString GetProfileName() = 0;

    // Navlib property getters setters
    // Set* is a Getter in Navlib and On* is a Setter in Navlib
    
    virtual void OnMotion(bool Value) {} // write_access
    
    virtual TResult<navlib::matrix_t> SetCoordinateSystem() { return {}; } // read_access
    
    virtual void OnEventsKeyPress(long Value) {} // write_access
    
    virtual void OnEventsKeyRelease(long Value) {} // write_access
    
    virtual void OnTransaction(long Value) {} // write_access
    
    virtual TResult<double> SetFrameTime() { return {}; } // read_access
    
    virtual TResult<long> SetFrameTimingSource() { return {}; } // read_access
    
    virtual void OnViewAffine(navlib::matrix_t Value) {} // read_write_access
    
    virtual TResult<navlib::matrix_t> SetViewAffine() { return {}; } // read_write_access
    
    virtual TResult<navlib::plane_t> SetViewConstructionPlane() { return {}; } // read_access
    
    virtual void OnViewExtents(navlib::box_t Value) {} // read_write_access
    
    virtual TResult<navlib::box_t> SetViewExtents() { return {}; } // read_write_access
    
    virtual void OnViewFov(float Value) {} // read_write_access
    
    virtual TResult<float> SetViewFov() { return {}; } // read_write_access
    
    virtual TResult<navlib::frustum_t> SetViewFrustum() { return {}; } // read_access
    
    virtual TResult<bool> SetViewPerspective() { return {}; } // read_access
    
    virtual TResult<bool> SetViewRotatable() { return {}; } // read_access
    
    virtual TResult<navlib::point_t> SetViewTarget() { return {}; } // read_access
    
    virtual TResult<navlib::matrix_t> SetViewsFront() { return {}; } // read_access
    
    virtual void OnPivotPosition(navlib::point_t Value) {} // read_write_access
    
    virtual TResult<navlib::point_t> SetPivotPosition() { return {}; } // read_write_access
    
    virtual void OnPivotVisible(bool Value) {} // write_access
    
    virtual void OnHitLookfrom(navlib::point_t Value) {} // write_access
    
    virtual void OnHitDirection(navlib::vector_t Value) {} // write_access
    
    virtual void OnHitAperture(float Value) {} // write_access
    
    virtual TResult<navlib::point_t> SetHitLookat() { return {}; } // read_access
    
    virtual void OnHitSelectionOnly(bool Value) {} // write_access
    
    virtual void OnSelectionAffine(navlib::matrix_t Value) {} // read_write_access
    
    virtual TResult<navlib::matrix_t> SetSelectionAffine() { return {}; } // read_write_access
    
    virtual TResult<bool> SetSelectionEmpty() { return {}; } // read_access
    
    virtual TResult<navlib::box_t> SetSelectionExtents() { return {}; } // read_access
    
    virtual TResult<navlib::box_t> SetModelExtents() { return {}; } // read_access
    
    virtual TResult<navlib::point_t> SetPointerPosition() { return {}; } // read_access

    // TODO command tree
    
    virtual void OnSettingsChanged(long Value) {} // write_access

    // End of Navlib getters/setters
    
private:
    
    navlib::nlHandle_t Navlib {};
    TUniquePtr<FTDxNavConnection> Connection;
};
