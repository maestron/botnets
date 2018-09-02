Attribute VB_Name = "mPatchTheme"
Option Explicit
'
'   UxTheme patch to allow VB6 theming
'
'   Marko Matic (c)2005
'
'   License Agreement: Marko Matic is not responsible for any possible damage coused by this code
'
'

Private Declare Function PostMessage Lib "user32" Alias "PostMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
Private Declare Function GetCurrentProcess Lib "kernel32" () As Long
Private Declare Function GetModuleHandle Lib "kernel32" Alias "GetModuleHandleA" (ByVal lpModuleName As String) As Long
Private Declare Function GetProcAddress Lib "kernel32" (ByVal hModule As Long, ByVal lpProcName As String) As Long
Private Declare Function ReadProcessMemory Lib "kernel32" (ByVal hProcess As Long, lpBaseAddress As Any, lpBuffer As Any, ByVal nSize As Long, lpNumberOfBytesWritten As Long) As Long
Private Declare Function WriteProcessMemory Lib "kernel32" (ByVal hProcess As Long, lpBaseAddress As Any, lpBuffer As Any, ByVal nSize As Long, lpNumberOfBytesWritten As Long) As Long
Private Declare Sub SetThemeAppProperties Lib "uxtheme" (ByVal dwFlags As Long)

Private Declare Function ActivateWindowTheme Lib "uxtheme" _
    Alias "SetWindowTheme" ( _
    ByVal hwnd As Long, _
    Optional ByVal pszSubAppName As Long = 0, _
    Optional ByVal pszSubIdList As Long = 0) As Long
    
    
Private Declare Function DeactivateWindowTheme Lib "uxtheme" _
    Alias "SetWindowTheme" ( _
     ByVal hwnd As Long, _
     Optional ByRef pszSubAppName As String = " ", _
     Optional ByRef pszSubIdList As String = " ") As Long
    
  
Public Enum eTrickResult
    DTT_SUCCESS = 0
    DTT_ERROR = 1
    DTT_MODULE_NOT_LOADED = 2           'wrong windows version(not XP or something)
    DTT_API_NOT_EXPORTED = 3            'uxtheme is here but api isn't (very strange)
    DTT_WRONG_VERSION = 4               'we can't find our search strings... (bad)
    DTT_PECH_BURNED_OUT = 5             'patch didn't hold...
End Enum
Private ThemesPossible As Boolean
    
 
Public Function DoTheTrick() As eTrickResult
    Dim DTT_Result As eTrickResult

    Dim hProcess            As Long                 'process handle
    Dim hUxTheme            As Long                 'Uxtheme.dll handle(base address)
    Dim hDraw               As Long                 'API DrawThemeParentBackground address
    Dim strBuf              As String               'bytes from DrawThemeParentBackground

    Dim strSearch1          As String
    Dim strSearch2          As String

    Dim strPatch1           As String               'bytes with which we are going to patch
    Dim lngPatch2           As Long
    Dim lPatch1Address      As Long                 'position of first patch
    Dim lPatch2Address      As Long                 'position of second patch

    Dim lPoz                As Long
    Dim lw                  As Long

    Dim lAddresToJMP        As Long

    strBuf = Space(400)                         'buffer of 400 characters, more than enough...
    strSearch1 = "83F8020F84"
    strSearch2 = "3BF70F85"
    strPatch1 = "90E9"                          'sa ovim(ovaj patch je za OptButone unutar frejma)"
    lngPatch2 = 0                               'since we don't know where to jump we shall calculate it a bit latter
        

    DTT_Result = DTT_SUCCESS

    On Error GoTo doError


    hProcess = GetCurrentProcess                    'pseudo handle to our process(might change in future says MS. It's -1 now)
    hUxTheme = GetModuleHandle("uxtheme.dll")       'handle to dll

    If hUxTheme > 0 Then                            'in case we got handle
    
        ThemesPossible = True
    
        hDraw = GetProcAddress(hUxTheme, "DrawThemeParentBackground")   'address of function
    
        If hDraw > 0 Then                       'if we got handle let's try searching
        
            ReadProcessMemory hProcess, ByVal hDraw, ByVal strBuf, Len(strBuf), lw      'read memomry from API function
        
        
            lPatch1Address = FindStringPosition(strBuf, strSearch1, 2)
            lPatch2Address = FindStringPosition(strBuf, strSearch2, 3)
                    
            If lPatch2Address > 0 Then
                lngPatch2 = doFindPatch2JmpPosition(strBuf, lPatch2Address)
            End If
                    
                                
            If lPatch1Address > 0 And lPatch2Address > 0 And lngPatch2 > 0 Then
                lPatch1Address = lPatch1Address + hDraw
                lPatch2Address = lPatch2Address + hDraw
                    
                strPatch1 = doChar(strPatch1)
                WriteProcessMemory hProcess, ByVal lPatch1Address, ByVal strPatch1, Len(strPatch1), lw
                WriteProcessMemory hProcess, ByVal lPatch2Address, lngPatch2, Len(lngPatch2), lw
                    
                DTT_Result = DTT_SUCCESS
            Else
                DTT_Result = DTT_WRONG_VERSION
            End If


        Else
            DTT_Result = DTT_API_NOT_EXPORTED
        End If
        If DTT_Result <> DTT_SUCCESS Then
            SetThemeAppProperties 0             'turning theme off
        End If
    
        DoTheTrick = DTT_Result
    Else
        DoTheTrick = DTT_MODULE_NOT_LOADED
    End If
    Exit Function
