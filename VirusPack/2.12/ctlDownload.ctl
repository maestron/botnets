VERSION 5.00
Begin VB.UserControl ctlDownload 
   ClientHeight    =   3600
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   ScaleHeight     =   3600
   ScaleWidth      =   4800
End
Attribute VB_Name = "ctlDownload"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

'==============================================================================
'EVENTS
'==============================================================================

Public Event WinsockError(Description As String)
Public Event OtherError(Description As String, Number As Long)
Public Event Completed(lngFileSize As Long)

'==============================================================================
'CONSTANTS
'==============================================================================

Private Const USERAGENT_TOKEN As String = "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)"

'==============================================================================
'MEMBER VARIABLES
'==============================================================================

Private m_strURL As String
Private m_strHost As String
Private m_strDirectory As String
Private m_strDestination As String
Private m_blnRedirDisabled As Boolean
Private m_blnExecute As Boolean
Private m_lngCmdIndex As Long
Private m_blnInUse As Boolean
Private m_strCRC As String

Private m_strHeader As String
Private m_blnHeaderArrived As Boolean
Private m_intFileHandle As Integer

'our socket
Private WithEvents cmSocket As clsSocketPlus
Attribute cmSocket.VB_VarHelpID = -1

'==============================================================================
'PROPERTIES
'==============================================================================

'Public Property Get CRC() As String
'    CRC = m_strCRC
'End Property

Public Property Let CRC(strCRC As String)
    m_strCRC = strCRC
End Property

Public Property Get InUse() As Boolean
    InUse = m_blnInUse
End Property

'Public Property Let InUse(blnInUse As Boolean)
'    m_blnInUse = blnInUse
'End Property

Public Property Get Destination() As String
    Destination = m_strDestination
End Property

Public Property Let Destination(strDestination As String)
    m_strDestination = Trim$(strDestination)
End Property

Public Property Get Execute() As Boolean
    Execute = m_blnExecute
End Property

Public Property Let Execute(blnExecute As Boolean)
    m_blnExecute = blnExecute
End Property

Public Property Get CmdIndex() As Long
    CmdIndex = m_lngCmdIndex
End Property

Public Property Let CmdIndex(lngCmdIndex As Long)
    m_lngCmdIndex = lngCmdIndex
End Property

Public Property Get DisableRedirection() As Boolean
    DisableRedirection = m_blnRedirDisabled
End Property

Public Property Let DisableRedirection(blnRedir As Boolean)
    m_blnRedirDisabled = blnRedir
End Property

Public Sub Cancel()
    Reset
End Sub

Public Sub Download(URL As Variant, Destination As Variant, Optional blnExecute As Boolean)
    On Error GoTo Error_Handler
    Set cmSocket = New clsSocketPlus
    cmSocket.ArrayAdd 1
    
    If m_blnInUse = True Then
        RaiseEvent OtherError("Download control already in use.", 0)
    End If
    m_blnInUse = True
    
    If Not IsMissing(URL) Then
        m_strURL = Trim$(URL)
    End If
    
    If Not IsMissing(Destination) Then
        m_strDestination = Trim$(Destination)
    End If
    
    m_blnExecute = blnExecute
    
    If Len(m_strURL) = 0 Or Len(m_strDestination) = 0 Then Exit Sub
    
    Call ParseURL(m_strURL, m_strHost, m_strDirectory)
    
    cmSocket.Connect 1, m_strHost, 80
    
    Exit Sub
Error_Handler:
    Dim strErr As String
    Dim lngNumber As Long
    strErr = Err.Description
    lngNumber = Err.Number
    Reset
    RaiseEvent OtherError(strErr, lngNumber)
End Sub


Private Sub cmSocket_Connect(ByVal Index As Variant)
    On Error GoTo Error_Handler
    
    If FileExists(m_strDestination) Then
        Call DeleteFile(m_strDestination)
    End If
    
    m_intFileHandle = FreeFile
    
    'pop out a 0 byte file first, cause for some reason a few bots bitched case
    'the file wasn't there. Duh its not there, you're supposed to create it
    'yourself, you stupid piece of shit. But apparently it doesn't see it that way.
    Open m_strDestination For Output As #m_intFileHandle
    Close #m_intFileHandle
    
    Open m_strDestination For Binary Lock Read Write As #m_intFileHandle
    
    Dim strCommand As New clsStringBuilder
    
    strCommand.Append "GET " & m_strDirectory & " HTTP/1.0" & vbCrLf
    strCommand.Append "Accept: */*" & vbCrLf
    strCommand.Append "Referer: " & m_strHost & vbCrLf
    strCommand.Append "User-Agent: " & USERAGENT_TOKEN & vbCrLf
    strCommand.Append "Host: " & m_strHost & vbCrLf & vbCrLf
    
    cmSocket.SendData 1, strCommand.ToString
    
    Exit Sub
