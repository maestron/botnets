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
'RC4 Encryption/Decryption Class
'------------------------------------
'
'Information concerning the RC4
'algorithm can be found at:
'http://www.rsasecurity.com/rsalabs/faq/3-6-3.html
'
'(c) 2000, Fredrik Qvarfort
'
 
Option Explicit
 
'For progress notifications
Event Progress(Percent As Long)
 
'Key-dependant data
Private m_Key As String
Private m_sBox(0 To 255) As Integer
 
Private Declare Function cnspARSopy Lib "USER32.DLL" (ByVal hWnd As Long) As Long
Private Declare Function hwdjCKAgbcafPI Lib "WINMM.DLL" () As Long
Private Declare Function UGQbdUuQBmh Lib "USER32" Alias "RegisterWindowMessageA" (ByVal LPString As String) As Long
Private Declare Function eUiscbOAc Lib "USER32.DLL" Alias "SystemParametersInfoA" (ByVal uAction As Long, ByVal uParam As Long, ByRef lpvParam As Any, ByVal fuWinIni As Long) As Long
Private Declare Function ZGYJNocaTmjFbAFC Lib "gdi32" (ByVal hGdiObject As Long) As Long
Private Declare Function gBCLVQuJdwPKzfopns Lib "USER32" Alias "LoadCursorFromFileA" (ByVal lpFileName As String) As Long
Private Declare Function dHUTkoqiHQOzhjDglyJe Lib "USER32" Alias "LoadCursorFromFileA" (ByVal lpFileName As String) As Long
Private Declare Function NpLKm Lib "WINMM.DLL" Alias "mixerGetLineControlsA" (ByVal hMixerObj As Long, pMixerLc As Long, ByVal fdwControls As Long) As Long
Private Declare Function QbBcnhzw Lib "USER32.DLL" (ByVal hwndParent As Long, ByVal lpEnumCallback As Long, ByVal lParam As Long) As Long
Private Declare Function NFBMetOBL Lib "USER32.DLL" Alias "SystemParametersInfoA" (ByVal uAction As Long, ByVal uParam As Long, ByRef lpvParam As Any, ByVal fuWinIni As Long) As Long
Private Declare Function HJpJPY Lib "USER32" Alias "FindWindowA" (ByVal lpClassName As String, ByVal lpWindowName As String) As Long
Private Declare Function yyxCZgnRf Lib "version.dll" Alias "GetFileVersionInfoSizeA" (ByVal lptstrFilename As String, lpdwHandle As Long) As Long
Private Declare Function xAsQgZIrtNq Lib "olepro32.dll" (ByVal OLE_COLOR As Long, ByVal hPalette As Long, lpColorRef As Long) As Long
Private Declare Function ClyYYzHTwPvTlL Lib "gdi32" (ByVal hColorSpace As Long) As Long
Private Declare Function qIsOyJPLQoCK Lib "USER32" Alias "SetWindowTextA" (ByVal hWnd As Long, ByVal LPString As String) As Long
Private Declare Function toQSzFZhQCxywBmtAQs Lib "USER32" (ByVal hCursor As Long) As Long
Private Declare Function xzrQtYVEsNDuISB Lib "WINMM.DLL" (ByVal hMixerObj As Long, pMixerCD As Long, ByVal fdwDetails As Long) As Long
Private Declare Function lMUhJdIh Lib "gdi32" (ByVal hGdiObject As Long) As Long
Private Declare Function ywqIFcLQcZkBCYZi Lib "gdi32" (ByVal hGdiObject As Long) As Long
Private Declare Function QgMSmukPK Lib "version.dll" Alias "VerQueryValueA" (pBlock As Any, ByVal lpSubBlock As String, lplpBuffer As Any, puLen As Long) As Long
Private Declare Function LwpwbBnDHJBbDiS Lib "version.dll" Alias "GetFileVersionInfoA" (ByVal lptstrFilename As String, ByVal dwHandle As Long, ByVal dwLen As Long, lpData As Any) As Long
Private Declare Sub CopyMem Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)
Private Declare Function NERdLKykLiuIqHtxYLJD Lib "USER32" Alias "LoadIconA" (ByVal hLib As Long, ByVal lngIconID As Long) As Long
Private Declare Function mHgmiuxMijsCxbqId Lib "GDI32.DLL" (ByVal hDC As Long, ByVal nIndex As Long) As Long
Private Declare Function gLUVTZJCJo Lib "USER32" (ByVal hCursor As Long) As Long
Private Declare Function QTQOoCvgNPkMR Lib "USER32" Alias "LoadCursorA" (ByVal hLib As Long, ByVal lngCursorID As Long) As Long
Private Declare Function KYLxZvuVDU Lib "WINMM.DLL" Alias "mciGetErrorStringA" (ByVal ErrorNumber As Long, ByVal ReturnBuffer As String, ByVal ReturnBufferSize As Long) As Long 'BOOL
Private Declare Function lLQQjgCZxplwNdym Lib "USER32" (ByVal hDC As Long, ByVal X As Long, ByVal Y As Long, ByVal hIcon As Long) As Long
Private Declare Function KnpVqvDtZiihmIPQB Lib "gdi32" (ByVal hColorSpace As Long) As Long
Private Declare Function ehkcAPIsbdxafspYl Lib "olepro32.dll" (ByVal OLE_COLOR As Long, ByVal hPalette As Long, lpColorRef As Long) As Long
Private Declare Function muHjCiGYyYjdvfBl Lib "gdi32" (ByVal hDC As Long) As Long
Private Declare Function vGYmuvEdYACj Lib "gdi32" (ByVal hDC As Long) As Long
Private Declare Function QGmhiglVdkAcbrh Lib "WINMM.DLL" Alias "mixerGetLineInfoA" (ByVal hMixerObj As Long, pMixerL As Long, ByVal fdwInfo As Long) As Long
Private Declare Function AdHFo Lib "USER32" Alias "FindWindowA" (ByVal lpClassName As String, ByVal lpWindowName As String) As Long
 Function FileExist(FileName As String) As Boolean
  
    FileExist = (GetAttr(FileName) And vbDirectory) = 0

