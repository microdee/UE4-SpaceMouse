$global:pluginVersion = "1.0.2"
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

function Get-UeVersionFromDirName {
    param (
        [string] $dirName
    )
    if($dirName -match "4\.\d\d") {
        return $Matches.0
    }
    else {
        Assert-Exception "UE4 version cannot be derived from its directory name."
    }
}
Export-ModuleMember -Function Get-UeVersionFromDirName

function Set-ProjectAssociatedUe {
    param (
        [string] $dirName
    )
    $ueVersion = Get-UeVersionFromDirName $dirName
    if([string]::IsNullOrWhiteSpace($ueVersion)) {
        Assert-Exception "Cannot decide on associated UE4 version."
    }
    else {
        [string] $projectPath = "$(Get-Location)\$global:testProjectName.uproject"
        $ueProject = [System.IO.File]::ReadAllText($projectPath);
        $output = ($ueProject -replace "`"EngineAssociation`"\:\s?`"4\.\d\d`"", "`"EngineAssociation`": `"$ueVersion`"")
        [System.IO.File]::WriteAllText($projectPath, $output)
    }
}
Export-ModuleMember -Function Set-ProjectAssociatedUe

function Clear-PreviousBuild {

    if(Test-Path .\Intermediate) {
        "Clearing Intermediate of $global:testProjectName"
        Remove-Item .\Intermediate -Recurse -Force
    }
    if(Test-Path .\Binaries) {
        "Clearing Binaries of $global:testProjectName"
        Remove-Item .\Binaries -Recurse -Force
    }

    Get-ChildItem "$PSScriptRoot\Plugins" | ForEach-Object {
        Push-Location $_.FullName

        if(Test-Path .\Intermediate) {
            "Clearing Intermediate of $($_.BaseName)"
            Remove-Item .\Intermediate -Recurse -Force
        }
        if(Test-Path .\Binaries) {
            "Clearing Binaries of $($_.BaseName)"
            Remove-Item .\Binaries -Recurse -Force
        }

        Pop-Location
    }

}
Export-ModuleMember -Function Clear-PreviousBuild

function Clear-PluginFromEngine
{
    param (
        [string] $PluginName
    )
    $enginePluginPath = "$global:ue4Path\Engine\Plugins\Marketplace\$PluginName";

    if(Test-Path $enginePluginPath) {
        "Removing $PluginName instance from Engine plugins"
        Remove-Item $enginePluginPath -Recurse -Force
    }
}
Export-ModuleMember -Function Clear-PluginFromEngine

function Build-Plugin {
    param (
        [string] $PluginName
    )
    
    Write-Section "PACKAGING $PluginName $global:pluginVersion"

    $enginePluginPath = "$global:ue4Path\Engine\Plugins\Marketplace\$PluginName";
    $packagedOutputPath = "$PSScriptRoot\__deploy\temp\$PluginName";
    
    if(Test-Path $packagedOutputPath) {
        "Clearing previous packaged instance of $PluginName"
        Remove-Item $packagedOutputPath -Recurse -Force
    }

    $ue4At = "$global:ue4Path\Engine\Binaries\DotNET\AutomationTool.exe"
    $ue4AtArgs = `
        "BuildPlugin", `
        "-Plugin=`"$PSScriptRoot\Plugins\$PluginName\$PluginName.uplugin`"", `
        "-Package=`"$packagedOutputPath`"", `
        "-CreateSubFolder"
    
    "Executing: $ue4At"
    "with arguments: $ue4AtArgs"
    
    & $ue4At $ue4AtArgs
    
    Assert-ErrorCode "Packaging $PluginName has failed"

    Copy-Item -Path $packagedOutputPath -Destination $enginePluginPath -Force -Recurse
}
Export-ModuleMember -Function Build-Plugin