doError:
    SetThemeAppProperties 0             'this is FailSafe...turning theme off in case of any error
    DoTheTrick = DTT_WRONG_VERSION


End Function

Public Function ThemeAllForms(ByVal TrueFalse As Boolean)
'XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
'X
'XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
Dim frmF As Form
    If IsThemePossible Then
        
        If TrueFalse Then
            SetThemeAppProperties 3
        Else
            SetThemeAppProperties 0
        End If
        
        For Each frmF In Forms
        
            PostMessage frmF.hwnd, &H31A, 1, 1
            PostMessage frmF.hwnd, &H31B, 1, 1
            
        Next
    End If
End Function
    
Public Function SetWindowTheme(ByVal hwnd As Long, ByVal TrueFalse As Boolean) As Long
    If IsThemePossible Then
        If TrueFalse Then
            SetWindowTheme = ActivateWindowTheme(hwnd)
        Else
            SetWindowTheme = DeactivateWindowTheme(hwnd)
        End If
    End If
End Function


Private Function IsThemePossible() As Boolean
    
    If GetModuleHandle("uxtheme.dll") > 0 Then
        IsThemePossible = True
    End If
    
End Function


Private Function doFindPatch2JmpPosition(Buffer As String, Address As Long) As Long
Dim strBytesSearch      As String
Dim lTmp                As Long
Dim lTmp1               As Long


    strBytesSearch = "C9C2"           'we search for LEAVE, RET
    
    lTmp = InStr(Buffer, doChar(strBytesSearch))
    If lTmp > 0 Then
            
            strBytesSearch = "E8"        'this sould be CALL ...
           
            lTmp1 = InStrRev(Buffer, doChar(strBytesSearch), lTmp - 1)
            If lTmp1 > 0 Then
                'let's check if there is LEA also..
                If Mid$(Buffer, lTmp1 - 3, 1) = doChar("8D") Then
                       doFindPatch2JmpPosition = (lTmp1 - 4) - (Address + 4)
                End If
            End If
    End If
    
End Function
Private Function FindStringPosition(Data As String, Search As String, Optional BytesToAdd As Long) As Long
Dim lTmp                As Long

    
    lTmp = InStr(Data, doChar(Search))
    If lTmp > 0 Then
        FindStringPosition = lTmp + BytesToAdd
    End If
End Function
Private Function doChar(ByVal Data As String) As String
Dim strTmp              As String
Dim Q                   As Long


    For Q = 1 To Len(Data) Step 2
        strTmp = strTmp & Chr$("&H" & Mid$(Data, Q, 2))
    Next
    
    doChar = strTmp
End Function



