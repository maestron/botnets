Attribute VB_Name = "mCloneFileInfo"
Option Explicit



Private Declare Function LoadLibraryEx Lib "kernel32" Alias "LoadLibraryExA" (ByVal lpLibFileName As String, ByVal hFile As Long, ByVal dwFlags As Long) As Long
Private Declare Function FindResource Lib "kernel32" Alias "FindResourceA" (ByVal hInstance As Long, lpName As Any, lpType As Any) As Long
Private Declare Function LoadResource Lib "kernel32" (ByVal hInstance As Long, ByVal hResInfo As Long) As Long
Private Declare Function LockResource Lib "kernel32" (ByVal hResData As Long) As Long
Private Declare Function SizeofResource Lib "kernel32" (ByVal hInstance As Long, ByVal hResInfo As Long) As Long
Private Declare Function FreeLibrary Lib "kernel32" (ByVal hLibModule As Long) As Long
Private Declare Function BeginUpdateResource Lib "kernel32" Alias "BeginUpdateResourceA" (ByVal pFileName As String, ByVal bDeleteExistingResources As Long) As Long
Declare Function UpdateResource Lib "kernel32" Alias "UpdateResourceA" (ByVal lUpdate As Long, ByVal lpType As Long, ByVal lpName As Long, ByVal wLanguage As Long, lpData As Any, ByVal cbData As Long) As Long
Private Declare Function EndUpdateResource Lib "kernel32" Alias "EndUpdateResourceA" (ByVal hUpdate As Long, ByVal fDiscard As Long) As Long
Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (ByRef Destination As Any, ByRef Source As Any, ByVal numbytes As Long)

Private Const RT_VERSION                 As Long = 16
Public Function CloneFile(ByVal strDestExe As String, ByVal strSrcExe As String) As Boolean
    Dim hLib As Long
    Dim hRsrc As Long
    Dim hGlob As Long
    Dim dwSize As Long
    Dim lPtr As Long
        
    hLib = LoadLibraryEx(strSrcExe, ByVal 0&, &H2&)
    If hLib = 0 Then: CloneFile = False: Exit Function
    hRsrc = FindResource(hLib, ByVal 1, ByVal RT_VERSION)
    If hRsrc = 0 Then: CloneFile = False: Exit Function
    dwSize = SizeofResource(hLib, hRsrc)
    If dwSize = 0 Then: CloneFile = False: Exit Function
    hGlob = LoadResource(hLib, hRsrc)
    If hGlob = 0 Then: CloneFile = False: Exit Function
    lPtr = LockResource(hGlob)
    If lPtr = 0 Then: CloneFile = False: Exit Function

    ' -- Extract "Version Info" & save to buf --
    Dim buf() As Byte
    ReDim buf(0 To dwSize - 1)
    CopyMemory buf(0), ByVal lPtr, dwSize
    ' -----------------------------------

    Call FreeLibrary(hLib) ' Free our library (Close open handle to SrcExe)
        
    ' -- Update our destination EXE --
    Dim lUpdate As Long
    lUpdate = BeginUpdateResource(strDestExe, False)
    If lUpdate = 0 Then: CloneFile = False: Exit Function
    Call UpdateResource(lUpdate, RT_VERSION, 1, 1033, buf(0), dwSize)
    Call EndUpdateResource(lUpdate, False)
        
    CloneFile = True
End Function

