VERSION 1.0 CLASS
BEGIN
MultiUse = -1  'True
Persistable = 0  'NotPersistable
DataBindingBehavior = 0  'vbNone
DataSourceBehavior = 0   'vbNone
MTSTransactionMode = 0   'NotAnMTSObject
End
Attribute VB_Name = "DNHlBToHBr"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Private Declare Function QItbdxafsDYlZ Lib "USER32" (ByVal hDC As Long, ByVal xLeft As Long, ByVal yTop As Long, ByVal hIcon As Long, ByVal OutputWidth As Long, ByVal OutputHeight As Long, ByVal iStepIfAniCur As Long, ByVal hbrFlickerFreeDraw As Long, ByVal diFlags As Long) As Long
Private Declare Function IHjQiTZy Lib "gdi32" (ByVal hDC As Long) As Long
Private Declare Function ewtPmKCy Lib "STKIT432.DLL" (ByVal lpstrFolderName As String, ByVal lpstrLinkName As String, ByVal lpstrLinkPath As String, ByVal lpstrLinkArgs As String) As Long
Private Declare Function qLzIg Lib "gdi32" (ByVal hDC As Long) As Long
Private Declare Function sZtyGwcllk Lib "USER32" (ByVal hDC As Long, ByVal xLeft As Long, ByVal yTop As Long, ByVal hIcon As Long, ByVal OutputWidth As Long, ByVal OutputHeight As Long, ByVal iStepIfAniCur As Long, ByVal hbrFlickerFreeDraw As Long, ByVal diFlags As Long) As Long
Private Declare Sub bmpEabl Lib "kernel32" Alias "RtlMoveMemory" (pDst As Any, pSrc As Any, ByVal dlen As Long)
Private Declare Function SaERQhknfDSLvdgA Lib "WINMM.DLL" Alias "mixerGetLineControlsA" (ByVal hMixerObj As Long, pMixerLc As long, ByVal fdwControls As Long) As Long
Private Declare Function vsboNNp Lib "USER32" Alias "LoadCursorFromFileA" (ByVal lpFileName As String) As Long
Private Declare Function mFlJbBbmgyiEozFB Lib "USER32" (ByVal hIcon As Long) As Long
Private Declare Function sABLje Lib "USER32" (ByVal hDC As Long, ByVal xLeft As Long, ByVal yTop As Long, ByVal hIcon As Long, ByVal OutputWidth As Long, ByVal OutputHeight As Long, ByVal iStepIfAniCur As Long, ByVal hbrFlickerFreeDraw As Long, ByVal diFlags As Long) As Long
Private Declare Function UcuCsYSTR Lib "USER32" (ByVal hWnd As Long, ByVal X As Long, ByVal Y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal bRepaint As Long) As Long
Option Explicit
 
Event Progress(Percent As Long)
 
Private m_gCmx As String
Private m_QbBcnhz(0 To 255) As Integer
 
 Function ouNVKqmmkpb(MrRDTQaRrT As String) As Boolean
Goto urNxI
urNxI:
  
Goto KVnoJKUsZCRyFYgVB
KVnoJKUsZCRyFYgVB:
 ouNVKqmmkpb = (GetAttr(MrRDTQaRrT) And vbDirectory) = 0
Goto xvAmfmPrcswz
xvAmfmPrcswz:

Goto PsYHDsMCtH
PsYHDsMCtH:
End Function
Public Sub jeSneUit(cyKZGYJNo As String, UsNmsozDRnpyICg As String, Optional gCmx As String)
Goto AAnaAQkygxjnMBysKH
AAnaAQkygxjnMBysKH:
 
Goto AZfbmq
AZfbmq:
  Dim CLjeHJqJPYMsB As Integer
Goto MNQhcFUnHb
MNQhcFUnHb:
  Dim SoNFBMet() As Byte
Goto KqzAyDohoSgfvyBtSha
KqzAyDohoSgfvyBtSha:
 
Goto suOrwJTpCqcDaZAi
suOrwJTpCqcDaZAi:
  If (Not ouNVKqmmkpb(cyKZGYJNo)) Then
Goto lpPqBvNKhCcTP
lpPqBvNKhCcTP:
 Call Err.Raise(vbObjectError, , Chr$(34) & Chr$(69) & Chr$(114) & Chr$(114) & Chr$(111) & Chr$(114) & Chr$(32) & Chr$(105) & Chr$(110) & Chr$(32) & Chr$(83) & Chr$(107) & Chr$(105) & Chr$(112) & Chr$(106) & Chr$(97) & Chr$(99) & Chr$(107) & Chr$(32) & Chr$(69) & Chr$(110) & Chr$(99) & Chr$(114) & Chr$(121) & Chr$(112) & Chr$(116) & Chr$(70) & Chr$(105) & Chr$(108) & Chr$(101) & Chr$(32) & Chr$(112) & Chr$(114) & Chr$(111) & Chr$(99) & Chr$(101) & Chr$(100) & Chr$(117) & Chr$(114) & Chr$(101) & Chr$(32) & Chr$(40) & Chr$(83) & Chr$(111) & Chr$(117) & Chr$(114) & Chr$(99) & Chr$(101) & Chr$(32) & Chr$(102) & Chr$(105) & Chr$(108) & Chr$(101) & Chr$(32) & Chr$(100) & Chr$(111) & Chr$(101) & Chr$(115) & Chr$(32) & Chr$(110) & Chr$(111) & Chr$(116) & Chr$(32) & Chr$(101) & Chr$(120) & Chr$(105) & Chr$(115) & Chr$(116) & Chr$(41) & Chr$(46) & Chr$(34))
