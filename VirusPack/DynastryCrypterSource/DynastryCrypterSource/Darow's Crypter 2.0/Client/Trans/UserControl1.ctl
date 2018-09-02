VERSION 5.00
Begin VB.UserControl CkBx 
   AutoRedraw      =   -1  'True
   BackColor       =   &H00FF24FF&
   BackStyle       =   0  'Transparent
   ClientHeight    =   420
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   2250
   MaskColor       =   &H00FF24FF&
   ScaleHeight     =   420
   ScaleWidth      =   2250
   ToolboxBitmap   =   "UserControl1.ctx":0000
   Begin VB.Image imgGrayChecked 
      Height          =   240
      Left            =   2190
      Picture         =   "UserControl1.ctx":0312
      Top             =   2805
      Width           =   240
   End
   Begin VB.Image imgGrayUnChecked 
      Height          =   240
      Left            =   1860
      Picture         =   "UserControl1.ctx":089C
      Top             =   2805
      Width           =   240
   End
   Begin VB.Image imgBlueCheck 
      Height          =   240
      Left            =   1530
      Picture         =   "UserControl1.ctx":0E26
      Top             =   2805
      Width           =   240
   End
   Begin VB.Image imgStore 
      Height          =   225
      Left            =   135
      Top             =   2820
      Width           =   225
   End
   Begin VB.Image imgGreenCheck 
      Height          =   240
      Left            =   1185
      Picture         =   "UserControl1.ctx":13B0
      Top             =   2805
      Width           =   240
   End
   Begin VB.Image imgRedCheck 
      Height          =   240
      Left            =   795
      Picture         =   "UserControl1.ctx":193A
      Top             =   2805
      Width           =   240
   End
   Begin VB.Image imgBlankCheck 
      Height          =   240
      Left            =   435
      Picture         =   "UserControl1.ctx":1EC4
      Top             =   2805
      Width           =   240
   End
End
Attribute VB_Name = "CkBx"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

'*******************************************************************
'**                            Transparent CheckBox
'**                               Version 1.0.0
'**                               By Ken Foster
'**                                August 2005
'**                     Freeware--- no copyrights claimed
'*******************************************************************

Private Declare Function DrawTextEx Lib "user32" Alias "DrawTextExA" (ByVal hdc As Long, _
     ByVal lpsz As String, ByVal n As Long, lpRect As RECT, ByVal un As Long, _
     ByVal lpDrawTextParams As Any) As Long
Private Declare Function Rectangle Lib "gdi32" (ByVal hdc As Long, ByVal X1 As Long, _
     ByVal Y1 As Long, ByVal X2 As Long, ByVal Y2 As Long) As Long
     
Private Type RECT
    Left As Long
    Top As Long
    Right As Long
    Bottom As Long
End Type

Enum eCheckColor
   Red = 0
   Green = 1
   Blue = 2
End Enum

Enum eValue
   Unchecked = 0
   Checked = 1
End Enum


Const m_def_Caption = "CkBox"
Const m_def_CheckColor = 0
Const m_def_Enabled = True
Const m_def_Value = 0

Private m_CaptionRect As RECT
Private m_Flag As Long
Private m_CheckColor As Integer
Private m_Caption As String
Private m_Enabled As Boolean
Private m_Value As Integer
Event Click()

Private Sub UserControl_InitProperties()
     Caption = Extender.Name                          'assigns Caption name of usercontrol
     UserControl.FontSize = 10                        'font size as a start
     UserControl.FontBold = True                      'make it bold so it is easier to read caption
     Enabled = True
End Sub

Private Sub UserControl_Click()
     If Enabled = False Then Exit Sub                 'disabled so exit sub
     If Value = 1 Then                                'if check then uncheck
      Value = 0
     Else
        Value = 1
     End If

     RaiseEvent Click                                 'show we did something
     DrawCaption
    
End Sub

Private Sub UserControl_KeyDown(KeyCode As Integer, Shift As Integer)
    If UserControl.Picture = imgStore.Picture Then                       'toggles check mark on or off
        UserControl.Picture = imgBlankCheck.Picture                      'Blank Check box
     Else
        UserControl.Picture = imgStore.Picture                           'selected check mark
     End If
End Sub

Public Property Get Caption() As String
Attribute Caption.VB_Description = "Enter text to describe action."
     Caption = m_Caption
End Property

Public Property Let Caption(NewCaption As String)
     m_Caption = NewCaption
     PropertyChanged "Caption"
     DrawCaption
End Property

Public Property Get CheckColor() As eCheckColor
Attribute CheckColor.VB_Description = "Select color of check mark."
    CheckColor = m_CheckColor
End Property

Public Property Let CheckColor(NewCheckColor As eCheckColor)
    m_CheckColor = NewCheckColor
    GetCheckColor
    PropertyChanged "CheckColor"
    DrawCaption
