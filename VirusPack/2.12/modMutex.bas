Attribute VB_Name = "modMutex"
Option Explicit

'The API functions and constant for mutex manipulation
Private Declare Function CreateMutex Lib "kernel32" Alias "CreateMutexA" (ByVal lpMutexAttributes As Long, ByVal bInitialOwner As Long, ByVal lpName As String) As Long
Private Declare Function ReleaseMutex Lib "kernel32" (ByVal hMutex As Long) As Long
Private Declare Function WaitForSingleObject Lib "kernel32" (ByVal hHandle As Long, ByVal dwMilliseconds As Long) As Long
Private Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long
Private Const WAIT_OBJECT_0 As Long = &H0

'This variable will have the handle of the mutex
Private GMutex As Long

Public Function CheckAndCreateMutex() As Boolean
    'MutexString
    GMutex = CreateMutex(0&, 0&, MutexString)         'First, lets create the mutex
    
    If GMutex = 0 Then
        'error occured... start anyway?
        CheckAndCreateMutex = True
    Else
        If WaitForSingleObject(GMutex, 0&) = WAIT_OBJECT_0 Then     'The mutex is signaled and no other thread owns it.
            CheckAndCreateMutex = True
        Else
            CheckAndCreateMutex = False
            Call CloseHandle(GMutex)            'The already owned mutex has been opened
        End If
    End If
End Function

Public Sub MutexCleanUp()
    Call ReleaseMutex(GMutex)            'A thread should release the mutex when no longer needed.
End Sub