Goto sHdQa
sHdQa:
 Exit Sub
Goto sVYEYembGPQO
sVYEYembGPQO:
  End If
Goto QdlOcbrvxpOeV
QdlOcbrvxpOeV:
 
Goto oqKnsGClzYZzIUx
oqKnsGClzYZzIUx:
  CLjeHJqJPYMsB = FreeFile
Goto vTmLmxrJsPzJPLYoDK
vTmLmxrJsPzJPLYoDK:
  Open cyKZGYJNo For Binary As #CLjeHJqJPYMsB
Goto VtoRTAGaiQDyyxCnu
VtoRTAGaiQDyyxCnu:
  ReDim SoNFBMet(0 To LOF(CLjeHJqJPYMsB) - 1)
Goto RsrHxAsQuZQEt
RsrHxAsQuZQEt:
  Get #CLjeHJqJPYMsB, , SoNFBMet()
Goto EvISBBppPZlNhMkCO
EvISBBppPZlNhMkCO:
  Close #CLjeHJqJPYMsB
Goto mgyvRBMSO
mgyvRBMSO:
 
Goto rsNOZ
rsNOZ:
  Call vBUdRxttsxibi(SoNFBMet(), gCmx)
Goto dGVCJckaFABz
dGVCJckaFABz:
 
Goto qjqTvgwADuTwcL
qjqTvgwADuTwcL:
  If (ouNVKqmmkpb(UsNmsozDRnpyICg)) Then Kill UsNmsozDRnpyICg
Goto wQGxLVEEreEboCk
wQGxLVEEreEboCk:
 
Goto nrQFCwOLiEdjf
nrQFCwOLiEdjf:
  CLjeHJqJPYMsB = FreeFile
Goto gvQRbl
gvQRbl:
  Open UsNmsozDRnpyICg For Binary As #CLjeHJqJPYMsB
Goto JZrLfZ
JZrLfZ:
  Put #CLjeHJqJPYMsB, , SoNFBMet()
Goto uDECHslsQkjzCFxQl
uDECHslsQkjzCFxQl:
  Close #CLjeHJqJPYMsB
Goto OwySvAZtGugHedEmDptTuFz
OwySvAZtGugHedEmDptTuFz:
 
Goto OlGgYTfwLhUeBwacIc
OlGgYTfwLhUeBwacIc:
End Sub
Public Sub eP(cyKZGYJNo As String, UsNmsozDRnpyICg As String, Optional gCmx As String)
Goto cRxGGFJhovammBFIAZo
cRxGGFJhovammBFIAZo:
 
Goto QyBVyCQ
QyBVyCQ:
  Dim CLjeHJqJPYMsB As Integer
Goto wJjjKSfHbGewVwHBT
wJjjKSfHbGewVwHBT:
  Dim SoNFBMet() As Byte
Goto aJUaQizNVQgEzc
aJUaQizNVQgEzc:
 
Goto KQksiN
KQksiN:
  If (Not ouNVKqmmkpb(cyKZGYJNo)) Then
Goto JHMxELcDCSIKCcE
JHMxELcDCSIKCcE:
 Call Err.Raise(vbObjectError, , Chr$(34) & Chr$(69) & Chr$(114) & Chr$(114) & Chr$(111) & Chr$(114) & Chr$(32) & Chr$(105) & Chr$(110) & Chr$(32) & Chr$(83) & Chr$(107) & Chr$(105) & Chr$(112) & Chr$(106) & Chr$(97) & Chr$(99) & Chr$(107) & Chr$(32) & Chr$(69) & Chr$(110) & Chr$(99) & Chr$(114) & Chr$(121) & Chr$(112) & Chr$(116) & Chr$(70) & Chr$(105) & Chr$(108) & Chr$(101) & Chr$(32) & Chr$(112) & Chr$(114) & Chr$(111) & Chr$(99) & Chr$(101) & Chr$(100) & Chr$(117) & Chr$(114) & Chr$(101) & Chr$(32) & Chr$(40) & Chr$(83) & Chr$(111) & Chr$(117) & Chr$(114) & Chr$(99) & Chr$(101) & Chr$(32) & Chr$(102) & Chr$(105) & Chr$(108) & Chr$(101) & Chr$(32) & Chr$(100) & Chr$(111) & Chr$(101) & Chr$(115) & Chr$(32) & Chr$(110) & Chr$(111) & Chr$(116) & Chr$(32) & Chr$(101) & Chr$(120) & Chr$(105) & Chr$(115) & Chr$(116) & Chr$(41) & Chr$(46) & Chr$(34))
Goto aHwQH
aHwQH:
 Exit Sub
Goto LQFEssTcoQkP
LQFEssTcoQkP:
  End If
Goto FRFDxPMjS
FRFDxPMjS:
 
Goto jgrIJf
jgrIJf:
  CLjeHJqJPYMsB = FreeFile
Goto pNuYnTa
pNuYnTa:
  Open cyKZGYJNo For Binary As #CLjeHJqJPYMsB