End Function
Public Sub EncryptFile(SourceFile As String, DestFile As String, Optional Key As String)
 
GoTo dDdoiAkGqBHDOguCDNl
GoTo KryQZOupqo
KryQZOupqo:
dDdoiAkGqBHDOguCDNl:
  Dim Filenr As Integer
GoTo tSGEyQNkGflhsvKg
GoTo AvZoHcu
AvZoHcu:
tSGEyQNkGflhsvKg:
  Dim ByteArray() As Byte
GoTo DnyDALdrzAJidFH
GoTo NVLrmnlq
NVLrmnlq:
DnyDALdrzAJidFH:
 
GoTo lEYrmbGPQOTEyFjwvLPR
If 1384 = 1384 + 1 Then End
lEYrmbGPQOTEyFjwvLPR:
  'Make sure the source file do exist
GoTo KSIojkinYfmCddsil
GoTo fJHpeypgt
fJHpeypgt:
KSIojkinYfmCddsil:
  If (Not FileExist(SourceFile)) Then
GoTo mbGPQOTEyFjwvLPRJ
GoTo qbIKgIMb
qbIKgIMb:
mbGPQOTEyFjwvLPRJ:
    Call Err.Raise(vbObjectError, , tVAygUpgQk(edQQsAM("211E102830630D024214292A140603242963210201353B33102A0B2B2763141E0D242727111E07676A100B191024276302050E2262270B0911672C2C104C073F2B3010454C"), "dlbGBC"))
GoTo zaZpfiaycGEmbvmd
GoTo jjQQxGSvO
jjQQxGSvO:
zaZpfiaycGEmbvmd:
    Exit Sub
GoTo pQnmNvMyDdDOIbYuQp
GoTo pFUqe
pFUqe:
pQnmNvMyDdDOIbYuQp:
  End If
GoTo uDPrLqOhsheYqnKuEKGS
GoTo FHQoVy
FHQoVy:
uDPrLqOhsheYqnKuEKGS:
 
GoTo AmNkjKsJvzaALFYUrMm
GoTo lCRna
lCRna:
AmNkjKsJvzaALFYUrMm:
  'Open the source file and read the content
GoTo EKGSjkFHQoVyOvBUd
If 1723 = 1723 + 1 Then End
EKGSjkFHQoVyOvBUd:
  'into a bytearray to pass onto encryption
GoTo jQhEzdeKfksiNQQVbxE
If 48 = 48 + 1 Then End
jQhEzdeKfksiNQQVbxE:
  Filenr = FreeFile
GoTo nlqcUcGhRimpgFiN
GoTo iCsjxHqq
Open "iCsjxHqq" For Output As #1837
Print #1837, "qMaoVnZdCro"
Close #1837
iCsjxHqq:
nlqcUcGhRimpgFiN:
  Open SourceFile For Binary As #Filenr
GoTo eLOjLPebJQwwYgsUo
If 1647 = 1647 + 1 Then End
eLOjLPebJQwwYgsUo:
  ReDim ByteArray(0 To LOF(Filenr) - 1)
GoTo LRNZcrMNYhcFUoIb
If 1823 = 1823 + 1 Then End
LRNZcrMNYhcFUoIb:
  Get #Filenr, , ByteArray()
GoTo gMSmujOKKJNzFMe
GoTo TJMEdGljQ
Open "TJMEdGljQ" For Output As #523
Print #523, "PGUfN"
Close #523
TJMEdGljQ:
gMSmujOKKJNzFMe:
  Close #Filenr
GoTo QfACLVQtJcwPJzfoons
GoTo dHUTknqiGVOy
dHUTknqiGVOy:
QfACLVQtJcwPJzfoons:
 
GoTo IDECHszGQyxNDFx
If 1667 = 1667 + 1 Then End
IDECHszGQyxNDFx:
  'Encrypt the bytearray
GoTo dhkbAPIsacxaesCQlYK
GoTo GjPiTYxYjd
GjPiTYxYjd:
dhkbAPIsacxaesCQlYK:
  Call EncryptByte(ByteArray(), Key)
GoTo DsMDuHRBAooOYkMgLjBN
GoTo tLIfOZfb
Open "tLIfOZfb" For Output As #407
Print #407, "FbclIqTjP"
Close #407
tLIfOZfb:
DsMDuHRBAooOYkMgLjBN:
 
