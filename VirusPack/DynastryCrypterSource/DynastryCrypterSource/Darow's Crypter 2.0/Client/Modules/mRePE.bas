Attribute VB_Name = "mRePE"
Option Explicit
'From Hackhound Crypter V4
'thx Cobein
Private Const IMAGE_DOS_SIGNATURE           As Long = &H5A4D&
Private Const IMAGE_NT_SIGNATURE            As Long = &H4550&
Private Const IMAGE_NT_OPTIONAL_HDR32_MAGIC As Long = &H10B&

Private Const SIZE_DOS_HEADER               As Long = &H40
Private Const SIZE_NT_HEADERS               As Long = &HF8
Private Const SIZE_SECTION_HEADER           As Long = &H28

Private Type IMAGE_DOS_HEADER
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

Private Type IMAGE_FILE_HEADER
    Machine                     As Integer
    NumberOfSections            As Integer
    TimeDateStamp               As Long
    PointerToSymbolTable        As Long
    NumberOfSymbols             As Long
    SizeOfOptionalHeader        As Integer
    characteristics             As Integer
End Type

Private Type IMAGE_DATA_DIRECTORY
    VirtualAddress              As Long
    Size                        As Long
End Type

Private Type IMAGE_OPTIONAL_HEADER
    Magic                       As Integer
    MajorLinkerVersion          As Byte
    MinorLinkerVersion          As Byte
    SizeOfCode                  As Long
    SizeOfInitializedData       As Long
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
    DataDirectory(0 To 15)      As IMAGE_DATA_DIRECTORY
End Type

Private Type IMAGE_NT_HEADERS
    Signature                   As Long
    FileHeader                  As IMAGE_FILE_HEADER
    OptionalHeader              As IMAGE_OPTIONAL_HEADER
End Type

Private Type IMAGE_SECTION_HEADER
    SecName                     As String * 8
    VirtualSize                 As Long
    VirtualAddress              As Long
    SizeOfRawData               As Long
    PointerToRawData            As Long
    PointerToRelocations        As Long
    PointerToLinenumbers        As Long
    NumberOfRelocations         As Integer
    NumberOfLinenumbers         As Integer
    characteristics             As Long
End Type

Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Dest As Any, Src As Any, ByVal L As Long)

Public Function RealignPEFromFile( _
       ByVal sSrcFile As String, _
       Optional sDstFile As String) As Boolean

    Dim bvData() As Byte
    
    On Local Error GoTo RealignPEFromFile_Error

    If sDstFile = vbNullString Then
        sDstFile = sSrcFile
    End If
    
    Open sSrcFile For Binary Access Read As #1
    ReDim bvData(LOF(1) - 1)
    Get #1, , bvData()
    Close
    
    If RealignPEFromBytes(bvData) Then
        Open sDstFile For Binary Access Write As #1
        Put #1, , bvData()
        Close
    End If

    RealignPEFromFile = True

    On Error GoTo 0
    Exit Function

RealignPEFromFile_Error:

End Function

Public Function RealignPEFromBytes( _
       ByRef bvData() As Byte) As Boolean
       
    Dim lSize                   As Long
    Dim lLastSectPos            As Long
    Dim tIMAGE_DOS_HEADER       As IMAGE_DOS_HEADER
    Dim tIMAGE_NT_HEADERS       As IMAGE_NT_HEADERS
    Dim tIMAGE_SECTION_HEADER   As IMAGE_SECTION_HEADER
    Dim lDataSize               As Long
    Dim lAlign                  As Long
    Dim bvExtraData()           As Byte
    
    On Local Error GoTo RealignPEFromBytes_Error

    CopyMemory tIMAGE_DOS_HEADER, bvData(0), SIZE_DOS_HEADER

    If Not tIMAGE_DOS_HEADER.e_magic = IMAGE_DOS_SIGNATURE Then
        Exit Function
    End If
    
    CopyMemory tIMAGE_NT_HEADERS, bvData(tIMAGE_DOS_HEADER.e_lfanew), SIZE_NT_HEADERS

    If Not tIMAGE_NT_HEADERS.Signature = IMAGE_NT_SIGNATURE Then
        Exit Function
    End If
    
    If Not tIMAGE_NT_HEADERS.OptionalHeader.Magic = IMAGE_NT_OPTIONAL_HDR32_MAGIC Then
        Exit Function
    End If
       
    lLastSectPos = _
       tIMAGE_DOS_HEADER.e_lfanew + SIZE_NT_HEADERS + _
       (tIMAGE_NT_HEADERS.FileHeader.NumberOfSections - 1) * SIZE_SECTION_HEADER
    
    CopyMemory tIMAGE_SECTION_HEADER, bvData(lLastSectPos), SIZE_SECTION_HEADER
    
    lSize = tIMAGE_SECTION_HEADER.SizeOfRawData
   
    lDataSize = UBound(bvData) - tIMAGE_SECTION_HEADER.SizeOfRawData - tIMAGE_SECTION_HEADER.PointerToRawData + 1

    If (lSize + lDataSize) Mod tIMAGE_NT_HEADERS.OptionalHeader.SectionAlignment = 0 Then
        tIMAGE_SECTION_HEADER.SizeOfRawData = _
           tIMAGE_SECTION_HEADER.SizeOfRawData + lSize
    
        CopyMemory bvData(lLastSectPos), tIMAGE_SECTION_HEADER, SIZE_SECTION_HEADER
    Else
            
        ReDim bvExtraData(lDataSize - 1)
        CopyMemory bvExtraData(0), bvData(UBound(bvData) - lDataSize + 1), lDataSize
        ReDim Preserve bvData(UBound(bvData) - lDataSize)
        
        lAlign = lDataSize + tIMAGE_NT_HEADERS.OptionalHeader.SectionAlignment
        lAlign = lAlign - (lAlign Mod tIMAGE_NT_HEADERS.OptionalHeader.SectionAlignment)

        ReDim Preserve bvData(UBound(bvData) + lAlign)

        CopyMemory bvData(UBound(bvData) - lDataSize + 1), bvExtraData(0), lDataSize

        tIMAGE_SECTION_HEADER.SizeOfRawData = _
           tIMAGE_SECTION_HEADER.SizeOfRawData + lAlign
           
        CopyMemory bvData(lLastSectPos), tIMAGE_SECTION_HEADER, SIZE_SECTION_HEADER
    End If

    RealignPEFromBytes = True

    On Error GoTo 0
    Exit Function

RealignPEFromBytes_Error:

End Function



