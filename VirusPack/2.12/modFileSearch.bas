Attribute VB_Name = "modFileSearch"
Option Explicit

Private Const vbDot = 46
Private Const MAX_PATH = 260
Private Const INVALID_HANDLE_VALUE = -1

Private Type FILETIME
   dwLowDateTime As Long
   dwHighDateTime As Long
End Type

Private Type WIN32_FIND_DATA
   dwFileAttributes As Long
   ftCreationTime As FILETIME
   ftLastAccessTime As FILETIME
   ftLastWriteTime As FILETIME
   nFileSizeHigh As Long
   nFileSizeLow As Long
   dwReserved0 As Long
   dwReserved1 As Long
   cFileName As String * MAX_PATH
   cAlternate As String * 14
End Type

Private Declare Function FindClose Lib "kernel32" (ByVal hFindFile As Long) As Long
Private Declare Function FindFirstFile Lib "kernel32" Alias "FindFirstFileA" (ByVal lpFileName As String, lpFindFileData As WIN32_FIND_DATA) As Long
Private Declare Function FindNextFile Lib "kernel32" Alias "FindNextFileA" (ByVal hFindFile As Long, lpFindFileData As WIN32_FIND_DATA) As Long

Public Declare Function lstrlen Lib "kernel32" Alias "lstrlenW" (ByVal lpString As Long) As Long

Private Declare Function PathMatchSpec Lib "shlwapi" Alias "PathMatchSpecW" (ByVal pszFileParam As Long, ByVal pszSpec As Long) As Long

Public Sub SearchForFiles(sRoot As String, sFileNameExt As String, bRecurse As Boolean, ByRef strFiles() As String, ByRef lngFileCount As Long)
    On Local Error Resume Next
    Dim WFD As WIN32_FIND_DATA
    Dim hFile As Long
  
    hFile = FindFirstFile(sRoot & "*.*", WFD)
  
    If hFile <> INVALID_HANDLE_VALUE Then
        Do
            'if a folder, and recurse specified, call
            'method again
            If (WFD.dwFileAttributes And vbDirectory) Then
                If Asc(WFD.cFileName) <> vbDot Then
                    If bRecurse Then
                        Call SearchForFiles(sRoot & TrimNull(WFD.cFileName) & "\", sFileNameExt, bRecurse, strFiles, lngFileCount)
                    End If
                End If
            Else
                'must be a file..
                If MatchSpec(WFD.cFileName, sFileNameExt) Then
                    ReDim Preserve strFiles(lngFileCount)
                    strFiles(lngFileCount) = sRoot & TrimNull(WFD.cFileName)
                    lngFileCount = lngFileCount + 1
                End If  'If MatchSpec
            End If 'If WFD.dwFileAttributes
        Loop While FindNextFile(hFile, WFD)
    End If 'If hFile
  
   Call FindClose(hFile)
End Sub

Private Function MatchSpec(sFile As String, sSpec As String) As Boolean
   MatchSpec = PathMatchSpec(StrPtr(sFile), StrPtr(sSpec))
End Function
