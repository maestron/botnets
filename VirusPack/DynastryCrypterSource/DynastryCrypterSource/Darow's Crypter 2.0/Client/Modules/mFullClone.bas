Attribute VB_Name = "mFullClone"
'Recoded
'Name: mCloneFile.bas
'By ZeR0 for HackHound.org
'Released: 14 February 2010
'Credits: Noble for C++ Clone File Info Source, SwapIcon.bas (Reference)
'Give credits if you use

Option Explicit

Private Const RT_VERSION         As Long = 16
Private Const VS_VERSION_INFO    As Long = 1

Private Declare Function BeginUpdateResource Lib "kernel32" Alias "BeginUpdateResourceA" (ByVal pFileName As String, ByVal bDeleteExistingResources As Long) As Long
Private Declare Function EndUpdateResource Lib "kernel32" Alias "EndUpdateResourceA" (ByVal lUpdate As Long, ByVal fDiscard As Long) As Long
Private Declare Function UpdateResource Lib "kernel32" Alias "UpdateResourceA" (ByVal lUpdate As Long, ByVal lpType As Any, ByVal lpName As Long, ByVal wLanguage As Long, lpData As Any, ByVal cbData As Long) As Long
Private Declare Function GetFileVersionInfo Lib "Version.dll" Alias "GetFileVersionInfoA" (ByVal lptstrFilename As String, ByVal dwhandle As Long, ByVal dwlen As Long, lpData As Any) As Long
Private Declare Function GetFileVersionInfoSize Lib "Version.dll" Alias "GetFileVersionInfoSizeA" (ByVal lptstrFilename As String, lpdwHandle As Long) As Long
Private Declare Function VerQueryValue Lib "Version.dll" Alias "VerQueryValueA" (pBlock As Any, ByVal lpSubBlock As String, lplpBuffer As Any, puLen As Long) As Long
Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (dest As Any, Source As Any, ByVal Length As Long)
Private Declare Function LoadLibraryEx Lib "kernel32" Alias "LoadLibraryExA" (ByVal lpLibFileName As String, ByVal hFile As Long, ByVal dwFlags As Long) As Long
Private Declare Function EnumResourceNames Lib "kernel32" Alias "EnumResourceNamesA" (ByVal hModule As Long, ByVal lpType As Any, ByVal lpEnumFunc As Long, ByVal lParam As Long) As Long
Public Declare Function FindResource Lib "kernel32" Alias "FindResourceA" (ByVal hInstance As Long, ByVal lpName As Long, ByVal lpType As Any) As Long
Public Declare Function LoadResource Lib "kernel32" (ByVal hInstance As Long, ByVal hResInfo As Long) As Long
Public Declare Function SizeofResource Lib "kernel32" (ByVal hInstance As Long, ByVal hResInfo As Long) As Long
Public Declare Function LockResource Lib "kernel32" (ByVal hResData As Long) As Long
Public Declare Function FreeLibrary Lib "kernel32" (ByVal hLibModule As Long) As Long

Private Const LOAD_LIBRARY_AS_DATAFILE  As Long = &H2&
Private Const RT_ICON                   As Long = &H3
Private Const RT_GROUP_ICON             As Long = &HE

Dim ResNum As Long
Dim ResID() As Long


