VERSION 5.00
Begin VB.UserControl Framez 
   Appearance      =   0  'Flat
   AutoRedraw      =   -1  'True
   ClientHeight    =   1230
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   1515
   ControlContainer=   -1  'True
   LockControls    =   -1  'True
   ScaleHeight     =   82
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   101
   ToolboxBitmap   =   "Framez.ctx":0000
End
Attribute VB_Name = "Framez"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
' /////////////////////////////////////
' //      Framez Version 1.14        //
' // Transparent Frame User Control  //
' //     Ed Wilk / Edgemeal 2009     //
' /////////////////////////////////////

'v1.14 - Fix: Selecting a system color for XP\7 border color was always black.
'v1.13 - Add option to disable transparency and set background color.
'v1.12 - Add Windows XP/7 frame styles.
'v1.09 - Fixes bugs in v1.06 to v1.08. (Framez inside of Framez)
'v1.05 - General usage.

Option Explicit

Private Type RECT
    Left    As Long
    Top     As Long
    Right   As Long
    Bottom  As Long
End Type

Private Const PS_SOLID As Long = 0
Private Declare Function LineTo Lib "gdi32.dll" (ByVal hdc As Long, ByVal x As Long, ByVal y As Long) As Long
Private Declare Function MoveToEx Lib "gdi32.dll" (ByVal hdc As Long, ByVal x As Long, ByVal y As Long, ByVal lpPoint As Any) As Long ' <<< Modified! (,lpPoint As POINTAPI) As Long)
Private Declare Function CreatePen Lib "gdi32.dll" (ByVal nPenStyle As Long, ByVal nWidth As Long, ByVal crColor As Long) As Long
Private Declare Function SelectObject Lib "gdi32.dll" (ByVal hdc As Long, ByVal hObject As Long) As Long
Private Declare Function DeleteObject Lib "gdi32.dll" (ByVal hObject As Long) As Long
Private Const DT_SINGLELINE = &H20
Private Declare Function DrawText Lib "User32.dll" Alias "DrawTextA" (ByVal hdc As Long, ByVal lpStr As String, ByVal nCount As Long, ByRef lpRect As RECT, ByVal wFormat As Long) As Long
Private Declare Function BitBlt Lib "gdi32" (ByVal hDCDest As Long, ByVal xDest As Long, ByVal yDest As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal hdcSrc As Long, ByVal xSrc As Long, ByVal ySrc As Long, ByVal dwRop As Long) As Long
Private Declare Function DrawEdge Lib "user32" (ByVal hdc As Long, qrc As RECT, ByVal edge As Long, ByVal grfFlags As Long) As Long
Private Declare Function FillRect Lib "user32" (ByVal hdc As Long, lpRect As RECT, ByVal hBrush As Long) As Long
Private Declare Function GetSysColor Lib "user32" (ByVal nIndex As Long) As Long

Public Enum Border
    XP_Blue_Silver = 11
    XP_Olive = 12
    Windows_7 = 13
    RaisedOut = 1
    SunkenOut = 2
    RaisedIn = 4
    SunkenIn = 8
    EtchedOut = RaisedOut Or SunkenIn
    EtchedIn = SunkenOut Or RaisedIn
    Button = RaisedIn Or RaisedOut
    Control = SunkenIn Or SunkenOut
    None = Button Or Control
End Enum

Private mBackColor          As OLE_COLOR
Private mForeColor          As OLE_COLOR
Private mForeColorDisabled  As OLE_COLOR
Private mXP7_BorderColor    As OLE_COLOR
Private mBorder             As Border
Private mCaption            As String
Private mEnabled            As Boolean
Private OkToDraw            As Boolean
Private mTransparent        As Boolean

Public Property Let Transparent(ByVal NewVal As Boolean)
    mTransparent = NewVal
    ReDraw
    PropertyChanged "Transparent"
End Property

Public Property Get Transparent() As Boolean
    Transparent = mTransparent
End Property

Public Property Let AutoReDraw(ByVal NewVal As Boolean)
    UserControl.AutoReDraw = NewVal
End Property

Public Property Get BackColor() As OLE_COLOR
    BackColor = mBackColor
End Property

Public Property Let BackColor(ByVal NewVal As OLE_COLOR)
    mBackColor = NewVal
    ReDraw
    PropertyChanged "BackColor"
End Property

Public Property Get Caption() As String
    Caption = mCaption
End Property

Public Property Let Caption(ByVal NewValue As String)
Attribute Caption.VB_UserMemId = -518
    mCaption = NewValue
    ReDraw
    PropertyChanged "Caption"
End Property

Public Property Get Enabled() As Boolean
    Enabled = mEnabled
