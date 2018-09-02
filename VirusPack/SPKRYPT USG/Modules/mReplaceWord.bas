Attribute VB_Name = "mReplaceWord"
' Replace a whole word

Public Function ReplaceWord(Source As String, Find As String, ReplaceStr As String, _
    Optional ByVal Start As Long = 1, Optional Count As Long = -1, _
    Optional Compare As VbCompareMethod = vbBinaryCompare) As String

    Dim findLen As Long
    Dim replaceLen As Long
    Dim index As Long
    Dim counter As Long
    Dim charcode As Long
    Dim replaceIt As Boolean
    
    findLen = Len(Find)
    replaceLen = Len(ReplaceStr)
    
    ' this prevents an endless loop
    If findLen = 0 Then Err.Raise 5
    
    If Start < 1 Then Start = 1
    index = Start
    
    ' let's start by assigning the source to the result
    ReplaceWord = Source
    
    Do
        index = InStr(index, ReplaceWord, Find, Compare)
        If index = 0 Then Exit Do
        
        replaceIt = False
        ' check that it is preceded by a punctuation symbol
        If index > 1 Then
            charcode = Asc(UCase$(Mid$(ReplaceWord, index - 1, 1)))
        Else
            charcode = 32
        End If
        If charcode < 65 Or charcode > 90 Then
            ' check that it is followed by a punctuation symbol
            charcode = Asc(UCase$(Mid$(ReplaceWord, index + Len(Find), _
                1)) & " ")
            If charcode < 65 Or charcode > 90 Then
                replaceIt = True
            End If
        End If
        
        If replaceIt Then
            ' do the replacement
            ReplaceWord = Left$(ReplaceWord, index - 1) & ReplaceStr & Mid$ _
                (ReplaceWord, index + findLen)
            ' skip over the string just added
            index = index + replaceLen
            ' increment the replacement counter
            counter = counter + 1
        Else
            ' skip over this false match
            index = index + findLen
        End If
        
        ' Note that the Loop Until test will always fail if Count = -1
    Loop Until counter = Count
    
End Function

