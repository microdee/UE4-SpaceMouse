param (
    [string] $ue4PathArg = "UE_4.24"
)

Import-Module .\ProjectModule.psm1

[string] $buildConfig = "Development"

if(Test-EnvironmentVariable "CI_BUILD_REF_SLUG") {
    "This script is running in a Gitlab CI/CD environment. It should immediately exit on error."
} else {
    "This script is assumed to be running attended."
}

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

# initialize environment
Get-Ue4Path $ue4PathArg

$pluginCopyTargetDir = "$(Get-Location)\__deploy\$ue4PathArg"
$deployDir = "$(Get-Location)\deploy"

Clear-OrCreate $pluginCopyTargetDir
Clear-OrCreate $deployDir

# building:
.\GenerateProjects.ps1 $ue4PathArg

Write-Section "BUILDING $global:testProjectName EDITOR"

$ue4Bt = "$global:ue4Path\Engine\Binaries\DotNET\UnrealBuildTool.exe"
$ue4BtArgs = `
    "$($global:testProjectName)Editor", "Win64", "Development", `
    "-Project=`"$(Get-Location)\$global:testProjectName.uproject`""

& $ue4Bt $ue4BtArgs

Assert-ErrorCode "Building the editor has failed"

# copy files and create archive
Write-Section "COPY $global:pluginName TO DEPLOYMENT FOLDER"

Copy-Item -Path $global:pluginFolder -Destination "$pluginCopyTargetDir\$global:pluginName" -Force -Recurse -Exclude @("*\Intermediate\", "*.pdb")
Remove-Item -Path "$pluginCopyTargetDir\$global:pluginName\Intermediate" -Force -Recurse

try {
    "7Zipping plugin"
    Compress-7Zip -Path $pluginCopyTargetDir `
        -ArchiveFileName "$deployDir\$global:pluginName-$global:pluginVersion-$ue4PathArg.7z"
}
catch {
    Write-Error $_
    Assert-Exception "7Zipping plugin has failed"
}