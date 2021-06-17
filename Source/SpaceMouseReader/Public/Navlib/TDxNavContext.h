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
        auto InVal = static_cast<F##Name##Property::FTypeNL>(*value); \
        reinterpret_cast<MSelf*>(param)->Name.SetCached(InVal); \
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
class SPACEMOUSEREADER_API FTDxNavContextBase
{
    
public:
    
    FTDxNavContextBase();
    virtual ~FTDxNavContextBase();

    void Open();
    
protected:
    virtual void OnPreOpen(TArray<navlib::accessor_t>& Accessors) {}
    virtual void OnPostOpen() {}
    
public:
    /** Name of this instance of a navigation context */
    virtual FString GetProfileName() = 0;

    // Navlib properties with their boilerplate

    NL_PROP(FTDxNavContextBase, Active                ,   ,   );
    NL_PROP(FTDxNavContextBase, Focus                 ,   ,   );
    NL_PROP(FTDxNavContextBase, Motion                ,   , W );
    NL_PROP(FTDxNavContextBase, CoordinateSystem      , R ,   );
    NL_PROP(FTDxNavContextBase, DevicePresent         ,   ,   );
    NL_PROP(FTDxNavContextBase, EventsKeyPress        ,   , W );
    NL_PROP(FTDxNavContextBase, EventsKeyRelease      ,   , W );
    NL_PROP(FTDxNavContextBase, Transaction           ,   , W );
    NL_PROP(FTDxNavContextBase, FrameTime             , R ,   );
    NL_PROP(FTDxNavContextBase, FrameTimingSource     , R ,   );
    NL_PROP(FTDxNavContextBase, ViewAffine            , R , W );
    NL_PROP(FTDxNavContextBase, ViewConstructionPlane , R ,   );
    NL_PROP(FTDxNavContextBase, ViewExtents           , R , W );
    NL_PROP(FTDxNavContextBase, ViewFov               , R , W );
    NL_PROP(FTDxNavContextBase, ViewFrustum           , R ,   );
    NL_PROP(FTDxNavContextBase, ViewPerspective       , R ,   );
    NL_PROP(FTDxNavContextBase, ViewRotatable         , R ,   );
    NL_PROP(FTDxNavContextBase, ViewTarget            , R ,   );
    NL_PROP(FTDxNavContextBase, ViewsFront            , R ,   );
    NL_PROP(FTDxNavContextBase, PivotPosition         , R , W );
    NL_PROP(FTDxNavContextBase, PivotUser             ,   ,   );
    NL_PROP(FTDxNavContextBase, PivotVisible          ,   , W );
    NL_PROP(FTDxNavContextBase, HitLookfrom           ,   , W );
    NL_PROP(FTDxNavContextBase, HitDirection          ,   , W );
    NL_PROP(FTDxNavContextBase, HitAperture           ,   , W );
    NL_PROP(FTDxNavContextBase, HitLookat             , R ,   );
    NL_PROP(FTDxNavContextBase, HitSelectionOnly      ,   , W );
    NL_PROP(FTDxNavContextBase, SelectionAffine       , R , W );
    NL_PROP(FTDxNavContextBase, SelectionEmpty        , R ,   );
    NL_PROP(FTDxNavContextBase, SelectionExtents      , R ,   );
    NL_PROP(FTDxNavContextBase, ModelExtents          , R ,   );
    NL_PROP(FTDxNavContextBase, PointerPosition       , R ,   );
    NL_PROP(FTDxNavContextBase, CommandsTree          ,   ,   );
    NL_PROP(FTDxNavContextBase, CommandsActiveSet     ,   ,   );
    NL_PROP(FTDxNavContextBase, CommandsActiveCommand ,   , W );
    NL_PROP(FTDxNavContextBase, Images                ,   ,   );
    NL_PROP(FTDxNavContextBase, Settings              ,   ,   );
    NL_PROP(FTDxNavContextBase, SettingsChanged       ,   , W );

    // TODO command tree

    // End of Navlib getters/setters
    
private:
    
    navlib::nlHandle_t Navlib {};
};

class SPACEMOUSEREADER_API FTDxNavContext : public FTDxNavContextBase
{
protected:
    virtual void OnPostOpen() override;
public:
    virtual void OnCoordinateSystemGet(FCoordinateSystemProperty& InValue) override;
    virtual void OnViewsFrontGet(FViewsFrontProperty& InValue) override;
    virtual void OnFrameTimeGet(FFrameTimeProperty& InValue) override;
    virtual void OnFrameTimingSourceGet(FFrameTimingSourceProperty& InValue) override;
};

#endif