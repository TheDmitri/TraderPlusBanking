# Define the repository URL
$repoUrl = "git@github.com:Arkensor/DayZ-CommunityFramework.git"

# Define the relative path where you want to clone the repository
$relativeLocalPath = "requiredFramework\JM"

# Define the relative path to the .bat file inside the cloned repository
$relativeScriptPath = "\SetupWorkdrive.bat"

# Get the absolute path of the current script's directory
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition

# Construct the absolute paths
$localPath = Join-Path -Path $scriptDir -ChildPath $relativeLocalPath
$scriptPath = Join-Path -Path $localPath -ChildPath $relativeScriptPath

# Clone the repository
Write-Host "Cloning repository from $repoUrl to $localPath"
git clone $repoUrl $localPath

# Check if the repository was cloned successfully
if (Test-Path -Path $localPath) {
    Write-Host "Repository cloned successfully."

    # Check if the .bat file exists
    if (Test-Path -Path $scriptPath) {
        Write-Host "Executing script at $scriptPath"

        # Execute the .bat file
        Start-Process -FilePath "cmd.exe" -ArgumentList "/c `"$scriptPath`"" -Wait
    } else {
        Write-Host "Script not found at $scriptPath"
    }
} else {
    Write-Host "Failed to clone repository."
}

$repoUrl = "git@github.com:InclementDab/DayZ-Dabs-Framework.git"

# Define the relative path where you want to clone the repository
$relativeLocalPath = "requiredFramework\DabsFramework"

# Define the relative path to the .bat file inside the cloned repository
$relativeScriptPath = "\SetupWorkdrive.bat"

# Get the absolute path of the current script's directory
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition

# Construct the absolute paths
$localPath = Join-Path -Path $scriptDir -ChildPath $relativeLocalPath
$scriptPath = Join-Path -Path $localPath -ChildPath $relativeScriptPath

# Clone the repository
Write-Host "Cloning repository from $repoUrl to $localPath"
git clone $repoUrl $localPath

# Check if the repository was cloned successfully
if (Test-Path -Path $localPath) {
    Write-Host "Repository cloned successfully."

    # Check if the .bat file exists
    if (Test-Path -Path $scriptPath) {
        Write-Host "Executing script at $scriptPath"

        # Execute the .bat file
        Start-Process -FilePath "cmd.exe" -ArgumentList "/c `"$scriptPath`"" -Wait
    } else {
        Write-Host "Script not found at $scriptPath"
    }
} else {
    Write-Host "Failed to clone repository."
}

# Set your source directory containing the folders.
$sourceDir = ".\src"

# Set your target directory where you want to create the junctions.
$destinationDir = "P:\"

# Check if the source directory exists
if (-Not (Test-Path -Path $sourceDir)) {
    Write-Host "The specified source directory does not exist." -ForegroundColor Red
    return
}

# Check if the destination directory exists, if not create it
if (-Not (Test-Path -Path $destinationDir)) {
    New-Item -ItemType Directory -Path $destinationDir | Out-Null
}

# Get all directories in the source directory
$directories = Get-ChildItem -Path $sourceDir -Directory

foreach ($dir in $directories) {
    # The name of the junction to create in the destination directory
    $junctionName = $dir.Name

    # The full path for the new junction link
    $junctionPath = Join-Path -Path $destinationDir -ChildPath $junctionName

    # Create the junction link if it doesn't already exist
    if (-Not (Test-Path -Path $junctionPath)) {
        New-Item -ItemType Junction -Path $junctionPath -Value $dir.FullName | Out-Null
        Write-Host "Junction created: $junctionPath -> $($dir.FullName)" -ForegroundColor Green
    }
    else {
        Write-Host "A junction already exists at $junctionPath" -ForegroundColor Yellow
    }
}


