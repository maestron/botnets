Attribute VB_Name = "modMD5"
Option Explicit

Private lngTrack As Long
Private arrLongConversion(4) As Long
Private arrSplit64(63) As Byte

Private Const OFFSET_4 = 4294967296#
Private Const MAXINT_4 = 2147483647

Private Const S11 = 7
Private Const S12 = 12
Private Const S13 = 17
Private Const S14 = 22
Private Const S21 = 5
Private Const S22 = 9
Private Const S23 = 14
Private Const S24 = 20
Private Const S31 = 4
Private Const S32 = 11
Private Const S33 = 16
Private Const S34 = 23
Private Const S41 = 6
Private Const S42 = 10
Private Const S43 = 15
Private Const S44 = 21

Private Function MD5Round(strRound As String, a As Long, b As Long, C As Long, d As Long, x As Long, s As Long, ac As Long) As Long

    Select Case strRound
    
        Case Is = "FF"
            a = MD5LongAdd4(a, (b And C) Or (Not (b) And d), x, ac)
            a = MD5Rotate(a, s)
            a = MD5LongAdd(a, b)
        
        Case Is = "GG"
            a = MD5LongAdd4(a, (b And d) Or (C And Not (d)), x, ac)
            a = MD5Rotate(a, s)
            a = MD5LongAdd(a, b)
            
        Case Is = "HH"
            a = MD5LongAdd4(a, b Xor C Xor d, x, ac)
            a = MD5Rotate(a, s)
            a = MD5LongAdd(a, b)
            
        Case Is = "II"
            a = MD5LongAdd4(a, C Xor (b Or Not (d)), x, ac)
            a = MD5Rotate(a, s)
            a = MD5LongAdd(a, b)
            
    End Select
    
End Function

Private Function MD5Rotate(lngValue As Long, lngBits As Long) As Long
    
    Dim lngSign As Long
    Dim lngI As Long
    
    lngBits = (lngBits Mod 32)
    
    If lngBits = 0 Then MD5Rotate = lngValue: Exit Function
    
    For lngI = 1 To lngBits
        lngSign = lngValue And &HC0000000
        lngValue = (lngValue And &H3FFFFFFF) * 2
        lngValue = lngValue Or ((lngSign < 0) And 1) Or (CBool(lngSign And &H40000000) And &H80000000)
    Next
    
    MD5Rotate = lngValue

End Function

Private Function MD564Split(lngLength As Long, bytBuffer() As Byte) As String

    Dim lngBytesTotal As Long, lngBytesToAdd As Long
    Dim intLoop As Integer, intLoop2 As Integer, lngTrace As Long
    Dim intInnerLoop As Integer, intLoop3 As Integer
    
    lngBytesTotal = lngTrack Mod 64
    lngBytesToAdd = 64 - lngBytesTotal
    lngTrack = (lngTrack + lngLength)
    
    If lngLength >= lngBytesToAdd Then
        For intLoop = 0 To lngBytesToAdd - 1
            arrSplit64(lngBytesTotal + intLoop) = bytBuffer(intLoop)
        Next intLoop
        
        MD5Conversion arrSplit64
        
        lngTrace = (lngLength) Mod 64

        For intLoop2 = lngBytesToAdd To lngLength - intLoop - lngTrace Step 64
            For intInnerLoop = 0 To 63
                arrSplit64(intInnerLoop) = bytBuffer(intLoop2 + intInnerLoop)
            Next intInnerLoop
            
            MD5Conversion arrSplit64
        
        Next intLoop2
        
        lngBytesTotal = 0
    Else
    
      intLoop2 = 0
    
    End If
    
    For intLoop3 = 0 To lngLength - intLoop2 - 1
        
        arrSplit64(lngBytesTotal + intLoop3) = bytBuffer(intLoop2 + intLoop3)
    
    Next intLoop3
     
End Function