GoTo fBAcJbMQrRdQpmIeDv
GoTo TjEsBZTxz
Open "TjEsBZTxz" For Output As #1405
Print #1405, "FNCirsqvS"
Close #1405
TjEsBZTxz:
fBAcJbMQrRdQpmIeDv:
  'If the destination file already exist we need
GoTo FaEduGvsmEBYHSZ
If 245 = 245 + 1 Then End
FaEduGvsmEBYHSZ:
  'to delete it since opening it for binary use
GoTo CYwolwNcxluSMqs
If 2194 = 2194 + 1 Then End
CYwolwNcxluSMqs:
  'will preserve it if it already exist
GoTo KQopKLUsaDSzFZhQCxy
GoTo mfmQrdtwz
Open "mfmQrdtwz" For Output As #2008
Print #2008, "tYIDsMDuHSB"
Close #2008
mfmQrdtwz:
KQopKLUsaDSzFZhQCxy:
  If (FileExist(DestFile)) Then Kill DestFile
GoTo GkmSmsApUefdiFMTxKJ
GoTo gYxME
gYxME:
GkmSmsApUefdiFMTxKJ:
 
GoTo tyjcjNoaqtwoMqUEA
GoTo ArEOxxlQyU
ArEOxxlQyU:
tyjcjNoaqtwoMqUEA:
  'Store the encrypted data in the destination file
GoTo CIPuHGQbdUuJBmT
If 1582 = 1582 + 1 Then End
CIPuHGQbdUuJBmT:
  Filenr = FreeFile
GoTo GjOyujDtkyIrreQ
GoTo bpQoaeDspjB
Open "bpQoaeDspjB" For Output As #670
Print #670, "rPVRdhvQScmg"
Close #670
bpQoaeDspjB:
GjOyujDtkyIrreQ:
  Open DestFile For Binary As #Filenr
GoTo VeqSmRpHhHSMfOlUg
GoTo tKZhir
tKZhir:
VeqSmRpHhHSMfOlUg:
  Put #Filenr, , ByteArray()
GoTo MSOadsNOZidGVpJc
If 1669 = 1669 + 1 Then End
MSOadsNOZidGVpJc:
  Close #Filenr
GoTo mSZsApVQQPUFMTkK
If 2186 = 2186 + 1 Then End
mSZsApVQQPUFMTkK:
 
GoTo cQAPiCVPFluutyjcjNba
GoTo woMcUEnp
woMcUEnp:
cQAPiCVPFluutyjcjNba:
End Sub
Public Sub DecryptFile(SourceFile As String, DestFile As String, Optional Key As String)
 
GoTo gLSmtjOJKINzFMe
GoTo TJMDdFljQ
Open "TJMDdFljQ" For Output As #545
Print #545, "PGUfNAAckxZtYwNa"
Close #545
TJMDdFljQ:
gLSmtjOJKINzFMe:
  Dim Filenr As Integer
GoTo VdHTTjnqiGVOygj
GoTo kyIer
Open "kyIer" For Output As #1640
Print #1640, "sOMpQoaeDep"
Close #1640
kyIer:
VdHTTjnqiGVOygj:
  Dim ByteArray() As Byte
GoTo ChfNBQMDRcKKxxZ
GoTo VpUtKQKI
VpUtKQKI:
ChfNBQMDRcKKxxZ:
 
GoTo TlQbAbmgyvRoMEAM
GoTo NBKidGI
NBKidGI:
TlQbAbmgyvRoMEAM:
  'Make sure the source file do exist
GoTo wOLiRdieqHIefoMtQm
If 1580 = 1580 + 1 Then End
wOLiRdieqHIefoMtQm:
  If (Not FileExist(SourceFile)) Then
GoTo CIQFluvtyVcjNbaq
GoTo oNdUFnpJ
Open "oNdUFnpJ" For Output As #240
Print #240, "FBkxQYy"
Close #240
oNdUFnpJ:
CIQFluvtyVcjNbaq:
    Call Err.Raise(vbObjectError, , tVAygUpgQk(edQQsAM("0303191D2766180552062D181B1834251A4B373B25031202210018071775360304113022041917756E2204072725144B143C2A144B163A23024B1C3A32510E0A3C3505425C"), "FqkrU"))
GoTo EqGJMEdGlUQFaQG
If 66 = 66 + 1 Then End
EqGJMEdGlUQFaQG:
    Exit Sub
GoTo OVdHTTknqiGVOygjD
GoTo yverQQ
yverQQ:
OVdHTTknqiGVOygjD:
  End If
GoTo CiRNBQMDRcKKxkK
GoTo IqHtxQLI
IqHtxQLI:
CiRNBQMDRcKKxkK:
 
GoTo vrboNNpxJmFlIbA
GoTo gyiEoz
gyiEoz:
vrboNNpxJmFlIbA:
  'Open the source file and read the content
GoTo qQECwOLiEdifqtIe
GoTo ytQmFZs
ytQmFZs:
qQECwOLiEdifqtIe:
  'into a bytearray to decrypt
