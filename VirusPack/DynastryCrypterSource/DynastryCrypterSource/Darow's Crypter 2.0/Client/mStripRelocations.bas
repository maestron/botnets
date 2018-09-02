Attribute VB_Name = "mStripRelocations"
'----------------------------------------------------------------------------------------------------------
' Module      :  mStripRelocations
' DateTime    :  11/10/2009  11:58
' Author VB6  :  Inj3ct
' Author Delphi: steve10120
' Thx for Help:  Slayer616
' Purpose     :  Delete the relocations from a PE file.
' Usage       :  At your own risk
' Requirements:  None
' History     :  First try
' Distribution:  You can freely use this code in your own
'                applications, but you may not reproduce
'                or publish this code on any web site,
'                online service, or distribute as source
'                on any media without express permission.
'
' I port it from Delphi to VB6 please give credits to steve10120, Slayer616 and me if you use this Function
'----------------------------------------------------------------------------------------------------------
Public Type IMAGE_DOS_HEADER
e_magic As Integer ' Magic number
e_cblp As Integer ' Bytes on last page of file
e_cp As Integer ' Pages in file
e_crlc As Integer ' Relocations
e_cparhdr As Integer ' Size of header in paragraphs
e_minalloc As Integer ' Minimum extra paragraphs needed
e_maxalloc As Integer ' Maximum extra paragraphs needed
e_ss As Integer ' Initial (relative) SS value
e_sp As Integer ' Initial SP value
e_csum As Integer ' Checksum
e_ip As Integer ' Initial IP value
e_cs As Integer ' Initial (relative) CS value
e_lfarlc As Integer ' File address of relocation table
e_ovno As Integer ' Overlay number
e_res(0 To 3) As Integer ' Reserved words
e_oemid As Integer ' OEM identifier (for e_oeminfo)
e_oeminfo As Integer ' OEM information; e_oemid specific
e_res2(0 To 9) As Integer ' Reserved words
e_lfanew As Long ' File address of new exe header
End Type

Public Type IMAGE_EXPORT_DIRECTORY
characteristics As Long
TimeDateStamp As Long
MajorVersion As Integer
MinorVersion As Integer
Name As Long
Base As Long
NumberOfFunctions As Long
NumberOfNames As Long
AddressOfFunctions As Long
AddressOfNames As Long
AddressOfNameOrdinals As Long
End Type

Public Type IMAGE_IMPORT_DIRECTORY
dwRVAFunctionNameList As Long
TimeDateStamp As Long
ForwarderChain As Long
dwRVAModuleName As Long
dwRVAFunctionAddressList As Long
End Type

Public Type IMAGE_FILE_HEADER
Machine As Integer
NumberOfSections As Integer
TimeDateStamp As Long
PointerToSymbolTable As Long
NumberOfSymbols As Long
SizeOfOptionalHeader As Integer
characteristics As Integer
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
SubSystem As Integer
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
VirtualAddress As Long
SizeOfRawData As Long
PointerToRawData As Long
PointerToRelocations As Long
PointerToLinenumbers As Long
NumberOfRelocations As Integer
NumberOfLinenumbers As Integer
characteristics As Long
End Type

'IMAGE DATA DIRECTORY:
'1-Export Table
'2-Import Table
'3-Resource Table
'4-Exception Table
'5-Certificate Table
'6-Relocation Table
'7-Debug Data
'8-Architecture Data
'9-Machine Value (MIPS GP)
'10-TLS Table
'11-Load Configuration Table
'12-Bound Import Table
'13-Import Address Table
'14-Delay Import Descriptor
'15-COM+ Runtime Header
'16-Reserved

Dim idh As IMAGE_DOS_HEADER
Dim inh As IMAGE_NT_HEADERS
Dim ish As IMAGE_SECTION_HEADER
Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Dest As Any, Src As Any, ByVal L As Long)
'Private Declare Sub ZeroMemory Lib "KERNEL32" Alias "RtlMoveMemory" (dest As Any, ByVal numBytes As Long)

Public Function StripRelocations(data As String) As Boolean
Dim bfile() As Byte

Open data For Binary As #1
ReDim bfile(LOF(1))
Get #1, , bfile
Close #1

Call CopyMemory(idh, bfile(0), 64)
Call CopyMemory(inh, bfile(idh.e_lfanew), 248)
Call CopyMemory(ish, bfile(idh.e_lfanew + 248 + (inh.FileHeader.NumberOfSections - 1) * 40), 40)
If Mid(ish.SecName, 1, 6) = ".reloc" Then
ReDim Preserve bfile(UBound(bfile) - ish.SizeOfRawData)
inh.OptionalHeader.DataDirectory(5).VirtualAddress = 0
inh.OptionalHeader.DataDirectory(5).Size = 0
'Call ZeroMemory(ByVal ish, 40)
Call CopyMemory(bfile(idh.e_lfanew + 248 + (inh.FileHeader.NumberOfSections - 1) * 40), ish, 40)
inh.FileHeader.NumberOfSections = inh.FileHeader.NumberOfSections - 1
Call CopyMemory(ish, bfile(idh.e_lfanew + 248 + (inh.FileHeader.NumberOfSections - 1) * 40), 40)
inh.OptionalHeader.SizeOfImage = ish.VirtualAddress + ish.VirtualSize
Call CopyMemory(bfile(idh.e_lfanew), inh, 248)
End If

Open data For Binary As #1
Put #1, , bfile
Close #1

StripRelocations = True

End Function

