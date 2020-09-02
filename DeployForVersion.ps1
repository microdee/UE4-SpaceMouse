param (
    [string] $ue4PathArg = "UE_4.25"
)

# urgh wugly, ugly but barely works
$global:ue4Path = ""
Import-Module .\ProjectModule.psm1

Write-Section "DEPLOYING $global:pluginName $global:pluginVersion for $ue4PathArg"

Import-SevenZip

# initialize environment
Get-Ue4Path $ue4PathArg

Write-Section "SWITCHING TO $ue4PathArg"

$pluginCopyTargetDir = "$PSScriptRoot\__deploy\$ue4PathArg"
$pluginTempDir = "$PSScriptRoot\__deploy\temp"
$deployDir = "$PSScriptRoot\deploy"

if(-not (Test-Path $deployDir)) {
    New-Item -Path $deployDir -ItemType Directory
}

Clear-OrCreate $pluginCopyTargetDir
Clear-OrCreate $pluginTempDir
Clear-PreviousBuild

# building:

Clear-PluginFromEngine $global:pluginName
Clear-PluginFromEngine "HIDUE"
Build-Plugin "HIDUE"
Copy-Item -Path "$PSScriptRoot\__deploy\temp\HIDUE" -Destination "$pluginCopyTargetDir\HIDUE" -Force -Recurse

Build-Plugin $global:pluginName
Copy-Item -Path "$PSScriptRoot\__deploy\temp\$global:pluginName" -Destination "$pluginCopyTargetDir\$global:pluginName" -Force -Recurse

try {
    "7Zipping plugin"
    Compress-7Zip -Path $pluginCopyTargetDir `
        -ArchiveFileName "$deployDir\$global:pluginName-$global:pluginVersion-$ue4PathArg.7z"
}
catch {
    Write-Error $_
    Assert-Exception "7Zipping plugin has failed"
}