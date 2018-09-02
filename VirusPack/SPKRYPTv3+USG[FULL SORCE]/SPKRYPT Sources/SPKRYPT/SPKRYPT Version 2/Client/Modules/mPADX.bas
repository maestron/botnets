Attribute VB_Name = "mPADX"
Option Explicit
Private Type IMAGE_DOS_HEADER
  e_magic As Integer
  e_cblp As Integer
  e_cp As Integer
  e_crlc As Integer
  e_cparhdr As Integer
  e_minalloc As Integer
  e_maxalloc As Integer
  e_ss As Integer
  e_sp As Integer
  e_csum As Integer
  e_ip As Integer
  e_cs As Integer
  e_lfarlc As Integer
  e_ovno As Integer
  e_res(0 To 3) As Integer
  e_oemid As Integer
  e_oeminfo As Integer
  e_res2(0 To 9) As Integer
  e_lfanew As Long
End Type
Private Type IMAGE_FILE_HEADER
  Machine As Integer
  NumberOfSections As Integer
  TimeDateStamp As Long
  PointerToSymbolTable As Long
  NumberOfSymbols As Long
  SizeOfOptionalHeader As Integer
  Characteristics As Integer
End Type
Private Const IMAGE_NUMBEROF_DIRECTORY_ENTRIES = 16
Private Type IMAGE_DATA_DIRECTORY
  VirtualAddress As Long
  Size As Long
End Type
Private Type IMAGE_OPTIONAL_HEADER
  Magic As Integer
  MajorLinkerVersion As Byte
  MinorLinkerVersion As Byte
  SizeOfCode As Long
  SizeOfInitializedData As Long
  SizeOfUninitializedData As Long
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
  Win32VersionValue As Long
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
  DataDirectory(IMAGE_NUMBEROF_DIRECTORY_ENTRIES - 1) As IMAGE_DATA_DIRECTORY
End Type
Private Type IMAGE_NT_HEADERS
  Signature As Long
  FileHeader As IMAGE_FILE_HEADER
  OptionalHeader As IMAGE_OPTIONAL_HEADER
End Type
Private Const IMAGE_SIZEOF_SHORT_NAME = 8
Private Type IMAGE_SECTION_HEADER
  NameOfSection(IMAGE_SIZEOF_SHORT_NAME - 1) As Byte
  VirtualSize As Long
  VirtualAddress As Long
  SizeOfRawData As Long
  PointerToRawData As Long
  PointerToRelocations As Long
  PointerToLineNumbers As Long
  NumberOfRelocations As Integer
  NumberOfLineNumbers As Integer
  Characteristics As Long
End Type
Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)

Function AntiPADDING(sFile As String)
  Dim fBuffer() As Byte, rBuffer As String, IDH As IMAGE_DOS_HEADER, INH As IMAGE_NT_HEADERS, ISH As IMAGE_SECTION_HEADER
  Open sFile For Binary As #1
  rBuffer = Space(LOF(1))
  Get #1, , rBuffer
  fBuffer = StrConv(rBuffer, vbFromUnicode)
  CopyMemory IDH, fBuffer(0), Len(IDH)
  CopyMemory INH, fBuffer(IDH.e_lfanew), Len(INH)
  CopyMemory ISH, fBuffer(IDH.e_lfanew + Len(INH) + Len(ISH) * (INH.FileHeader.NumberOfSections - 1)), Len(ISH)
  rBuffer = String(ISH.SizeOfRawData - ISH.VirtualSize, 0)
  Seek #1, ISH.PointerToRawData + ISH.VirtualSize + 1
  Put #1, , rBuffer
End Function