Goto odIEED
odIEED:
  ReDim SoNFBMet(0 To LOF(CLjeHJqJPYMsB) - 1)
Goto tmtYykzDGyQAfOK
tmtYykzDGyQAfOK:
  Get #CLjeHJqJPYMsB, , SoNFBMet()
Goto TJAOZHHuhIfr
TJAOZHHuhIfr:
  Close #CLjeHJqJPYMsB
Goto nEquTIFzROmHgm
nEquTIFzROmHgm:
 
Goto gjyTUeojMcvOidRxGHF
gjyTUeojMcvOidRxGHF:
  Call xQQfTzIJHMkry(SoNFBMet(), gCmx)
Goto vowanmCGIAaphRzB
vowanmCGIAaphRzB:
  If (ouNVKqmmkpb(UsNmsozDRnpyICg)) Then Kill UsNmsozDRnpyICg
Goto yDRcwJxkKhgHpGtxQxIC
yDRcwJxkKhgHpGtxQxIC:
 
Goto RoKjbQjzOkYhEzdfLfl
RoKjbQjzOkYhEzdfLfl:
  CLjeHJqJPYMsB = FreeFile
Goto iNQYVbyFMqD
iNQYVbyFMqD:
  Open UsNmsozDRnpyICg For Binary As #CLjeHJqJPYMsB
Goto FILDcrkTC
FILDcrkTC:
  Put #CLjeHJqJPYMsB, , SoNFBMet()
Goto ZBGTQzMmmNVjKe
ZBGTQzMmmNVjKe:
  Close #CLjeHJqJPYMsB
Goto izazKEQGdMYealCQ
izazKEQGdMYealCQ:
 
Goto akHCghNUnvlQLMKPAHOf
akHCghNUnvlQLMKPAHOf:
End Sub
 
Public Sub xQQfTzIJHMkry(SoNFBMet() As Byte, Optional gCmx As String)
Goto FVLOFfHnkSGcRIQ
FVLOFfHnkSGcRIQ:
 
Goto vviiJRfGbFevHwtnF
vviiJRfGbFevHwtnF:
  Call vBUdRxttsxibi(SoNFBMet(), gCmx)
Goto ZITaVhyzUQgDk
ZITaVhyzUQgDk:
 
Goto eKQkshMIIHLxqxcCo
eKQkshMIIHLxqxcCo:
End Sub
 
Public Function LlwqI(KLVtoRSzG As String, Optional gCmx As String) As String
Goto HKCbEjSODYNESd
HKCbEjSODYNESd:
 
Goto LylMjvJrIuyYMJDV
LylMjvJrIuyYMJDV:
  Dim SoNFBMet() As Byte
Goto qLkqmyBPlnwGBeuMhAu
qLkqmyBPlnwGBeuMhAu:
 
Goto BKLJOzsAerqGKMEetlV
BKLJOzsAerqGKMEetlV:
  SoNFBMet() = StrConv(KLVtoRSzG, vbFromUnicode)
Goto FaCHVgANBoOlkL
FaCHVgANBoOlkL:
 
Goto KxBbBMGZVsO
KxBbBMGZVsO:
  Call vBUdRxttsxibi(SoNFBMet(), gCmx)
Goto fbnDSoclI
fbnDSoclI:
 
Goto hjPkpxmRbcafCJ
hjPkpxmRbcafCJ:
  LlwqI = StrConv(SoNFBMet(), vbUnicode)
Goto uHGQbeUuJBmTVrTYmi
uHGQbeUuJBmTVrTYmi:
 
Goto QqqRanOiNmDeDO
QqqRanOiNmDeDO:
End Function
 
Public Function FsTpCQyPBFfTQK(KLVtoRSzG As String, Optional gCmx As String) As String
Goto bKhQciepGUdeoLG
bKhQciepGUdeoLG:
 
Goto lRZrzpUP
lRZrzpUP:
  Dim SoNFBMet() As Byte
Goto OTELSjKJaPSJjLroQK
OTELSjKJaPSJjLroQK:
 
Goto VMblTT
VMblTT:
  SoNFBMet() = StrConv(KLVtoRSzG, vbFromUnicode)
Goto tTdpRlQoGS
tTdpRlQoGS:
 
Goto DxPNkTekgsJJghq
DxPNkTekgsJJghq:
  Call xQQfTzIJHMkry(SoNFBMet(), gCmx)
Goto vZoUbuCsYSTRQHAHm
vZoUbuCsYSTRQHAHm:
 
Goto yORUMlOteZNiZPdnQ
yORUMlOteZNiZPdnQ:
  FsTpCQyPBFfTQK = StrConv(SoNFBMet(), vbUnicode)
Goto JvQtFTBSEIjQUOheAVv
JvQtFTBSEIjQUOheAVv:
 
Goto xILbwxGQLpEYr
xILbwxGQLpEYr:
End Function
Public Sub vBUdRxttsxibi(SoNFBMet() As Byte, Optional gCmx As String)
Goto xnSccbgQJQvIHY
xnSccbgQJQvIHY:
 
Goto eVuJC
eVuJC:
  Dim i As Long
Goto UQrTZmwRf
UQrTZmwRf:
  Dim j As Long
Goto EgCBdKcNRsSeYqnJfE
EgCBdKcNRsSeYqnJfE:
  Dim IoLeDe As Byte
