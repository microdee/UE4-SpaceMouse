// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#if WITH_3DX_NAVLIB

#include "CoreMinimal.h"
#include "NavlibTypes.h"

#define NL_PROP_R(MSelf, Name) \
    static long Name##Reader(const navlib::param_t param, const navlib::property_t name, navlib::value_t *value) \
    { \
        auto Self = reinterpret_cast<MSelf*>(param); \
        auto& Prop = Self->Name; \
        if (Self->Is##Name##Available()) \
        { \
            Self->On##Name##Get(Prop); \
            *value = Prop.GetCached(); \
            return 0; \
        } \
        return navlib::make_result_code(navlib::navlib_errc::no_data_available); \
    }

#define NL_PROP_W(MSelf, Name) \
    static long Name##Writer(const navlib::param_t param, const navlib::property_t name, const navlib::value_t *value) \
    { \
        /* reinterpret_cast<MSelf*>(param)->Name = value; */ \
        reinterpret_cast<MSelf*>(param)->Name.SetCached(*value); \
        return 0; \
    }

#define NL_PROP_ACC_R(MSelf, Name) &MSelf::Name##Reader
#define NL_PROP_ACC_W(MSelf, Name) &MSelf::Name##Writer

#define NL_PROP_(...)
#define NL_PROP_ACC_(...) nullptr

#define NL_PROP(MSelf, Name, Read, Write) \
    public: using F##Name##Property = navlib::TProperty<navlib::EProperty::Name>; \
    protected: virtual bool Is##Name##Available() { return true; } \
    protected: virtual void On##Name##Set(const F##Name##Property& InValue) { } \
    protected: virtual void On##Name##Get(F##Name##Property& InValue) { } \
    public: F##Name##Property Name { \
        Navlib, \
    }; \
    private: NL_PROP_##Read(MSelf, Name) NL_PROP_##Write(MSelf, Name) \
    private: void Add##Name##Accessor(TArray<navlib::accessor_t>& OutArray) \
    { \
        navlib::accessor_t Accessor; \
        Accessor.name = decltype(Name)::GetProperty(); \
        Accessor.param = reinterpret_cast<navlib::param_t>(this); \
        Accessor.fnGet = NL_PROP_ACC_##Read(MSelf, Name); \
        Accessor.fnSet = NL_PROP_ACC_##Write(MSelf, Name); \
        OutArray.Add(Accessor); \
    } \

/**
 * 
 */
class SPACEMOUSEREADER_API FTDxNavContext
{
    
public:
    
    FTDxNavContext();
    virtual ~FTDxNavContext();

    void Open();
    
protected:
    virtual void OnPreOpen(TArray<navlib::accessor_t>& Accessors) {}
    virtual void OnPostOpen() {}
    
public:
    /** Name of this instance of a navigation context */
    virtual FString GetProfileName() = 0;

    // Navlib properties with their boilerplate

    NL_PROP(FTDxNavContext, Active                ,   ,   );
    NL_PROP(FTDxNavContext, Focus                 ,   ,   );
    NL_PROP(FTDxNavContext, Motion                ,   , W );
    NL_PROP(FTDxNavContext, CoordinateSystem      , R ,   );
    NL_PROP(FTDxNavContext, DevicePresent         ,   ,   );
    NL_PROP(FTDxNavContext, EventsKeyPress        ,   , W );
    NL_PROP(FTDxNavContext, EventsKeyRelease      ,   , W );
    NL_PROP(FTDxNavContext, Transaction           ,   , W );
    NL_PROP(FTDxNavContext, FrameTime             , R ,   );
    NL_PROP(FTDxNavContext, FrameTimingSource     , R ,   );
    NL_PROP(FTDxNavContext, ViewAffine            , R , W );
    NL_PROP(FTDxNavContext, ViewConstructionPlane , R ,   );
    NL_PROP(FTDxNavContext, ViewExtents           , R , W );
    NL_PROP(FTDxNavContext, ViewFov               , R , W );
    NL_PROP(FTDxNavContext, ViewFrustum           , R ,   );
    NL_PROP(FTDxNavContext, ViewPerspective       , R ,   );
    NL_PROP(FTDxNavContext, ViewRotatable         , R ,   );
    NL_PROP(FTDxNavContext, ViewTarget            , R ,   );
    NL_PROP(FTDxNavContext, ViewsFront            , R ,   );
    NL_PROP(FTDxNavContext, PivotPosition         , R , W );
    NL_PROP(FTDxNavContext, PivotUser             ,   ,   );
    NL_PROP(FTDxNavContext, PivotVisible          ,   , W );
    NL_PROP(FTDxNavContext, HitLookfrom           ,   , W );
    NL_PROP(FTDxNavContext, HitDirection          ,   , W );
    NL_PROP(FTDxNavContext, HitAperture           ,   , W );
    NL_PROP(FTDxNavContext, HitLookat             , R ,   );
    NL_PROP(FTDxNavContext, HitSelectionOnly      ,   , W );
    NL_PROP(FTDxNavContext, SelectionAffine       , R , W );
    NL_PROP(FTDxNavContext, SelectionEmpty        , R ,   );
    NL_PROP(FTDxNavContext, SelectionExtents      , R ,   );
    NL_PROP(FTDxNavContext, ModelExtents          , R ,   );
    NL_PROP(FTDxNavContext, PointerPosition       , R ,   );
    NL_PROP(FTDxNavContext, CommandsTree          ,   ,   );
    NL_PROP(FTDxNavContext, CommandsActiveSet     ,   ,   );
    NL_PROP(FTDxNavContext, CommandsActiveCommand ,   , W );
    NL_PROP(FTDxNavContext, Images                ,   ,   );
    NL_PROP(FTDxNavContext, Settings              ,   ,   );
    NL_PROP(FTDxNavContext, SettingsChanged       ,   , W );

    // TODO command tree

    // End of Navlib getters/setters
    
private:
    
    navlib::nlHandle_t Navlib {};
};

#endif