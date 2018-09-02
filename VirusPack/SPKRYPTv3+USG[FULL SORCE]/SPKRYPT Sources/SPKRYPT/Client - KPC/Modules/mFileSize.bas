Attribute VB_Name = "mFileSize"
Option Explicit
'---------------------------------------------------------------------------------------
' Module      : mFileSize
' DateTime    : 25/12/09 02:19
' Author      : Mi4night
' Mail        : mi4night@hotmail.com
' Usage       : At your own risk.
' Purpose     : Get the size of a file
' Distribution: You can freely use this code in your own
'               applications, but you may not reproduce
'               or publish this code on any web site,
'               online service, or distribute as source
'               on any media without express permission.
'---------------------------------------------------------------------------------------
Private Declare Function GetCompressedFileSize _
                Lib "kernel32" _
                Alias "GetCompressedFileSizeA" (ByVal lpFileName As String, _
                                                lpFileSizeHigh As Long) As Long

Public Function GetFileSize(FilePath As String) As String
    'Variable Declaration
    Dim FSize As Double
    
    'Verify that the FilePath is given
    If Len(FilePath) <> 0 Then
        
        'Getting FileSize in bit
        FSize = GetCompressedFileSize(FilePath, ByVal 0&)

        If FSize < "1024" Then
            GetFileSize = FSize & " Bytes"
        ElseIf FSize >= "1024" And FSize < "1048576" Then
            GetFileSize = Round(FSize / 1024, 2) & " KB"
        ElseIf FSize >= "1048576" Then
            GetFileSize = Round(FSize / 1048576, 2) & " MB"
        End If

    Else
        Exit Function
    End If

End Function

