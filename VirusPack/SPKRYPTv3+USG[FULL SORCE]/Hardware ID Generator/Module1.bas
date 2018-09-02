Attribute VB_Name = "Module1"
Private Declare Function GetVolumeSerialNumber Lib "kernel32.dll" Alias "GetVolumeInformationA" (ByVal lpRootPathName As String, ByVal lpVolumeNameBuffer As String, ByVal nVolumeNameSize As Long, lpVolumeSerialNumber As Long, lpMaximumComponentLength As Long, lpFileSystemFlags As Long, ByVal lpFileSystemNameBuffer As String, ByVal nFileSystemNameSize As Long) As Long

Public Function HardwareID() As String
    Dim sVolLabel As String, sSerial As Long, sName As String
    Dim objCPUItem As Object, objCPU As Object
    Dim objBaseBoard As Object, objBoard As Object
  
    If GetVolumeSerialNumber(Left(Environ("windir"), 3), sVolLabel, 0, sSerial, 0, 0, sName, 0) Then
        HardwareID = Hex(sSerial)
    Else
        HardwareID = "00000000"
    End If
    
    Set objCPUItem = GetObject("winmgmts:").InstancesOf("Win32_Processor")

    If Err.Number = 0 Then
        For Each objCPU In objCPUItem
            HardwareID = HardwareID & objCPU.MaxClockSpeed
            HardwareID = HardwareID & objCPU.ProcessorId
        Next
        Set objCPUItem = Nothing
    End If

    Set objBaseBoard = GetObject("WinMgmts:").InstancesOf("Win32_BaseBoard")

    For Each objBoard In objBaseBoard
        HardwareID = HardwareID & objBoard.SerialNumber
        Exit For
    Next
    
    For i = 1 To Len(HardwareID)
        If IsNumeric(Mid(HardwareID, i, 1)) = True Then
            sTmp = sTmp + Mid(HardwareID, i, 1)
        End If
    Next
    
    For i = 1 To Len(sTmp)
        sresult = sresult & Mid(sTmp, i, 1) Mod 12
    Next
    
    HardwareID = encrypt(encrypt(StrReverse(sresult)))
    
    
End Function