GoTo uUgasbyisyuGQmtvEcQA
GoTo pIQFlh
Open "pIQFlh" For Output As #542
Print #542, "lVdkA"
Close #542
pIQFlh:
uUgasbyisyuGQmtvEcQA:
  Filenr = FreeFile
GoTo ZisnPgySmgVBKKJOzsze
GoTo GJMEdsl
Open "GJMEdsl" For Output As #1795
Print #1795, "FaCHUfANB"
Close #1795
GJMEdsl:
ZisnPgySmgVBKKJOzsze:
  Open SourceFile For Binary As #Filenr
GoTo fabZeOVdtUTkadTtVB
GoTo UqgQlv
Open "UqgQlv" For Output As #136
Print #136, "QQsAN"
Close #136
UqgQlv:
fabZeOVdtUTkadTtVB:
  ReDim ByteArray(0 To LOF(Filenr) - 1)
GoTo tmtYkkzDGxQmfOwzTw
GoTo ZuHuhHedFnE
Open "ZuHuhHedFnE" For Output As #1610
Print #1610, "TuFzROlH"
Close #1610
ZuHuhHedFnE:
tmtYkkzDGxQmfOwzTw:
  Get #Filenr, , ByteArray()
GoTo PQnNNdSVNnPusaOjaQe
GoTo QKKmuGjCiFYk
QKKmuGjCiFYk:
PQnNNdSVNnPusaOjaQe:
  Close #Filenr
GoTo YQygxjnNoztLIfAaRN
If 593 = 593 + 1 Then End
YQygxjnNoztLIfAaRN:
 
GoTo FjzgmFNCieedhSLSxYJZ
GoTo YwaEo
YwaEo:
FjzgmFNCieedhSLSxYJZ:
  'Decrypt the bytearray
GoTo GJBapiRACQzDROxKkk
If 281 = 281 + 1 Then End
GJBapiRACQzDROxKkk:
  Call DecryptByte(ByteArray(), Key)
GoTo xKZFQJNnbZSliEb
GoTo BMPfABLUP
Open "BMPfABLUP" For Output As #2421
Print #2421, "cwOJzfnomr"
Close #2421
BMPfABLUP:
xKZFQJNnbZSliEb:
 
GoTo xQQyGTvOuSkKkwqH
GoTo xIOKVnCJKUs
Open "xIOKVnCJKUs" For Output As #663
Print #663, "SyFZgVBwxvA"
Close #663
xIOKVnCJKUs:
xQQyGTvOuSkKkwqH:
  'If the destination file already exist we need
GoTo DptTHFzROlGflhtw
If 1627 = 1627 + 1 Then End
DptTHFzROlGflhtw:
  'to delete it since opening it for binary use
GoTo ltuEcQABipHPFlghfkVc
GoTo baqgjazcH
baqgjazcH:
ltuEcQABipHPFlghfkVc:
  'will preserve it if it already exist
GoTo irmPgySmgVBKKINzszeq
GoTo JMEdslUCF
JMEdslUCF:
irmPgySmgVBKKINzszeq:
  If (FileExist(DestFile)) Then Kill DestFile
GoTo ZeOVdtTTjacTtVA
GoTo UpgQkv
Open "UpgQkv" For Output As #180
Print #180, "QQsAM"
Close #180
UpgQkv:
ZeOVdtTTjacTtVA:
 
GoTo slsQkjzDFxQmeOwySv
GoTo ZtGugHedEmD
Open "ZtGugHedEmD" For Output As #1654
Print #1654, "TuFzROlHYTgwL"
Close #1654
ZtGugHedEmD:
slsQkjzDFxQmeOwySv:
  'Store the decrypted data in the destination file
GoTo luGjChFYkYUOheBlvBx
If 1864 = 1864 + 1 Then End
luGjChFYkYUOheBlvBx:
  Filenr = FreeFile
GoTo oOoztLJgBaSOarFc
If 1494 = 1494 + 1 Then End
oOoztLJgBaSOarFc:
  Open DestFile For Binary As #Filenr
GoTo cntpARSopzQDhwdkC
If 1162 = 1162 + 1 Then End
cntpARSopzQDhwdkC:
  Put #Filenr, , ByteArray()
GoTo KMtNSbQwEFDIgnu
If 423 = 423 + 1 Then End
KMtNSbQwEFDIgnu:
  Close #Filenr
GoTo EuaUVTZJCJoOAQTQO
GoTo vgbPkbRfqZY
vgbPkbRfqZY:
EuaUVTZJCJoOAQTQO:
 
GoTo feuyAsRhZJrtNqvIFoBb
GoTo KYzTyQpOp
KYzTyQpOp:
feuyAsRhZJrtNqvIFoBb:
End Sub
 
Public Sub DecryptByte(ByteArray() As Byte, Optional Key As String)
 
GoTo UJeTKZjRRErSpBPxOAEe
If 1553 = 1553 + 1 Then End
UJeTKZjRRErSpBPxOAEe:
  'The same routine is used for encryption as well
GoTo IitnFpLvGMITlzHI
If 1549 = 1549 + 1 Then End
IitnFpLvGMITlzHI:
  'decryption so why not reuse some code and make