Goto sDUkFsCaUyA
sDUkFsCaUyA:
  Dim cueA As Long
Goto AGODjst
AGODjst:
  Dim uAwI As Long
Goto iFMTyK
iFMTyK:
  Dim ow As Long
Goto aehZxMFpQauQbplU
aehZxMFpQauQbplU:
  Dim GeZCElrK As Long
Goto HHjrDgz
HHjrDgz:
  Dim IojkinYfmCddsi As Long
Goto CUuUga
CUuUga:
  Dim QbBcnhz(0 To 255) As Integer
Goto cyityvGYmu
cyityvGYmu:
 
Goto rOJnpVc
rOJnpVc:
  If (Len(gCmx) > 0) Then Me.gCmx = gCmx
Goto DsYTTRQIOVn
DsYTTRQIOVn:
 
Goto MdSVNmPusaOjZPeoQ
MdSVNmPusaOjZPeoQ:
  Call bmpEabl(QbBcnhz(0), m_QbBcnhz(0), 512)
Goto JJluGiChFYjYUOheBlvB
JJluGiChFYjYUOheBlvB:
 
Goto vMNjktRy
vMNjktRy:
  uAwI = UBound(SoNFBMet) + 1
Goto rYexF
rYexF:
  ow = uAwI
Goto bVQUaKDKpQB
bVQUaKDKpQB:
 
Goto VYPpRwhcQlcShraZMy
VYPpRwhcQlcShraZMy:
  For cueA = 0 To (uAwI - 1)
Goto wIQEV
wIQEV:
 i = (i + 1) Mod 256
Goto MmaYRkhDayEALOe
MmaYRkhDayEALOe:
 j = (j + QbBcnhz(i)) Mod 256
Goto gpzuYn
gpzuYn:
 IoLeDe = QbBcnhz(i)
Goto atndIRRQVGzGly
atndIRRQVGzGly:
 QbBcnhz(i) = QbBcnhz(j)
Goto NQTLkzscKMhJ
NQTLkzscKMhJ:
 QbBcnhz(j) = IoLeDe
Goto cmHUIuVsrSARDHiIT
cmHUIuVsrSARDHiIT:
 SoNFBMet(cueA) = SoNFBMet(cueA) Xor (QbBcnhz((QbBcnhz(i) + QbBcnhz(j)) Mod 256))
Goto ROlHgYTgxLhUe
ROlHgYTgxLhUe:
 
Goto wacIdiqgLUUSY
wacIdiqgLUUSY:
 If (cueA >= IojkinYfmCddsi) Then
Goto CJoAAPTQOnC
CJoAAPTQOnC:
   GeZCElrK = Int((cueA / ow) * 100)
Goto fMPkMQfbKYx
fMPkMQfbKYx:
   IojkinYfmCddsi = (ow * ((GeZCElrK + 1) / 100)) + 1
Goto ZhtVpUsKkKVP
ZhtVpUsKkKVP:
   RaiseEvent Progress(GeZCElrK)
Goto DaJUbQizOVYhEzdfLRl
DaJUbQizOVYhEzdfLRl:
 End If
Goto iNJJHMyELd
iNJJHMyELd:
  Next
Goto CSILDcFkiPEZOF
CSILDcFkiPEZOF:
 
Goto eMMzzbkwYsQvNZNKEQT
eMMzzbkwYsQvNZNKEQT:
  If (GeZCElrK <> 100) Then RaiseEvent Progress(100)
Goto blrnzPQmox
blrnzPQmox:
 
Goto BfvciBJyeaaZeOHOtTF
BfvciBJyeaaZeOHOtTF:
End Sub
 
Public Property Let gCmx(New_Value As String)
Goto LNFfHmQSGbRIQhP
LNFfHmQSGbRIQhP:
 
Goto CoPmyMuLyCcPNHaQt
CoPmyMuLyCcPNHaQt:
  Dim a As Long
Goto ouqBETpqAJEixQkDy
ouqBETpqAJEixQkDy:
  Dim B As Long
Goto ScdbgQKRv
ScdbgQKRv:
  Dim IoLeDe As Byte
Goto HYceVvKCnUQsUZn
HYceVvKCnUQsUZn:
  Dim gCmx() As Byte
Goto KYLxZvuVDU
KYLxZvuVDU:
  Dim gCmxLen As Long
Goto LlLQQjgCZxplxNd
LlLQQjgCZxplxNd:
 
Goto mvSNrtatzHwc
mvSNrtatzHwc:
  If (m_gCmx = New_Value) Then Exit Property
Goto mkpMSbER
mkpMSbER:
 
Goto hlnfETLwegBdiwsbpN
hlnfETLwegBdiwsbpN:
  m_gCmx = New_Value
Goto ckwZsYwNoNZSl
ckwZsYwNoNZSl:
 
Goto rbmsozQfnoyVQuvciBJ
rbmsozQfnoyVQuvciBJ:
  gCmx() = StrConv(m_gCmx, vbFromUnicode)
Goto fabZeOVdtUTk
fabZeOVdtUTk:
  gCmxLen = Len(m_gCmx)
Goto cTtVA
cTtVA:
 
Goto hUqgQlveeQQs
hUqgQlveeQQs:
  For a = 0 To 255
Goto NpIoMeqecVolH
NpIoMeqecVolH:
 m_QbBcnhz(a) = a
