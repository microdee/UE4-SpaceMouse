param (
    [string] $ue4PathArg = "UE_4.25"
)

# urgh wugly, ugly but barely works
$global:ue4Path = ""
Import-Module .\ProjectModule.psm1

Get-Ue4Path $ue4PathArg

Write-Section "Generating $global:testProjectName"

Set-ProjectAssociatedUe $ue4PathArg

$ue4Bt = "$global:ue4Path\Engine\Binaries\DotNET\UnrealBuildTool.exe"
$ue4BtArgs = `
    "-projectfiles", `
    "-project=`"$(Get-Location)\$global:testProjectName.uproject`"", `
    "-game", "-rocket", "-progress" `

"Executing: $ue4Bt"
"with arguments: $ue4BtArgs"

& $ue4Bt $ue4BtArgs

Assert-ErrorCode "Generating $global:testProjectName project files are failed"