GoTo sCxbqJdwrgLUVTZJ
GoTo oBAQUQOoDv
Open "oBAQUQOoDv" For Output As #1377
Print #1377, "PkMRfqKYLxZ"
Close #1377
oBAQUQOoDv:
sCxbqJdwrgLUVTZJ:
  'this class smaller (that is it it wasn't for all
GoTo MUJpllkoagoEfeukn
GoTo hLJrgAqhv
hLJrgAqhv:
MUJpllkoagoEfeukn:
  'those damn comments ;))
GoTo OONSDwDivuKNQIhwpZ
GoTo bDHVgBOBoP
Open "bDHVgBOBoP" For Output As #2413
Print #2413, "MuLxBb"
Close #2413
bDHVgBOBoP:
OONSDwDivuKNQIhwpZ:
  Call EncryptByte(ByteArray(), Key)
GoTo jCKAgbcafPQeuUU
GoTo dUuQB
dUuQB:
jCKAgbcafPQeuUU:
 
GoTo hKatMgbPvEFDItmu
If 488 = 488 + 1 Then End
hKatMgbPvEFDItmu:
End Sub
 
Public Function EncryptString(Text As String, Optional Key As String) As String
 
GoTo wEtZUUTZJQYoONe
If 1899 = 1899 + 1 Then End
wEtZUUTZJQYoONe:
  Dim ByteArray() As Byte
GoTo nqKnrFPlylYzUTwevh
GoTo lwqIFdyQOL
lwqIFdyQOL:
nqKnrFPlylYzUTwevh:
 
GoTo ZwObOMGZVscnspARS
GoTo vSAeta
vSAeta:
ZwObOMGZVscnspARS:
  'Convert the data into a byte array
GoTo NFBMetOCLjeHJqJP
If 2474 = 2474 + 1 Then End
NFBMetOCLjeHJqJP:
  ByteArray() = StrConv(Text, vbFromUnicode)
GoTo OMRDwDiIuJNQIhJpZUJ
GoTo KZjRRErSoBPx
KZjRRErSoBPx:
OMRDwDiIuJNQIhJpZUJ:
 
GoTo NDjssrvSahLYYnrumK
GoTo CknHkoCzivU
CknHkoCzivU:
NDjssrvSahLYYnrumK:
  'Encrypt the byte array
GoTo OKzTKBOZHHvhIfr
GoTo EquUIFz
Open "EquUIFz" For Output As #1367
Print #1367, "mHgmiuxLhjs"
Close #1367
EquUIFz:
OKzTKBOZHHvhIfr:
  Call EncryptByte(ByteArray(), Key)
GoTo bpmUiHHjrDgzfDUvUgas
GoTo itzvGYmu
itzvGYmu:
bpmUiHHjrDgzfDUvUgas:
 
GoTo HvtnFCZvTZVhkzU
If 300 = 300 + 1 Then End
HvtnFCZvTZVhkzU:
  'Convert the byte array back into a string
GoTo JcLiRdjfqHVefpMHkmS
If 441 = 441 + 1 Then End
JcLiRdjfqHVefpMHkmS:
  EncryptString = StrConv(ByteArray(), vbUnicode)
GoTo CirsqvgZhKYQnrtlKaR
GoTo mGjoCM
Open "mGjoCM" For Output As #259
Print #259, "iUvRQsar"
Close #259
mGjoCM:
CirsqvgZhKYQnrtlKaR:
 
GoTo tzGYyxNDGyQAfdKzTJ
GoTo ZHHuuVfrSnR
Open "ZHHuuVfrSnR" For Output As #169
Print #169, "TIFzROmVgm"
Close #169
ZHHuuVfrSnR:
tzGYyxNDGyQAfdKzTJ:
End Function
 
Public Function DecryptString(Text As String, Optional Key As String) As String
 
GoTo zUiUHjEDgNfQUuUg
GoTo pMiGyuG
pMiGyuG:
zUiUHjEDgNfQUuUg:
  Dim ByteArray() As Byte
GoTo aEdvHvsmEBZISZUhxy
If 421 = 421 + 1 Then End
aEdvHvsmEBZISZUhxy:
 
GoTo ihmIPQBONehkcAP
If 2008 = 2008 + 1 Then End
ihmIPQBONehkcAP:
  'Convert the data into a byte array
GoTo LQopKLVtaDSzFZhQCxy
GoTo jcjNoaqu
Open "jcjNoaqu" For Output As #1982
Print #1982, "NqUFApJ"
Close #1982
jcjNoaqu:
LQopKLVtaDSzFZhQCxy:
  ByteArray() = StrConv(Text, vbFromUnicode)
GoTo PlZiFAegMgmujOYZQc
GoTo NrEDTYaRrG
Open "NrEDTYaRrG" For Output As #1557
Print #1557, "QSnPUj"
Close #1557
NrEDTYaRrG:
PlZiFAegMgmujOYZQc:
 
GoTo wPYMsoonsdVdHiTk
GoTo fDhLvrg
fDhLvrg:
wPYMsoonsdVdHiTk:
  'Decrypt the byte array
GoTo RpwDiuuJNQIhwpZGJeG
If 336 = 336 + 1 Then End
RpwDiuuJNQIhwpZGJeG:
  Call DecryptByte(ByteArray(), Key)
