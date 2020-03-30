param (
    [string] $ue4PathArg = "UE_4.24"
)

Import-Module .\ProjectModule.psm1

Write-Section "DEPLOYING $global:pluginName $global:pluginVersion for $ue4PathArg"

Import-SevenZip

# initialize environment
Get-Ue4Path $ue4PathArg

$pluginCopyTargetDir = "$(Get-Location)\__deploy\$ue4PathArg"
$deployDir = "$(Get-Location)\deploy"

if(-not (Test-Path $deployDir)) {
    New-Item -Path $deployDir -ItemType Directory
}

Clear-OrCreate $pluginCopyTargetDir
Clear-PreviousBuild

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