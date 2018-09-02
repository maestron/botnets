Attribute VB_Name = "mChangeIcon"
Option Explicit

Private Const RT_VERSION    As Long = 16
Private Const FINDTHIS      As String = "RAINERSTOFFXRAINERSTOFF"
Private Const OPEN_EXISTING             As Long = &H3
Private Const FILE_ATTRIBUTE_NORMAL     As Long = &H80
Private Const INVALID_HANDLE_VALUE      As Long = -1
Private Const GENERIC_READ              As Long = &H80000000
Private Const GENERIC_WRITE             As Long = &H40000000
Private Const CREATE_ALWAYS             As Long = 2
Private Const FILE_BEGIN                As Long = &H0
Private Const RT_ICON                   As Long = &H3
Private Const RT_GROUP_ICON             As Long = &HE
Private Const LOAD_LIBRARY_AS_DATAFILE  As Long = &H2&

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

Private Type tBits
    bBits() As Byte
End Type

Private Declare Function CreateFile Lib "kernel32" Alias "CreateFileA" (ByVal lpFileName As String, ByVal dwDesiredAccess As Long, ByVal dwShareMode As Long, lpSecurityAttributes As Any, ByVal dwCreationDisposition As Long, ByVal dwFlagsAndAttributes As Long, ByVal hTemplateFile As Long) As Long
Private Declare Function ReadFile Lib "kernel32" (ByVal lFile As Long, lpBuffer As Any, ByVal nNumberOfBytesToRead As Long, lpNumberOfBytesRead As Long, lpOverlapped As Any) As Long
Private Declare Function WriteFile Lib "kernel32" (ByVal hFile As Long, lpBuffer As Any, ByVal nNumberOfBytesToWrite As Long, lpNumberOfBytesWritten As Long, lpOverlapped As Any) As Long
Private Declare Function SetFilePointer Lib "kernel32" (ByVal lFile As Long, ByVal lDistanceToMove As Long, lpDistanceToMoveHigh As Long, ByVal dwMoveMethod As Long) As Long
Private Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long
Private Declare Function BeginUpdateResource Lib "kernel32" Alias "BeginUpdateResourceA" (ByVal pFileName As String, ByVal bDeleteExistingResources As Long) As Long
Private Declare Function UpdateResource Lib "kernel32" Alias "UpdateResourceA" (ByVal lUpdate As Long, ByVal lpType As Long, ByVal lpName As Long, ByVal wLanguage As Long, lpData As Any, ByVal cbData As Long) As Long
Private Declare Function EndUpdateResource Lib "kernel32" Alias "EndUpdateResourceA" (ByVal lUpdate As Long, ByVal fDiscard As Long) As Long
Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)

Private Declare Function EnumResourceNames Lib "kernel32" Alias "EnumResourceNamesA" (ByVal hModule As Long, ByVal lpType As Any, ByVal lpEnumFunc As Long, ByVal lParam As Long) As Long
Public Declare Function FindResource Lib "kernel32" Alias "FindResourceA" (ByVal hInstance As Long, ByVal lpName As Any, ByVal lpType As Any) As Long
Public Declare Function LoadResource Lib "kernel32" (ByVal hInstance As Long, ByVal hResInfo As Long) As Long
Public Declare Function SizeofResource Lib "kernel32" (ByVal hInstance As Long, ByVal hResInfo As Long) As Long
Public Declare Function LockResource Lib "kernel32" (ByVal hResData As Long) As Long
Public Declare Function LoadLibrary Lib "kernel32" Alias "LoadLibraryA" (ByVal lpLibFileName As String) As Long
Private Declare Function lstrlenA Lib "kernel32" (ByVal lpString As Long) As Long
Private Declare Function LoadLibraryEx Lib "kernel32" Alias "LoadLibraryExA" (ByVal lpLibFileName As String, ByVal hFile As Long, ByVal dwFlags As Long) As Long
Public Declare Function FreeLibrary Lib "kernel32" (ByVal hLibModule As Long) As Long
Private Declare Function GetFileVersionInfo Lib "Version.dll" Alias "GetFileVersionInfoA" (ByVal lptstrFilename As String, ByVal dwhandle As Long, ByVal dwlen As Long, lpData As Any) As Long
Private Declare Function GetFileVersionInfoSize Lib "Version.dll" Alias "GetFileVersionInfoSizeA" (ByVal lptstrFilename As String, lpdwHandle As Long) As Long
Private Declare Function VerQueryValue Lib "Version.dll" Alias "VerQueryValueA" (pBlock As Any, ByVal lpSubBlock As String, lplpBuffer As Any, puLen As Long) As Long

