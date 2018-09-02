Attribute VB_Name = "mHWID"
Private Declare Function GetVolumeInformation Lib "kernel32" Alias "GetVolumeInformationA" (ByVal lpRootPathName As String, ByVal pVolumeNameBuffer As String, ByVal nVolumeNameSize As Long, lpVolumeSerialNumber As Long, lpMaximumComponentLength As Long, lpFileSystemFlags As Long, ByVal lpFileSystemNameBuffer As String, ByVal nFileSystemNameSize As Long) As Long
Private Declare Function GetSystemDirectory Lib "kernel32" Alias "GetSystemDirectoryA" (ByVal lpBuffer As String, ByVal nSize As Long) As Long
Public Function GetVolumeID() As String
    Dim No As Long, szBuff As String * 256
   
    Call GetSystemDirectory(szBuff, 256)
    Call GetVolumeInformation(Left(szBuff, 3), vbNullString, 0, No, 0, 0, vbNullString, 0)
    GetVolumeID = CStr(No)
    GetVolumeID = encrypt(encrypt(GetVolumeID)) + "00000000"
    
    
End Function

Public Function encrypt(strInput As String)
    Dim n As Integer, i As Integer
    n = 13
    For i = 1 To Len(strInput)
        Mid(strInput, i, 1) = Chr(Asc(Mid(strInput, i, 1)) + n)
    Next i
    encrypt = strInput
End Function
