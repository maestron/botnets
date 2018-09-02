VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "cFileDialog"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'Name:      cFileDialog
'Version:   1.0
'Date:      02/10/2001
'
'Developer: Bill Bither
'           http://www.atalasoft.com/
'           support@atalasoft.com
'
'Description:
'
'This class module was created to replace Microsoft's heavy Common Dialog Control
'Most of the time ShowOpen and ShowSave are the only dialogs used. Instead of making
'a more versatile control with print dialogs, color dialogs, and hooking, I decided
'to make a very lightweight one since the CommonControl Print and Color Dialogs are
'essentially useless
'
'I could have added hooking functionality, but that would involve including a standard module
'as well.  The only major benefit of hooking is the ability to center the dialog.  However,
'with this code, as long as you specify the form's handle, it will position the dialog to the
'upper left of the form
'
'I use this class exclusively in my apps
'
'This is a direct replacement to the Microsoft CommonDialog control and will involve very little
'Change in coding to implement.  If any bugs are found, please contact me
'
'Disclaimer:
'
'This code may be used for commercial purposes. I take no responsibility for bugs or problems from
'using this code.
'
'Code Example:
'
'1) Add this class module 'cFileDialog' to your project
'
'2) In a module, form, or procedure declare the cFileDialog object:
'   [Private] [Public] [Dim] fD as cFileDialog
'
'3) In a load event create the object:
'   Set fD = New cFileDialog
'
'4) To use the open dialog:
'   fD.Hwnd = me.Hwnd
'   fD.ShowOpen
'   sFilename = fD.FileName
'
'5) When unloading, be sure to set the cFileDialog to Nothing to prevent memory leaks:
'   Set fD = Nothing

Option Explicit

'This is the easiest way to get VB to recognize the
'constants project wide when in a class module
Public Enum DialogFlags
    OFN_READONLY = &H1
    OFN_OVERWRITEPROMPT = &H2
    OFN_HIDEREADONLY = &H4
    OFN_NOCHANGEDIR = &H8
    OFN_SHOWHELP = &H10
    OFN_ENABLEHOOK = &H20
    OFN_ENABLETEMPLATE = &H40
    OFN_ENABLETEMPLATEHANDLE = &H80
    OFN_NOVALIDATE = &H100
    OFN_ALLOWMULTISELECT = &H200
    OFN_EXTENSIONDIFFERENT = &H400
    OFN_PATHMUSTEXIST = &H800
    OFN_FILEMUSTEXIST = &H1000
    OFN_CREATEPROMPT = &H2000
    OFN_SHAREAWARE = &H4000
    OFN_NOREADONLYRETURN = &H8000
    OFN_NOTESTFILECREATE = &H10000
    OFN_NONETWORKBUTTON = &H20000
    OFN_NOLONGNAMES = &H40000
    OFN_EXPLORER = &H80000
    OFN_NODEREFERENCELINKS = &H100000
    OFN_LONGNAMES = &H200000
    cdlCancel = 32755
End Enum

Private Type OPENFILENAME
  nStructSize       As Long
  hWndOwner         As Long
  hInstance         As Long
  sFilter           As String
  sCustomFilter     As String
  nMaxCustFilter    As Long
  nFilterIndex      As Long
  sFile             As String
  nMaxFile          As Long
  sFileTitle        As String
  nMaxTitle         As Long
  sInitialDir       As String
  sDialogTitle      As String
  flags             As Long
  nFileOffset       As Integer
  nFileExtension    As Integer
  sDefFileExt       As String
  nCustData         As Long
  fnHook            As Long
  sTemplateName     As String
End Type

Private OFN As OPENFILENAME

Private Declare Function GetOpenFileName Lib "comdlg32.dll" Alias "GetOpenFileNameA" (pOpenfilename As OPENFILENAME) As Long
Private Declare Function GetSaveFileName Lib "comdlg32.dll" Alias "GetSaveFileNameA" (pOpenfilename As OPENFILENAME) As Long

'Module level variables
Private m_bCancelError As Boolean
Private m_sFileName As String
Private m_sFileTitle As String
Private m_sFilter As String
Private m_sDefaultExt As String
Private m_sInitDir As String
Private m_lFlags As Long

Public Property Get CancelError() As Boolean
    CancelError = m_bCancelError
End Property
Public Property Let CancelError(ByVal bCancelError As Boolean)
    m_bCancelError = bCancelError
End Property
Public Property Get Filename() As String
    'return object's FileName property
    Filename = m_sFileName
End Property
Public Property Let Filename(ByVal sFilename As String)
    'assign object's FileName property
    m_sFileName = sFilename
    OFN.sFile = sFilename & Space$(1024 - Len(sFilename)) & vbNullChar & vbNullChar
End Property
Public Property Get FileTitle() As String
    'return object's FileTitle property
    FileTitle = m_sFileTitle
End Property
Public Property Let FileTitle(ByVal vNewValue As String)
    'assign object's FileTitle property
    m_sFileTitle = vNewValue
End Property
Public Property Get Filter() As String
    'return object's Filter property
    Filter = m_sFilter
End Property
Public Property Let Filter(ByVal sFilter As String)
    Dim S As String
    'assign object's Filter property
    m_sFilter = sFilter
    ' To make Windows-style filter, replace | and : with nulls
   Dim ch As String, i As Integer
   For i = 1 To Len(sFilter)
      ch = Mid$(sFilter, i, 1)
      If ch = "|" Or ch = ":" Then
          S = S & vbNullChar
      Else
          S = S & ch
      End If
   Next
   ' Put double null at end
   OFN.sFilter = S & vbNullChar & vbNullChar