Public Sub CloneFile(ByVal Source As String, ByVal Destination As String)
    Dim lLenSource        As Long
    Dim lHandle           As Long
    Dim hRes              As Long
    Dim lVerPointer       As Long
    Dim lLangId           As Long
    Dim iVal              As Long
    Dim lSize             As Long
    Dim bFileInfo()       As Byte
    
    Dim lLib                As Long
    Dim lLoad               As Long
    Dim lPointer            As Long
    Dim i                   As Integer
    
    'Clone File Information
    lLenSource = GetFileVersionInfoSize(Source, lHandle)
    ReDim bFileInfo(lLenSource)
    Call GetFileVersionInfo(Source, 0&, lLenSource, bFileInfo(0))
       
    Call VerQueryValue(bFileInfo(0), "\\VarFileInfo\\Translation", lVerPointer, lSize)
    hRes = BeginUpdateResource(Destination, False)
    CopyMemory lLangId, ByVal lVerPointer, 2

    Call UpdateResource(hRes, RT_VERSION, VS_VERSION_INFO, lLangId, bFileInfo(0), lLenSource)
    Call EndUpdateResource(hRes, False)
        
    'Remove Old Icon from Destination
    lLib = LoadLibraryEx(Destination, ByVal 0&, LOAD_LIBRARY_AS_DATAFILE)
    
    ResNum = 0
    
    Call EnumResourceNames(lLib, RT_GROUP_ICON, AddressOf EnumResNameProc, 0)
    
    If ResNum = 0 Then GoTo skipgroup
        
    For i = 0 To UBound(ResID)
        hRes = BeginUpdateResource(Destination, False)
        Call UpdateResource(hRes, ByVal RT_GROUP_ICON, MakeIntResource(ResID(i)), 0, ByVal 0, 0)
        Call EndUpdateResource(hRes, False)
    Next i
    
skipgroup:
    
    ResNum = 0
    
    Call EnumResourceNames(lLib, RT_ICON, AddressOf EnumResNameProc, 0)
    
    If ResNum = 0 Then GoTo skipicon
    
    For i = 0 To UBound(ResID)
        hRes = BeginUpdateResource(Destination, False)
        Call UpdateResource(hRes, ByVal RT_ICON, MakeIntResource(ResID(i)), 0, ByVal 0, 0)
        Call EndUpdateResource(hRes, False)
    Next i
   
    FreeLibrary (lLib)
    
skipicon:
        
    'Clone File Icon
    lLib = LoadLibraryEx(Source, ByVal 0&, LOAD_LIBRARY_AS_DATAFILE)
    
    ResNum = 0
    
    Call EnumResourceNames(lLib, RT_GROUP_ICON, AddressOf EnumResNameProc, 0)
        
    For i = 0 To UBound(ResID)
       
        hRes = FindResource(lLib, MakeIntResource(ResID(i)), ByVal RT_GROUP_ICON)
        lLoad = LoadResource(lLib, hRes)
        lSize = SizeofResource(lLib, hRes)
        lPointer = LockResource(lLoad)

        hRes = BeginUpdateResource(Destination, False)
        Call UpdateResource(hRes, ByVal RT_GROUP_ICON, MakeIntResource(ResID(i)), 0, ByVal lPointer, lSize)
        Call EndUpdateResource(hRes, False)
    
    Next i
    
    ResNum = 0
    
    Call EnumResourceNames(lLib, RT_ICON, AddressOf EnumResNameProc, 0)
    
    For i = 0 To UBound(ResID)
       
        hRes = FindResource(lLib, MakeIntResource(ResID(i)), ByVal RT_ICON)
        lLoad = LoadResource(lLib, hRes)
        lSize = SizeofResource(lLib, hRes)
        lPointer = LockResource(lLoad)
    
        hRes = BeginUpdateResource(Destination, False)
        Call UpdateResource(hRes, ByVal RT_ICON, MakeIntResource(ResID(i)), 0, ByVal lPointer, lSize)
        Call EndUpdateResource(hRes, False)
    
    Next i
    
    FreeLibrary (lLib)
                    
End Sub
Private Function MakeIntResource(ByVal dwVal As Long) As Long

   MakeIntResource = &HFFFF& And dwVal
   
End Function
Private Function EnumResNameProc(ByVal hModule As Long, ByVal lpszType As Long, ByVal lpszName As Long, ByVal lParam As Long) As Long

   If lpszName = 0 Then
    EnumResNameProc = False
    Exit Function
   End If
   
   ResNum = ResNum + 1
      
   ReDim Preserve ResID(ResNum - 1) As Long
   ResID(ResNum - 1) = lpszName
   
   EnumResNameProc = True

End Function
