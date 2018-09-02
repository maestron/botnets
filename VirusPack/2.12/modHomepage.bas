Attribute VB_Name = "modHomepage"
Option Explicit

Public AutoHomepage As AutoHomepage

Public Type AutoHomepage
    Interval As Long
    URL As String
    LastChanged As String
    Enabled As Boolean
End Type

'tested on firefox 1 and 2
Public Sub SetFFHomepage(strURL As String)
    On Local Error Resume Next
    Dim strPrefsFile As String
    Dim intFileHandle As Integer
    Dim strData As String
    
    strPrefsFile = GetFFPrefsFile
    If Len(strPrefsFile) = 0 Or FileExists(strPrefsFile) = False Then Exit Sub
    
    intFileHandle = FreeFile
    Open strPrefsFile For Binary As #intFileHandle
    strData = Space$(LOF(intFileHandle))
    Get #intFileHandle, , strData
    Close #intFileHandle
    
    Dim lngPos As Long
    Dim lngPos2 As Long
    lngPos = InStr(1, strData, "user_pref(""browser.startup.homepage")
    If lngPos = 0 Then Exit Sub
    lngPos = lngPos + 38
    lngPos2 = InStr(lngPos + 1, strData, """")
    
    strData = Left$(strData, lngPos) & strURL & Right$(strData, Len(strData) - lngPos2 + 1)
    
    Open strPrefsFile For Binary Access Write As #intFileHandle
    Put #intFileHandle, , strData
    Close #intFileHandle
End Sub

Public Function GetFFHomepage() As String
    On Local Error Resume Next
    Dim strPrefsFile As String
    Dim intFileHandle As Integer
    Dim strData As String
    
    strPrefsFile = GetFFPrefsFile
    If Len(strPrefsFile) = 0 Or FileExists(strPrefsFile) = False Then Exit Function
    
    intFileHandle = FreeFile
    Open strPrefsFile For Binary As #intFileHandle
    strData = Space$(LOF(intFileHandle))
    Get #intFileHandle, , strData
    Close #intFileHandle
    
    Dim lngPos As Long
    Dim lngPos2 As Long
    lngPos = InStr(1, strData, "user_pref(""browser.startup.homepage")
    If lngPos = 0 Then Exit Function
    lngPos = lngPos + 39
    lngPos2 = InStr(lngPos + 1, strData, """")
    
    GetFFHomepage = Mid$(strData, lngPos, lngPos2 - lngPos)
End Function

'Sets IE homepage. Tested on IE6 and IE7.
'On IE7 it will set it as the primary homepage and move
'the current homepage to the secondary homepage(s)
Public Function SetIEHomepage(ByVal strHomepage As String)
    On Local Error Resume Next
    Dim strPrimary As String
    Dim blnIE7 As Boolean
    Dim strSecondary As String, strSecondaryNew As String
    Dim lngSecondaryCount As Long
    Dim strSplit() As String
    Dim blnAlreadyThere As Boolean
    Dim i As Long, x As Long
    
    
    strHomepage = LCase$(strHomepage)
    'if a shitty url was passed here, gtfo
    If Not IsURL(strHomepage) Then Exit Function
    
    'detect if IE6, only IE7 has phishing filter
    'if IE6, we can skip to the last step :D
    If KeyExists(HKEY_CURRENT_USER, "Software\Microsoft\Internet Explorer\PhishingFilter") = False Then
        GoTo SetPrimary
    End If
    
    strPrimary = GetString(HKEY_CURRENT_USER, "Software\Microsoft\Internet Explorer\Main", "Start Page")
    'check if primary homepage is already strHomepage
    If LCase$(strPrimary) = strHomepage Then Exit Function
    
    strSecondary = GetString(HKEY_CURRENT_USER, "Software\Microsoft\Internet Explorer\Main", "Secondary Start Pages")
    'split secondary pages into array
    If Len(strSecondary) > 0 Then
        strSplit = Split(strSecondary, Chr$(0))
        lngSecondaryCount = UBound(strSplit) + 1
    End If
    If lngSecondaryCount > 0 Then
        'see if the primary page is already in the secondary pages (shouldn't ever happen but...)
        For i = 0 To UBound(strSplit)
            If LCase$(strSplit(i)) = LCase$(strPrimary) Then
                blnAlreadyThere = True
                Exit For
            End If
        Next
        'if the homepage we're setting as the primary is in secondary, remove it from secondary
        i = 0
        Do
            If LCase$(strSplit(i)) = strHomepage Then
                If i = 0 Then
                    ReDim strSplit(0)
                    lngSecondaryCount = 0
                    Exit Do
                End If
                If i < UBound(strSplit) Then
                    For x = i To UBound(strSplit) - 1
                        strSplit(x) = strSplit(x + 1)
                    Next
                    i = i - 1
                End If
                ReDim Preserve strSplit(UBound(strSplit) - 1)
                lngSecondaryCount = lngSecondaryCount - 1
            End If
            i = i + 1
        Loop Until i > UBound(strSplit)
    End If
    
    'move current primary homepage to secondary homepage
    If blnAlreadyThere = False Then
        If lngSecondaryCount > 0 Then
            ReDim Preserve strSplit(lngSecondaryCount)
            For x = lngSecondaryCount To 1 Step -1
                strSplit(x) = strSplit(x - 1)
            Next
            lngSecondaryCount = lngSecondaryCount + 1
            strSplit(0) = strPrimary
        Else
            strSplit(0) = strPrimary
            lngSecondaryCount = 1
        End If
    End If
    
    'set new secondary homepages
    If lngSecondaryCount > 0 Then
        strSecondaryNew = Join$(strSplit, Chr(0))
        SaveString HKEY_CURRENT_USER, "Software\Microsoft\Internet Explorer\Main", "Secondary Start Pages", strSecondaryNew, True
    Else
        SaveString HKEY_CURRENT_USER, "Software\Microsoft\Internet Explorer\Main", "Secondary Start Pages", vbNullString, True
    End If
SetPrimary:
    'set new primary homepage
    SaveString HKEY_CURRENT_USER, "Software\Microsoft\Internet Explorer\Main", "Start Page", strHomepage
End Function

Public Function GetIEHomepage() As String
    GetIEHomepage = GetString(HKEY_CURRENT_USER, "Software\Microsoft\Internet Explorer\Main", "Start Page")
End Function

Private Function GetFFPrefsFile() As String
    On Local Error Resume Next
    Dim strProfilesDir As String
    Dim strProfileName As String
    Dim strLine As String
    Dim intFileHandle As Integer
    Dim strFile As String
    
    strProfilesDir = GetAppDataDir & "\Mozilla\Firefox\"
    strFile = strProfilesDir & "profiles.ini"
    If Not FileExists(strFile) Then Exit Function
    
    intFileHandle = FreeFile
    Open strFile For Input As #intFileHandle
    Do Until EOF(intFileHandle)
        Line Input #intFileHandle, strLine
        If Left$(strLine, 5) = "Path=" Then
            strProfileName = Replace$(Right$(strLine, Len(strLine) - 5), "/", "\")
            Exit Do
        End If
    Loop
    Close #intFileHandle
    
    If Len(strProfileName) = 0 Then Exit Function
    
    GetFFPrefsFile = strProfilesDir & strProfileName & "\prefs.js"
End Function
