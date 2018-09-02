Attribute VB_Name = "modEncrypt"
'This module is a collection of the encryption shit
'It contains RC4 Encryption, yEncode, etc

Option Explicit
Dim s(0 To 255) As Integer 'S-Box
Dim i As Integer, j As Integer

'The RC4 encryption uses a randomly generated 256 bit key.
'This can be automatically generated with the configuration editor.
'SpazBot, SpazCrypt, and the configuration editor need the same keys.
Public Sub SetEncKey()
    s(0) = 63
    s(1) = 58
    s(2) = 13
    s(3) = 21
    s(4) = 3
    s(5) = 14
    s(6) = 56
    s(7) = 214
    s(8) = 111
    s(9) = 113
    s(10) = 38
    s(11) = 59
    s(12) = 99
    s(13) = 39
    s(14) = 4
    s(15) = 47
    s(16) = 61
    s(17) = 103
    s(18) = 21
    s(19) = 45
    s(20) = 81
    s(21) = 25
    s(22) = 58
    s(23) = 34
    s(24) = 97
    s(25) = 56
    s(26) = 19
    s(27) = 24
    s(28) = 26
    s(29) = 90
    s(30) = 95
    s(31) = 60
    s(32) = 60
    s(33) = 108
    s(34) = 99
    s(35) = 35
    s(36) = 78
    s(37) = 125
    s(38) = 119
    s(39) = 45
    s(40) = 124
    s(41) = 53
    s(42) = 49
    s(43) = 3
    s(44) = 14
    s(45) = 96
    s(46) = 42
    s(47) = 63
    s(48) = 3
    s(49) = 43
    s(50) = 110
    s(51) = 39
    s(52) = 75
    s(53) = 107
    s(54) = 2
    s(55) = 22
    s(56) = 36
    s(57) = 20
    s(58) = 14
    s(59) = 120
    s(60) = 12
    s(61) = 78
    s(62) = 41
    s(63) = 112
    s(64) = 101
    s(65) = 31
    s(66) = 67
    s(67) = 25
    s(68) = 39
    s(69) = 69
    s(70) = 45
    s(71) = 102
    s(72) = 62
    s(73) = 35
    s(74) = 69
    s(75) = 39
    s(76) = 4
    s(77) = 86
    s(78) = 61
    s(79) = 41
    s(80) = 89
    s(81) = 100
    s(82) = 11
    s(83) = 121
    s(84) = 95
    s(85) = 17
    s(86) = 107
    s(87) = 70
    s(88) = 82
    s(89) = 78
    s(90) = 16
    s(91) = 97
    s(92) = 4
    s(93) = 79
    s(94) = 106
    s(95) = 98
    s(96) = 118
    s(97) = 56
    s(98) = 16
    s(99) = 105
    s(100) = 19
    s(101) = 115
    s(102) = 78
    s(103) = 126
    s(104) = 6
    s(105) = 34
    s(106) = 74
    s(107) = 22
    s(108) = 59
    s(109) = 44
    s(110) = 80
    s(111) = 51
    s(112) = 115
    s(113) = 118
    s(114) = 62
    s(115) = 39
    s(116) = 0
    s(117) = 48
    s(118) = 9
    s(119) = 118
    s(120) = 32
    s(121) = 74
    s(122) = 110
    s(123) = 86
    s(124) = 118
    s(125) = 2
    s(126) = 52
    s(127) = 85
    s(128) = 36
    s(129) = 27
    s(130) = 30
    s(131) = 22
    s(132) = 5
    s(133) = 45
    s(134) = 111
    s(135) = 55
    s(136) = 7
    s(137) = 19
    s(138) = 21
    s(139) = 83
    s(140) = 37
    s(141) = 5
    s(142) = 120
    s(143) = 32
    s(144) = 2
    s(145) = 68
    s(146) = 92
    s(147) = 53
    s(148) = 33
    s(149) = 108
    s(150) = 113
    s(151) = 106
    s(152) = 66
    s(153) = 107
    s(154) = 124
    s(155) = 92
    s(156) = 86
    s(157) = 11
    s(158) = 29
    s(159) = 13
    s(160) = 35
    s(161) = 45
    s(162) = 65
    s(163) = 37
    s(164) = 115
    s(165) = 21
    s(166) = 35
    s(167) = 87
    s(168) = 118
    s(169) = 92
    s(170) = 123
    s(171) = 99
    s(172) = 56
    s(173) = 7
    s(174) = 72
    s(175) = 52
    s(176) = 60
    s(177) = 51
    s(178) = 56
    s(179) = 38
    s(180) = 56
    s(181) = 106
    s(182) = 54
    s(183) = 103
    s(184) = 107
    s(185) = 21
    s(186) = 13
    s(187) = 119
    s(188) = 24
    s(189) = 14
    s(190) = 57
    s(191) = 78
    s(192) = 38
    s(193) = 81
    s(194) = 77
    s(195) = 25
    s(196) = 80
    s(197) = 80
    s(198) = 126
    s(199) = 33
    s(200) = 6
    s(201) = 97
    s(202) = 77
    s(203) = 73
    s(204) = 103
    s(205) = 84
    s(206) = 84
    s(207) = 51
    s(208) = 85
    s(209) = 38
    s(210) = 40
    s(211) = 127
    s(212) = 56
    s(213) = 76
    s(214) = 108
    s(215) = 47
    s(216) = 79
    s(217) = 44
    s(218) = 118
    s(219) = 42
    s(220) = 49
    s(221) = 47
    s(222) = 27
    s(223) = 92
    s(224) = 97
    s(225) = 108
    s(226) = 21
    s(227) = 119
    s(228) = 15
    s(229) = 2
    s(230) = 20
    s(231) = 89
    s(232) = 108
    s(233) = 5
    s(234) = 98
    s(235) = 11
    s(236) = 37
    s(237) = 18
    s(238) = 48
    s(239) = 97
    s(240) = 1
    s(241) = 1
    s(242) = 126
    s(243) = 67
    s(244) = 21
    s(245) = 54
    s(246) = 40
    s(247) = 8
    s(248) = 35
    s(249) = 22
    s(250) = 11
    s(251) = 123
    s(252) = 19
    s(253) = 18
    s(254) = 86
    s(255) = 123