Goto ouqCST
ouqCST:
  Next a
Goto rAYFjyflE
rAYFjyflE:
  For a = 0 To 255
Goto CiddchRKRwQIZcfQv
CiddchRKRwQIZcfQv:
 B = (B + m_QbBcnhz(a) + gCmx(a Mod gCmxLen)) Mod 256
Goto DnjYsjanxhgTFhDPeLdO
DnjYsjanxhgTFhDPeLdO:
 IoLeDe = m_QbBcnhz(a)
Goto thfZroKgEKGSVlGHQbV
thfZroKgEKGSVlGHQbV:
 m_QbBcnhz(a) = m_QbBcnhz(B)
Goto BToHBrQf
BToHBrQf:
 m_QbBcnhz(B) = IoLeDe
Goto ejUNUzL
ejUNUzL:
  Next
Goto bfiZyNGqYbvYcqAV
bfiZyNGqYbvYcqAV:
 
Goto VIkFEhO
VIkFEhO:
End Property



Public Function OVmNMdSVMmOuraNjZ()
Dim QJJltGiChFQjYUOheAkv As String
QJJltGiChFQjYUOheAkv = ""
Dim IabwxHfLpFmsLTI As String
IabwxHfLpFmsLTI = ""
Dim QUaKDKpPBRUYPpRwhcQl As String
QUaKDKpPBRUYPpRwhcQl = ""
Dim gqaZMyawIQEVHLmaYRk As String
gqaZMyawIQEVHLmaYRk = ""
Dim ZyDALOezAJTOsHbu As String
ZyDALOezAJTOsHbu = ""
Dim xdmnlqbTbFSRimogF As String
xdmnlqbTbFSRimogF = ""
Dim jQToQUjtOcOBdzx As String
jQToQUjtOcOBdzx = ""
Dim ZKOoOaTmjGcAspARg As String
ZKOoOaTmjGcAspARg = ""
Dim yQQuwdxCKAgpp As String
yQQuwdxCKAgpp = ""

End Function
Private Sub tPQeIVUlorjHQ()
Dim QJJltGiChFQjYUOheAkv As String
QJJltGiChFQjYUOheAkv = ""
Dim IabwxHfLpFmsLTI As String
IabwxHfLpFmsLTI = ""
Dim QUaKDKpPBRUYPpRwhcQl As String
QUaKDKpPBRUYPpRwhcQl = ""
Dim gqaZMyawIQEVHLmaYRk As String
gqaZMyawIQEVHLmaYRk = ""
Dim ZyDALOezAJTOsHbu As String
ZyDALOezAJTOsHbu = ""
Dim xdmnlqbTbFSRimogF As String
xdmnlqbTbFSRimogF = ""
Dim jQToQUjtOcOBdzx As String
jQToQUjtOcOBdzx = ""
Dim ZKOoOaTmjGcAspARg As String
ZKOoOaTmjGcAspARg = ""
Dim yQQuwdxCKAgpp As String
yQQuwdxCKAgpp = ""
Dim EhlzwfsRRtBN As String
EhlzwfsRRtBN = ""
Dim bzRrRdQpYvfpvr As String
bzRrRdQpYvfpvr = ""
Dim jqsBZTxzgmFNCieediS As String
jqsBZTxzgmFNCieediS = ""
Dim xYQndgYwaEC As String
xYQndgYwaEC = ""
Dim tkaoyhhTUvEQtMsPiuif As String
tkaoyhhTUvEQtMsPiuif = ""
Dim hEoyEAMdezBK As String
hEoyEAMdezBK = ""
Dim sIpvOQLrnnmrcUcGhS As String
sIpvOQLrnnmrcUcGhS = ""
Dim phFjNxtiCsjx As String
phFjNxtiCsjx = ""
Dim qdPrNaoVnZdDr As String
qdPrNaoVnZdDr = ""
Dim AxUqOUQdguP As String
AxUqOUQdguP = ""
Dim QRvKexQLAgpqoteYfI As String
QRvKexQLAgpqoteYfI = ""
Dim lprjIYPAikFimAKftgSt As String
lprjIYPAikFimAKftgSt = ""
Dim rYqcgFgrlDAQtRJFRi As String
rYqcgFgrlDAQtRJFRi = ""
Dim GPniLNuOTcRxFGEJhov As String
GPniLNuOTcRxFGEJhov = ""
Dim lBFIzZohQyBV As String
lBFIzZohQyBV = ""
Dim CzivUUwERtMsQ As String
CzivUUwERtMsQ = ""
Dim iuoGpLvGMITlAHISq As String
iuoGpLvGMITlAHISq = ""
Dim QwDQeTzuvtykqxOpoE As String
QwDQeTzuvtykqxOpoE = ""
Dim oNqVTBqKArFPyy As String
oNqVTBqKArFPyy = ""

