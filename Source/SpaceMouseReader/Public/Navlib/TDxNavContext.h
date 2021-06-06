// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#if WITH_3DX_NAVLIB

#include "CoreMinimal.h"
#include "NavlibTypes.h"

#define NL_PROP_R(Name) \
    static long Name##Reader(const navlib::param_t param, const navlib::property_t name, navlib::value_t *value) \
    { \
        auto& Prop = reinterpret_cast<FTDxNavContext*>(param)->Name; \
        *value = Prop.GetCached(); \
        return Prop.IsAvailable() ? 0 : navlib::make_result_code(navlib::navlib_errc::no_data_available); \
    }

#define NL_PROP_W(Name) \
    static long Name##Writer(const navlib::param_t param, const navlib::property_t name, const navlib::value_t *value) \
    { \
        reinterpret_cast<FTDxNavContext*>(param)->Name = value; \
        return 0; \
    }

#define NL_PROP_ACC_R(Name) &FTDxNavContext::Name##Reader
#define NL_PROP_ACC_W(Name) &FTDxNavContext::Name##Writer

#define NL_PROP_()
#define NL_PROP_ACC_() nullptr

#define NL_PROP(Name, Read, Write) \
    public: using F##Name##Property = navlib::TProperty<navlib::EProperty::Name>; \
    protected: virtual bool Is##Name##Available() { return true; } \
    protected: virtual void On##Name##Set(const F##Name##Property::FTypeUe& InValue) { } \
    public: F##Name##Property Name { \
        Navlib, \
        F##Name##Property::FChange::CreateRaw(this, &FTDxNavContext::On##Name##Set), \
        F##Name##Property::FAvailable::CreateRaw(this, &FTDxNavContext::Is##Name##Available) \
    }; \
    private: NL_PROP_##Read(Name) NL_PROP_##Write(Name) \
    private: void Add##Name##Accessor(TArray<navlib::accessor_t>& OutArray) \
    { \
        navlib::accessor_t Accessor; \
        Accessor.name = decltype(Name)::GetProperty(); \
        Accessor.param = reinterpret_cast<navlib::param_t>(this); \
        Accessor.fnGet = NL_PROP_ACC_##Read(Name); \
        Accessor.fnSet = NL_PROP_ACC_##Write(Name); \
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

    NL_PROP(Active                ,   ,   );
    NL_PROP(Focus                 ,   ,   );
    NL_PROP(Motion                ,   , W );
    NL_PROP(CoordinateSystem      , R ,   );
    NL_PROP(DevicePresent         ,   ,   );
    NL_PROP(EventsKeyPress        ,   , W );
    NL_PROP(EventsKeyRelease      ,   , W );
    NL_PROP(Transaction           ,   , W );
    NL_PROP(FrameTime             , R ,   );
    NL_PROP(FrameTimingSource     , R ,   );
    NL_PROP(ViewAffine            , R , W );
    NL_PROP(ViewConstructionPlane , R ,   );
    NL_PROP(ViewExtents           , R , W );
    NL_PROP(ViewFov               , R , W );
    NL_PROP(ViewFrustum           , R ,   );
    NL_PROP(ViewPerspective       , R ,   );
    NL_PROP(ViewRotatable         , R ,   );
    NL_PROP(ViewTarget            , R ,   );
    NL_PROP(ViewsFront            , R ,   );
    NL_PROP(PivotPosition         , R , W );
    NL_PROP(PivotUser             ,   ,   );
    NL_PROP(PivotVisible          ,   , W );
    NL_PROP(HitLookfrom           ,   , W );
    NL_PROP(HitDirection          ,   , W );
    NL_PROP(HitAperture           ,   , W );
    NL_PROP(HitLookat             , R ,   );
    NL_PROP(HitSelectionOnly      ,   , W );
    NL_PROP(SelectionAffine       , R , W );
    NL_PROP(SelectionEmpty        , R ,   );
    NL_PROP(SelectionExtents      , R ,   );
    NL_PROP(ModelExtents          , R ,   );
    NL_PROP(PointerPosition       , R ,   );
    NL_PROP(CommandsTree          ,   ,   );
    NL_PROP(CommandsActiveSet     ,   ,   );
    NL_PROP(CommandsActiveCommand ,   , W );
    NL_PROP(Images                ,   ,   );
    NL_PROP(Settings              ,   ,   );
    NL_PROP(SettingsChanged       ,   , W );

    // TODO command tree

    // End of Navlib getters/setters
    
private:
    
    navlib::nlHandle_t Navlib {};
};

#endif