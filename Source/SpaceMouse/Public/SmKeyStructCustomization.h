// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"

/**
 * 
 */
class SPACEMOUSE_API FSmKeyStructCustomization
    : public IPropertyTypeCustomization
{
public:
    FSmKeyStructCustomization();
    ~FSmKeyStructCustomization();
    
    virtual void CustomizeHeader(
        TSharedRef<class IPropertyHandle> StructPropertyHandle,
        class FDetailWidgetRow& HeaderRow,
        IPropertyTypeCustomizationUtils& StructCustomizationUtils
    ) override;
    
    virtual void CustomizeChildren(
        TSharedRef<IPropertyHandle> StructPropertyHandle,
        class IDetailChildrenBuilder& ChildBuilder,
        IPropertyTypeCustomizationUtils& StructCustomizationUtils
    ) override { };
    
    virtual bool ShouldInlineKey() const override { return true; }
    
    void CustomizeHeaderOnlyWithButton(
        TSharedRef<class IPropertyHandle> StructPropertyHandle,
        class FDetailWidgetRow& HeaderRow,
        IPropertyTypeCustomizationUtils& StructCustomizationUtils,
        TSharedRef<SWidget> Button
    );
    
    static TSharedRef<IPropertyTypeCustomization> MakeInstance();

protected:

    TOptional<FKey> GetCurrentKey() const;
    void OnKeyChanged(TSharedPtr<FKey> SelectedKey);
    TSharedPtr<IPropertyHandle> PropertyHandle;
};