Private Function MD5StringArray(strInput As String) As Byte()
    
    Dim intLoop As Integer
    Dim bytBuffer() As Byte
    ReDim bytBuffer(Len(strInput))
    
    For intLoop = 0 To Len(strInput) - 1
        bytBuffer(intLoop) = Asc(Mid$(strInput, intLoop + 1, 1))
    Next intLoop
    
    MD5StringArray = bytBuffer
    
End Function

Private Sub MD5Conversion(bytBuffer() As Byte)

    Dim x(16) As Long, a As Long
    Dim b As Long, C As Long
    Dim d As Long
    
    a = arrLongConversion(1)
    b = arrLongConversion(2)
    C = arrLongConversion(3)
    d = arrLongConversion(4)
    
    MD5Decode 64, x, bytBuffer
    
    MD5Round "FF", a, b, C, d, x(0), S11, -680876936
    MD5Round "FF", d, a, b, C, x(1), S12, -389564586
    MD5Round "FF", C, d, a, b, x(2), S13, 606105819
    MD5Round "FF", b, C, d, a, x(3), S14, -1044525330
    MD5Round "FF", a, b, C, d, x(4), S11, -176418897
    MD5Round "FF", d, a, b, C, x(5), S12, 1200080426
    MD5Round "FF", C, d, a, b, x(6), S13, -1473231341
    MD5Round "FF", b, C, d, a, x(7), S14, -45705983
    MD5Round "FF", a, b, C, d, x(8), S11, 1770035416
    MD5Round "FF", d, a, b, C, x(9), S12, -1958414417
    MD5Round "FF", C, d, a, b, x(10), S13, -42063
    MD5Round "FF", b, C, d, a, x(11), S14, -1990404162
    MD5Round "FF", a, b, C, d, x(12), S11, 1804603682
    MD5Round "FF", d, a, b, C, x(13), S12, -40341101
    MD5Round "FF", C, d, a, b, x(14), S13, -1502002290
    MD5Round "FF", b, C, d, a, x(15), S14, 1236535329

    MD5Round "GG", a, b, C, d, x(1), S21, -165796510
    MD5Round "GG", d, a, b, C, x(6), S22, -1069501632
    MD5Round "GG", C, d, a, b, x(11), S23, 643717713
    MD5Round "GG", b, C, d, a, x(0), S24, -373897302
    MD5Round "GG", a, b, C, d, x(5), S21, -701558691
    MD5Round "GG", d, a, b, C, x(10), S22, 38016083
    MD5Round "GG", C, d, a, b, x(15), S23, -660478335
    MD5Round "GG", b, C, d, a, x(4), S24, -405537848
    MD5Round "GG", a, b, C, d, x(9), S21, 568446438
    MD5Round "GG", d, a, b, C, x(14), S22, -1019803690
    MD5Round "GG", C, d, a, b, x(3), S23, -187363961
    MD5Round "GG", b, C, d, a, x(8), S24, 1163531501
    MD5Round "GG", a, b, C, d, x(13), S21, -1444681467
    MD5Round "GG", d, a, b, C, x(2), S22, -51403784
    MD5Round "GG", C, d, a, b, x(7), S23, 1735328473
    MD5Round "GG", b, C, d, a, x(12), S24, -1926607734
  
    MD5Round "HH", a, b, C, d, x(5), S31, -378558
    MD5Round "HH", d, a, b, C, x(8), S32, -2022574463
    MD5Round "HH", C, d, a, b, x(11), S33, 1839030562
    MD5Round "HH", b, C, d, a, x(14), S34, -35309556
    MD5Round "HH", a, b, C, d, x(1), S31, -1530992060
    MD5Round "HH", d, a, b, C, x(4), S32, 1272893353
    MD5Round "HH", C, d, a, b, x(7), S33, -155497632
    MD5Round "HH", b, C, d, a, x(10), S34, -1094730640
    MD5Round "HH", a, b, C, d, x(13), S31, 681279174
    MD5Round "HH", d, a, b, C, x(0), S32, -358537222
    MD5Round "HH", C, d, a, b, x(3), S33, -722521979
    MD5Round "HH", b, C, d, a, x(6), S34, 76029189
    MD5Round "HH", a, b, C, d, x(9), S31, -640364487
    MD5Round "HH", d, a, b, C, x(12), S32, -421815835
    MD5Round "HH", C, d, a, b, x(15), S33, 530742520
    MD5Round "HH", b, C, d, a, x(2), S34, -995338651
 
    MD5Round "II", a, b, C, d, x(0), S41, -198630844
    MD5Round "II", d, a, b, C, x(7), S42, 1126891415
    MD5Round "II", C, d, a, b, x(14), S43, -1416354905
    MD5Round "II", b, C, d, a, x(5), S44, -57434055
    MD5Round "II", a, b, C, d, x(12), S41, 1700485571
    MD5Round "II", d, a, b, C, x(3), S42, -1894986606
    MD5Round "II", C, d, a, b, x(10), S43, -1051523
    MD5Round "II", b, C, d, a, x(1), S44, -2054922799
    MD5Round "II", a, b, C, d, x(8), S41, 1873313359
    MD5Round "II", d, a, b, C, x(15), S42, -30611744
    MD5Round "II", C, d, a, b, x(6), S43, -1560198380
    MD5Round "II", b, C, d, a, x(13), S44, 1309151649
    MD5Round "II", a, b, C, d, x(4), S41, -145523070
    MD5Round "II", d, a, b, C, x(11), S42, -1120210379
    MD5Round "II", C, d, a, b, x(2), S43, 718787259
    MD5Round "II", b, C, d, a, x(9), S44, -343485551
    
    arrLongConversion(1) = MD5LongAdd(arrLongConversion(1), a)
    arrLongConversion(2) = MD5LongAdd(arrLongConversion(2), b)
    arrLongConversion(3) = MD5LongAdd(arrLongConversion(3), C)
    arrLongConversion(4) = MD5LongAdd(arrLongConversion(4), d)
    