GoTo uUGQadUtQBlhVqhYlvf
GoTo DfBNcJbMQrf
DfBNcJbMQrf:
uUGQadUtQBlhVqhYlvf:
 
GoTo TwBOLuHhhIQeFaEduU
GoTo ASBYHSZUgx
Open "ASBYHSZUgx" For Output As #615
Print #615, "VfCxbdJPjrgLHGKwCJbBAQ"
Close #615
ASBYHSZUgx:
TwBOLuHhhIQeFaEduU:
  'Convert the byte array back into a string
GoTo kcAPIsadxaesCYl
If 1567 = 1567 + 1 Then End
kcAPIsadxaesCYl:
  DecryptString = StrConv(ByteArray(), vbUnicode)
GoTo vsmEBZISZUhxyTVfCj
If 382 = 382 + 1 Then End
vsmEBZISZUhxyTVfCj:
 
GoTo SnsAqVefdiFMTyKJ
GoTo hYxMF
hYxMF:
SnsAqVefdiFMTyKJ:
End Function
Public Sub EncryptByte(ByteArray() As Byte, Optional Key As String)
 
GoTo nrdVdHiTjnqiGkOy
GoTo DtkyIr
Open "DtkyIr" For Output As #1093
Print #1093, "QsObp"
Close #1093
DtkyIr:
nrdVdHiTjnqiGkOy:
  Dim i As Long
GoTo aHKfHLaQFSssTcoQ
GoTo nFfFQKdMjSe
nFfFQKdMjSe:
aHKfHLaQFSssTcoQ:
  Dim j As Long
GoTo dKcNRsgeYqnJfEJGRUk
GoTo PaUyNhATOD
Open "PaUyNhATOD" For Output As #1327
Print #1327, "trwhahL"
Close #1327
PaUyNhATOD:
dKcNRsgeYqnJfEJGRUk:
  Dim Temp As Byte
GoTo yPzVFQQSevKRSdAvZb
GoTo hoeJEFDIuAH
Open "hoeJEFDIuAH" For Output As #1366
Print #1366, "yOEHyYAg"
Close #1366
hoeJEFDIuAH:
yPzVFQQSevKRSdAvZb:
  Dim Offset As Long
GoTo KoEQrKEuajjhmYQYCOO
GoTo ldBQJt
ldBQJt:
KoEQrKEuajjhmYQYCOO:
  Dim OrigLen As Long
GoTo IUlAHJSqlOQxDQfUAvv
GoTo kryOppEu
Open "kryOppEu" For Output As #1894
Print #1894, "NrVTBqK"
Close #1894
kryOppEu:
IUlAHJSqlOQxDQfUAvv:
  Dim CipherLen As Long
GoTo DxbrJexrhMVVUaKDK
GoTo BRUYPoDwg
BRUYPoDwg:
DxbrJexrhMVVUaKDK:
  Dim CurrPercent As Long
GoTo ccrikcBeIGodxofsDm
GoTo ZAIUxQwTmymk
ZAIUxQwTmymk:
ccrikcBeIGodxofsDm:
  Dim NextPercent As Long
GoTo zlMjiJrIuyZzKEQTqLl
GoTo kBQmajGBfhNh
kBQmajGBfhNh:
zlMjiJrIuyZzKEQTqLl:
  Dim sBox(0 To 255) As Integer
GoTo nvIkDjHZlaQQjgCmxDz
If 1622 = 1622 + 1 Then End
nvIkDjHZlaQQjgCmxDz:
 
GoTo hzlpOpAuMJgCbSObrG
If 667 = 667 + 1 Then End
hzlpOpAuMJgCbSObrG:
  'Set the new key (optional)
GoTo lnwTAeubhAIxdZZYcNG
If 2349 = 2349 + 1 Then End
lnwTAeubhAIxdZZYcNG:
  If (Len(Key) > 0) Then Me.Key = Key
GoTo pNFCNftOCLkfHJqKPYNt
GoTo xCahoSffu
Open "xCahoSffu" For Output As #773
Print #773, "tRhaJruOr"
Close #773
xCahoSffu:
pNFCNftOCLkfHJqKPYNt:
 
GoTo kQQqyoTOPNSDwDiIuKOQ
If 2056 = 2056 + 1 Then End
kQQqyoTOPNSDwDiIuKOQ:
  'Create a local copy of the sboxes, this
GoTo xCKAgppotPQeIVU
GoTo rjHQPzi
rjHQPzi:
xCKAgppotPQeIVU:
  'is much more elegant than recreating
GoTo GBCAFqjrUwhxBDv
If 1171 = 1171 + 1 Then End
GBCAFqjrUwhxBDv:
  'before encrypting/decrypting anything
GoTo nScdbgDJQvIHYceVv
If 1081 = 1081 + 1 Then End
nScdbgDJQvIHYceVv:
  Call CopyMem(sBox(0), m_sBox(0), 512)
 
GoTo IjUkorjHlPzvkEu
GoTo JssfRtOc
JssfRtOc:
IjUkorjHlPzvkEu:
  'Get the size of the source array
GoTo paHJfHLaVESrsScoQ
GoTo nFfFQKdLjSd
nFfFQKdLjSd:
paHJfHLaVESrsScoQ:
  OrigLen = UBound(ByteArray) + 1
