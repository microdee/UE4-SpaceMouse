// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE

// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppNonExplicitConversionOperator
#include "SmKey.h"

FSmKey::FSmKey(const FKey& InKey)
    : Key(InKey)
{
}

FSmKey::FSmKey(const FName InName)
    : Key(InName)
{
}

FSmKey::FSmKey(const TCHAR* InName)
    : Key(InName)
{
}

FSmKey::FSmKey(const ANSICHAR* InName)
    : Key(InName)
{
}

bool FSmKey::SerializeFromMismatchedTag(FPropertyTag const& Tag, FStructuredArchive::FSlot Slot)
{
    return Key.SerializeFromMismatchedTag(Tag, Slot);
}

bool FSmKey::ExportTextItem(FString& ValueStr, FKey const& DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const
{
    return Key.ExportTextItem(ValueStr, DefaultValue, Parent, PortFlags, ExportRootScope);
}

bool FSmKey::ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText)
{
    return Key.ImportTextItem(Buffer, PortFlags, Parent, ErrorText);
}

void FSmKey::PostSerialize(const FArchive& Ar)
{
    Key.PostSerialize(Ar);
}

void FSmKey::PostScriptConstruct()
{
    Key.PostScriptConstruct();
}

FSmKey::operator FKey() const
{
    return Key;
}
