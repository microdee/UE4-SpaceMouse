// Fill out your copyright notice in the Description page of Project Settings.


#include "SmRuntimeManager.h"

FUserSettings FSmRuntimeManager::GetUserSettings()
{
    static FUserSettings BaseSettings {};
    return BaseSettings;
}