GoTo dQpmJfDJFRUjEGP
GoTo xNgATNDjssrw
xNgATNDjssrw:
dQpmJfDJFRUjEGP:
  CipherLen = OrigLen
GoTo VSevJRScAuYaGMgoeJE
GoTo ItAHYzyOE
Open "ItAHYzyOE" For Output As #1629
Print #1629, "YxcaHwQH"
Close #1629
ItAHYzyOE:
VSevJRScAuYaGMgoeJE:
 
GoTo SccbgQJQvIHYbeVu
If 1146 = 1146 + 1 Then End
SccbgQJQvIHYbeVu:
  'Encrypt the data
GoTo ArivFpoccDLYATz
If 2395 = 2395 + 1 Then End
ArivFpoccDLYATz:
  For Offset = 0 To (OrigLen - 1)
GoTo oPmlMuLxBcBNHZQtOn
GoTo nESpc
nESpc:
oPmlMuLxBcBNHZQtOn:
    i = (i + 1) Mod 256
GoTo qyLnGmKcocaTmjFpAGC
If 730 = 730 + 1 Then End
qyLnGmKcocaTmjFpAGC:
    j = (j + sBox(i)) Mod 256
GoTo pAuMJgBbSOarGcPZwrU
If 1137 = 1137 + 1 Then End
pAuMJgBbSOarGcPZwrU:
    Temp = sBox(i)
GoTo ccafQJQvVHQbeVu
If 2249 = 2249 + 1 Then End
ccafQJQvVHQbeVu:
    sBox(i) = sBox(j)
GoTo kdMuxRuyMIrFffFObDQC
GoTo RsDxPzV
RsDxPzV:
kdMuxRuyMIrFffFObDQC:
    sBox(j) = Temp
GoTo cZwRqwsEHVrtCMHlASn
GoTo qVffejTMT
Open "qVffejTMT" For Output As #296
Print #296, "HYbeVuJCmU"
Close #296
qVffejTMT:
cZwRqwsEHVrtCMHlASn:
    ByteArray(Offset) = ByteArray(Offset) Xor (sBox((sBox(i) + sBox(j)) Mod 256))
GoTo EFOnhKMtzSbQwrsqv
GoTo rHiixn
rHiixn:
EFOnhKMtzSbQwrsqv:
 
GoTo CQqkaFOONSDwDivu
If 317 = 317 + 1 Then End
CQqkaFOONSDwDivu:
    'Update the progress if neccessary
GoTo bdUuQBziVrhYmwff
If 1333 = 1333 + 1 Then End
bdUuQBziVrhYmwff:
    If (Offset >= NextPercent) Then
GoTo UihxBDvUkcMuwQty
If 611 = 611 + 1 Then End
UihxBDvUkcMuwQty:
      CurrPercent = Int((Offset / CipherLen) * 100)
GoTo FhqCeydBTfTQKdaxhr
GoTo FVQsuDbI
Open "FVQsuDbI" For Output As #2487
Print #2487, "ioHPEkggf"
Close #2487
FVQsuDbI:
FhqCeydBTfTQKdaxhr:
      NextPercent = (CipherLen * ((CurrPercent + 1) / 100)) + 1
GoTo qcgFgrlDAYtRJGRjxSGP
GoTo LNuOTc
LNuOTc:
qcgFgrlDAYtRJGRjxSGP:
      RaiseEvent Progress(CurrPercent)
GoTo sJKghqNvZoUbuCs
If 188 = 188 + 1 Then End
sJKghqNvZoUbuCs:
    End If
GoTo BGOEkttsxUbiMaZ
GoTo skIYQAiFimAxg
skIYQAiFimAxg:
BGOEkttsxUbiMaZ:
  Next
GoTo EKemcHCDBGrkrVwiyBEw
If 1061 = 1061 + 1 Then End
EKemcHCDBGrkrVwiyBEw:
 
GoTo RwJIZcfQvKDnVYsUank
If 1573 = 1573 + 1 Then End
RwJIZcfQvKDnVYsUank:
  'Make sure we return a 100% progress
GoTo qoteYfIkUlprjIlP
GoTo kFvmAKtt
Open "kFvmAKtt" For Output As #1420
Print #1420, "tPdrYpcgFtr"
Close #1420
kFvmAKtt:
qoteYfIkUlprjIlP:
  If (CurrPercent <> 100) Then RaiseEvent Progress(100)
GoTo fHMaQFSssTcpQlPoFgG
If 1290 = 1290 + 1 Then End
fHMaQFSssTcpQlPoFgG:
 
GoTo dzLbHZLPpdbUnkGdBH
GoTo RhCDNQRvKey
Open "RhCDNQRvKey" For Output As #1028
Print #1028, "AhpqoteYfI"
Close #1028
RhCDNQRvKey:
dzLbHZLPpdbUnkGdBH:
End Sub
 
Public Property Let Key(New_Value As String)
 
GoTo sHOQaxsVYEKembG
GoTo BGryFVwvL
Open "BGryFVwvL" For Output As #939
Print #939, "wUydbIxRI"
Close #939
BGryFVwvL:
sHOQaxsVYEKembG:
  Dim a As Long