End Property
Public Property Get FilterIndex() As Long
    'return object's FilterIndex property
    FilterIndex = OFN.nFilterIndex
End Property
Public Property Let FilterIndex(ByVal lFilterIndex As Long)
    'assign object's FilterIndex property
    OFN.nFilterIndex = lFilterIndex
End Property
Public Property Get DefaultExt() As String
    'return object's DefaultExt property
    DefaultExt = m_sDefaultExt
End Property
Public Property Let DefaultExt(ByVal sDefaultExt As String)
    'assign object's DefaultExt property
    m_sDefaultExt = sDefaultExt
    OFN.sDefFileExt = sDefaultExt & vbNullChar & vbNullChar
End Property
Public Property Get DialogTitle() As String
    'return object's FileTitle property
    DialogTitle = OFN.sDialogTitle
End Property
Public Property Let DialogTitle(ByVal vNewValue As String)
    'assign object's FileTitle property
    OFN.sDialogTitle = vNewValue
End Property
Public Property Get flags() As Long
    'return object's Flags property
    flags = m_lFlags
End Property
Public Property Let flags(ByVal vNewValue As DialogFlags)
    'assign object's Flags property
    m_lFlags = vNewValue
End Property
Public Property Get hwnd() As Long
    'Return object's hWnd property
    hwnd = OFN.hWndOwner
End Property
Public Property Let hwnd(ByVal vNewValue As Long)
    'Assign object's hWnd property
    OFN.hWndOwner = vNewValue
End Property
Public Property Get InitDir() As String
    'Return object's InitDir property
    InitDir = m_sInitDir
End Property
Public Property Let InitDir(ByVal vNewValue As String)
    'Assign object's InitDir property
    m_sInitDir = vNewValue
    OFN.sInitialDir = vNewValue & vbNullChar & vbNullChar
End Property

Public Sub ShowOpen()
    Dim sBuff As String
    Dim lReturn As Long
    Dim lFileSize As Long
    
    With OFN
        .flags = m_lFlags

        'If multiselect then OFN_EXPLORER must be active else it'll crash
        ' Pad file and file title buffers to maximum path
        If (.flags And OFN_ALLOWMULTISELECT) = OFN_ALLOWMULTISELECT Then
            .flags = .flags Or OFN_EXPLORER
            lFileSize = 8192
        Else
            lFileSize = 1024
        End If
        
        .sFile = m_sFileName & String$(lFileSize - Len(m_sFileName), 0)
        .nMaxFile = lFileSize
        .sFileTitle = m_sFileTitle & String$(lFileSize - Len(FileTitle), 0)
        .nMaxTitle = lFileSize
            
        lReturn = GetOpenFileName(OFN)
        If lReturn Then
            If (.flags And OFN_ALLOWMULTISELECT) Then
                sBuff = .sFile
            Else
                sBuff = TrimNull(.sFile)
            End If
            m_sFileName = sBuff
        Else
            If m_bCancelError Then
                Err.Raise cdlCancel, App.EXEName & ".cFileDialog", "User selected cancel."
            End If
        End If
    End With
End Sub

Public Sub ShowSave()
    Dim sBuff As String
    Dim lReturn As Long
    
    With OFN
        .flags = m_lFlags
        .sFile = m_sFileName & String$(1024 - Len(m_sFileName), 0)
        .nMaxFile = 1024
        .sFileTitle = m_sFileTitle & String$(1024 - Len(FileTitle), 0)
        .nMaxTitle = 1024
        
        lReturn = GetSaveFileName(OFN)
        If lReturn Then
            sBuff = TrimNull(.sFile)
            m_sFileName = sBuff
        Else
            If m_bCancelError Then
                Err.Raise cdlCancel, App.EXEName & ".cFilenDialog", "User selected cancel."
            End If
        End If
    End With
End Sub

Public Sub ParseMultiFileName(ByRef sDir As String, ByRef sFiles() As String, ByRef lFileCount As Long)
Dim lPos As Long
Dim lNextPos As Long
Dim sAllFiles As String
Dim i As Long
    
    lPos = InStr(m_sFileName, vbNullChar & vbNullChar)
    sAllFiles = Left$(m_sFileName, lPos - 1)
    lNextPos = InStr(sAllFiles, vbNullChar)
    If lNextPos <> 0 Then
        ' multi names
        sDir = Mid$(sAllFiles, 1, lNextPos - 1)
        Do While lNextPos <> 0
            lPos = lNextPos + 1
            lNextPos = InStr(lPos, sAllFiles, vbNullChar)
            lFileCount = lFileCount + 1
            ReDim Preserve sFiles(0 To lFileCount - 1) As String
            If lNextPos > 0 Then
                sFiles(lFileCount - 1) = Mid$(sAllFiles, lPos, lNextPos - lPos)
            Else
                sFiles(lFileCount - 1) = Mid$(sAllFiles, lPos)
            End If
        Loop
    Else
        ' single file
        lFileCount = 1
        ReDim sFiles(0)
        lPos = InStrRev(m_sFileName, "\")
        If lPos > 0 Then
            sDir = Left$(m_sFileName, lPos)
            sFiles(0) = TrimNull(Right$(m_sFileName, Len(m_sFileName) - lPos))
        Else
            sDir = ""
            sFiles(0) = m_sFileName
        End If
    End If

End Sub

Private Sub Class_Initialize()
    With OFN
        .nFilterIndex = 1
        .nStructSize = Len(OFN)
    End With
End Sub

Private Function TrimNull(ByVal item As String) As String

    Dim pos As Integer
    pos = InStr(item, Chr$(0))
    If pos Then item = Left$(item, pos - 1)
    TrimNull = item

End Function
