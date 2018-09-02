VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsCPUID"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'==============================================================================
' cCPUID.cls - Class to retrieve the results of the CPUID op-code
'
' Copyright free, use as and how you please.
' Paul_Caton@hotmail.com
'==============================================================================
Option Explicit

'API declarations
Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)
Private Declare Function GlobalAlloc Lib "kernel32" (ByVal wFlags As Long, ByVal dwBytes As Long) As Long
Private Declare Function GlobalLock Lib "kernel32" (ByVal hMem As Long) As Long
Private Declare Function GlobalUnlock Lib "kernel32" (ByVal hMem As Long) As Long
Private Declare Function GlobalFree Lib "kernel32" (ByVal hMem As Long) As Long

Private Type tPD                                            'Proc Details type
  hMem  As Long                                             'Memory handle for new code
  pOld  As Long                                             'Pointer to old code
End Type

Private pMe         As Long                                 'Pointer to me, the class instance
Private nEntries    As Long                                 'Number of ProcDets entries
Private ProcDets()  As tPD                                  'Proc details array

'Retrieve the CPU clock cycle count into the Cycles parameter
Public Sub CpuClk(Cycles As Currency)
End Sub

'Execute the CPUID instruction at the indicated level, pass back the result registers
'Public Sub CpuID(ByVal nLevel As Long, _
'                 ByRef eax As Long, _
'                 ByRef ebx As Long, _
'                 ByRef ecx As Long, _
'                 ByRef edx As Long)
'End Sub

'Shift right the Value parameter by the Shift parameter number of bits and return the result
'Public Function ShiftRight(ByVal Value As Long, _
'                           ByVal Shift As Long) As Long
'End Function

'Replace the stub procs with our machine code routines
Private Sub Class_Initialize()
  Call CopyMemory(pMe, ByVal ObjPtr(Me), 4)                 'Get pointer to object Me
  
  'CpuClk
  Call InitCode("0F318B4C2408890189510433C0C20800")
  
  'CPUID
  'Call InitCode("558BEC83C4FC539C580FBAF815509D9C5A33C2740A33C033DB33C933D2EB058B450C0FA28955FC8B551089028B5514891A8B5518890A8B551C8B45FC89025B33C0C9C21800")
  
  'ShiftRight
  'Call InitCode("8B4424088B4C240C8B542410D3E8890233C0C21000")
End Sub

'Convert the hex pairs in the sCode parameter into bytes in allocated memory, patch the class instance's
'vtable to point to the new code, replacing the existing class methods in the order of their declaration
Private Sub InitCode(sCode As String)
Dim i     As Long, _
    j     As Long, _
    pNew  As Long, _
    pOld  As Long, _
    nLen  As Long, _
    nOff  As Long, _
    hMem  As Long, _
    b     As Byte
  
  On Error Resume Next
  
  nOff = &H1C + (nEntries * 4)                              'Calculate the vtable offset
  nLen = Len(sCode) \ 2                                     'Memory buffer length
  hMem = GlobalAlloc(0, nLen)                               'Allocate memory for the m/c and save handle
  pNew = GlobalLock(hMem)                                   'Get pointer to the locked/allocated memory
  
'Convert the string of opcodes from hex pairs to bytes and store in the allocated memory
  j = 1                                                     'Set the character index to the start of the opcode string
  For i = 0 To nLen - 1                                     'For each byte of the code buffer
    b = Val("&H" & Mid$(sCode, j, 2))                       'Pull a pair of hex characters and convert to a byte
    Call CopyMemory(ByVal pNew + i, b, 1)                   'Copy machine code byte to memory
    j = j + 2                                               'Bump to the next pair of characters
  Next i                                                    'Next byte of the code buffer
  
  Call CopyMemory(pOld, ByVal pMe + nOff, 4)                'Save old vtable code pointer
  Call CopyMemory(ByVal pMe + nOff, pNew, 4)                'Store the new vtable code pointer
  Call GlobalUnlock(hMem)                                   'Unlock memory

  nEntries = nEntries + 1                                   'Bump the entry count
  ReDim Preserve ProcDets(1 To nEntries)                    'Dimension the proc details array
  ProcDets(nEntries).hMem = hMem                            'Save memory handle
  ProcDets(nEntries).pOld = pOld                            'Save pointer to the old vtable code
End Sub

'Cleanup, restore the original vtable pointers
Private Sub Class_Terminate()
Dim i     As Long, _
    nOff  As Long, _
    pOld  As Long, _
    hMem  As Long
  
  On Error Resume Next
  
  For i = 1 To nEntries                                     'For each ProcDets entry
    nOff = &H1C + ((i - 1) * 4)                             'Calculate the vtable offset
    pOld = ProcDets(i).pOld                                 '
    hMem = ProcDets(i).hMem                                 '
    Call CopyMemory(ByVal pMe + nOff, pOld, 4)              'Restore old VT entry
    Call GlobalFree(hMem)                                   'Release the allocated memory
  Next i
    
  Erase ProcDets
End Sub
