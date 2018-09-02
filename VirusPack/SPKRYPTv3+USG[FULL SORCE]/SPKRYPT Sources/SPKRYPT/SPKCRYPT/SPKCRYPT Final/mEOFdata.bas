Attribute VB_Name = "mEOFdata"
Option Explicit
'thx to enzym !
Public Function ReadEOFData(sFilePath As String) As String
On Error GoTo Err:
Dim sFileBuf As String, sEOFBuf As String, sChar As String
Dim lFF As Long, lPos As Long, lPos2 As Long, lCount As Long
If Dir(sFilePath) = "" Then GoTo Err:
lFF = FreeFile
Open sFilePath For Binary As #lFF
sFileBuf = Space(LOF(lFF))
Get #lFF, , sFileBuf
Close #lFF
lPos = InStr(1, StrReverse(sFileBuf), GetNullBytes(30))
sEOFBuf = (Mid(StrReverse(sFileBuf), 1, lPos - 1))
ReadEOFData = StrReverse(sEOFBuf)
Err:
ReadEOFData = vbNullString
End Function
Sub WriteEOFData(sFilePath As String, sEOFData As String)
Dim sFileBuf As String
Dim lFF As Long
On Error Resume Next
If Dir(sFilePath) = "" Then Exit Sub
lFF = FreeFile
Open sFilePath For Binary As #lFF
sFileBuf = Space(LOF(lFF))
Get #lFF, , sFileBuf
Close #lFF
Kill sFilePath
lFF = FreeFile
Open sFilePath For Binary As #lFF
Put #lFF, , sFileBuf & sEOFData
Close #lFF
End Sub
Public Function GetNullBytes(lNum) As String
Dim sBuf As String
Dim i As Integer
For i = 1 To lNum
sBuf = sBuf & Chr(0)
Next
GetNullBytes = sBuf
End Function