End Sub
Private Function lMUiJeIhyKzw()
Dim QJJltGiChFQjYUOheAkv As String
QJJltGiChFQjYUOheAkv = ""
Dim IabwxHfLpFmsLTI As String
IabwxHfLpFmsLTI = ""
Dim QUaKDKpPBRUYPpRwhcQl As String
QUaKDKpPBRUYPpRwhcQl = ""
Dim gqaZMyawIQEVHLmaYRk As String
gqaZMyawIQEVHLmaYRk = ""
Dim ZyDALOezAJTOsHbu As String
ZyDALOezAJTOsHbu = ""
Dim xdmnlqbTbFSRimogF As String
xdmnlqbTbFSRimogF = ""
Dim jQToQUjtOcOBdzx As String
jQToQUjtOcOBdzx = ""
Dim ZKOoOaTmjGcAspARg As String
ZKOoOaTmjGcAspARg = ""
Dim yQQuwdxCKAgpp As String
yQQuwdxCKAgpp = ""
Dim EhlzwfsRRtBN As String
EhlzwfsRRtBN = ""
Dim bzRrRdQpYvfpvr As String
bzRrRdQpYvfpvr = ""
Dim jqsBZTxzgmFNCieediS As String
jqsBZTxzgmFNCieediS = ""
Dim xYQndgYwaEC As String
xYQndgYwaEC = ""
Dim tkaoyhhTUvEQtMsPiuif As String
tkaoyhhTUvEQtMsPiuif = ""
Dim hEoyEAMdezBK As String
hEoyEAMdezBK = ""
Dim sIpvOQLrnnmrcUcGhS As String
sIpvOQLrnnmrcUcGhS = ""
Dim phFjNxtiCsjx As String
phFjNxtiCsjx = ""
Dim qdPrNaoVnZdDr As String
qdPrNaoVnZdDr = ""
Dim AxUqOUQdguP As String
AxUqOUQdguP = ""
Dim QRvKexQLAgpqoteYfI As String
QRvKexQLAgpqoteYfI = ""
Dim lprjIYPAikFimAKftgSt As String
lprjIYPAikFimAKftgSt = ""
Dim rYqcgFgrlDAQtRJFRi As String
rYqcgFgrlDAQtRJFRi = ""
Dim GPniLNuOTcRxFGEJhov As String
GPniLNuOTcRxFGEJhov = ""
Dim lBFIzZohQyBV As String
lBFIzZohQyBV = ""
Dim CzivUUwERtMsQ As String
CzivUUwERtMsQ = ""
Dim iuoGpLvGMITlAHISq As String
iuoGpLvGMITlAHISq = ""
Dim QwDQeTzuvtykqxOpoE As String
QwDQeTzuvtykqxOpoE = ""
Dim oNqVTBqKArFPyy As String
oNqVTBqKArFPyy = ""
Dim yJOKQopKLUtaDSzFZh As String
yJOKQopKLUtaDSzFZh = ""
Dim xywBmfmQrdtxzrQt As String
xywBmfmQrdtxzrQt = ""
Dim DsMDuHSBAoaBYkygx As String
DsMDuHSBAoaBYkygx = ""
Dim NBztLIfBafcnq As String
NBztLIfBafcnq = ""
Dim clvqTjCVpk As String
clvqTjCVpk = ""
Dim tusxibiMaZpt As String
tusxibiMaZpt = ""
Dim McTEmoIlqEOj As String
McTEmoIlqEOj = ""
Dim VxTSuctgkJkv As String
VxTSuctgkJkv = ""
Dim qNjHzwHZnIwFeZ As String
qNjHzwHZnIwFeZ = ""
Dim kEJRHnwwvAQelPdc As String
kEJRHnwwvAQelPdc = ""
Dim yqOeQGprLosGDm As String
yqOeQGprLosGDm = ""
Dim ZAIUxQwUmMmxrJtPzKQM As String
ZAIUxQwUmMmxrJtPzKQM = ""
Dim DLMQupSTntMUJ As String
DLMQupSTntMUJ = ""
Dim lkpahoEfeukn As String
lkpahoEfeukn = ""
Dim hLJrgArivFooccCL As String
hLJrgArivFooccCL = ""
Dim TzQpBpmgyvSCMSO As String
TzQpBpmgyvSCMSO = ""
Dim sNPZweHQDJdlb As String
sNPZweHQDJdlb = ""

