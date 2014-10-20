# set encoding
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

# set profile name
New-Variable -Name sprof -Value c:/Users/lwang/Documents/GitHub/src/scripts/powershell/Microsoft.PowerShell_profile.ps1 -Scope Global
New-Variable -Name data -Value C:\Users\lwang\OneDrive\Documents\Datas -Scope Global
New-Variable -Name src -Value C:\Users\lwang\Documents\GitHub\src -Scope Global
New-Variable -Name code -Value C:\Users\lwang\Documents\code -Scope Global
New-Variable -Name writing -Value C:\Users\lwang\OneDrive\Documents\Writing -Scope Global

New-Variable -Name nbtools -Value ${src}\Nbody\Tools -Scope Global

# gnuwin32
if (test-path "C:\Program Files (x86)\GnuWin32\bin")
{$env:PATH="$env:PATH;C:\Program Files (x86)\GnuWin32\bin"}
# gnuplot
if (test-path "C:\Program Files (x86)\gnuplot\bin")
{$env:PATH="$env:PATH;C:\Program Files (x86)\gnuplot\bin"}
# emacs
if (test-path "C:\Program Files (x86)\emacs-24.3\bin")
{$env:PATH="$env:PATH;C:\Program Files (x86)\emacs-24.3\bin"}
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
function global:l {Get-Childitem -name}

# proxy switcher
Function global:set-proxy ($x)
{
    $varPath=¡±HKCU:\Software\Microsoft\Windows\CurrentVersion\Internet Settings¡±
    if($x -eq "on")
    {      
        set-itemproperty -path $varPath proxyenable -value 1
        set-itemproperty -path $varPath proxyhttp1.1 -value 0
        set-itemproperty -path $varPath proxyserver -value "127.0.0.1:8087"
        set-itemproperty -path $varPath ProxyOverride -value "<local>"
    }
    else
    {
        set-itemproperty -path $varPath proxyenable -value 0
        set-itemproperty -path $varPath proxyhttp1.1 -value 1
    }
}
