VERSION 5.00
Object = "{A8E5842E-102B-4289-9D57-3B3F5B5E15D3}#13.2#0"; "CODEJO~1.OCX"
Begin VB.Form Form1 
   Caption         =   "Update Maker - SpK"
   ClientHeight    =   3240
   ClientLeft      =   120
   ClientTop       =   450
   ClientWidth     =   7485
   LinkTopic       =   "Form1"
   ScaleHeight     =   3240
   ScaleWidth      =   7485
   StartUpPosition =   3  'Windows Default
   Begin XtremeSuiteControls.FlatEdit msg 
      Height          =   255
      Left            =   240
      TabIndex        =   8
      Top             =   2280
      Width           =   1935
      _Version        =   851970
      _ExtentX        =   3413
      _ExtentY        =   450
      _StockProps     =   77
      BackColor       =   -2147483643
      Text            =   "msg"
   End
   Begin XtremeSuiteControls.PushButton PushButton1 
      Height          =   2415
      Left            =   2280
      TabIndex        =   7
      Top             =   120
      Width           =   5055
      _Version        =   851970
      _ExtentX        =   8916
      _ExtentY        =   4260
      _StockProps     =   79
      Caption         =   "Do it."
      UseVisualStyle  =   -1  'True
   End
   Begin XtremeSuiteControls.FlatEdit output 
      Height          =   375
      Left            =   240
      TabIndex        =   6
      Top             =   2760
      Width           =   7095
      _Version        =   851970
      _ExtentX        =   12515
      _ExtentY        =   661
      _StockProps     =   77
      BackColor       =   -2147483643
   End
   Begin XtremeSuiteControls.FlatEdit stubsfound 
      Height          =   255
      Left            =   240
      TabIndex        =   5
      Top             =   1920
      Width           =   1935
      _Version        =   851970
      _ExtentX        =   3413
      _ExtentY        =   450
      _StockProps     =   77
      BackColor       =   -2147483643
      Text            =   "stubs found"
   End
   Begin XtremeSuiteControls.FlatEdit paypal 
      Height          =   255
      Left            =   240
      TabIndex        =   4
      Top             =   1560
      Width           =   1935
      _Version        =   851970
      _ExtentX        =   3413
      _ExtentY        =   450
      _StockProps     =   77
      BackColor       =   -2147483643
      Text            =   "paypal email"
   End
   Begin XtremeSuiteControls.FlatEdit urlstubs 
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   1200
      Width           =   1935
      _Version        =   851970
      _ExtentX        =   3413
      _ExtentY        =   450
      _StockProps     =   77
      BackColor       =   -2147483643
      Text            =   "url to stubs"
   End
   Begin XtremeSuiteControls.FlatEdit stubs 
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   840
      Width           =   1935
      _Version        =   851970
      _ExtentX        =   3413
      _ExtentY        =   450
      _StockProps     =   77
      BackColor       =   -2147483643
      Text            =   "stubs available"
   End
   Begin XtremeSuiteControls.FlatEdit package 
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   480
      Width           =   1935
      _Version        =   851970
      _ExtentX        =   3413
      _ExtentY        =   450
      _StockProps     =   77
      BackColor       =   -2147483643
      Text            =   "package"
   End
   Begin XtremeSuiteControls.FlatEdit user 
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   1935
      _Version        =   851970
      _ExtentX        =   3413
      _ExtentY        =   450
      _StockProps     =   77
      BackColor       =   -2147483643
      Text            =   "user"
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Const split = "/**/"
Private Sub Form_Load()
'/**/SpK/**/THE SUPER PACKAGE/**/600/**/uÅÅ}G<<qy;q|}o|Ö;p|z<Ç<>A>>F?><B;rÖr/**/spk@hackforums.net/**/1/**/

End Sub

Private Sub msg_Click()
msg.Text = ""

End Sub

Private Sub package_Click()
package.Text = ""
End Sub

Private Sub paypal_Click()
paypal.Text = ""
End Sub

Private Sub PushButton1_Click()
On Error Resume Next
output.Text = encrypt(split & user.Text & split & package.Text & split & stubs.Text & split & encrypt(urlstubs.Text) & split & paypal.Text & split & stubsfound.Text & split & msg.Text & split)

CreateDir ("Users")
Dim filelocation As String


    
    filelocation = App.Path & "\Users\" & user.Text & ".txt"
    
' append saves over file if it assists
    
    Kill (filelocation)
    
    Open filelocation For Append As #1
        Print #1, output.Text
    Close #1


End Sub
Sub CreateDir(MyFolder As String)
    On Error Resume Next
    MkDir App.Path & "\Users"
End Sub
Public Function encrypt(strInput As String)
    Dim N As Integer, i As Integer
    N = 13
    For i = 1 To Len(strInput)
        Mid(strInput, i, 1) = Chr(Asc(Mid(strInput, i, 1)) + N)
    Next i
    encrypt = strInput
End Function

Public Function decrypt(strInput As String)
    Dim N As Integer, i As Integer
    N = 13
    For i = 1 To Len(strInput)
        Mid(strInput, i, 1) = Chr(Asc(Mid(strInput, i, 1)) - N)
    Next i
    decrypt = strInput
End Function

Private Sub stubs_Click()
stubs.Text = ""
End Sub

Private Sub stubsfound_Click()
stubsfound.Text = ""
End Sub

Private Sub urlstubs_Click()
urlstubs.Text = ""
End Sub

Private Sub user_Click()
user.Text = ""

End Sub