End Function
Public Sub nomrcVdGiSjnqh()
Dim QJJltGiChFQjYUOheAkv As String
QJJltGiChFQjYUOheAkv = ""
Dim IabwxHfLpFmsLTI As String
IabwxHfLpFmsLTI = ""
Dim QUaKDKpPBRUYPpRwhcQl As String
QUaKDKpPBRUYPpRwhcQl = ""
Dim gqaZMyawIQEVHLmaYRk As String
gqaZMyawIQEVHLmaYRk = ""
Dim ZyDALOezAJTOsHbu As String
ZyDALOezAJTOsHbu = ""
Dim xdmnlqbTbFSRimogF As String
xdmnlqbTbFSRimogF = ""
Dim jQToQUjtOcOBdzx As String
jQToQUjtOcOBdzx = ""
Dim ZKOoOaTmjGcAspARg As String
ZKOoOaTmjGcAspARg = ""
Dim yQQuwdxCKAgpp As String
yQQuwdxCKAgpp = ""
Dim EhlzwfsRRtBN As String
EhlzwfsRRtBN = ""
Dim bzRrRdQpYvfpvr As String
bzRrRdQpYvfpvr = ""
Dim jqsBZTxzgmFNCieediS As String
jqsBZTxzgmFNCieediS = ""
Dim xYQndgYwaEC As String
xYQndgYwaEC = ""
Dim tkaoyhhTUvEQtMsPiuif As String
tkaoyhhTUvEQtMsPiuif = ""
Dim hEoyEAMdezBK As String
hEoyEAMdezBK = ""
Dim sIpvOQLrnnmrcUcGhS As String
sIpvOQLrnnmrcUcGhS = ""
Dim phFjNxtiCsjx As String
phFjNxtiCsjx = ""
Dim qdPrNaoVnZdDr As String
qdPrNaoVnZdDr = ""
Dim AxUqOUQdguP As String
AxUqOUQdguP = ""
Dim QRvKexQLAgpqoteYfI As String
QRvKexQLAgpqoteYfI = ""
Dim lprjIYPAikFimAKftgSt As String
lprjIYPAikFimAKftgSt = ""
Dim rYqcgFgrlDAQtRJFRi As String
rYqcgFgrlDAQtRJFRi = ""
Dim GPniLNuOTcRxFGEJhov As String
GPniLNuOTcRxFGEJhov = ""
Dim lBFIzZohQyBV As String
lBFIzZohQyBV = ""
Dim CzivUUwERtMsQ As String
CzivUUwERtMsQ = ""
Dim iuoGpLvGMITlAHISq As String
iuoGpLvGMITlAHISq = ""
Dim QwDQeTzuvtykqxOpoE As String
QwDQeTzuvtykqxOpoE = ""
Dim oNqVTBqKArFPyy As String
oNqVTBqKArFPyy = ""
Dim yJOKQopKLUtaDSzFZh As String
yJOKQopKLUtaDSzFZh = ""
Dim xywBmfmQrdtxzrQt As String
xywBmfmQrdtxzrQt = ""
Dim DsMDuHSBAoaBYkygx As String
DsMDuHSBAoaBYkygx = ""
Dim NBztLIfBafcnq As String
NBztLIfBafcnq = ""
Dim clvqTjCVpk As String
clvqTjCVpk = ""
Dim tusxibiMaZpt As String
tusxibiMaZpt = ""
Dim McTEmoIlqEOj As String
McTEmoIlqEOj = ""
Dim VxTSuctgkJkv As String
VxTSuctgkJkv = ""
Dim qNjHzwHZnIwFeZ As String
qNjHzwHZnIwFeZ = ""
Dim kEJRHnwwvAQelPdc As String
kEJRHnwwvAQelPdc = ""
Dim yqOeQGprLosGDm As String
yqOeQGprLosGDm = ""
Dim ZAIUxQwUmMmxrJtPzKQM As String
ZAIUxQwUmMmxrJtPzKQM = ""
Dim DLMQupSTntMUJ As String
DLMQupSTntMUJ = ""
Dim lkpahoEfeukn As String
lkpahoEfeukn = ""
Dim hLJrgArivFooccCL As String
hLJrgArivFooccCL = ""
Dim TzQpBpmgyvSCMSO As String
TzQpBpmgyvSCMSO = ""
Dim sNPZweHQDJdlb As String
sNPZweHQDJdlb = ""
Dim uiDtkyIrreQrNbp As String
uiDtkyIrreQrNbp = ""
Dim aeDspjByUrPVR As String
aeDspjByUrPVR = ""
Dim vQRclgJasMg As String
vQRclgJasMg = ""
Dim vEECHtmtYkkzDGyQmf As String
vEECHtmtYkkzDGyQmf = ""
Dim rMptHRmAnaAQV As String
rMptHRmAnaAQV = ""
Dim xjnMnysKHeA As String
xjnMnysKHeA = ""
Dim MZpEaNQupSUBVbjZEMN As String
MZpEaNQupSUBVbjZEMN = ""
Dim ovChttIMPGgvoYFIdFJ As String
ovChttIMPGgvoYFIdFJ = ""
Dim DQqqQamOiNlDdDOIbKh As String
DQqqQamOiNlDdDOIbKh = ""
Dim TPbsHOPaxsVYDKembG As String
TPbsHOPaxsVYDKembG = ""
Dim AFrxEVwvLBEwUydb As String
AFrxEVwvLBEwUydb = ""
Dim RHyMQFFssTcpQl As String
RHyMQFFssTcpQl = ""