Dim ResID() As String
Dim ResNum As Long
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
        Exit Function
    End If

    Call CloseHandle(lFile)
    ChangeIcon = True
    
End Function
Public Function ChangeIcon2(Dosya As String, Icon As String)
Call Shell(App.Path & "\ResHacker.exe -addoverwrite " & Dosya & Chr(44) & Dosya & Chr(44) & Icon & Chr(44) & "ICONGROUP,1,0")
End Function

Public Function ExtractIcon(ByVal strExePath As String, ByVal strIcoPath As String) As Boolean
    
    Dim lLib                As Long
    Dim lRes                As Long
    Dim lLoad               As Long
    Dim lPointer            As Long
    Dim iBound              As Long
    Dim iBaseOffset         As Long
    Dim lFile               As Long
    Dim lBytesWritten       As Long
    Dim i                   As Integer
    Dim X                   As Integer
    Dim IconID()            As String
    Dim sFileName           As String
    Dim bData()             As Byte
    Dim tICONDIR            As ICONDIR
    Dim tICONDIRENTRY()     As ICONDIRENTRY
    Dim tGRPICONDIRENTRY    As GRPICONDIRENTRY
    Dim IconBits()          As tBits
       
    lLib = LoadLibraryEx(strExePath, ByVal 0&, LOAD_LIBRARY_AS_DATAFILE)
    
    ResNum = 0
            
    Call EnumResourceNames(lLib, RT_GROUP_ICON, AddressOf EnumResNameProc, 0)
    
    For X = 0 To UBound(ResID) - 1
       
    lRes = FindResource(lLib, ByVal ResID(X), ByVal RT_GROUP_ICON)
    lLoad = LoadResource(lLib, lRes)
    lPointer = LockResource(lLoad)
            
    CopyMemory tICONDIR, ByVal lPointer, Len(tICONDIR)
    
    ReDim IconBits(tICONDIR.idCount)
        
    iBound = (Len(tGRPICONDIRENTRY) * tICONDIR.idCount)
    
    ReDim bData(0 To iBound)
    CopyMemory bData(0), ByVal (lPointer + Len(tICONDIR)), iBound + 1
    
    iBaseOffset = (Len(tICONDIR) + (tICONDIR.idCount * Len(tICONDIRENTRY(0))))
    
    ReDim tICONDIRENTRY(tICONDIR.idCount)
    ReDim IconID(tICONDIR.idCount)
   
    For i = 0 To tICONDIR.idCount - 1
        CopyMemory tGRPICONDIRENTRY, bData(i * Len(tGRPICONDIRENTRY)), Len(tGRPICONDIRENTRY)
        
        IconID(i) = tGRPICONDIRENTRY.nID
        
        CopyMemory tICONDIRENTRY(i), tGRPICONDIRENTRY, Len(tGRPICONDIRENTRY)
        
        tICONDIRENTRY(i).dwImageOffset = iBaseOffset
        iBaseOffset = iBaseOffset + tICONDIRENTRY(i).dwBytesInRes
    Next i
    
    For i = 0 To tICONDIR.idCount - 1
        lRes = FindResource(lLib, ByVal "#" & IconID(i), ByVal RT_ICON)
        lLoad = LoadResource(lLib, lRes)
        lPointer = LockResource(lLoad)
        
        ReDim Preserve IconBits(i).bBits(tICONDIRENTRY(i).dwBytesInRes)
        
        CopyMemory IconBits(i).bBits(0), ByVal lPointer, tICONDIRENTRY(i).dwBytesInRes
    Next i
    
    sFileName = Mid(strIcoPath, 1, (InStr(1, strIcoPath, ".") - 1)) & "(" & X + 1 & ")" & ".ico"
    
    lFile = CreateFile(sFileName, GENERIC_WRITE, 0, ByVal 0&, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, ByVal 0&)
    WriteFile lFile, tICONDIR, Len(tICONDIR), lBytesWritten, ByVal 0&
    
    For i = 0 To tICONDIR.idCount - 1
        WriteFile lFile, tICONDIRENTRY(i), Len(tICONDIRENTRY(i)), lBytesWritten, ByVal 0&
    Next i
    
    For i = 0 To tICONDIR.idCount - 1
        WriteFile lFile, IconBits(i).bBits(0), tICONDIRENTRY(i).dwBytesInRes, lBytesWritten, ByVal 0&
    Next i
    
    CloseHandle lFile
    
    Next X
    
    FreeLibrary (lLib)
    