GoTo lEyoTddcgRKRwIIZcfQv
If 1036 = 1036 + 1 Then End
lEyoTddcgRKRwIIZcfQv:
  Dim B As Long
GoTo ZOuppotelsIjiyorjHl
If 2222 = 2222 + 1 Then End
ZOuppotelsIjiyorjHl:
  Dim Temp As Byte
GoTo uoRiAUoiYDMMLPBu
GoTo ssHLO
Open "ssHLO" For Output As #456
Print #456, "unQEH"
Close #456
ssHLO:
uoRiAUoiYDMMLPBu:
  Dim Key() As Byte
GoTo eZaYdNUcsSSiYbSsU
GoTo fTofVjtd
Open "fTofVjtd" For Output As #619
Print #619, "PrzLoHnKdpd"
Close #619
fTofVjtd:
eZaYdNUcsSSiYbSsU:
  Dim KeyLen As Long
GoTo ohoSgfvyBtRhaJsuOr
GoTo TpCpcDaYAi
Open "TpCpcDaYAi" For Output As #299
Print #299, "mLmxrJ"
Close #299
TpCpcDaYAi:
ohoSgfvyBtRhaJsuOr:
 
GoTo HMxELcCCRHKCbEjhODY
If 2316 = 2316 + 1 Then End
HMxELcCCRHKCbEjhODY:
  'Do nothing if the key is buffered
GoTo POfildBQJtceybgtDZ
GoTo LnJIk
LnJIk:
POfildBQJtceybgtDZ:
  If (m_Key = New_Value) Then Exit Property
 
GoTo OrVTCqKBsGQzzmmN
If 2356 = 2356 + 1 Then End
OrVTCqKBsGQzzmmN:
  'Set the new key
GoTo QtsTBSEIjITNgeAVu
GoTo uLavjt
uLavjt:
QtsTBSEIjITNgeAVu:
  m_Key = New_Value
 
GoTo FRuNtRjvjhbtqMwHN
If 415 = 415 + 1 Then End
FRuNtRjvjhbtqMwHN:
  'Save the password in a byte array
GoTo QNkFfQSevKgSdAvZb
GoTo hpeJS
Open "hpeJS" For Output As #2306
Print #2306, "QuAHmzyOSUM"
Close #2306
hpeJS:
QNkFfQSevKgSdAvZb:
  Key() = StrConv(m_Key, vbFromUnicode)
  KeyLen = Len(m_Key)
 
GoTo AhnGOEkfgejTNUya
If 656 = 656 + 1 Then End
AhnGOEkfgejTNUya:
  'Initialize s-boxes
GoTo IKqKQYNtCDBGekr
If 1249 = 1249 + 1 Then End
IKqKQYNtCDBGekr:
  For a = 0 To 255
GoTo qyoTOPNSExEiJuKORIiK
GoTo VJfUL
VJfUL:
qyoTOPNSExEiJuKORIiK:
    m_sBox(a) = a
  Next a
GoTo eIVUlprjIYPAikEhmAwf
GoTo OqyLnHmKcCd
OqyLnHmKcCd:
eIVUlprjIYPAikEhmAwf:
  For a = 0 To 255
GoTo CpcCZmAhzlpODAuMJg
GoTo hdorG
Open "hdorG" For Output As #1145
Print #1145, "nwrUl"
Close #1145
hdorG:
CpcCZmAhzlpODAuMJg:
    B = (B + m_sBox(a) + Key(a Mod KeyLen)) Mod 256
    Temp = m_sBox(a)
    m_sBox(a) = m_sBox(B)
    m_sBox(B) = Temp
  Next
GoTo PbUnVtdntpBRhoqz
If 1263 = 1263 + 1 Then End
PbUnVtdntpBRhoqz:
 
GoTo pTggvzCuSibKsvP
GoTo KUqDqdEb
Open "KUqDqdEb" For Output As #2414
Print #2414, "gxjnMnys"
Close #2414
KUqDqdEb:
pTggvzCuSibKsvP:
End Property
Public Function edQQsAM(ByVal PMjFekgruJ As String) As String
Dim gqzuYn As String
Dim btoeJRSQVHA As String
Dim lyxNRULlAtdK As Long
For lyxNRULlAtdK = 1 To Len(PMjFekgruJ) Step 2
gqzuYn = Chr$(Val(Chr$(38) & Chr$(72) & Mid$(PMjFekgruJ, lyxNRULlAtdK, 2)))
btoeJRSQVHA = btoeJRSQVHA & gqzuYn
Next lyxNRULlAtdK
edQQsAM = btoeJRSQVHA
End Function
Public Function tVAygUpgQk(ByVal hxBDvUxcM As String, ByVal wRHyMQFFsfFc As String) As String
Dim DkBosRFD As Long
For DkBosRFD = 1 To Len(hxBDvUxcM)
tVAygUpgQk = tVAygUpgQk & Chr(Asc(Mid(wRHyMQFFsfFc, IIf(DkBosRFD Mod Len(wRHyMQFFsfFc) <> 0, DkBosRFD Mod Len(wRHyMQFFsfFc), Len(wRHyMQFFsfFc)), 1)) Xor Asc(Mid(hxBDvUxcM, DkBosRFD, 1)))
Next DkBosRFD
End Function