End Sub

'RC4
Public Function EnDeCrypt(plaintxt As String) As String
    On Local Error Resume Next
    Dim temp As Integer, a As Long, i As Integer, j As Integer, k As Integer
    Dim cipherby As Byte, cipher As String
    
    If Len(plaintxt) = 0 Then
        EnDeCrypt = vbNullString
        Exit Function
    End If
    
    SetEncKey

    For a = 1 To Len(plaintxt)
        i = (i + 1) Mod 256
        j = (j + s(i)) Mod 256
        ' Swap( S(i),S(j) )
        temp = s(i)
        s(i) = s(j)
        s(j) = temp
        'Generate Keybyte k
        k = s((s(i) + s(j)) Mod 256)
        'Plaintextbyte xor Keybyte
        cipherby = Asc(Mid$(plaintxt, a, 1)) Xor k
        cipher = cipher & Chr(cipherby)
    Next a
    EnDeCrypt = cipher
End Function

'Public Function UUDecode(ByVal InString As String) As String
'    On Local Error Resume Next
'    Dim OutString As String
'    Dim i As Long
'    Dim UnCodedArray() As Byte
'    Dim CodedArray() As Byte
'
'    If Len(InString) = 0 Then
'        UUDecode = ""
'        Exit Function
'    End If
'
'    'Convert the string to an array of bytes
'    StringToByteArray InString, UnCodedArray()
'
'    'Set up the array to recieve the decoded bytes
'    ReDim CodedArray((Len(InString) / 4) * 3)
'
'    For i = 0 To (Len(InString) / 4) - 1  'For i = 0 to 14
'        'Check for characters that should be spaces and convert them back
'        If (UnCodedArray(i * 4 + 0) = 96) Then UnCodedArray(i * 4 + 0) = 32
'        If (UnCodedArray(i * 4 + 1) = 96) Then UnCodedArray(i * 4 + 1) = 32
'        If (UnCodedArray(i * 4 + 2) = 96) Then UnCodedArray(i * 4 + 2) = 32
'        If (UnCodedArray(i * 4 + 3) = 96) Then UnCodedArray(i * 4 + 3) = 32
'
'        'Decode the 3 bytes
'        CodedArray(i * 3 + 0) = ((UnCodedArray(i * 4 + 0) - 32) * 4) + ((UnCodedArray(i * 4 + 1) - 32) \ 16) 'Calculate the 3 chars
'        CodedArray(i * 3 + 1) = ((UnCodedArray(i * 4 + 1) Mod 16) * 16) + ((UnCodedArray(i * 4 + 2) - 32) \ 4)
'        CodedArray(i * 3 + 2) = ((UnCodedArray(i * 4 + 2) Mod 4) * 64) + (UnCodedArray(i * 4 + 3) - 32)
'    Next i
'    ByteArrayToString CodedArray(), OutString
'    Do Until Right$(OutString, 1) <> Chr(0)
'        OutString = VBA.Left$(OutString, Len(OutString) - 1)
'    Loop
'    UUDecode = OutString
'End Function