End Property

Public Property Let Enabled(ByVal NewVal As Boolean)
    mEnabled = NewVal
    ' Ignore in design mode so if disabled you can still size/move controls inside the Framez!
    If UserControl.Ambient.UserMode = True Then UserControl.Enabled = NewVal
    ReDraw
    PropertyChanged "Enabled"
End Property

Public Property Get Font() As Font
    Set Font = UserControl.Font
End Property

Public Property Set Font(ByVal Value As Font)
    Set UserControl.Font = Value
    PropertyChanged "Font"
    ReDraw
End Property

Public Property Get ForeColor() As OLE_COLOR
     ForeColor = mForeColor
End Property

Public Property Let ForeColor(ByVal NewVal As OLE_COLOR)
     mForeColor = NewVal
     ReDraw
     PropertyChanged "ForeColor"
End Property

Public Property Get ForeColorDisabled() As OLE_COLOR
     ForeColorDisabled = mForeColorDisabled
End Property

Public Property Let ForeColorDisabled(ByVal NewVal As OLE_COLOR)
     mForeColorDisabled = NewVal
     ReDraw
     PropertyChanged "ForeColorDisabled"
End Property

Public Property Get FrameStyle() As Border
    FrameStyle = mBorder
End Property

Public Property Let FrameStyle(ByVal NewValue As Border)
    
    mBorder = NewValue
    
    ' forecolors
    If mBorder = XP_Blue_Silver Then
        mForeColor = &HD54600        ' XP Blue and Silver theme (blue-ish text)
    ElseIf mBorder = XP_Olive Then
        mForeColor = &HA5499                     ' XP Olive-Green theme (red-brown-ish text)
    Else
        mForeColor = 0
        mForeColorDisabled = &H808080
    End If
    
    ' borders/disabled forecolor
    If mBorder = XP_Olive Or mBorder = XP_Blue_Silver Then
        mForeColorDisabled = mForeColor ' XP Frame caption color when disabled
        mXP7_BorderColor = &HBFD0D0     ' XP frame border color (gray-ish)
    ElseIf mBorder = Windows_7 Then
        mForeColorDisabled = 0        ' Windows 7 caption color when disabled
        mXP7_BorderColor = &HE5DFD5   ' Windows 7 frame border color (blue-gray-ish)
    End If
    
    ' update control
    ReDraw
    PropertyChanged "FrameStyle"
End Property

Public Property Get hdc() As Long
    hdc = UserControl.hdc
End Property

