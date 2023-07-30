// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"
#include "SmUeVersion.h"

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

    // New functions in UE 4.26
#if UE_VERSION >= MAKE_UE_VERSION(4, 26)
    
    virtual bool ShouldInlineKey() const override { return true; }
    
#endif
    
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
