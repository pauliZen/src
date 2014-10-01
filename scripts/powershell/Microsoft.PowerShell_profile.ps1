# set profile name
# New-Variable sprof c:/Users/lwang/Documents/GitHub/src/scripts/powershell/Microsoft.PowerShell_profile.ps1

# awk
if (test-path "C:\Program Files (x86)\gawk-3.1.6-1\bin")
{$env:PATH="$env:PATH;C:\Program Files (x86)\gawk-3.1.6-1\bin"}
# gnuplot
if (test-path "C:\Program Files (x86)\gnuplot\bin")
{$env:PATH="$env:PATH;C:\Program Files (x86)\gnuplot\bin"}
# emacs
if (test-path "C:\Program Files (x86)\emacs-24.3\bin")
{$env:PATH="$env:PATH;C:\Program Files (x86)\emacs-24.3\bin"}
# sed
if (test-path "C:\Program Files (x86)\sed-4.2.1\bin")
{$env:PATH="$env:PATH;C:\Program Files (x86)\sed-4.2.1\bin"}
# grep
if (test-path "C:\Program Files (x86)\grep-2.5.4\bin")
{$env:PATH="$env:PATH;C:\Program Files (x86)\grep-2.5.4\bin"}
# svn
if (test-path "C:\Program Files (x86)\Apache-Subversion-1.8.10\bin")
{$env:PATH="$env:PATH;C:\Program Files (x86)\Apache-Subversion-1.8.10\bin"}

#set console color style
$Host.UI.RawUI.BackgroundColor = ($bckgrnd = 'Black')
$Host.UI.RawUI.ForegroundColor = 'White'
$Host.PrivateData.ErrorForegroundColor = 'Red'
$Host.PrivateData.ErrorBackgroundColor = $bckgrnd
$Host.PrivateData.WarningForegroundColor = 'Magenta'
$Host.PrivateData.WarningBackgroundColor = $bckgrnd
$Host.PrivateData.DebugForegroundColor = 'Yellow'
$Host.PrivateData.DebugBackgroundColor = $bckgrnd
$Host.PrivateData.VerboseForegroundColor = 'Green'
$Host.PrivateData.VerboseBackgroundColor = $bckgrnd
$Host.PrivateData.ProgressForegroundColor = 'Cyan'
$Host.PrivateData.ProgressBackgroundColor = $bckgrnd
Clear-Host

# list only name
# function l {Get-Childitem -name}