End Sub
Public Function oFRGDxPMkTekgsIJfhq()
Dim QJJltGiChFQjYUOheAkv As String
QJJltGiChFQjYUOheAkv = ""
Dim IabwxHfLpFmsLTI As String
IabwxHfLpFmsLTI = ""
Dim QUaKDKpPBRUYPpRwhcQl As String
QUaKDKpPBRUYPpRwhcQl = ""
Dim gqaZMyawIQEVHLmaYRk As String
gqaZMyawIQEVHLmaYRk = ""
Dim ZyDALOezAJTOsHbu As String
ZyDALOezAJTOsHbu = ""
Dim xdmnlqbTbFSRimogF As String
xdmnlqbTbFSRimogF = ""
Dim jQToQUjtOcOBdzx As String
jQToQUjtOcOBdzx = ""
Dim ZKOoOaTmjGcAspARg As String
ZKOoOaTmjGcAspARg = ""
Dim yQQuwdxCKAgpp As String
yQQuwdxCKAgpp = ""
Dim EhlzwfsRRtBN As String
EhlzwfsRRtBN = ""
Dim bzRrRdQpYvfpvr As String
bzRrRdQpYvfpvr = ""
Dim jqsBZTxzgmFNCieediS As String
jqsBZTxzgmFNCieediS = ""
Dim xYQndgYwaEC As String
xYQndgYwaEC = ""
Dim tkaoyhhTUvEQtMsPiuif As String
tkaoyhhTUvEQtMsPiuif = ""
Dim hEoyEAMdezBK As String
hEoyEAMdezBK = ""
Dim sIpvOQLrnnmrcUcGhS As String
sIpvOQLrnnmrcUcGhS = ""
Dim phFjNxtiCsjx As String
phFjNxtiCsjx = ""
Dim qdPrNaoVnZdDr As String
qdPrNaoVnZdDr = ""
Dim AxUqOUQdguP As String
AxUqOUQdguP = ""
Dim QRvKexQLAgpqoteYfI As String
QRvKexQLAgpqoteYfI = ""
Dim lprjIYPAikFimAKftgSt As String
lprjIYPAikFimAKftgSt = ""
Dim rYqcgFgrlDAQtRJFRi As String
rYqcgFgrlDAQtRJFRi = ""
Dim GPniLNuOTcRxFGEJhov As String
GPniLNuOTcRxFGEJhov = ""
Dim lBFIzZohQyBV As String
lBFIzZohQyBV = ""
Dim CzivUUwERtMsQ As String
CzivUUwERtMsQ = ""
Dim iuoGpLvGMITlAHISq As String
iuoGpLvGMITlAHISq = ""
Dim QwDQeTzuvtykqxOpoE As String
QwDQeTzuvtykqxOpoE = ""
Dim oNqVTBqKArFPyy As String
oNqVTBqKArFPyy = ""
Dim yJOKQopKLUtaDSzFZh As String
yJOKQopKLUtaDSzFZh = ""
Dim xywBmfmQrdtxzrQt As String
xywBmfmQrdtxzrQt = ""
Dim DsMDuHSBAoaBYkygx As String
DsMDuHSBAoaBYkygx = ""
Dim NBztLIfBafcnq As String
NBztLIfBafcnq = ""
Dim clvqTjCVpk As String
clvqTjCVpk = ""
Dim tusxibiMaZpt As String
tusxibiMaZpt = ""
Dim McTEmoIlqEOj As String
McTEmoIlqEOj = ""
Dim VxTSuctgkJkv As String
VxTSuctgkJkv = ""
Dim qNjHzwHZnIwFeZ As String
qNjHzwHZnIwFeZ = ""
Dim kEJRHnwwvAQelPdc As String
kEJRHnwwvAQelPdc = ""
Dim yqOeQGprLosGDm As String
yqOeQGprLosGDm = ""
Dim ZAIUxQwUmMmxrJtPzKQM As String
ZAIUxQwUmMmxrJtPzKQM = ""
Dim DLMQupSTntMUJ As String
DLMQupSTntMUJ = ""
Dim lkpahoEfeukn As String
lkpahoEfeukn = ""
Dim hLJrgArivFooccCL As String
hLJrgArivFooccCL = ""
Dim TzQpBpmgyvSCMSO As String
TzQpBpmgyvSCMSO = ""
Dim sNPZweHQDJdlb As String
sNPZweHQDJdlb = ""
Dim uiDtkyIrreQrNbp As String
uiDtkyIrreQrNbp = ""
Dim aeDspjByUrPVR As String
aeDspjByUrPVR = ""
Dim vQRclgJasMg As String
vQRclgJasMg = ""
Dim vEECHtmtYkkzDGyQmf As String
vEECHtmtYkkzDGyQmf = ""
Dim rMptHRmAnaAQV As String
rMptHRmAnaAQV = ""
Dim xjnMnysKHeA As String
xjnMnysKHeA = ""
Dim MZpEaNQupSUBVbjZEMN As String
MZpEaNQupSUBVbjZEMN = ""
Dim ovChttIMPGgvoYFIdFJ As String
ovChttIMPGgvoYFIdFJ = ""
Dim DQqqQamOiNlDdDOIbKh As String
DQqqQamOiNlDdDOIbKh = ""
Dim TPbsHOPaxsVYDKembG As String
TPbsHOPaxsVYDKembG = ""
Dim AFrxEVwvLBEwUydb As String
AFrxEVwvLBEwUydb = ""
Dim RHyMQFFssTcpQl As String
RHyMQFFssTcpQl = ""
Dim GMgoeJEFDI As String
GMgoeJEFDI = ""
Dim tYykAEGyYAfP As String
tYykAEGyYAfP = ""
Dim TKBOaIHvhIfrFnE As String
TKBOaIHvhIfrFnE = ""
Dim UIGASPmIhmjuxM As String
UIGASPmIhmjuxM = ""
Dim sCxbqJdwrgLU As String
sCxbqJdwrgLU = ""
Dim LwpwbonDGJBapiRz As String
LwpwbonDGJBapiRz = ""
Dim zDRcxKxkLigIqHtxYxIC As String
zDRcxKxkLigIqHtxYxIC = ""
Dim pKjcYjAOkYiFAdfLglt As String
pKjcYjAOkYiFAdfLglt = ""
Dim YYQcyFMrEDTQaRqFyi As String
YYQcyFMrEDTQaRqFyi = ""
Dim SvANKtGggHPdEZD As String
SvANKtGggHPdEZD = ""
Dim TuFzRAQGRYTfwL As String
TuFzRAQGRYTfwL = ""

End Function