Public Sub ReDraw()
    '// Draw the frame //
    Dim Area            As RECT
    Dim rc              As RECT
    Dim TxtHeightOffSet As Long
    Dim XP7_TxtOffSet   As Long
    Dim hPen            As Long
    Dim hOld            As Long
    Dim XP7_StyleUsed   As Boolean
        
    If OkToDraw = False Then Exit Sub
    On Error GoTo ErrorHandler
    ' is frame set to a XP/7 style?
    If mBorder = XP_Blue_Silver Or mBorder = XP_Olive Or mBorder = Windows_7 Then
        XP7_StyleUsed = True
        XP7_TxtOffSet = 2 ' Offset caption text spacing to right to account for rounded frame edges.
    End If
    ' get half height of caption text
    TxtHeightOffSet = UserControl.TextHeight(mCaption) / 2
    ' set bottom/right cords for drawing
    rc.Right = UserControl.ScaleWidth
    rc.Bottom = UserControl.ScaleHeight
    ' clear control
    UserControl.Cls
    ' set back color
    UserControl.BackColor = mBackColor
    
    ' copy the parent container background (For transparent effect)
    If mTransparent = True Then
        pvMakeTransparent
    End If
    
    ' draw frame edge with selected style
    If XP7_StyleUsed = True Then
        ' Draw lines for Win7 look
        With UserControl
            ' top
            pvDrawLine mXP7_BorderColor, .ScaleWidth - 3, TxtHeightOffSet, 0, TxtHeightOffSet
            ' left side
            pvDrawLine mXP7_BorderColor, 0, .ScaleHeight - 3, 0, TxtHeightOffSet
            ' bottom
            pvDrawLine mXP7_BorderColor, .ScaleWidth - 3, .ScaleHeight - 1, 0, .ScaleHeight - 1
            ' right side
            pvDrawLine mXP7_BorderColor, .ScaleWidth - 1, .ScaleHeight - 3, .ScaleWidth - 1, TxtHeightOffSet
            ' top left corner
            pvDrawLine mXP7_BorderColor, 1, TxtHeightOffSet + 1, 1, TxtHeightOffSet + 1
            ' bottom left corner
            pvDrawLine mXP7_BorderColor, 1, .ScaleHeight - 2, 1, .ScaleHeight - 2
            ' bottom right corner
            pvDrawLine mXP7_BorderColor, .ScaleWidth - 2, .ScaleHeight - 2, .ScaleWidth - 2, .ScaleHeight - 2
            ' top right corner
            pvDrawLine mXP7_BorderColor, .ScaleWidth - 2, TxtHeightOffSet + 1, .ScaleWidth - 2, TxtHeightOffSet + 1
            ' Draw additional lines to fill corners for WinXP look
            If mBorder <> Windows_7 Then
                ' XP top left corner
                pvDrawLine mXP7_BorderColor, 3, TxtHeightOffSet, 0, TxtHeightOffSet + 3
                ' XP bottom right corner
                pvDrawLine mXP7_BorderColor, .ScaleWidth - 2, .ScaleHeight - 3, .ScaleWidth - 4, .ScaleHeight - 1
                ' XP bottom left corner
                pvDrawLine mXP7_BorderColor, 0, .ScaleHeight - 4, 3, .ScaleHeight - 1
                ' XP top right corner
                pvDrawLine mXP7_BorderColor, .ScaleWidth - 1, TxtHeightOffSet + 3, .ScaleWidth - 4, TxtHeightOffSet
            End If
        End With
    Else ' draw other selected style
        rc.Top = TxtHeightOffSet
        rc.Left = 0
        DrawEdge UserControl.hdc, rc, mBorder, 15
    End If
    ' erase frame where caption text will go
    If Len(mCaption) > 0 Then
        If mTransparent = False Then
            ' if not transparent then color background area for caption
            With UserControl
                hPen = CreatePen(PS_SOLID, 1, EvalCol(mBackColor))
                hOld = SelectObject(.hdc, hPen)
                Area.Bottom = .TextHeight(mCaption)
                Area.Right = .TextWidth(mCaption) + 12 + XP7_TxtOffSet '8+ 4=12
                Area.Top = 0
                Area.Left = 8 + XP7_TxtOffSet
                Call FillRect(.hdc, Area, hPen)
                SelectObject .hdc, hOld         ' Restore the previous pen
                DeleteObject hPen                          ' clear pen object from memory
            End With
        Else ' copy the area of parent container
            With UserControl.Extender.Container
                BitBlt UserControl.hdc, 8 + XP7_TxtOffSet, 0, _
                UserControl.TextWidth(mCaption) + 4, _
                UserControl.TextHeight(mCaption), _
                .hdc, _
                .ScaleX(UserControl.Extender.Left, .ScaleMode, vbPixels) + (UserControl.ScaleLeft + 8 + XP7_TxtOffSet), _
                .ScaleY(UserControl.Extender.Top, .ScaleMode, vbPixels), _
                vbSrcCopy
            End With
        End If
        
        'draw caption text
        If mEnabled = True Then ' draw caption text for enabled frame.
            rc.Top = 0
            rc.Left = 10 + XP7_TxtOffSet
            UserControl.ForeColor = mForeColor
            DrawText UserControl.hdc, mCaption, Len(mCaption), rc, DT_SINGLELINE
        Else ' draw caption text for disabled frame (offset for embossed look)
            If XP7_StyleUsed = False Then ' dont emboss if XP/7 style.
                rc.Top = 1
                rc.Left = 9
                UserControl.ForeColor = vbWhite ' <<< Hard coded color (add code to make this settable).
                DrawText UserControl.hdc, mCaption, Len(mCaption), rc, DT_SINGLELINE
            End If
            ' draw caption text for disabled frame (normal position).
            rc.Top = 0
            rc.Left = 10 + XP7_TxtOffSet
            UserControl.ForeColor = mForeColorDisabled
            DrawText UserControl.hdc, mCaption, Len(mCaption), rc, DT_SINGLELINE
        End If
    End If
    Exit Sub
ErrorHandler:
    Debug.Print "ReDraw Error: " & Err.Description
End Sub

Public Property Get ScaleMode() As ScaleModeConstants
    ScaleMode = UserControl.ScaleMode
End Property

Public Property Get ScaleX(ByVal Width As Single, ByVal FromScale As ScaleModeConstants, ByVal ToScale As ScaleModeConstants)
    ScaleX = UserControl.ScaleX(Width, FromScale, ToScale) / Screen.TwipsPerPixelX
End Property

Public Property Get ScaleY(ByVal Height As Single, ByVal FromScale As ScaleModeConstants, ByVal ToScale As ScaleModeConstants)
    ScaleY = UserControl.ScaleY(Height, FromScale, ToScale) / Screen.TwipsPerPixelY
