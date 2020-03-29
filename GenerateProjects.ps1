param (
    [string] $ue4PathArg = "UE_4.24"
)

Import-Module .\ProjectModule.psm1

Get-Ue4Path $ue4PathArg

Write-Section "Generating $global:testProjectName"

$ue4Bt = "$global:ue4Path\Engine\Binaries\DotNET\UnrealBuildTool.exe"
$ue4BtArgs = `
    "-projectfiles", `
    "-project=`"$(Get-Location)\$global:testProjectName.uproject`"", `
    "-game", "-rocket", "-progress" `

& $ue4Bt $ue4BtArgs

Assert-ErrorCode "Generating $global:testProjectName project files are failed"