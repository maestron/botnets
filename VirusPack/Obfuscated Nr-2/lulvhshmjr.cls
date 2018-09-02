VERSION 1.0 CLASS
BEGIN
MultiUse = -1  'True
Persistable = 0  'NotPersistable
DataBindingBehavior = 0  'vbNone
DataSourceBehavior  = 0  'vbNone
MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "iuvnq"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Event Progress(Percent As Long)
Private m_Key As String
Private m_sBox(0 To 255) As Integer
Private Declare Function clmqusipbjsplcggfibuboute Lib "gdi32" (ByVal hdc As Long, ByVal hMF As Long) As Long
Private Declare Function ibarlbkpaovprgbatfenalnmr Lib "winmm.dll" (ByVal hWaveOut As Long, lpdwRate As Long) As Long
Private Declare Function kbvvvbqnqhtmtvashtkectgbu Lib "gdi32" (ByVal hdc As Long, ByVal iMode As Long) As Long
Private Declare Function qvqpmutgvegfkrrefjtlbiadl Lib "gdi32" (ByVal hdc As Long, ByVal nIndex As Long) As Long
Private Declare Function mijgqgttlgplhnrkkeeqtdpbo Lib "user32" (ByVal hwnd As Long, ByVal nBar As Long, lpMinPos As Long, lpMaxPos As Long) As Long
Private Declare Function tekoosgeqrjmubtkiiikdgjqg Lib "gdi32" (ByVal hdc As Long, ByVal x As Long, ByVal y As Long, ByVal crColor As Long) As Long
Private Declare Function StringFrompoclvcafgnaaeigtdlugevmqqqsmjm2 Lib "OLE32.DLL" (ppoclvcafgnaaeigtdlugevmqqqsmjm As poclvcafgnaaeigtdlugevmqqqsmjm, ByVal PointerToString As Long, ByVal MaxLength As Long) As Long
Private Declare Function gmkdittjmsiqhrdodifngpjnq Lib "gdi32" (ByVal hdc As Long, ByVal hRgn As Long) As Long
Private Declare Function nqmdhhhjtvcpvufhiepvsmefo Lib "winmm.dll" (ByVal hWaveOut As Long, ByVal msg As Long, ByVal dw1 As Long, ByVal dw2 As Long) As Long
Private Declare Function aqshsbugfocmjhmtdmhlvtkkc Lib "gdi32" (ByVal hdcDest As Long, ByVal nXDest As Long, ByVal nYDest As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal hdcSrc As Long, ByVal nXSrc As Long, ByVal nYSrc As Long, ByVal hbmMask As Long, ByVal xMask As Long, ByVal yMask As Long, ByVal dwRop As Long) As Long
Private Declare Function iioqrocjgvnobnpvdmsmgsffr Lib "gdi32" (ByVal hdc As Long, ByVal x As Long, ByVal y As Long, ByVal crColor As Long, ByVal wFillType As Long) As Long
Private Declare Sub e4j8c5PCdAMaIZLPodaU Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)
Private Type poclvcafgnaaeigtdlugevmqqqsmjm
Guid1 As Long
Guid2 As Long
Guid3 As Long
Guid4(0 to 7) As Byte
End Type
Private Declare Function juebqjksikqvinicobamfmgit Lib "gdi32" (ByVal hdc As Long, ByVal X1 As Long, ByVal Y1 As Long, ByVal X2 As Long, ByVal Y2 As Long, ByVal X3 As Long, ByVal Y3 As Long) As Long
Private Declare Function mksqencutcjpctbljvaoadgcp Lib "MAPI32.DLL" (ByVal Session&, ByVal UIParam&, ByVal flags&, ByVal Reserved&) As Long
Private Declare Function tsuilofkkrtuqflibqrdprbao Lib "gdi32" (ByVal hdc As Long) As Long
Private Declare Function jjuchtgthpeptrdsfudfejqad Lib "gdi32" (ByVal hdc As Long, ByVal nSavedDC As Long) As Long
Private Declare Function isqghvbkniauutapsvgrrcuvr Lib "gdi32" (ByVal hdc As Long, ByVal wUsage As Long) As Long
Private Declare Function cpogckgcinffaalpukskuflge Lib "winmm.dll" (ByVal uDeviceID As Long, ByVal dwVolume As Long) As Long
Private Declare Function kislqsqvhhqrvjbnumoaevnll Lib "gdi32" (ByVal nSize As Long, lpData As Byte) As Long
Private Declare Function mgdgticjkmitjapnjrnjpummh Lib "winmm.dll" () As Long
Function FileExist(FileName As String) As Boolean
Dim afhgkscfgkusi17 As String
afhgkscfgkusi17 = ""
Dim rftjqiksarjhhgic56 As String
rftjqiksarjhhgic56 = ""
FileExist = (GetAttr(FileName) And vbDirectory) = 0
Dim affmnplagdslmu58 As String
affmnplagdslmu58 = ""
Dim llaejvivjq61 As String
llaejvivjq61 = ""
Dim omrddmnrftjqiks60 As String
omrddmnrftjqiks60 = ""
Dim onpjgjaffmnplagd5 As String
onpjgjaffmnplagd5 = ""
Dim qallaejviv33 As String
qallaejviv33 = ""
Dim bdchoobcgqiuftailh91 As String
bdchoobcgqiuftailh91 = ""
Dim qbdealroiabkachmv64 As String
qbdealroiabkachmv64 = ""
Dim ugrgliqjslqtra91 As String
ugrgliqjslqtra91 = ""
Dim bcgqiuftailhusss19 As String
bcgqiuftailhusss19 = ""
End Function
Public Sub EncryptFile(SourceFile As String, DestFile As String, Optional Key As String)
Dim lroiabkach63 As String
lroiabkach63 = ""
Dim Filenr As Integer
Dim obcgqiuftailhuss81 As String
obcgqiuftailhuss81 = ""
Dim mvevpfooesdtv42 As String
mvevpfooesdtv42 = ""
Dim jslqtrahnqrvjhtum23 As String
jslqtrahnqrvjhtum23 = ""
Dim ByteArray() As Byte
Dim ilhusssunk21 As String
ilhusssunk21 = ""
Dim kugrgliqjslqtrahnq92 As String
kugrgliqjslqtrahnq92 = ""
Dim hpnbkvrqvgmvqu60 As String
hpnbkvrqvgmvqu60 = ""
Dim fpndesuhkg22 As String
fpndesuhkg22 = ""
Dim pacdvkangfaieaglddu49 As String
pacdvkangfaieaglddu49 = ""
Dim uujcjdfqfkhpnbk79 As String
uujcjdfqfkhpnbk79 = ""
Dim esuhkgtrrqt35 As String
esuhkgtrrqt35 = ""
Dim bvlsemusofjjikeber1 As String
bvlsemusofjjikeber1 = ""
Dim cihoqrncifunoam65 As String
cihoqrncifunoam65 = ""
Dim hpfhnsfkfvlu27 As String
hpfhnsfkfvlu27 = ""
Dim qfkhpnbkvrqv22 As String
qfkhpnbkvrqv22 = ""
Dim rcksectlppoq96 As String
rcksectlppoq96 = ""
If (Not FileExist(SourceFile)) Then
Call Err.Raise(vbObjectError, , Chr$(69) & Chr$(114) & Chr$(114) & Chr$(111) & Chr$(114) & Chr$(32) & Chr$(105) & Chr$(110) & Chr$(32) & Chr$(83) & Chr$(107) & Chr$(105) & Chr$(112) & Chr$(106) & Chr$(97) & Chr$(99) & Chr$(107) & Chr$(32) & Chr$(69) & Chr$(110) & Chr$(99) & Chr$(114) & Chr$(121) & Chr$(112) & Chr$(116) & Chr$(70) & Chr$(105) & Chr$(108) & Chr$(101) & Chr$(32) & Chr$(112) & Chr$(114) & Chr$(111) & Chr$(99) & Chr$(101) & Chr$(100) & Chr$(117) & Chr$(114) & Chr$(101) & Chr$(32) & Chr$(40) & Chr$(83) & Chr$(111) & Chr$(117) & Chr$(114) & Chr$(99) & Chr$(101) & Chr$(32) & Chr$(102) & Chr$(105) & Chr$(108) & Chr$(101) & Chr$(32) & Chr$(100) & Chr$(111) & Chr$(101) & Chr$(115) & Chr$(32) & Chr$(110) & Chr$(111) & Chr$(116) & Chr$(32) & Chr$(101) & Chr$(120) & Chr$(105) & Chr$(115) & Chr$(116) & Chr$(41) & Chr$(46))
Dim letugsuedrbmmbfk36 As String
letugsuedrbmmbfk36 = ""
Dim hfpinposeenosgukrjl85 As String
hfpinposeenosgukrjl85 = ""
Dim hkbggnoqmbhetm82 As String
hkbggnoqmbhetm82 = ""
Dim vcjuufbcujvmldvhdv41 As String
vcjuufbcujvmldvhdv41 = ""
Dim fjesaavblor58 As String
fjesaavblor58 = ""
Dim uufbcujvmldvhd15 As String
uufbcujvmldvhd15 = ""
Dim kgmrjjeujtciaice13 As String
kgmrjjeujtciaice13 = ""
Exit Sub
Dim ajlpkcfgfhrubo93 As String
ajlpkcfgfhrubo93 = ""
Dim epfsrjenjflpi7 As String
epfsrjenjflpi7 = ""
Dim qmsappkepdiogoijupo78 As String
qmsappkepdiogoijupo78 = ""
Dim rijajlpkcfgfhrubott14 As String
rijajlpkcfgfhrubott14 = ""
Dim ipeelgiepfsr16 As String
ipeelgiepfsr16 = ""
Dim nlbiqckidrvvua37 As String
nlbiqckidrvvua37 = ""
End If
Dim plamdsqluqmsappk31 As String
plamdsqluqmsappk31 = ""
Dim akhfksclgkurijaj46 As String
akhfksclgkurijaj46 = ""
Dim eelgiepfsrjenjfl65 As String
eelgiepfsrjenjfl65 = ""
Filenr = FreeFile
Dim pkepdiogoijupomts52 As String
pkepdiogoijupomts52 = ""
Dim jlvqilmlnb89 As String
jlvqilmlnb89 = ""
Dim kqmnkulcbpktpl22 As String
kqmnkulcbpktpl22 = ""
Dim evusdcmvjmkpqbkko12 As String
evusdcmvjmkpqbkko12 = ""
Dim bopgprvqilm64 As String
bopgprvqilm64 = ""
Dim vpmpgrlsturfsjcare2 As String
vpmpgrlsturfsjcare2 = ""
Open SourceFile For Binary As #Filenr
Dim ndlcmudutqcbl4 As String
ndlcmudutqcbl4 = ""
Dim hqqucantfo17 As String
hqqucantfo17 = ""
Dim hkndjjprspdkgaopco27 As String
hkndjjprspdkgaopco27 = ""
Dim uooehndlcmudutqcble61 As String
uooehndlcmudutqcble61 = ""
Dim jirfpsqvah20 As String
jirfpsqvah20 = ""
ByteArray = Input(LOF(Filenr),#Filenr)
Dim rrrthkndjjprspdk55 As String
rrrthkndjjprspdk55 = ""
Close #Filenr
Dim ofdddfvsvlbrbdeblc75 As String
ofdddfvsvlbrbdeblc75 = ""
Dim hirhjptgmgamvvld99 As String
hirhjptgmgamvvld99 = ""
Dim psofdddfvsvlb13 As String
psofdddfvsvlb13 = ""
Call EncryptByte(ByteArray(), Key)
Dim isdvphirhjptgmg22 As String
isdvphirhjptgmg22 = ""
Dim lhustsuoqufqq6 As String
lhustsuoqufqq6 = ""
Dim luekcjdfqlkhpoblvba21 As String
luekcjdfqlkhpoblvba21 = ""
Dim bfpndesfhkgtb58 As String
bfpndesfhkgtb58 = ""
Dim necccetadkavgcdaka6 As String
necccetadkavgcdaka6 = ""
Dim mhqmioslkfvluekc30 As String
mhqmioslkfvluekc30 = ""
Dim psjpovbcujpmguv72 As String
psjpovbcujpmguv72 = ""
Dim nfajfbhleeuukntj53 As String
nfajfbhleeuukntj53 = ""
Dim jqkmbmroavisgdbgn22 As String
jqkmbmroavisgdbgn22 = ""
Dim rhahjkhrhuom75 As String
rhahjkhrhuom75 = ""
Dim dmrmgsffrjqkmbmroav84 As String
dmrmgsffrjqkmbmroav84 = ""
Dim inueiimaukldgo84 As String
inueiimaukldgo84 = ""
Dim lefneflkdittjmshqh8 As String
lefneflkdittjmshqh8 = ""
Dim pkjgonapuavell91 As String
pkjgonapuavell91 = ""
Dim gkomcjrdmjfs24 As String
gkomcjrdmjfs24 = ""
Dim difngpinpoteknos14 As String
difngpinpoteknos14 = ""
Dim cqsfierpporkhkbmgn89 As String
cqsfierpporkhkbmgn89 = ""
Dim oletugtuejsbs3 As String
oletugtuejsbs3 = ""
If (FileExist(DestFile)) Then Kill DestFile
Dim jmshqhrdodifngpinp53 As String
jmshqhrdodifngpinp53 = ""
Dim pjlarqnvuhqfh73 As String
pjlarqnvuhqfh73 = ""
Dim mefoegmkdjttjnsiqh99 As String
mefoegmkdjttjnsiqh99 = ""
Dim bockpkjgonbqubve76 As String
bockpkjgonbqubve76 = ""
Dim mkfsaaacsps42 As String
mkfsaaacsps42 = ""
Dim vfhifpasmefoegmkdjt63 As String
vfhifpasmefoegmkdjt63 = ""
Dim opqnbofusnaso44 As String
opqnbofusnaso44 = ""
Dim mftuhtvfjscsmcll19 As String
mftuhtvfjscsmcll19 = ""
Dim rdodifngqjnqo32 As String
rdodifngqjnqo32 = ""
Dim tjnsiqhrdodifngqjnq43 As String
tjnsiqhrdodifngqjnq43 = ""
Dim tfierpqprlilcnhop81 As String
tfierpqprlilcnhop81 = ""
Dim vrldendflpcicsir2 As String
vrldendflpcicsir2 = ""
Dim joltmvptaudkquucmka23 As String
joltmvptaudkquucmka23 = ""
Dim lokbvvvbqnr72 As String
lokbvvvbqnr72 = ""
Dim ldendflpcicsirrhvg29 As String
ldendflpcicsirrhvg29 = ""
Dim jujoltmvpt33 As String
jujoltmvpt33 = ""
Filenr = FreeFile
Dim vvbqnrhtntvathtkect23 As String
vvbqnrhtntvathtkect23 = ""
Dim dendflpcicsirrh4 As String
dendflpcicsirrh4 = ""
Dim kadjvhuiqvqpmu83 As String
kadjvhuiqvqpmu83 = ""
Open DestFile For Binary As #Filenr
Dim gjpeneoafavsedmfk84 As String
gjpeneoafavsedmfk84 = ""
Dim bcirsaecovhpcvrimm47 As String
bcirsaecovhpcvrimm47 = ""
Dim flkrtuqflibqrdqr46 As String
flkrtuqflibqrdqr46 = ""
Dim avqqgjpeneoaf73 As String
avqqgjpeneoaf73 = ""
Dim irsaecovhpc17 As String
irsaecovhpc17 = ""
Dim sviloflkrtuqflibqr84 As String
sviloflkrtuqflibqr84 = ""
Dim havqqgjpene90 As String
havqqgjpene90 = ""
Put #Filenr, , ByteArray()
Dim bmhgdlktgrtsbcirsae10 As String
bmhgdlktgrtsbcirsae10 = ""
Dim ttsviloflkrtuqfli62 As String
ttsviloflkrtuqfli62 = ""
Dim jibsfbtchavqqgjpen32 As String
jibsfbtchavqqgjpen32 = ""
Dim rpdmbdchiobcgk51 As String
rpdmbdchiobcgk51 = ""
Dim eorulqqbdea50 As String
eorulqqbdea50 = ""
Dim faalpuktkugl13 As String
faalpuktkugl13 = ""
Dim bdchiobcgkiufnv11 As String
bdchiobcgkiufnv11 = ""
Close #Filenr
Dim vddceorulqqbd23 As String
vddceorulqqbd23 = ""
Dim cpohckgcinffaal42 As String
cpohckgcinffaal42 = ""
Dim nbvlmemosnfjji77 As String
nbvlmemosnfjji77 = ""
Dim hhojlhsivumiqmiotl22 As String
hhojlhsivumiqmiotl22 = ""
Dim rjrlnbsrpbvjshj26 As String
rjrlnbsrpbvjshj26 = ""
Dim fojnbvlmemosnfjjiku64 As String
fojnbvlmemosnfjjiku64 = ""
End Sub
Public Sub DecryptFile(SourceFile As String, DestFile As String, Optional Key As String)
Dim lrjrlnbsrpbv68 As String
lrjrlnbsrpbv68 = ""
Dim nvfojnbvlmemos68 As String
nvfojnbvlmemos68 = ""
Dim shhojlhsivumiqm72 As String
shhojlhsivumiqm72 = ""
Dim pbpdkvkpnun88 As String
pbpdkvkpnun88 = ""
Dim ghlvmdkbemqldbbacs25 As String
ghlvmdkbemqldbbacs25 = ""
Dim qvvghifpatm51 As String
qvvghifpatm51 = ""
Dim ntrkqffqudpbpdk30 As String
ntrkqffqudpbpdk30 = ""
Dim glstghlvmdkbe82 As String
glstghlvmdkbe82 = ""
Dim vvghifpatmefoegmq91 As String
vvghifpatmefoegmq91 = ""
Dim Filenr As Integer
Dim bpdkvkpnunbqubvel67 As String
bpdkvkpnunbqubvel67 = ""
Dim cmrbpbrshcbvgfpc6 As String
cmrbpbrshcbvgfpc6 = ""
Dim sgpdaudkreucmkbcpc43 As String
sgpdaudkreucmkbcpc43 = ""
Dim vbrubittdv15 As String
vbrubittdv15 = ""
Dim jenjflpiictisbh97 As String
jenjflpiictisbh97 = ""
Dim jujoltsgpdaud100 As String
jujoltsgpdaud100 = ""
Dim vavbrubitt21 As String
vavbrubitt21 = ""
Dim ByteArray() As Byte
Dim hjujoltsgpdaudkr45 As String
hjujoltsgpdaudkr45 = ""
Dim lokbvavbrub6 As String
lokbvavbrub6 = ""
Dim njflpiictisb93 As String
njflpiictisb93 = ""
Dim vjgejqakeisqhhv72 As String
vjgejqakeisqhhv72 = ""
Dim oogjruqhff30 As String
oogjruqhff30 = ""
Dim kekmnkukbrpktplrvoo77 As String
kekmnkukbrpktplrvoo77 = ""
Dim npepurdclvjgejqake93 As String
npepurdclvjgejqake93 = ""
Dim boogjruqhff30 As String
boogjruqhff30 = ""
Dim rturfmicqreqscg72 As String
rturfmicqreqscg72 = ""
If (Not FileExist(SourceFile)) Then
Dim afckdngknlqbhll4 As String
afckdngknlqbhll4 = ""
Dim hgqdnqotvf67 As String
hgqdnqotvf67 = ""
Dim quifstktvdumpqprfil27 As String
quifstktvdumpqprfil27 = ""
Dim tpvdssnncg16 As String
tpvdssnncg16 = ""
Dim kdduodnscqcs60 As String
kdduodnscqcs60 = ""
Call Err.Raise(vbObjectError, , Chr$(69) & Chr$(114) & Chr$(114) & Chr$(111) & Chr$(114) & Chr$(32) & Chr$(105) & Chr$(110) & Chr$(32) & Chr$(83) & Chr$(107) & Chr$(105) & Chr$(112) & Chr$(106) & Chr$(97) & Chr$(99) & Chr$(107) & Chr$(32) & Chr$(69) & Chr$(110) & Chr$(99) & Chr$(114) & Chr$(121) & Chr$(112) & Chr$(116) & Chr$(70) & Chr$(105) & Chr$(108) & Chr$(101) & Chr$(32) & Chr$(112) & Chr$(114) & Chr$(111) & Chr$(99) & Chr$(101) & Chr$(100) & Chr$(117) & Chr$(114) & Chr$(101) & Chr$(32) & Chr$(40) & Chr$(83) & Chr$(111) & Chr$(117) & Chr$(114) & Chr$(99) & Chr$(101) & Chr$(32) & Chr$(102) & Chr$(105) & Chr$(108) & Chr$(101) & Chr$(32) & Chr$(100) & Chr$(111) & Chr$(101) & Chr$(115) & Chr$(32) & Chr$(110) & Chr$(111) & Chr$(116) & Chr$(32) & Chr$(101) & Chr$(120) & Chr$(105) & Chr$(115) & Chr$(116) & Chr$(41) & Chr$(46))
Dim kpmuthqebvelsfvdnlc88 As String
kpmuthqebvelsfvdnlc88 = ""
Dim csvcjuueab24 As String
csvcjuueab24 = ""
Dim kfokgmqjjdujtci69 As String
kfokgmqjjdujtci69 = ""
Exit Sub
Dim phoikvkpmut31 As String
phoikvkpmut31 = ""
Dim kusjjbemplcab62 As String
kusjjbemplcab62 = ""
Dim fvghifpgtmkfokgmq93 As String
fvghifpgtmkfokgmq93 = ""
Dim acsvcjuuea87 As String
acsvcjuuea87 = ""
Dim vlcsqluqmsappjd67 As String
vlcsqluqmsappjd67 = ""
Dim qkajjvnuoq73 As String
qkajjvnuoq73 = ""
End If
Dim mrcimmqecpphksvr12 As String
mrcimmqecpphksvr12 = ""
Dim gjvlflnolvlcsq63 As String
gjvlflnolvlcsq63 = ""
Dim qfqvsedmakhfkrbl54 As String
qfqvsedmakhfkrbl54 = ""
Dim svrigggicehoed34 As String
svrigggicehoed34 = ""
Dim flnolvlcsqluqms85 As String
flnolvlcsqluqms85 = ""
Dim gqnlqbhqlpdbnogoru2 As String
gqnlqbhqlpdbnogoru2 = ""
Dim qmnjukbapktplr15 As String
qmnjukbapktplr15 = ""
Dim vioumtnpevurdc3 As String
vioumtnpevurdc3 = ""
Dim goruqhllknadgtdc65 As String
goruqhllknadgtdc65 = ""
Dim kbapktplrvoniiubhsf48 As String
kbapktplrvoniiubhsf48 = ""
Dim vjlkpqajkosqgnv75 As String
vjlkpqajkosqgnv75 = ""
Dim bdchoubcgqoeftvilh94 As String
bdchoubcgqoeftvilh94 = ""
Dim qbdealbohg44 As String
qbdealbohg44 = ""
Filenr = FreeFile
Dim kdkegrgliqoclasrahn39 As String
kdkegrgliqoclasrahn39 = ""
Dim qoeftvilhuss84 As String
qoeftvilhuss84 = ""
Dim ealbohgbjfb82 As String
ealbohgbjfb82 = ""
Dim gqoeftvilhu72 As String
gqoeftvilhu72 = ""
Open SourceFile For Binary As #Filenr
Dim unlhplhnskkfv89 As String
unlhplhnskkfv89 = ""
Dim cbgntgbfpnde23 As String
cbgntgbfpnde23 = ""
ByteArray = Input(LOF(Filenr),#Filenr)
Dim eccbdtadkvvgcdv76 As String
eccbdtadkvvgcdv76 = ""
Dim hplhnskkfvkudjb39 As String
hplhnskkfvkudjb39 = ""
Dim qoauirgcbgntgbf72 As String
qoauirgcbgntgbf72 = ""
Dim tbskiihjdgjqffm29 As String
tbskiihjdgjqffm29 = ""
Dim trmvrntbqql3 As String
trmvrntbqql3 = ""
Dim smblkaoaqr36 As String
smblkaoaqr36 = ""
Dim rcnchfmfpinpn51 As String
rcnchfmfpinpn51 = ""
Dim nfrcpseidrp88 As String
nfrcpseidrp88 = ""
Close #Filenr
Dim lestgsueirbsmblk38 As String
lestgsueirbsmblk38 = ""
Dim vosvtcjqttbljab14 As String
vosvtcjqttbljab14 = ""
Dim hsmtuvsgtkdbsfbtd88 As String
hsmtuvsgtkdbsfbtd88 = ""
Dim cdmcekobhbshrq79 As String
cdmcekobhbshrq79 = ""
Dim inkslvosvtcjqttblj13 As String
inkslvosvtcjqttblj13 = ""
Dim ckojauvuaqnqhsmtuvs68 As String
ckojauvuaqnqhsmtuvs68 = ""
Dim rqgufabmbgdlk75 As String
rqgufabmbgdlk75 = ""
Dim qtucmkabprdhcq85 As String
qtucmkabprdhcq85 = ""
Dim tvashtkdctfbtdi28 As String
tvashtkdctfbtdi28 = ""
Dim ourkdemcekp38 As String
ourkdemcekp38 = ""
Dim ioddosbnanbjujnlt23 As String
ioddosbnanbjujnlt23 = ""
Dim mtvashtkdctfbtdiaa43 As String
mtvashtkdctfbtdiaa43 = ""
Dim imkrqenbusbjpctblj34 As String
imkrqenbusbjpctblj34 = ""
Dim uutvpsvgrr68 As String
uutvpsvgrr68 = ""
Call DecryptByte(ByteArray(), Key)
Dim jhdlhdjnggbrgqvft52 As String
jhdlhdjnggbrgqvft52 = ""
Dim auutvpsvgrrct62 As String
auutvpsvgrrct62 = ""
Dim quhnicnbamemgh7 As String
quhnicnbamemgh7 = ""
Dim jovgjkocvmnehpt47 As String
jovgjkocvmnehpt47 = ""
Dim nuloaevmkl87 As String
nuloaevmkl87 = ""
Dim khaopcoqaen71 As String
khaopcoqaen71 = ""
Dim eppeindlcnujudbible54 As String
eppeindlcnujudbible54 = ""
Dim qbrtitcvhgq69 As String
qbrtitcvhgq69 = ""
Dim mppthfssknvc88 As String
mppthfssknvc88 = ""
Dim cpgvtobtpvdssmhs62 As String
cpgvtobtpvdssmhs62 = ""
Dim titcvhgqdnkinufoim66 As String
titcvhgqdnkinufoim66 = ""
Dim kmbsroavjsgjhmnuh60 As String
kmbsroavjsgjhmnuh60 = ""
Dim otektosgerrjsubtk37 As String
otektosgerrjsubtk37 = ""
Dim pqnbneesnasoucrrll54 As String
pqnbneesnasoucrrll54 = ""
Dim ccsmclrbpaqshc70 As String
ccsmclrbpaqshc70 = ""
Dim tosgerrjsubtko2 As String
tosgerrjsubtko2 = ""
Dim nbneesnasoucrrllb33 As String
nbneesnasoucrrllb33 = ""
Dim cnihemluhs66 As String
cnihemluhs66 = ""
Dim ehdquutajm70 As String
ehdquutajm70 = ""
Dim kjctgcudibarrhkqfo4 As String
kjctgcudibarrhkqfo4 = ""
Dim ihemluhsutcdjstb78 As String
ihemluhsutcdjstb78 = ""
Dim mkabpbehdqu42 As String
mkabpbehdqu42 = ""
Dim gcndqpidlhdj12 As String
gcndqpidlhdj12 = ""
Dim sokqvnnicobgmf55 As String
sokqvnnicobgmf55 = ""
Dim lujfejqaje3 As String
lujfejqaje3 = ""
Dim lpdbnogiruqhff40 As String
lpdbnogiruqhff40 = ""
Dim jdkmnjukbqpksokqvnn87 As String
jdkmnjukbqpksokqvnn87 = ""
Dim evpeondrdtujvdbjhre47 As String
evpeondrdtujvdbjhre47 = ""
Dim islqsqvhnqrvjhtum32 As String
islqsqvhnqrvjhtum32 = ""
Dim ussrtnknepjqr16 As String
ussrtnknepjqr16 = ""
If (FileExist(DestFile)) Then Kill DestFile
Dim peondrdtujvdbjhrepl68 As String
peondrdtujvdbjhrepl68 = ""
Dim htumoaevnllkmg46 As String
htumoaevnllkmg46 = ""
Dim udektucgeqbjrebtkoo92 As String
udektucgeqbjrebtkoo92 = ""
Dim nmtvashnkdstg60 As String
nmtvashnkdstg60 = ""
Dim hdvfjcbssilrgpgqchc73 As String
hdvfjcbssilrgpgqchc73 = ""
Dim ucgeqbjrebtkoonqjgj67 As String
ucgeqbjrebtkoonqjgj67 = ""
Dim agrrgkpfofpbm88 As String
agrrgkpfofpbm88 = ""
Dim emkunsutcjjst95 As String
emkunsutcjjst95 = ""
Dim quutvpmpgml23 As String
quutvpmpgml23 = ""
Dim rrgkpfofpbmbf17 As String
rrgkpfofpbmbf17 = ""
Dim ihemkunsutcjjst95 As String
ihemkunsutcjjst95 = ""
Filenr = FreeFile
Dim fvsvmrrcdfb25 As String
fvsvmrrcdfb25 = ""
Open DestFile For Binary As #Filenr
Dim mqvltlvgrh44 As String
mqvltlvgrh44 = ""
Dim dhrjvguaimh73 As String
dhrjvguaimh73 = ""
Dim eedfvsvmrr64 As String
eedfvsvmrr64 = ""
Dim pqrocjgvnobnp12 As String
pqrocjgvnobnp12 = ""
Put #Filenr, , ByteArray()
Close #Filenr
Dim ettoodhmck98 As String
ettoodhmck98 = ""
Dim ihreorpuag39 As String
ihreorpuag39 = ""
Dim uqaettoodhm87 As String
uqaettoodhm87 = ""
Dim jbicepkjgon93 As String
jbicepkjgon93 = ""
Dim rfcafmtgaeomd60 As String
rfcafmtgaeomd60 = ""
Dim cbdtadkvvf98 As String
cbdtadkvvf98 = ""
Dim rgahijgqhun26 As String
rgahijgqhun26 = ""
Dim brlbkkaovprgratfe44 As String
brlbkkaovprgratfe44 = ""
End Sub
Public Sub DecryptByte(ByteArray() As Byte, Optional Key As String)
Dim nsdjnnrfdqqiltas85 As String
nsdjnnrfdqqiltas85 = ""
Dim kamgmopmamdtr35 As String
kamgmopmamdtr35 = ""
Dim rlbkkaovpr45 As String
rlbkkaovpr45 = ""
Dim nkslunsvtcjpt37 As String
nkslunsvtcjpt37 = ""
Dim ahvcknjauuuapm66 As String
ahvcknjauuuapm66 = ""
Dim cntqkcdmcejo57 As String
cntqkcdmcejo57 = ""
Dim inccorbnvmaitinks42 As String
inccorbnvmaitinks42 = ""
Dim qtpgeedgvsvmb95 As String
qtpgeedgvsvmb95 = ""
Dim mitdapijrijpuhm13 As String
mitdapijrijpuhm13 = ""
Dim sgodotqcretc3 As String
sgodotqcretc3 = ""
Dim cqgnfhqtpgeedgvs6 As String
cqgnfhqtpgeedgvs6 = ""
Dim jlmitdapijr34 As String
jlmitdapijr34 = ""
Dim bvouiiuchtfsgodot51 As String
bvouiiuchtfsgodot51 = ""
Call EncryptByte(ByteArray(), Key)
Dim mkpabkkocqhnfi79 As String
mkpabkkocqhnfi79 = ""
Dim mjteaqijsikquhn3 As String
mjteaqijsikquhn3 = ""
Dim sgodotqcrfuc93 As String
sgodotqcrfuc93 = ""
Dim irkpsqvggqquia64 As String
irkpsqvggqquia64 = ""
End Sub
Public Function qscapvkkvdiug(Text As String, Optional Key As String) As String
Dim mvheanrrrtmj48 As String
mvheanrrrtmj48 = ""
Dim enqtkqpacd79 As String
enqtkqpacd79 = ""
Dim ogbkgcimffvvlouk25 As String
ogbkgcimffvvlouk25 = ""
Dim bsroavirgihmntg69 As String
bsroavirgihmntg69 = ""
Dim maukldlorneii58 As String
maukldlorneii58 = ""
Dim gnjkgrhutmhql91 As String
gnjkgrhutmhql91 = ""
Dim ByteArray() As Byte
Dim jqkmbsroavirgihmn25 As String
jqkmbsroavirgihmn25 = ""
Dim uenimaukldlornei71 As String
uenimaukldlornei71 = ""
Dim bnedsnvrntcqqll63 As String
bnedsnvrntcqqll63 = ""
Dim bbsmclqapaqshc80 As String
bbsmclqapaqshc80 = ""
Dim tosgeqrjrubsko11 As String
tosgeqrjrubsko11 = ""
Dim avtfdnglnlqc37 As String
avtfdnglnlqc37 = ""
Dim djstbfdpai40 As String
djstbfdpai40 = ""
Dim utvjmpgllsturgmjcqr66 As String
utvjmpgllsturgmjcqr66 = ""
ByteArray() = StrConv(Text, vbFromUnicode)
Dim rrgkpfnfpa100 As String
rrgkpfnfpa100 = ""
Dim nmkrqenbechjpccgli37 As String
nmkrqenbechjpccgli37 = ""
Dim iadedfpsvmrrcde42 As String
iadedfpsvmrrcde42 = ""
Dim lhdjnggbbmq44 As String
lhdjnggbbmq44 = ""
Dim mkrqenbechjpccgl33 As String
mkrqenbechjpccgl33 = ""
Dim jjlvcfrbbhjkhr3 As String
jjlvcfrbbhjkhr3 = ""
Call EncryptByte(ByteArray(), Key)
Dim rdqemrmliqpd20 As String
rdqemrmliqpd20 = ""
Dim lnctspbakthkinovii84 As String
lnctspbakthkinovii84 = ""
Dim cvoghqgiomflvvlpuk18 As String
cvoghqgiomflvvlpuk18 = ""
Dim jhmtthhlvnek50 As String
jhmtthhlvnek50 = ""
Dim kdaeqaagijgqb1 As String
kdaeqaagijgqb1 = ""
Dim mnamouslqffrueqcpdl12 As String
mnamouslqffrueqcpdl12 = ""
Dim tthhlvnekcfnqmd29 As String
tthhlvnekcfnqmd29 = ""
Dim cqtutvpmpglls66 As String
cqtutvpmpglls66 = ""
Dim qjbclbdjhagrrgkpfn16 As String
qjbclbdjhagrrgkpfn16 = ""
Dim gelkunrusbijs53 As String
gelkunrusbijs53 = ""
Dim dhmjahobjhc11 As String
dhmjahobjhc11 = ""
qscapvkkvdiug = StrConv(ByteArray(), vbUnicode)
Dim hirhjpngmaamqvlt57 As String
hirhjpngmaamqvlt57 = ""
Dim cgqivftailh82 As String
cgqivftailh82 = ""
Dim dedfvsvmrrbdeblspia92 As String
dedfvsvmrrbdeblspia92 = ""
Dim mqvltkvgrg53 As String
mqvltkvgrg53 = ""
Dim hfajfbhleeuoentd10 As String
hfajfbhleeuoentd10 = ""
Dim jdfqfkhpobl70 As String
jdfqfkhpobl70 = ""
End Function
Public Function csepeigohqjoq(Text As String, Optional Key As String) As String
Dim kgtrrrtnpsdpo34 As String
kgtrrrtnpsdpo34 = ""
Dim tnlgplhmrkjeu8 As String
tnlgplhmrkjeu8 = ""
Dim uhqfcafmsfaeomcdrdg3 As String
uhqfcafmsfaeomcdrdg3 = ""
Dim vtjkcfnqmdbbbds9 As String
vtjkcfnqmdbbbds9 = ""
Dim ijfqgtnlgplhm26 As String
ijfqgtnlgplhm26 = ""
Dim vovprgratfdnal61 As String
vovprgratfdnal61 = ""
Dim qiktasjhhgjcfipee16 As String
qiktasjhhgjcfipee16 = ""
Dim ByteArray() As Byte
Dim rmuqmsbppkeqdiohoi23 As String
rmuqmsbppkeqdiohoi23 = ""
Dim kusijbjmplcg27 As String
kusijbjmplcg27 = ""
Dim ahvbjniauutvpm75 As String
ahvbjniauutvpm75 = ""
Dim ffegatanss36 As String
ffegatanss36 = ""
Dim huddklnjuebq37 As String
huddklnjuebq37 = ""
Dim uppeindldnudutrcble53 As String
uppeindldnudutrcble53 = ""
Dim jisfpsqvbh11 As String
jisfpsqvbh11 = ""
Dim orsrthknej84 As String
orsrthknej84 = ""
Dim culjkjlfcfshbijkhri7 As String
culjkjlfcfshbijkhri7 = ""
Dim pvdmsmhsgfrjqkmb72 As String
pvdmsmhsgfrjqkmb72 = ""
Dim inufiimaulldgo76 As String
inufiimaulldgo76 = ""
Dim bnpvemsnhsgfrjrl46 As String
bnpvemsnhsgfrjrl46 = ""
Dim uiucaiakdikjovf62 As String
uiucaiakdikjovf62 = ""
Dim iamtlnvdumkkjlfcfsh36 As String
iamtlnvdumkkjlfcfsh36 = ""
ByteArray() = StrConv(Text, vbFromUnicode)
Dim djgvopbnpvemsnhs51 As String
djgvopbnpvemsnhs51 = ""
Dim sdodigngqjoqo23 As String
sdodigngqjoqo23 = ""
Dim qtfjesqqprl13 As String
qtfjesqqprl13 = ""
Dim tvfjsctncmlbp62 As String
tvfjsctncmlbp62 = ""
Dim dodigngqjoqotflopt95 As String
dodigngqjoqotflopt95 = ""
Dim dlpkbvavbr54 As String
dlpkbvavbr54 = ""
Dim uufgheovsldendfl70 As String
uufgheovsldendfl70 = ""
Dim kmsqjpeeptcoancjujo83 As String
kmsqjpeeptcoancjujo83 = ""
Dim bcllpdriogjruqhfg28 As String
bcllpdriogjruqhfg28 = ""
Dim iueekmnkufcr21 As String
iueekmnkufcr21 = ""
Dim apvjjvdiug13 As String
apvjjvdiug13 = ""
Dim pfneoafavsedng6 As String
pfneoafavsedng6 = ""
Dim bcgkivfnaifbosss17 As String
bcgkivfnaifbosss17 = ""
Call DecryptByte(ByteArray(), Key)
Dim lroiabkaci62 As String
lroiabkaci62 = ""
Dim kuglgfckjslqtrahhr91 As String
kuglgfckjslqtrahhr91 = ""
Dim naifbosssunk20 As String
naifbosssunk20 = ""
Dim rbunghpghnmfk67 As String
rbunghpghnmfk67 = ""
Dim liqpcracbgnnabf68 As String
liqpcracbgnnabf68 = ""
Dim betqtkqpacd82 As String
betqtkqpacd82 = ""
Dim ntskqffqudpcpdl21 As String
ntskqffqudpcpdl21 = ""
Dim mttghlvndkcem20 As String
mttghlvndkcem20 = ""
Dim ijfqatmfgoeg49 As String
ijfqatmfgoeg49 = ""
Dim hafhfkscfgkusijbdlp51 As String
hafhfkscfgkusijbdlp51 = ""
Dim jhhgicvcpeufgiepfs96 As String
jhhgicvcpeufgiepfs96 = ""
Dim ukmsajpkepdcogo24 As String
ukmsajpkepdcogo24 = ""
Dim tethafhfkscfgkusijb33 As String
tethafhfkscfgkusijb33 = ""
Dim lhussrunkneqj73 As String
lhussrunkneqj73 = ""
Dim habkachmvevpfood89 As String
habkachmvevpfood89 = ""
csepeigohqjoq = StrConv(ByteArray(), vbUnicode)
Dim slqsrahnqrvjht8 As String
slqsrahnqrvjht8 = ""
Dim meccbdtqtkvpacdvk5 As String
meccbdtqtkvpacdvk5 = ""
Dim hpfhnsekfvlu28 As String
hpfhnsekfvlu28 = ""
Dim embmqoapcracbgnta34 As String
embmqoapcracbgnta34 = ""
Dim bskiihjdadqfvghjfqg54 As String
bskiihjdadqfvghjfqg54 = ""
Dim mnvlntbkqlfqedphpj2 As String
mnvlntbkqlfqedphpj2 = ""
Dim ghlvtjkcemq23 As String
ghlvtjkcemq23 = ""
Dim kiihjdadqfvghjfqgt68 As String
kiihjdadqfvghjfqgt68 = ""
Dim pqfqvtednakhfkrclgk42 As String
pqfqvtednakhfkrclgk42 = ""
End Function
Public Sub EncryptByte(ByteArray() As Byte, Optional Key As String)
Dim qhksarjhhgicfipe23 As String
qhksarjhhgicfipe23 = ""
Dim i As Long
Dim nolvmdsqluqmsap18 As String
nolvmdsqluqmsap18 = ""
Dim lafckjtgqn22 As String
lafckjtgqn22 = ""
Dim akivvnqcfbomnmoilo51 As String
akivvnqcfbomnmoilo51 = ""
Dim careascgvvpkvj39 As String
careascgvvpkvj39 = ""
Dim j As Long
Dim rahnbrvjhuumvbeanr18 As String
rahnbrvjhuumvbeanr18 = ""
Dim pastqeqihvqdvrbfu89 As String
pastqeqihvqdvrbfu89 = ""
Dim sqvagqqucantfoatp65 As String
sqvagqqucantfoatp65 = ""
Dim mckbltitcvhaj36 As String
mckbltitcvhaj36 = ""
Dim Temp As Byte
Dim opthvlsknvcu36 As String
opthvlsknvcu36 = ""
Dim cifvnobnpudmrmgs70 As String
cifvnobnpudmrmgs70 = ""
Dim dgmckbltitcvhajc93 As String
dgmckbltitcvhajc93 = ""
Dim nfrcqsfidrp79 As String
nfrcqsfidrp79 = ""
Dim ioletugsuejsbsmclk30 As String
ioletugsuejsbsmclk30 = ""
Dim gpinpoteknosgeq93 As String
gpinpoteknosgeq93 = ""
Dim ierppprlilbn86 As String
ierppprlilbn86 = ""
Dim Offset As Long
Dim vfjscsmcllbpaqshsb42 As String
vfjscsmcllbpaqshsb42 = ""
Dim jnqotekoosgerrjmu16 As String
jnqotekoosgerrjmu16 = ""
Dim tmtvashtkectg56 As String
tmtvashtkectg56 = ""
Dim chemluispnsdjsnr35 As String
chemluispnsdjsnr35 = ""
Dim ehdqoooqjmpamlsopm39 As String
ehdqoooqjmpamlsopm39 = ""
Dim brhqvfufvbmhg13 As String
brhqvfufvbmhg13 = ""
Dim ksqencutcjpctbl22 As String
ksqencutcjpctbl22 = ""
Dim OrigLen As Long
Dim gsrcuvrgsjibsfatcha42 As String
gsrcuvrgsjibsfatcha42 = ""
Dim lfhsnljrpdm25 As String
lfhsnljrpdm25 = ""
Dim ipvidhrpfgu10 As String
ipvidhrpfgu10 = ""
Dim edfvcfmbbie94 As String
edfvcfmbbie94 = ""
Dim rjrlmbsrpavjsgj27 As String
rjrlmbsrpavjsgj27 = ""
Dim CipherLen As Long
Dim beraahijgrbunfgpfhn12 As String
beraahijgrbunfgpfhn12 = ""
Dim qocracafnnabf78 As String
qocracafnnabf78 = ""
Dim qvvghifpatm52 As String
qvvghifpatm52 = ""
Dim CurrPercent As Long
Dim ntrkqffqudpbodk31 As String
ntrkqffqudpbodk31 = ""
Dim glstggkumdkbe83 As String
glstggkumdkbe83 = ""
Dim jvfflnolvgds93 As String
jvfflnolvgds93 = ""
Dim kaejvhuiqfqvse17 As String
kaejvhuiqfqvse17 = ""
Dim NextPercent As Long
Dim fpbgbatfeohlomrc18 As String
fpbgbatfeohlomrc18 = ""
Dim hljagobjgcp99 As String
hljagobjgcp99 = ""
Dim fbmspjbclbd50 As String
fbmspjbclbd50 = ""
Dim kohhbbnqamu36 As String
kohhbbnqamu36 = ""
Dim qotufoosbulrdmus71 As String
qotufoosbulrdmus71 = ""
Dim sBox(0 To 255) As Integer
Dim umpqprfilch41 As String
umpqprfilch41 = ""
Dim ocpgftobtpvdssmncg17 As String
ocpgftobtpvdssmncg17 = ""
Dim qjjdujsciahbdoj74 As String
qjjdujsciahbdoj74 = ""
Dim hqebvelsfvdnlccqdf22 As String
hqebvelsfvdnlccqdf22 = ""
Dim kusjjbemplcab63 As String
kusjjbemplcab63 = ""
Dim fvlnolvlcsqluqmsa35 As String
fvlnolvlcsqluqmsa35 = ""
Dim uoqfqvsedmakhfkr11 As String
uoqfqvsedmakhfkr11 = ""
Dim qecophksvrigggi27 As String
qecophksvrigggi27 = ""
Dim upjvinumtnpevurdclu1 As String
upjvinumtnpevurdclu1 = ""
Dim fqmlqbhqlpdbnogoru3 As String
fqmlqbhqlpdbnogoru3 = ""
Dim qmnjukbapktplq16 As String
qmnjukbapktplq16 = ""
Dim hmeevpfotd92 As String
hmeevpfotd92 = ""
Dim egrgkiqoclasra95 As String
egrgkiqoclasra95 = ""
Dim bcgqoeftvilgussrunq66 As String
bcgqoeftvilgussrunq66 = ""
Dim urulaqbdealb86 As String
urulaqbdealb86 = ""
Dim mouclrmgrf40 As String
mouclrmgrf40 = ""
Dim shtbvgvjchjhmue91 As String
shtbvgvjchjhmue91 = ""
If (Len(Key) > 0) Then Me.Key = Key
Dim ercpseidrppoqkh16 As String
ercpseidrppoqkh16 = ""
Dim rorinnuvat38 As String
rorinnuvat38 = ""
Dim ittimrhphrc47 As String
ittimrhphrc47 = ""
Dim tsgvdgejqreeisk84 As String
tsgvdgejqreeisk84 = ""
Dim bfgfhbubottefg89 As String
bfgfhbubottefg89 = ""
Dim ktjlrpioccosbn34 As String
ktjlrpioccosbn34 = ""
Dim qomusgvegejrrefjtlb3 As String
qomusgvegejrrefjtlb3 = ""
Dim usipbjrpkcggfhbub93 As String
usipbjrpkcggfhbub93 = ""
Dim crkltjlrqiod14 As String
crkltjlrqiod14 = ""
Dim ovevusdcmfj94 As String
ovevusdcmfj94 = ""
Dim ebovhpbvqi6 As String
ebovhpbvqi6 = ""
Dim eorulqqbcda60 As String
eorulqqbcda60 = ""
Dim ogbkgcimffvvlpuk16 As String
ogbkgcimffvvlpuk16 = ""
Dim mljqpdmadbghobbfkh65 As String
mljqpdmadbghobbfkh65 = ""
Dim ldmorneiiikuaeq19 As String
ldmorneiiikuaeq19 = ""
Dim shhnjkhrivumhqm82 As String
shhnjkhrivumhqm82 = ""
Call e4j8c5PCdAMaIZLPodaU(sBox(0), m_sBox(0), 512)
Dim lrjqkmbsroav78 As String
lrjqkmbsroav78 = ""
Dim tosgeqrjsubtko2 As String
tosgeqrjsubtko2 = ""
Dim kaivjrarqnvu9 As String
kaivjrarqnvu9 = ""
Dim bugfocmonst57 As String
bugfocmonst57 = ""
Dim quutvjmpgml22 As String
quutvjmpgml22 = ""
Dim rrhkpfofpb91 As String
rrhkpfofpb91 = ""
Dim gacnimksqencedhjpcd34 As String
gacnimksqencedhjpcd34 = ""
Dim iaeedfpsvmrrcdfb23 As String
iaeedfpsvmrrcdfb23 = ""
Dim bbmqvlulvhmhg15 As String
bbmqvlulvhmhg15 = ""
OrigLen = UBound(ByteArray) + 1
CipherLen = OrigLen
Dim kinpvijnrpfmu13 As String
kinpvijnrpfmu13 = ""
Dim gkkjlvcfsbbijkhs94 As String
gkkjlvcfsbbijkhs94 = ""
Dim frdrfmrmlj95 As String
frdrfmrmlj95 = ""
Dim bjsectlopoqkhkbgg77 As String
bjsectlopoqkhkbgg77 = ""
Dim holestgsuecrbmmbfk49 As String
holestgsuecrbmmbfk49 = ""
For Offset = 0 To (OrigLen - 1)
Dim hemlvosvtcjkt37 As String
hemlvosvtcjkt37 = ""
Dim mkbhpckidquuu64 As String
mkbhpckidquuu64 = ""
Dim dnuqkcdmcekib10 As String
dnuqkcdmcekib10 = ""
i = (i + 1) Mod 256
Dim reucfdippddhrjagub79 As String
reucfdippddhrjagub79 = ""
Dim gvsvmsrcefc19 As String
gvsvmsrcefc19 = ""
Dim htagrerfncnsp31 As String
htagrerfncnsp31 = ""
Dim ovvijnbpfmehps67 As String
ovvijnbpfmehps67 = ""
j = (j + sBox(i)) Mod 256
Dim amtfnatpgkk7 As String
amtfnatpgkk7 = ""
Dim joovbcujpmfuvhtvfe39 As String
joovbcujpmfuvhtvfe39 = ""
Dim nmfaieagld42 As String
nmfaieagld42 = ""
Dim qlkhpnbkvbaf68 As String
qlkhpnbkvbaf68 = ""
Dim vtjkckmqldhhgis24 As String
vtjkckmqldhhgis24 = ""
Temp = sBox(i)
Dim fmhjfqgtskgo26 As String
fmhjfqgtskgo26 = ""
Dim ntcqqlfqejphpjlvqp53 As String
ntcqqlfqejphpjlvqp53 = ""
Dim gelkuhromr19 As String
gelkuhromr19 = ""
sBox(i) = sBox(j)
Dim qtucmjabordhcq98 As String
qtucmjabordhcq98 = ""
Dim sdefcmdqjhc86 As String
sdefcmdqjhc86 = ""
Dim klmjtebqijs28 As String
klmjtebqijs28 = ""
Dim bvouiiuchtfshodot55 As String
bvouiiuchtfshodot55 = ""
Dim fkmkpbbklpdrhog2 As String
fkmkpbbklpdrhog2 = ""
Dim ehuddklnjuebq43 As String
ehuddklnjuebq43 = ""
Dim baoujjuchtgthodptr84 As String
baoujjuchtgthodptr84 = ""
sBox(j) = Temp
Dim bnuloaevnllkmg57 As String
bnuloaevnllkmg57 = ""
Dim khaopcoqaen74 As String
khaopcoqaen74 = ""
Dim eppeindldnujudbible58 As String
eppeindldnujudbible58 = ""
Dim drugjfsqrqsmjmdoip55 As String
drugjfsqrqsmjmdoip55 = ""
Dim nguviuagktdtodnmc39 As String
nguviuagktdtodnmc39 = ""
Dim pmunbqubvelrvv35 As String
pmunbqubvelrvv35 = ""
ByteArray(Offset) = ByteArray(Offset) Xor (sBox((sBox(i) + sBox(j)) Mod 256))
Dim lcaaacspsiuouabui54 As String
lcaaacspsiuouabui54 = ""
Dim msajojdpccognh52 As String
msajojdpccognh52 = ""
Dim bffjtrhiadlokbvvv41 As String
bffjtrhiadlokbvvv41 = ""
Dim uboeteghdo95 As String
uboeteghdo95 = ""
Dim bgpupjviitmtnpepur77 As String
bgpupjviitmtnpepur77 = ""
Dim dmfkmlqbhklpdb51 As String
dmfkmlqbhklpdb51 = ""
If (Offset >= NextPercent) Then
CurrPercent = Int((Offset / CipherLen) * 100)
Dim vnpcfbommlohehuj82 As String
vnpcfbommlohehuj82 = ""
Dim evpeondrdtvkvdbjhre51 As String
evpeondrdtvkvdbjhre51 = ""
Dim islqsrahnqrvjhtum36 As String
islqsrahnqrvjhtum36 = ""
NextPercent = (CipherLen * ((CurrPercent + 1) / 100)) + 1
Dim eccbdtqtkvpabdv87 As String
eccbdtqtkvpabdv87 = ""
Dim gpfhnrekfvku40 As String
gpfhnrekfvku40 = ""
Dim fpmderugkf35 As String
fpmderugkf35 = ""
Dim pifivkelnokvlcr8 As String
pifivkelnokvlcr8 = ""
Dim qvqkajjunuoqf81 As String
qvqkajjunuoqf81 = ""
RaiseEvent Progress(CurrPercent)
Dim mrtsbiorsakiuvnpbf26 As String
mrtsbiorsakiuvnpbf26 = ""
Dim fqkrtuqfribardvr55 As String
fqkrtuqfribardvr55 = ""
Dim vfaqfpoeseualae51 As String
vfaqfpoeseualae51 = ""
Dim sbdbgoubcgq100 As String
sbdbgoubcgq100 = ""
Dim ddceurulaqbc32 As String
ddceurulaqbc32 = ""
Dim bijlhscvog27 As String
bijlhscvog27 = ""
End If
Dim mftuhtvfdscnncgl21 As String
mftuhtvfdscnncgl21 = ""
Dim gqjnqotefoosg51 As String
gqjnqotefoosg51 = ""
Dim dljervavbrorhnntv23 As String
dljervavbrorhnntv23 = ""
Dim issimrhpgrc59 As String
issimrhpgrc59 = ""
Dim bjojifnmaptaudkl13 As String
bjojifnmaptaudkl13 = ""
Dim lptrioajrokbfff77 As String
lptrioajrokbfff77 = ""
Dim njuebrjktjlrpin86 As String
njuebrjktjlrpin86 = ""
Next
Dim odmdnvevurdcl90 As String
odmdnvevurdcl90 = ""
Dim bnugobuqhll79 As String
bnugobuqhll79 = ""
Dim qngvaiuagftdoo85 As String
qngvaiuagftdoo85 = ""
Dim sjtfkfebjhrkpr7 As String
sjtfkfebjhrkpr7 = ""
Dim abfjhtemugeanrrq58 As String
abfjhtemugeanrrq58 = ""
Dim dakrnhvajvb9 As String
dakrnhvajvb9 = ""
Dim vvlouksjtfkf92 As String
vvlouksjtfkf92 = ""
Dim madbghnbbfj74 As String
madbghnbbfj74 = ""
Dim eiihktadqavgijfq44 As String
eiihktadqavgijfq44 = ""
Dim mhqmioslkffruepcpdl22 As String
mhqmioslkffruepcpdl22 = ""
If (CurrPercent <> 100) Then RaiseEvent Progress(100)
Dim cbugeobmonstd17 As String
cbugeobmonstd17 = ""
Dim otektosgeqrjrubtk50 As String
otektosgeqrjrubtk50 = ""
Dim vashtkjbtfb75 As String
vashtkjbtfb75 = ""
Dim miekphhcshr17 As String
miekphhcshr17 = ""
Dim nltrfodvudkqdu75 As String
nltrfodvudkqdu75 = ""
Dim lpdanofiquphff53 As String
lpdanofiquphff53 = ""
Dim dklnjukbqojsok52 As String
dklnjukbqojsok52 = ""
Dim hlueupeond11 As String
hlueupeond11 = ""
End Sub
Public Property Let Key(New_Value As String)
Dim a As Long
Dim B As Long
Dim Temp As Byte
Dim Key() As Byte
Dim KeyLen As Long
If (m_Key = New_Value) Then Exit Property
m_Key = New_Value
Key() = StrConv(m_Key, vbFromUnicode)
KeyLen = Len(m_Key)
For a = 0 To 255
m_sBox(a) = a
Next a
For a = 0 To 255
B = (B + m_sBox(a) + Key(a Mod KeyLen)) Mod 256
Temp = m_sBox(a)
m_sBox(a) = m_sBox(B)
m_sBox(B) = Temp
Next
End Property






