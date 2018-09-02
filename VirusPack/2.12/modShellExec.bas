Attribute VB_Name = "modShellExec"
Option Explicit

Public Declare Function GetDesktopWindow Lib "user32" () As Long
Public Declare Function ShellExecute Lib "shell32.dll" Alias "ShellExecuteA" (ByVal hWnd As Long, ByVal lpOperation As String, ByVal lpFile As String, ByVal lpParameters As String, ByVal lpDirectory As String, ByVal nShowCmd As Long) As Long

Private Const ERROR_FILE_NOT_FOUND = 2&
Private Const ERROR_PATH_NOT_FOUND = 3&
Private Const ERROR_BAD_FORMAT = 11&
Private Const SE_ERR_ACCESSDENIED = 5        ' access denied
Private Const SE_ERR_ASSOCINCOMPLETE = 27
Private Const SE_ERR_DDEBUSY = 30
Private Const SE_ERR_DDEFAIL = 29
Private Const SE_ERR_DDETIMEOUT = 28
Private Const SE_ERR_DLLNOTFOUND = 32
Private Const SE_ERR_FNF = 2                ' file not found
Private Const SE_ERR_NOASSOC = 31
Private Const SE_ERR_PNF = 3                ' path not found
Private Const SE_ERR_OOM = 8                ' out of memory
Private Const SE_ERR_SHARE = 26

'SW_HIDE = 0
'SW_MAXIMIZE = 3
'SW_MINIMIZE = 6
'SW_SHOWMAXIMIZED = 3
'SW_SHOWMINIMIZED = 2
'SW_SHOWNORMAL = 1
'SW_SHOWNOACTIVATE = 4
'SW_SHOWNA = 8
'SW_SHOWMINNOACTIVE = 7
'SW_SHOWDEFAULT = 10
'SW_RESTORE = 9
'SW_SHOW = 5

Public Function ShellEx(ByVal sFile As String, Optional ByVal sParameters As String = "", Optional ByVal sDefaultDir As String = "", Optional lShowCmd As Long = 0) As Boolean
    Dim lR As Long
    'Dim lErr As Long, sErr As String
    
    On Local Error Resume Next
    lR = ShellExecute(GetForegroundWindow(), "open", sFile, sParameters, sDefaultDir, lShowCmd)
    
    If (lR < 0) Or (lR > 32) Then
        ShellEx = True
    Else
        ' raise an appropriate error:
        'lErr = vbObjectError + 1048 + lR
        'Select Case lR
        'Case 0
        '    lErr = 7: sErr = "Out of memory"
        'Case ERROR_FILE_NOT_FOUND
        '    lErr = 53: sErr = "File not found"
        'Case ERROR_PATH_NOT_FOUND
        '    lErr = 76: sErr = "Path not found"
        'Case ERROR_BAD_FORMAT
        '    sErr = "The executable file is invalid or corrupt"
        'Case SE_ERR_ACCESSDENIED
        '    lErr = 75: sErr = "Path/file access error"
        'Case SE_ERR_ASSOCINCOMPLETE
        '    sErr = "This file type does not have a valid file association."
        'Case SE_ERR_DDEBUSY
        '    lErr = 285: sErr = "The file could not be opened because the target application is busy. Please try again in a moment."
        'Case SE_ERR_DDEFAIL
        '    lErr = 285: sErr = "The file could not be opened because the DDE transaction failed. Please try again in a moment."
        'Case SE_ERR_DDETIMEOUT
        '    lErr = 286: sErr = "The file could not be opened due to time out. Please try again in a moment."
        'Case SE_ERR_DLLNOTFOUND
        '    lErr = 48: sErr = "The specified dynamic-link library was not found."
        'Case SE_ERR_FNF
        '    lErr = 53: sErr = "File not found"
        'Case SE_ERR_NOASSOC
        '    sErr = "No application is associated with this file type."
        'Case SE_ERR_OOM
        '    lErr = 7: sErr = "Out of memory"
        'Case SE_ERR_PNF
        '    lErr = 76: sErr = "Path not found"
        'Case SE_ERR_SHARE
        '    lErr = 75: sErr = "A sharing violation occurred."
        'Case Else
        '    sErr = "An error occurred occurred whilst trying to open or print the selected file."
        'End Select
        '
        'Err.Raise lErr, Client.EXEName & ".GShell", sErr
        ShellEx = False
    End If

End Function
