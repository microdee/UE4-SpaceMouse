$global:pluginFolder = ".\Plugins\SpaceMouse"
$global:pluginVersion = "0.7.0"
$global:pluginName = "SpaceMouse"
$global:testProjectName = "SpaceMouseTest"

function TestUe4Path {
    param (
        [string] $ue4path
    )
    $locUe4Path = "X:\XXXXX";
    if(-not ([string]::IsNullOrWhiteSpace($global:ue4Path))) {
        $locUe4Path = $global:ue4Path;
    }
    if(-not (Test-Path $locUe4Path)) {
        $global:ue4Path = $ue4path
    }
}

function Test-EnvironmentVariable {
    param (
        [string] $envvar
    )
    
    $res = [System.Environment]::GetEnvironmentVariable($envvar)
    return -not ([string]::IsNullOrWhiteSpace($res))
}
Export-ModuleMember -Function Test-EnvironmentVariable

function Write-Section {
    param (
        [string] $message
    )
"
$($message.ToUpper())
$("=" * $message.Length)
"
}
Export-ModuleMember -Function Write-Section

function Get-InternalUe4Path
{
    param (
        [Parameter()]
        [string]
        $Ue4DirName
    )
    # directory name of the associated UE4 engine version
    # this is not only the version but the entire folder name
    # but not the entire folder path
    if(Test-EnvironmentVariable "JOB_TARGET_UE4_VERSION") {
        $Ue4DirName = $env:JOB_TARGET_UE4_VERSION
    }

    # if you can't already see your folder containing your UE4 installations
    # please add it to this list with TestUe4Path X:\path\to\engines\$Ue4DirName
    # the first match from top will be used.
    TestUe4Path "C:\Program Files\Epic Games\$Ue4DirName"
    TestUe4Path "C:\ue4\$Ue4DirName"
    TestUe4Path "D:\ue4\$Ue4DirName"
    TestUe4Path "D:\$Ue4DirName"
}
Export-ModuleMember -Function Get-InternalUe4Path

function Assert-ErrorCode {
    param(
        [string] $message
    )
    
    if(-not ($LastExitCode -eq 0)) {
        Write-Error $message
        if(Test-EnvironmentVariable "CI_BUILD_REF_SLUG") {
            $host.SetShouldExit($LastExitCode)
            exit $LastExitCode
        } else {
            "Press Enter to continue..."
        }
    }
}
Export-ModuleMember -Function Assert-ErrorCode

function Assert-Exception {
    param (
        [string] $message
    )
    Write-Error $message
    if(Test-EnvironmentVariable "CI_BUILD_REF_SLUG") {
        $host.SetShouldExit(1)
        exit 1
    } else {
        "Press Enter to continue..."
    }
}
Export-ModuleMember -Function Assert-Exception

function Get-Ue4Path
{
    param (
        [Parameter()]
        [string]
        $Ue4DirName
    )

    Get-InternalUe4Path $Ue4DirName

    if(-not (Test-Path $global:ue4Path)) {
        Assert-Exception "Unreal Engine installation folder could not be found.
        Please add it in ProjectModule.psm1 with TestUe4Path X:\path\to\`$Ue4DirName"
    }
}
Export-ModuleMember -Function Get-Ue4Path

function Clear-OrCreate {
    param(
        [string] $path
    )

    if(-not (Test-Path $path)) {
        New-Item -Path $path -ItemType Directory
    }
    else {
        Write-Output "Clearing previous deployment"
        Get-ChildItem -Path $path | ForEach-Object {
            Remove-Item -Path $_.FullName -Force -Recurse
        }
    }
}
Export-ModuleMember -Function Clear-OrCreate

function Import-SevenZip {
    try {
        Import-Module 7Zip4Powershell
    }
    catch {
        # trying to import 7Zip4Powershell
        try {
            "Installing 7Zip4Powershell module"
            Install-Module -Scope CurrentUser -Name 7Zip4Powershell -Force
            Import-Module 7Zip4Powershell
        }
        catch {
            Write-Error $_
            Assert-Exception "Error installing/importing 7Zip module"
        }
    }
}
Export-ModuleMember -Function Import-SevenZip