'Takes sets of 3 characters (binary) and returns sets of 4 characters (ASCII)
'Public Function UUEncode(ByVal InString As String) As String
'    On Local Error Resume Next
'    Dim OutString As String
'    Dim i As Integer
'    Dim UnCodedArray() As Byte
'    Dim CodedArray() As Byte
'
'    If Len(InString) = 0 Then
'        UUEncode = ""
'        Exit Function
'    End If
'
'    'Pad with null characters if necessary
'    If Len(InString) Mod 3 <> 0 Then
'        InString = InString & String$(3 - Len(InString) Mod 3, Chr$(0))
'    End If
'
'    'Convert string to a byte array. This is MUCH faster than the Asc/Chr combo.
'    StringToByteArray InString, UnCodedArray()
'
'    'Make sure our output array is the correct size
'    ReDim CodedArray(((Len(InString) / 3) * 4) - 1)
'
'    For i = 0 To (Len(InString) / 3) - 1
'        'Encode 4 bytes at a time
'        CodedArray(i * 4 + 0) = UnCodedArray(i * 3 + 0) \ 4 + 32
'        CodedArray(i * 4 + 1) = ((UnCodedArray(i * 3 + 0) Mod 4) * 16) + (UnCodedArray(i * 3 + 1) \ 16 + 32)
'        CodedArray(i * 4 + 2) = ((UnCodedArray(i * 3 + 1) Mod 16) * 4) + (UnCodedArray(i * 3 + 2) \ 64 + 32)
'        CodedArray(i * 4 + 3) = (UnCodedArray(i * 3 + 2) Mod 64) + 32
'
'        'Check for spaces and eliminate them
'        If CodedArray(i * 4 + 0) = 32 Then CodedArray(i * 4 + 0) = 96
'        If CodedArray(i * 4 + 1) = 32 Then CodedArray(i * 4 + 1) = 96
'        If CodedArray(i * 4 + 2) = 32 Then CodedArray(i * 4 + 2) = 96
'        If CodedArray(i * 4 + 3) = 32 Then CodedArray(i * 4 + 3) = 96
'    Next i
'    ByteArrayToString CodedArray(), OutString
'    UUEncode = OutString
'End Function

Public Sub DecipherBArray(ByRef bArray() As Byte, lngnum As Long)
    Dim i As Long
    Dim lngNewByte As Long
    Dim lngLen As Long
    Dim bOut() As Byte
    
    lngLen = UBound(bArray)
    ReDim bOut(lngLen)
    For i = lngLen To 0 Step -1
        bOut((i - lngLen) * -1) = bArray(i)
    Next
    bArray = bOut
    
    For i = 0 To lngLen
        lngNewByte = bArray(i) - lngnum - (i Mod 10)
        If lngNewByte < 0 Then
            lngNewByte = lngNewByte + 256
        End If
        bArray(i) = lngNewByte
    Next
