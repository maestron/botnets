Attribute VB_Name = "mIconChanger"
'=====================================================================
'Module: mIconChanger.bas
'By: ZeR0/0cm4n for HackHound.org
'Works on all Icon Sizes
'Based on Tughack's C Icon Changer
'First Release: 28 June 2009
'To Do: Delete Old Icon Resource, Extract Icon
'=====================================================================
Option Explicit

Private Const OPEN_EXISTING             As Long = &H3
Private Const INVALID_HANDLE_VALUE      As Long = -1
Private Const GENERIC_READ              As Long = &H80000000
Private Const FILE_ATTRIBUTE_NORMAL     As Long = &H80
Private Const FILE_BEGIN                As Long = &H0
Private Const RT_ICON                   As Long = &H3
Private Const RT_GROUP_ICON             As Long = &HE

Private Type ICONDIRENTRY
    bWidth          As Byte
    bHeight         As Byte
    bColorCount     As Byte
    bReserved       As Byte
    wPlanes         As Integer
    wBitCount       As Integer
    dwBytesInRes    As Long
    dwImageOffset   As Long
End Type
 
Private Type ICONDIR
    idReserved      As Integer
    idType          As Integer
    idCount         As Integer
End Type
 
Private Type GRPICONDIRENTRY
    bWidth          As Byte
    bHeight         As Byte
    bColorCount     As Byte
    bReserved       As Byte
    wPlanes         As Integer
    wBitCount       As Integer
    dwBytesInRes    As Long
    nID             As Integer
End Type
 
Private Type GRPICONDIR
    idReserved      As Integer
    idType          As Integer
    idCount         As Integer
    idEntries()     As GRPICONDIRENTRY
End Type

Private Declare Function CreateFile Lib "kernel32" Alias "CreateFileA" (ByVal lpFileName As String, ByVal dwDesiredAccess As Long, ByVal dwShareMode As Long, lpSecurityAttributes As Any, ByVal dwCreationDisposition As Long, ByVal dwFlagsAndAttributes As Long, ByVal hTemplateFile As Long) As Long
Private Declare Function ReadFile Lib "kernel32" (ByVal lFile As Long, lpBuffer As Any, ByVal nNumberOfBytesToRead As Long, lpNumberOfBytesRead As Long, lpOverlapped As Any) As Long
Private Declare Function SetFilePointer Lib "kernel32" (ByVal lFile As Long, ByVal lDistanceToMove As Long, lpDistanceToMoveHigh As Long, ByVal dwMoveMethod As Long) As Long
Private Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long
Private Declare Function BeginUpdateResource Lib "kernel32" Alias "BeginUpdateResourceA" (ByVal pFileName As String, ByVal bDeleteExistingResources As Long) As Long
Private Declare Function UpdateResource Lib "kernel32" Alias "UpdateResourceA" (ByVal lUpdate As Long, ByVal lpType As Long, ByVal lpName As Long, ByVal wLanguage As Long, lpData As Any, ByVal cbData As Long) As Long
Private Declare Function EndUpdateResource Lib "kernel32" Alias "EndUpdateResourceA" (ByVal lUpdate As Long, ByVal fDiscard As Long) As Long
Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)

Public Function ChangeIcon(ByVal strExePath As String, ByVal strIcoPath As String) As Boolean
    Dim lFile               As Long
    Dim lUpdate             As Long
    Dim lRet                As Long
    Dim i                   As Integer
    Dim tICONDIR            As ICONDIR
    Dim tGRPICONDIR         As GRPICONDIR
    Dim tICONDIRENTRY()     As ICONDIRENTRY
   
    Dim bIconData()         As Byte
    Dim bGroupIconData()    As Byte
   
    lFile = CreateFile(strIcoPath, GENERIC_READ, 0, ByVal 0&, OPEN_EXISTING, 0, ByVal 0&)
   
    If lFile = INVALID_HANDLE_VALUE Then
        ChangeIcon = False
        CloseHandle (lFile)
        Exit Function
    End If
   
    Call ReadFile(lFile, tICONDIR, Len(tICONDIR), lRet, ByVal 0&)
   
    ReDim tICONDIRENTRY(tICONDIR.idCount - 1)
   
    For i = 0 To tICONDIR.idCount - 1
        Call ReadFile(lFile, tICONDIRENTRY(i), Len(tICONDIRENTRY(i)), lRet, ByVal 0&)
    Next i
   
    ReDim tGRPICONDIR.idEntries(tICONDIR.idCount - 1)
   
    tGRPICONDIR.idReserved = tICONDIR.idReserved
    tGRPICONDIR.idType = tICONDIR.idType
    tGRPICONDIR.idCount = tICONDIR.idCount
   
    For i = 0 To tGRPICONDIR.idCount - 1
        tGRPICONDIR.idEntries(i).bWidth = tICONDIRENTRY(i).bWidth
        tGRPICONDIR.idEntries(i).bHeight = tICONDIRENTRY(i).bHeight
        tGRPICONDIR.idEntries(i).bColorCount = tICONDIRENTRY(i).bColorCount
        tGRPICONDIR.idEntries(i).bReserved = tICONDIRENTRY(i).bReserved
        tGRPICONDIR.idEntries(i).wPlanes = tICONDIRENTRY(i).wPlanes
        tGRPICONDIR.idEntries(i).wBitCount = tICONDIRENTRY(i).wBitCount
        tGRPICONDIR.idEntries(i).dwBytesInRes = tICONDIRENTRY(i).dwBytesInRes
        tGRPICONDIR.idEntries(i).nID = i + 1
    Next i
   
    lUpdate = BeginUpdateResource(strExePath, False)
    For i = 0 To tICONDIR.idCount - 1
        ReDim bIconData(tICONDIRENTRY(i).dwBytesInRes)
        SetFilePointer lFile, tICONDIRENTRY(i).dwImageOffset, ByVal 0&, FILE_BEGIN
        Call ReadFile(lFile, bIconData(0), tICONDIRENTRY(i).dwBytesInRes, lRet, ByVal 0&)
   
        If UpdateResource(lUpdate, RT_ICON, tGRPICONDIR.idEntries(i).nID, 0, bIconData(0), tICONDIRENTRY(i).dwBytesInRes) = False Then
            ChangeIcon = False
            CloseHandle (lFile)
            Exit Function
        End If
       
    Next i

    ReDim bGroupIconData(6 + 14 * tGRPICONDIR.idCount)
    CopyMemory ByVal VarPtr(bGroupIconData(0)), ByVal VarPtr(tICONDIR), 6
 
    For i = 0 To tGRPICONDIR.idCount - 1
        CopyMemory ByVal VarPtr(bGroupIconData(6 + 14 * i)), ByVal VarPtr(tGRPICONDIR.idEntries(i).bWidth), 14&
    Next
               
    If UpdateResource(lUpdate, RT_GROUP_ICON, 1, 0, ByVal VarPtr(bGroupIconData(0)), UBound(bGroupIconData)) = False Then
        ChangeIcon = False
        CloseHandle (lFile)
        Exit Function
    End If
   
    If EndUpdateResource(lUpdate, False) = False Then
        ChangeIcon = False
        CloseHandle (lFile)
    End If

    Call CloseHandle(lFile)
    ChangeIcon = True
End Function

