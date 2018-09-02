Attribute VB_Name = "Module1"
'---------------------------------------------------------------------------------------
' Module        : mVirtualized
' Author        : Karcrack
' Date          : 09/09/09
' Used for?     : Detect Virtualized Machines... like VMWare/V.PC/QEmu...
' Tested On     :
'                   - Virtual PC 2007, 1.0      (Tested by: KIASH!)
'                   - VMWare ,6.5.3.185404      (Tested by: SkyWeb!)
'
' Reference     :
'                   :http://www.cs.nps.navy.mil/people/faculty/irvine/publications/2000/VMM-usenix00-0611.pdf
'                   :http://invisiblethings.org/papers/redpill.html
'                   :http://www.ntsecurity.nu/onmymind/2007/2007-02-27.html
'                   :http://blog.assarbad.net/wp-content/uploads/2006/11/redpill_getting_colorless.pdf
'---------------------------------------------------------------------------------------
Global isinsandboxEs

Private Declare Function CreateToolhelp32Snapshot Lib "kernel32" (ByVal dwFlags As Long, ByVal th32ProcessID As Long) As Long
    
Private Declare Function Module32First Lib "kernel32" (ByVal hSnapShot As Long, lppe As MODULEENTRY32) As Long

Private Declare Function Module32Next Lib "kernel32" (ByVal hSnapShot As Long, lppe As MODULEENTRY32) As Long

Private Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long

Private Declare Function GetCurrentProcessId Lib "kernel32" () As Long

Private Declare Function RegOpenKeyEx Lib "advapi32" Alias "RegOpenKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal ulOptions As Long, ByVal samDesired As Long, ByRef phkResult As Long) As Long

Private Declare Function RegQueryValueEx Lib "advapi32" Alias "RegQueryValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal lpReserved As Long, ByRef lpType As Long, ByVal lpData As String, ByRef lpcbData As Long) As Long

Private Declare Function RegCloseKey Lib "advapi32" (ByVal hKey As Long) As Long

Private Type MODULEENTRY32
    dwSize As Long
    th32ModuleID As Long
    th32ProcessID As Long
    GlblcntUsage As Long
    ProccntUsage As Long
    modBaseAddr As Byte
    modBaseSize As Long
    hModule As Long
    szModule As String * 256
    szExePath As String * 1024
End Type

Const HKEY_LOCAL_MACHINE = &H80000002
Const REG_SZ = 1&
Const KEY_ALL_ACCESS = &H3F
Const TH32CS_SNAPMODULE = &H8
'USER32
Private Declare Function CallThunk8 Lib "USER32" Alias "CallWindowProcW" (ByRef cThunk As Currency, Optional ByVal Param1 As Long, Optional ByVal Param2 As Long, Optional ByVal Param3 As Long, Optional ByVal Param4 As Long) As Long
 
Public Function ImVirtualized() As Boolean
    Dim tIDT(2 + 4)     As Byte
 
'    mov ecx, [esp+4]\
'    sidt [ecx]       |->; -439297879751758.3221@
'    retn            /
 
    Call CallThunk8(-439297879751758.3221@, ByVal VarPtr(tIDT(0)))
    ImVirtualized = (tIDT(5) > &HD0)
End Function

'---------------------------------------------------------------------------------------
' Module      : mDetectVM
' DateTime    : 03/07/2008 07:32
' Author      : Cobein
' Mail        : cobein27@hotmail.com
' WebPage     : http://cobein27.googlepages.com/vb6
' Purpose     : Mini Virtual Machine detection module
' Usage       : At your own risk
' Requirements: None
' Distribution: You can freely use this code in your own
'               applications, but you may not reproduce
'               or publish this code on any web site,
'               online service, or distribute as source
'               on any media without express permission.
'
' History     : 03/07/2008 First Cut....................................................
'---------------------------------------------------------------------------------------
'Detect 5 Different Sandboxes
'Coded by stoopid
'
' Detects:
'   -> Sandboxie : http://www.sandboxie.com/
'   -> ThreatExpert : http://www.threatexpert.com/
'   -> Anubis : http://anubis.iseclab.org/
'   -> CWSandbox : http://www.cwsandbox.org/
'   -> JoeBox : http://www.joebox.org/
'




Public Function IsVirtualPCPresent() As Long
    Dim lhKey       As Long
    Dim sBuffer     As String
    Dim lLen        As Long

    If RegOpenKeyEx(&H80000002, "SYSTEM\ControlSet001\Services\Disk\Enum", _
       0, &H20019, lhKey) = 0 Then
        sBuffer = Space$(255): lLen = 255
        If RegQueryValueEx(lhKey, "0", 0, 1, ByVal sBuffer, lLen) = 0 Then
            sBuffer = UCase(Left$(sBuffer, lLen - 1))
            Select Case True
                Case sBuffer Like "*VIRTUAL*":   IsVirtualPCPresent = 1
                Case sBuffer Like "*VMWARE*":    IsVirtualPCPresent = 2
                Case sBuffer Like "*VBOX*":      IsVirtualPCPresent = 3
            End Select
        End If
        Call RegCloseKey(lhKey)
    End If
End Function



Public Function IsInSandbox() As Long
Dim hKey As Long, hOpen As Long, hQuery As Long, hSnapShot As Long
Dim me32 As MODULEENTRY32
Dim szBuffer As String * 128
hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId)
me32.dwSize = Len(me32)
Module32First hSnapShot, me32
Do While Module32Next(hSnapShot, me32) <> 0
    If InStr(1, LCase(me32.szModule), "sbiedll.dll") > 0 Then 'Sandboxie
        isinsandboxEs = 1
   
    ElseIf InStr(1, LCase(me32.szModule), "dbghelp.dll") > 0 Then 'ThreatExpert
        isinsandboxEs = 2
    End If
Loop
CloseHandle (hSnapShot)
If IsInSandbox = False Then
    hOpen = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\Microsoft\Windows\CurrentVersion", 0, KEY_ALL_ACCESS, hKey)
    If hOpen = 0 Then
        hQuery = RegQueryValueEx(hKey, "ProductId", 0, REG_SZ, szBuffer, 128)
        If hQuery = 0 Then
            If InStr(1, szBuffer, "76487-337-8429955-22614") > 0 Then 'Anubis
                isinsandboxEs = 3
            ElseIf InStr(1, szBuffer, "76487-644-3177037-23510") > 0 Then 'CWSandbox
                isinsandboxEs = 4
            ElseIf InStr(1, szBuffer, "55274-640-2673064-23950") > 0 Then 'JoeBox
                isinsandboxEs = 5
            End If
        End If
    End If
    RegCloseKey (hKey)
End If

End Function

Public Function CheckAntis()
Call IsInSandbox
Call IsVirtualPCPresent
End Function

Public Function Tegen()
    If AntiSandBoxie = 1 And isinsandboxEs = 1 Then: End
    If AntiThreatExpert = 1 And isinsandboxEs = 2 Then: End
    If AntiAnubis = 1 And isinsandboxEs = 3 Then: End
    If AntiCWSandBox = 1 And isinsandboxEs = 4 Then: End
    If AntiJoeBox = 1 And isinsandboxEs = 5 Then: End
    If AntiVMware = 1 And IsVirtualPCPresent = 1 Then: End
    If AntiVirtualPC = 1 And IsVirtualPCPresent = 2 Then: End
    If AntiVirtualBox = 1 And IsVirtualPCPresent = 3 Then: End
End Function




