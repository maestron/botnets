Attribute VB_Name = "Module1"

Public Declare Sub CopyMemory Lib "Kernel32" Alias "RtlMoveMemory" (dest As Any, Src As Any, ByVal L As Long)

Public Type IMAGE_DOS_HEADER
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
Public Type IMAGE_FILE_HEADER
    Machine As Integer
    NumberOfSections As Integer
    TimeDateStamp As Long
    PointerToSymbolTable As Long
    NumberOfSymbols As Long
    SizeOfOptionalHeader As Integer
    Characteristics As Integer
End Type
Public Type IMAGE_DATA_DIRECTORY
    VirtualAddress As Long
    Size As Long
End Type
Public Type IMAGE_OPTIONAL_HEADER
    Magic As Integer
    MajorLinkerVersion As Byte
    MinorLinkerVersion As Byte
    SizeOfCode As Long
    SizeOfInitializedData As Long
    SizeOfUnitializedData As Long
    AddressOfEntryPoint As Long
    BaseOfCode As Long
    BaseOfData As Long
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
    Subsystem As Integer
    DllCharacteristics As Integer
    SizeOfStackReserve As Long
    SizeOfStackCommit As Long
    SizeOfHeapReserve As Long
    SizeOfHeapCommit As Long
    LoaderFlags As Long
    NumberOfRvaAndSizes As Long
    DataDirectory(0 To 15) As IMAGE_DATA_DIRECTORY
End Type
Public Type IMAGE_NT_HEADERS
    Signature As Long
    FileHeader As IMAGE_FILE_HEADER
    OptionalHeader As IMAGE_OPTIONAL_HEADER
End Type
Public Type IMAGE_SECTION_HEADER
   SecName As String * 8
   VirtualSize As Long
   VirtualAddress  As Long
   SizeOfRawData As Long
   PointerToRawData As Long
   PointerToRelocations As Long
   PointerToLinenumbers As Long
   NumberOfRelocations As Integer
   NumberOfLinenumbers As Integer
   Characteristics  As Long
End Type

Public Sub pathEOF(strFile As String)

    Dim idh As IMAGE_DOS_HEADER
    Dim inh As IMAGE_NT_HEADERS
    Dim ish As IMAGE_SECTION_HEADER
    Dim FileData As String
    Dim ExeData() As Byte
    Dim ExeLen As Long
   
    'Get binary data to file and convert to byte array
    FileData = GetFileData(strFile)
    ExeData = StrConv(FileData, vbFromUnicode)
   
    'Copy ExeData into IMAGE_DOS_HEADER and check if it's valid
    CopyMemory idh, ExeData(0), 64
    If idh.e_magic <> &H5A4D Then
        Debug.Print "Not Valid EXE!"
        Exit Sub
    End If

    'Copy ExeData into IMAGE_NT_HEADER and check if it's valid
    CopyMemory inh, ExeData(idh.e_lfanew), 248
    If inh.Signature <> &H4550 Then
        Debug.Print "Not Valid EXE!"
        Exit Sub
    End If
       
    'Copy the last secion into IMAGE_SECTION_HEADER
    CopyMemory ish, ExeData(idh.e_lfanew + 248 + (inh.FileHeader.NumberOfSections - 1) * 40), 40

    'Get length of EXE from headers
    ExeLen = ish.PointerToRawData + ish.SizeOfRawData

    'Set SizeOfRawData to cover EOF data
    ish.SizeOfRawData = ish.SizeOfRawData + (Len(FileData) - ExeLen + 2)
    
    'Copy IMAGE_SECTION_HEADER back into ExeData
    CopyMemory ExeData(idh.e_lfanew + 248 + (inh.FileHeader.NumberOfSections - 1) * 40), ish, 40

    'Convert from byte array to string, and save file
    FileData = StrConv(ExeData(), vbUnicode)
    SaveFileData strFile, FileData
    
End Sub

Public Function GetFileData(strFile As String) As String

Dim strData As String
Open strFile For Binary Access Read Lock Write As #1
    strData = String$(LOF(1), Chr$(0))
    Get #1, , strData
Close #1
GetFileData = strData

End Function

Public Sub SaveFileData(strFile As String, strData As String)

Open strFile For Output As #1
    Print #1, strData
Close #1

End Sub