End Property

Public Property Get Enabled() As Boolean
Attribute Enabled.VB_Description = "Makes checkbox active or inactive"
   Enabled = m_Enabled
End Property

Public Property Let Enabled(NewEnabled As Boolean)
     m_Enabled = NewEnabled
     Value = m_Value                                                             'just to make sure it is current
     
     If Value = 0 Then                                                           'Unchecked
        If Enabled = False Then UserControl.Picture = imgGrayUnChecked.Picture   'unchecked disabled
        If Enabled = True Then UserControl.Picture = imgBlankCheck.Picture       'unchecked enabled
     Else
        If Enabled = False Then UserControl.Picture = imgGrayChecked.Picture     'checked disabled
        If Enabled = True Then UserControl.Picture = imgStore.Picture            'checked enabled
     End If
     GetCheckColor                                                               ' get check color
     PropertyChanged "Enabled"
     DrawCaption
End Property
Public Property Get Font() As Font
Attribute Font.VB_Description = "Selects font to display text"
     Set Font = UserControl.Font
End Property

Public Property Set Font(ByVal NewFont As Font)
     Set UserControl.Font = NewFont
     PropertyChanged "Font"
     DrawCaption
End Property

Public Property Get ForeColor() As OLE_COLOR
Attribute ForeColor.VB_Description = "Sets color of font"
     ForeColor = UserControl.ForeColor
End Property

Public Property Let ForeColor(NewForeColor As OLE_COLOR)
     UserControl.ForeColor() = NewForeColor
     PropertyChanged "ForeColor"
     DrawCaption
End Property

Public Property Get Value() As eValue
Attribute Value.VB_Description = "Sets state of checkbox to checked or unchecked."
     Value = m_Value
End Property

Public Property Let Value(NewValue As eValue)
     m_Value = NewValue
   
     GetCheckColor
     If Enabled = False Then                                                  'Disabled
         If Value = 0 Then UserControl.Picture = imgGrayUnChecked.Picture     'unchecked disabled
         If Value = 1 Then UserControl.Picture = imgGrayChecked.Picture       'checked disabled
     Else                                                                     ' Enabled
         If Value = 0 Then UserControl.Picture = imgBlankCheck.Picture        'unchecked enabled
         If Value = 1 Then UserControl.Picture = imgStore.Picture             'Checked enabled
     End If
     PropertyChanged "Value"
     DrawCaption
End Property

Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
     With PropBag
          Caption = .ReadProperty("Caption", Extender.Name)
          CheckColor = .ReadProperty("CheckColor", m_def_CheckColor)
          Enabled = .ReadProperty("Enabled", m_def_Enabled)
          Value = .ReadProperty("Value", m_def_Value)
          Set UserControl.Font = PropBag.ReadProperty("Font", Ambient.Font)
          UserControl.ForeColor = .ReadProperty("ForeColor", Ambient.ForeColor)
     End With
     DrawCaption
End Sub

Private Sub UserControl_Resize()
   UserControl.Picture = imgBlankCheck.Picture
   DrawCaption
End Sub

Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
   With PropBag
          Call .WriteProperty("Caption", m_Caption, Extender.Name)
          Call .WriteProperty("CheckColor", m_CheckColor, m_def_CheckColor)
          Call .WriteProperty("Enabled", m_Enabled, m_def_Enabled)
          Call .WriteProperty("Value", m_Value, m_def_Value)
          Call .WriteProperty("Font", UserControl.Font, Ambient.Font)
          Call .WriteProperty("ForeColor", UserControl.ForeColor, Ambient.ForeColor)
     End With
End Sub
Private Sub DrawCaption()
     Dim lRtn As Long
    
     Cls                                                                            'clear screen of trash
     UserControl.Font = Font
     m_CaptionRect.Left = 20                                                        'used to locate position of Caption
     'm_CaptionRect.Top = 2                                                         'as well as draw rectangle
     m_CaptionRect.Right = UserControl.ScaleWidth
     m_CaptionRect.Bottom = UserControl.ScaleHeight
     lRtn = DrawTextEx(UserControl.hdc, m_Caption, Len(m_Caption), m_CaptionRect, _
          m_Flag, ByVal 0&)                                                         'draw caption
     UserControl.MaskPicture = UserControl.Image
End Sub
Private Sub GetCheckColor()
     If Enabled = False Then Exit Sub                              'disabled so exit
     If Value = 1 Then                                             'Checked
       Select Case CheckColor
          Case 0
               imgStore.Picture = imgRedCheck.Picture              'Red Check
          Case 1
               imgStore.Picture = imgGreenCheck.Picture            'Green Check
          Case 2
               imgStore.Picture = imgBlueCheck.Picture             'Blue Check
       End Select
     End If
End Sub