End Property

Public Property Get XP7_BorderColor() As OLE_COLOR
     XP7_BorderColor = mXP7_BorderColor
End Property

Public Property Let XP7_BorderColor(ByVal NewVal As OLE_COLOR)
     mXP7_BorderColor = NewVal
     ReDraw
     PropertyChanged "XP7_BorderColor"
End Property

Private Function EvalCol(ByVal inCol As Long) As Long ' Returns the RGB of a long colour value (System colour aware)
    If ((inCol And &HFFFFFF00) = &H80000000) Then EvalCol = GetSysColor(inCol And &HFF) Else EvalCol = inCol
End Function

Private Sub pvDrawLine(ByVal Color As Long, ByVal X1 As Long, ByVal Y1 As Long, ByVal X2 As Long, ByVal Y2 As Long)
    '// Draw a line with the specified color and coordinates //
    Dim hOld As Long, hPen As Long
    hPen = CreatePen(PS_SOLID, 1, EvalCol(Color))
    hOld = SelectObject(hdc, hPen)
    If (X1 = X2) Then Y2 = Y2 + 1   ' LineTo draws a line up to, but not
    If (Y1 = Y2) Then X2 = X2 + 1   ' including the defined point.
    MoveToEx hdc, X1, Y1, 0&        ' Set starting position of line
    LineTo hdc, X2, Y2              ' then draw a line to this point
    SelectObject hdc, hOld          ' Restore the previous pen
    DeleteObject hPen               ' then clear pen object from memory
End Sub

Private Sub pvMakeTransparent()
    ' // Make UC appear transparent //
    On Error GoTo ErrorHandler
    With UserControl.Extender.Container
        .AutoReDraw = True
        BitBlt UserControl.hdc, 0, 0, _
        .ScaleX(UserControl.Width, .ScaleMode, vbPixels), _
        .ScaleY(UserControl.Height, .ScaleMode, vbPixels), _
        .hdc, _
        .ScaleX(UserControl.Extender.Left, .ScaleMode, vbPixels), _
        .ScaleY(UserControl.Extender.Top, .ScaleMode, vbPixels), _
         vbSrcCopy
    End With
    Exit Sub
ErrorHandler:
    Debug.Print "pvMakeTransparent Error: " & Err.Description
End Sub

Private Sub UserControl_InitProperties()
    ' set default style to XP Blue/Silver look.
    mBackColor = vbButtonFace
    mBorder = Border.XP_Blue_Silver
    mForeColor = &HD54600      ' XP Blue and Silver theme (blue-ish text)
    mForeColorDisabled = mForeColor ' XP Frame colors dont change when disabled
    mXP7_BorderColor = &HBFD0D0 ' Set default XP frame border edge color (gray-ish)
    ' enable control
    mEnabled = True
    ' In design mode allow Redraw so control is seen when added from toolbox.
    If UserControl.Ambient.UserMode = False Then OkToDraw = True
    ' set default caption
    Caption = Extender.Name
End Sub

Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
    With PropBag
        Set UserControl.Font = .ReadProperty("Font", Ambient.Font)
        FrameStyle = .ReadProperty("FrameStyle", Border.XP_Blue_Silver)
        Caption = .ReadProperty("Caption", UserControl.Extender.Name)
        BackColor = .ReadProperty("BackColor", vbButtonFace)
        ForeColor = .ReadProperty("ForeColor", vbBlack)
        ForeColorDisabled = .ReadProperty("ForeColorDisabled", &H808080)
        XP7_BorderColor = .ReadProperty("XP7_BorderColor", &HBFD0D0)
        Enabled = .ReadProperty("Enabled", True)
        Transparent = .ReadProperty("Transparent", False)
    End With
    ' Only draw the control after all properties have been set.
    ' After ReadProperties runs, UserControl_Resize will call Redraw.
    OkToDraw = True ' allow redraws
End Sub

Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
    With PropBag
        .WriteProperty "Font", UserControl.Font, Ambient.Font
        .WriteProperty "FrameStyle", mBorder, Border.XP_Blue_Silver
        .WriteProperty "BackColor", mBackColor, vbButtonFace
        .WriteProperty "ForeColor", mForeColor, vbBlack
        .WriteProperty "ForeColorDisabled", mForeColorDisabled, &H808080
        .WriteProperty "XP7_BorderColor", mXP7_BorderColor, &HBFD0D0
        .WriteProperty "Caption", mCaption, UserControl.Extender.Name
        .WriteProperty "Transparent", mTransparent, False
        .WriteProperty "Enabled", mEnabled, True
    End With
End Sub

Private Sub UserControl_Resize()
    ReDraw
End Sub