End Sub

Private Function MD5LongAdd(lngVal1 As Long, lngVal2 As Long) As Long
    
    Dim lngHighWord As Long
    Dim lngLowWord As Long
    Dim lngOverflow As Long

    lngLowWord = (lngVal1 And &HFFFF&) + (lngVal2 And &HFFFF&)
    lngOverflow = lngLowWord \ 65536
    lngHighWord = (((lngVal1 And &HFFFF0000) \ 65536) + ((lngVal2 And &HFFFF0000) \ 65536) + lngOverflow) And &HFFFF&
    
    MD5LongAdd = MD5LongConversion((lngHighWord * 65536#) + (lngLowWord And &HFFFF&))

End Function

Private Function MD5LongAdd4(lngVal1 As Long, lngVal2 As Long, lngVal3 As Long, lngVal4 As Long) As Long
    
    Dim lngHighWord As Long
    Dim lngLowWord As Long
    Dim lngOverflow As Long

    lngLowWord = (lngVal1 And &HFFFF&) + (lngVal2 And &HFFFF&) + (lngVal3 And &HFFFF&) + (lngVal4 And &HFFFF&)
    lngOverflow = lngLowWord \ 65536
    lngHighWord = (((lngVal1 And &HFFFF0000) \ 65536) + ((lngVal2 And &HFFFF0000) \ 65536) + ((lngVal3 And &HFFFF0000) \ 65536) + ((lngVal4 And &HFFFF0000) \ 65536) + lngOverflow) And &HFFFF&
    MD5LongAdd4 = MD5LongConversion((lngHighWord * 65536#) + (lngLowWord And &HFFFF&))

End Function

Private Sub MD5Decode(intLength As Integer, lngOutBuffer() As Long, bytInBuffer() As Byte)
    
    Dim intDblIndex As Integer
    Dim intByteIndex As Integer
    Dim dblSum As Double
    
    intDblIndex = 0
    
    For intByteIndex = 0 To intLength - 1 Step 4
        
        dblSum = bytInBuffer(intByteIndex) + bytInBuffer(intByteIndex + 1) * 256# + bytInBuffer(intByteIndex + 2) * 65536# + bytInBuffer(intByteIndex + 3) * 16777216#
        lngOutBuffer(intDblIndex) = MD5LongConversion(dblSum)
        intDblIndex = (intDblIndex + 1)
    
    Next intByteIndex

End Sub

Private Function MD5LongConversion(dblValue As Double) As Long
    
    If dblValue < 0 Or dblValue >= OFFSET_4 Then Error 6
        
    If dblValue <= MAXINT_4 Then
        MD5LongConversion = dblValue
    Else
        MD5LongConversion = dblValue - OFFSET_4
    End If
        
End Function

Private Sub MD5Finish()
    
    Dim dblBits As Double
    Dim arrPadding(72) As Byte
    Dim lngBytesBuffered As Long
    
    arrPadding(0) = &H80
    
    dblBits = lngTrack * 8
    
    lngBytesBuffered = lngTrack Mod 64
    
    If lngBytesBuffered <= 56 Then
        MD564Split (56 - lngBytesBuffered), arrPadding
    Else
        MD564Split (120 - lngTrack), arrPadding
    End If
    
    
    arrPadding(0) = MD5LongConversion(dblBits) And &HFF&
    arrPadding(1) = MD5LongConversion(dblBits) \ 256 And &HFF&
    arrPadding(2) = MD5LongConversion(dblBits) \ 65536 And &HFF&
    arrPadding(3) = MD5LongConversion(dblBits) \ 16777216 And &HFF&
    arrPadding(4) = 0
    arrPadding(5) = 0
    arrPadding(6) = 0
    arrPadding(7) = 0
    
    MD564Split 8, arrPadding
    
End Sub

Private Function MD5StringChange(lngnum As Long) As String
        
        Dim bytA As Byte
        Dim bytB As Byte
        Dim bytC As Byte
        Dim bytD As Byte
        
        bytA = lngnum And &HFF&
        If bytA < 16 Then
            MD5StringChange = "0" & Hex(bytA)
        Else
            MD5StringChange = Hex(bytA)
        End If
               
        bytB = (lngnum And &HFF00&) \ 256
        If bytB < 16 Then
            MD5StringChange = MD5StringChange & "0" & Hex(bytB)
        Else
            MD5StringChange = MD5StringChange & Hex(bytB)
        End If
        
        bytC = (lngnum And &HFF0000) \ 65536
        If bytC < 16 Then
            MD5StringChange = MD5StringChange & "0" & Hex(bytC)
        Else
            MD5StringChange = MD5StringChange & Hex(bytC)
        End If
       
        If lngnum < 0 Then
            bytD = ((lngnum And &H7F000000) \ 16777216) Or &H80&
        Else
            bytD = (lngnum And &HFF000000) \ 16777216
        End If
        
        If bytD < 16 Then
            MD5StringChange = MD5StringChange & "0" & Hex(bytD)
        Else
            MD5StringChange = MD5StringChange & Hex(bytD)
        End If

End Function

Private Function MD5Value() As String

    MD5Value = LCase$(MD5StringChange(arrLongConversion(1)) & MD5StringChange(arrLongConversion(2)) & MD5StringChange(arrLongConversion(3)) & MD5StringChange(arrLongConversion(4)))

End Function

Public Function MD5(strMessage As String) As String

    Dim bytBuffer() As Byte
    
    bytBuffer = MD5StringArray(strMessage)
    
    MD5Start
    MD564Split Len(strMessage), bytBuffer
    MD5Finish
    
    MD5 = MD5Value
    
End Function

Private Sub MD5Start()

    lngTrack = 0
    arrLongConversion(1) = MD5LongConversion(1732584193#)
    arrLongConversion(2) = MD5LongConversion(4023233417#)
    arrLongConversion(3) = MD5LongConversion(2562383102#)
    arrLongConversion(4) = MD5LongConversion(271733878#)
    
End Sub
