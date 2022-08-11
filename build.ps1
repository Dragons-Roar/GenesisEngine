$app = $args[0]
$config = $args[1]
$platform = $args[2]
$system = $args[3]

$testApp = "NONE"
if($args.Length -ge 5) {
	$testApp = $args[4]
	$testDir = "bin/${system}/${config}/${testApp}"
	$testApp = "${testApp}.exe"
}
$outdir = "bin/${system}/${config}/${app}/"
$appFile = "${app}.exe"

# Find Visual Studio and MSBuild
Write-Host "Searching VSWhere..."
if($vsWhere = Get-Command "vswhere.exe" -ErrorAction SilentlyContinue) {
	$vsWhere = $vsWhere.Path
} elseif(Test-Path "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe") {
	$vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
} else {
	Write-Error "vswhere not found. Aborting." -ErrorAction Stop	
}
Write-Host "VSWhere found at: $vsWhere" -ForegroundColor Green

# Get Path to Visual Studio
Write-Host "Searching for Visual Studio..."
$vsPath = & $vsWhere -latest -products * -version "[15.0, 22.0)" `
	-requires Microsoft.Component.MSBuild `
	-property installationpath

If ([string]::IsNullOrEmpty("$vsPath")) {
	Write-Error "Failed to find Visual Studio installation. Aborting." -ErrorAction Stop
}
Write-Host "Using Visual Studio installation at: ${vsPath}" -ForegroundColor Green

# Set Visual Studio CMD Variables
Write-Host "Setting Visual Stuido CMD Variables..." -ForegroundColor Yellow

if(Test-Path env:LIBPATH) {
	Write-Host "Visual Studio Command Prompt variables already set." -ForegroundColor Yellow
} else {
	# Load VC vars
	Push-Location "${vsPath}\VC\Auxiliary\Build"
	cmd /c "vcvarsall.bat x64&set" |
	ForEach-Object {
		If($_ -match "=") {
			$v = $_.split("="); Set-Item -Force -Path "ENV:\$($v[0])" -Value "$($v[1])"
		}
	}
	Pop-Location
	Write-Host "Visual Studio Command Prompt variables set." -ForegroundColor Green
}

$msbuild = "${vsPath}/Msbuild/Current/Bin/MSBuild.exe"

# Build using premake
Write-Host "Building..." -ForegroundColor Yellow
premake5.exe vs2022

if($? -ne "True") {
	Write-Error "Failed building!"
	Exit
}

Write-Host "Builded successfully!" -ForegroundColor Green

Write-Host "Compiling..." -ForegroundColor Yellow
Write-Host "${platform}"

& "${msbuild}" GenesisEngine.sln /p:Configuration=${config} /p:Platform=${platform} -verbosity:minimal

if($? -ne "True") {
	Write-Error "Failed compiling!"
}

Write-Host "Compiled successfully!" -ForegroundColor Green

if($testApp -ne "NONE") {
	Write-Host "Running Tests '${testDir}/${testApp}'" -ForegroundColor Yellow
	$tempPath = Get-Location

	Set-Location $testDir
	& "./${testApp}"

	if($? -ne "True") {
		Set-Location $tempPath
		Write-Error "Tests Failed!"
	} else {
		Write-Host "Tests Passed!" -ForegroundColor Green
	}
	
	Set-Location $tempPath
}


if($app -ne "NONE") {
	$tempPath = Get-Location
	Set-Location $outdir
	& "./${appFile}"
	Set-Location $tempPath
}