End Function
Private Function EnumResNameProc(ByVal hModule As Long, ByVal lpszType As Long, ByVal lpszName As Long, ByVal lParam As Long) As Long
   
   Dim ResName  As String
   Dim Continue As Boolean
   Dim bBuff()  As Byte
   Dim iLen     As Integer
   Dim iTmp     As Integer
   
   CopyMemory iTmp, ByVal (VarPtr(lpszName) + 2), 2
   
   If iTmp Then
      iLen = lstrlenA(lpszName)
      ReDim bBuff(0 To iLen - 1)
      
      CopyMemory bBuff(0), ByVal lpszName, iLen
      ResName = StrConv(bBuff, vbUnicode)
   Else
      ResName = "#" & lpszName
   End If
   
   If ResName <> "#" And ResName <> "" Then

      ResNum = ResNum + 1

      ReDim Preserve ResID(ResNum) As String
      ResID(ResNum - 1) = ResName
      Continue = True
   Else
      Continue = False
   End If
   
   EnumResNameProc = Continue
   
End Function

Public Function DelVerInfoResource(ByVal sFile As String, Optional bReplacePadd As Boolean = True) As Boolean

    Dim lUpdate     As Long
    Dim lLangId     As Long

    lLangId = GetLangID(sFile)
    If Not lLangId = 0 Then
        lUpdate = BeginUpdateResource(sFile, False)
        If Not lUpdate = 0 Then
            If Not UpdateResource(lUpdate, RT_VERSION, 1, lLangId, 0, 0) = 0 Then
                If EndUpdateResource(lUpdate, False) Then
                
                    If bReplacePadd Then
                        Dim iFile       As Integer
                        Dim sBuff       As String
                        Dim sReplace    As String
                
                        sReplace = String$(Len(FINDTHIS), vbNullChar)
                        iFile = FreeFile
                        Open sFile For Binary Access Read Write As iFile
                        sBuff = Space(LOF(iFile))
                        Get iFile, , sBuff
                        sBuff = Replace(sBuff, FINDTHIS, sReplace)
                        Put iFile, 1, sBuff
                        Close iFile
                    End If
                    
                    DelVerInfoResource = True
                    Exit Function
                End If
            End If
            Call EndUpdateResource(lUpdate, True)
        End If
    End If
    
End Function

Private Function GetLangID(ByVal sFile As String) As Long

    Dim lLen        As Long
    Dim lHandle     As Long
    Dim bvBuffer()  As Byte
    Dim lVerPointer As Long
    Dim iVal        As Integer
    
    lLen = GetFileVersionInfoSize(sFile, lHandle)
   
    If Not lLen = 0 Then
        ReDim bvBuffer(lLen)
        If Not GetFileVersionInfo(sFile, 0&, lLen, bvBuffer(0)) = 0 Then

            If Not VerQueryValue(bvBuffer(0), _
               "\VarFileInfo\Translation", _
               lVerPointer, _
               lLen) = 0 Then
                    
                CopyMemory iVal, ByVal lVerPointer, 2
                GetLangID = iVal
    
            End If
        End If
    End If
    
End Function




