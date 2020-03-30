
$global:ue4Path = ""
Import-Module .\ProjectModule.psm1

if(Test-EnvironmentVariable "CI_BUILD_REF_SLUG") {
    "This script is running in a Gitlab CI/CD environment. It should immediately exit on error."
} else {
    "This script is assumed to be running attended."
}

$pluginCopyTargetDir = "$(Get-Location)\__deploy\$ue4PathArg"
$deployDir = "$(Get-Location)\deploy"

Clear-OrCreate $deployDir

.\DeployForVersion.ps1 "UE_4.21"
.\DeployForVersion.ps1 "UE_4.22"
.\DeployForVersion.ps1 "UE_4.23"
.\DeployForVersion.ps1 "UE_4.24"
.\DeployForVersion.ps1 "UE_4.25"
