// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#if WITH_3DX_NAVLIB

#include "CoreMinimal.h"

#include <navlib/navlib_types.h>

class FTDxNavConnection;


#define REGISTER_PROP(type, prop, ...) \
    { TNavlibAccessor<type> $(prop); \
    __VA_ARGS__ \
    Connection->AddAccessor($, Accessors); }

/**
* 
*/
template<typename TVal>
struct TNavlibAccessor
{
    DECLARE_DELEGATE_RetVal(FTDxNavContext::TResult<TVal>, FGetterDel);
    DECLARE_DELEGATE_OneParam(FSetterDel, TVal);

    explicit TNavlibAccessor(navlib::property_t InTargetProperty)
        : TargetProperty(InTargetProperty)
    { }
    
    navlib::property_t TargetProperty;
    FGetterDel Getter {};
    FSetterDel Setter {};
};

class FTDxNavConnection
{
    template<typename TVal>
    struct TPerInstanceData
    {
        TMap<navlib::property_t, TNavlibAccessor<TVal>> Properties;
    };
    
    template<typename TVal>
    static TMap<navlib::param_t, TPerInstanceData<TVal>> Accessor;

public:
    template<typename TVal>
    static long GetterWrap(const navlib::param_t param, const navlib::property_t name, navlib::value_t *value)
    {
        using namespace navlib;
        
        if(Accessor<TVal>[param].Properties[name].Getter.IsBound())
        {
            auto [Val, Result] = Accessor<TVal>[param].Properties[name].Getter.Execute();
            if(Result) return Result;
            *value = Val;
            return 0;
        }
        return make_result_code(navlib_errc::function_not_supported);
    }
    
    template<typename TVal>
    static long SetterWrap(const navlib::param_t param, const navlib::property_t name, const navlib::value_t *value)
    {
        using namespace navlib;
        
        if(Accessor<TVal>[param].Properties[name].Setter.IsBound())
        {
            Accessor<TVal>[param].Properties[name].Setter.Execute(*value);
            return 0;
        }
        return make_result_code(navlib_errc::function_not_supported);
    }
    
    template<typename TVal>
    void AddAccessor(
        TNavlibAccessor<TVal> InAccessor,
        TArray<navlib::accessor_t>& OutArray
    ) {
        using namespace navlib;
        
        auto Self = reinterpret_cast<param_t>(this);
        if(!Accessor<TVal>.Contains(Self))
            Accessor<TVal>.Add(Self);
        Accessor<TVal>[Self].Properties.Add(InAccessor.TargetProperty, InAccessor);

        accessor_t NlAccessor;
        NlAccessor.name = InAccessor.TargetProperty;
        NlAccessor.fnGet = InAccessor.Getter.IsBound() ? &FTDxNavConnection::GetterWrap<TVal> : nullptr;
        NlAccessor.fnSet = InAccessor.Setter.IsBound() ? &FTDxNavConnection::SetterWrap<TVal> : nullptr;
        NlAccessor.param = Self;
        
        OutArray.Add(NlAccessor);
    }
};

#endif