Error_Handler:
    Dim strErr As String
    Dim lngNumber As Long
    strErr = Err.Description
    lngNumber = Err.Number
    Reset
    RaiseEvent OtherError(strErr, lngNumber)
End Sub

Private Sub cmSocket_DataArrival(ByVal Index As Variant, ByVal bytesTotal As Long)
    On Error GoTo Error_Handler
    Dim strChunk As String
    cmSocket.GetData 1, strChunk
    
    'if header hasn't arrived
    If m_blnHeaderArrived = False Then
        
        m_strHeader = m_strHeader & strChunk
        
        Dim lngSplit As Long
        lngSplit = InStr(1, m_strHeader, vbCrLf & vbCrLf)
        
        'has the header finished on this chunk?
        If lngSplit = 0 Or lngSplit = Null Then Exit Sub
        
        'yes! the header has finished
        m_blnHeaderArrived = True
        
        'maybe this chunk is half header and half file
        'we split the two
        strChunk = Right$(m_strHeader, Len(m_strHeader) - lngSplit - 3)
        m_strHeader = VBA.Left$(m_strHeader, lngSplit + 3)
        
        'is redirection enabled?
        If m_blnRedirDisabled = False Then
            Dim strLocation As String
            strLocation = GetVariableValue(m_strHeader, "Location")
            'does the header indicates a redirection?
            If strLocation <> "" Then
                Reset
                
                If VBA.Left$(strLocation, 1) = "/" Then
                    m_strURL = m_strHost & strLocation
                    Call ParseURL(m_strURL, m_strHost, m_strDirectory)
                Else
                    m_strURL = strLocation
                    Call ParseURL(m_strURL, m_strHost, m_strDirectory)
                End If
                
                Call Download(m_strURL, m_strDirectory)
                Exit Sub
            End If
        End If
    End If
    
    'if header has arrived
    
    Put m_intFileHandle, LOF(m_intFileHandle) + 1, strChunk
    
    Exit Sub
Error_Handler:
    Dim strErr As String
    Dim lngNumber As Long
    strErr = Err.Description
    lngNumber = Err.Number
    Reset
    RaiseEvent OtherError(strErr, lngNumber)
End Sub

Private Sub cmSocket_CloseSck(ByVal Index As Variant)
    On Local Error Resume Next
    'some web pages don't have headers
    Dim lngFileSize As Long
    If m_blnHeaderArrived = False Then
        
        Dim strData As String
        strData = m_strHeader
        m_strHeader = ""
        
        Put m_intFileHandle, LOF(m_intFileHandle) + 1, strData
    End If
    
    'Check header to make sure download was a success
    Dim strSplit() As String
    strSplit = Split(m_strHeader, vbCrLf)
    If UBound(strSplit) > -1 Then
        If Not LCase$(strSplit(0)) Like "http* 200*" Then
            Reset
            RaiseEvent WinsockError("Non-successful HTTP response: " & strSplit(0))
            Call DeleteFile(m_strDestination)
            Exit Sub
        End If
    End If
    
    lngFileSize = LOF(m_intFileHandle)
    
    Close m_intFileHandle
    
    If Len(m_strCRC) > 0 Then
        Dim strCRC As String
        strCRC = Hex$(CalculateFile(m_strDestination))
        Dim strCRC2 As String
        strCRC2 = m_strCRC
        
        If strCRC <> strCRC2 Then
            Reset
            RaiseEvent OtherError("Bad File CRC: " & strCRC & " (Expecting " & strCRC2 & ")", 31337)
            Call DeleteFile(m_strDestination)
            Exit Sub
        End If
    End If

    Reset
    RaiseEvent Completed(lngFileSize)
End Sub

Private Sub cmSocket_Error(ByVal Index As Variant, ByVal Number As Integer, Description As String, ByVal sCode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
    Reset
    RaiseEvent WinsockError(Description)
End Sub

'get variable value from the header
Private Function GetVariableValue(ByRef strHeader As String, ByVal strVariable As String) As String
    On Local Error Resume Next
    Dim Init As Long
    Dim Last As Long
    
    Init = InStr(1, strHeader, strVariable, vbTextCompare)
    
    If Init = 0 Or Init = Null Then
        GetVariableValue = ""
        Exit Function
    End If
    
    Init = Init + Len(strVariable) + 1
    Last = InStr(Init, strHeader, vbCrLf, vbTextCompare)
    
    GetVariableValue = Trim$(Mid$(strHeader, Init, Last - Init))
End Function

'reset variables
Private Sub Reset()
    On Local Error Resume Next
    m_blnInUse = False
    'cmSocket.ArrayRemove 1
    Set cmSocket = Nothing
    m_strCRC = vbNullString
    m_strHeader = vbNullString
    m_blnHeaderArrived = False
    If m_intFileHandle <> 0 Then Close #m_intFileHandle
    m_intFileHandle = 0
End Sub

Private Sub UserControl_Terminate()
    Reset
End Sub