End Sub

Public Function yEncode(sString As String) As String
    On Local Error Resume Next
    Dim bOut() As Byte, bIn() As Byte, lChar As Long, lPos As Long, bTest As Byte, lLine As Long
    StringToByteArray sString, bIn 'Load the input string.
    ReDim bOut(UBound(bIn) * 2 + 2) 'Make the output buffer. Double size will almost always be enough. 2 extra
    'chars per 72 and worst case would be all characters escaped. If so, use Base64.
    
    If Len(sString) = 0 Then Exit Function
    
    For lChar = 0 To UBound(bIn)
        bTest = (bIn(lChar) + 42) Mod 256 'Try the preferred transform.

        Select Case bTest
            Case 1 To 8, 11 To 12, 14 To 45, 47 To 60, 62 To 255 'Normal processing
                bOut(lPos) = bTest
                lPos = lPos + 1
                lLine = lLine + 1
            Case 46 'Test For column one, escape If In that col.
                If lLine <> 0 Then
                    bOut(lPos) = bTest
                    lPos = lPos + 1
                    lLine = lLine + 1
                Else
                    bOut(lPos) = 61
                    bOut(lPos + 1) = (bTest + 64) Mod 256
                    lPos = lPos + 2
                    lLine = lLine + 2
                End If
            Case Else 'Critical char, needs To be escaped.
                bOut(lPos) = 61
                bOut(lPos + 1) = (bTest + 64) Mod 256
                lPos = lPos + 2
                lLine = lLine + 2
        End Select
    Next lChar
    
    ReDim Preserve bOut(lPos - 1) 'Truncate the unused portion of the buffer.
    ByteArrayToString bOut, yEncode
End Function

Public Function yDecode(sString As String) As String
    On Local Error Resume Next
    Dim bOut() As Byte, bIn() As Byte, bTest As Byte, bEscaped As Boolean, lPos As Long, lChar As Long
    StringToByteArray sString, bIn 'Load the input string.
    ReDim bOut(UBound(bIn)) 'There is no Case where the output will be larger.
    
    If Len(sString) = 0 Then Exit Function

    For lChar = 0 To UBound(bIn)
        If bIn(lChar) <> 61 Then
            bTest = ((bIn(lChar) + 256) - 42) Mod 256

            If bEscaped Then
                bTest = ((bTest + 256) - 64) Mod 256
                bEscaped = False
            End If
            bOut(lPos) = bTest
            lPos = lPos + 1
        Else
            bEscaped = True
        End If
    Next lChar
    
    ReDim Preserve bOut(lPos - 1) 'Truncate the unused portion of the buffer.
    ByteArrayToString bOut, yDecode 'Convert back To a String and return.
End Function

Public Function SCODecipherStr(sString As String) As String
    On Local Error Resume Next
    Dim bSCOOut() As Byte, bIn() As Byte, bTest As Byte, bEscaped As Boolean, lPos As Long, lChar As Long
    StringToByteArray sString, bIn 'Load the input string.
    ReDim bSCOOut(UBound(bIn)) 'There is no Case where the output will be larger.
    
    If Len(sString) = 0 Then Exit Function

    For lChar = 0 To UBound(bIn)
        If bIn(lChar) <> 61 Then
            bTest = ((bIn(lChar) + 256) - 42) Mod 256

            If bEscaped Then
                bTest = ((bTest + 256) - 64) Mod 256
                bEscaped = False
            End If
            bSCOOut(lPos) = bTest
            lPos = lPos + 1
        Else
            bEscaped = True
        End If
    Next lChar
    
    ReDim Preserve bSCOOut(lPos - 1) 'Truncate the unused portion of the buffer.
    
    'unfuck it up
DecipherBArray bSCOOut, 184
    
    ByteArrayToString bSCOOut, SCODecipherStr
End Function
