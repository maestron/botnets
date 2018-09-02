VERSION 5.00
Begin VB.Form f 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Stub Gen 2.0"
   ClientHeight    =   2175
   ClientLeft      =   150
   ClientTop       =   735
   ClientWidth     =   5085
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2175
   ScaleWidth      =   5085
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox Text4 
      Height          =   285
      Left            =   2760
      TabIndex        =   11
      Text            =   "authcode"
      Top             =   960
      Width           =   855
   End
   Begin VB.TextBox Text3 
      Height          =   285
      Left            =   2760
      TabIndex        =   10
      Text            =   "user"
      Top             =   600
      Width           =   855
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Index           =   7
      Left            =   1440
      TabIndex        =   9
      Text            =   "ProjName"
      Top             =   1440
      Width           =   1095
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Index           =   6
      Left            =   1440
      TabIndex        =   8
      Text            =   "ExeName"
      Top             =   1080
      Width           =   1095
   End
   Begin VB.TextBox Text2 
      Height          =   285
      Left            =   2760
      TabIndex        =   7
      Text            =   "enckey"
      Top             =   120
      Width           =   855
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Index           =   5
      Left            =   1440
      TabIndex        =   6
      Text            =   "mResLoad"
      Top             =   720
      Width           =   1095
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Index           =   4
      Left            =   1440
      TabIndex        =   5
      Text            =   "mDecString"
      Top             =   360
      Width           =   1095
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Index           =   3
      Left            =   240
      TabIndex        =   4
      Text            =   "mPE"
      Top             =   1440
      Width           =   1095
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Index           =   2
      Left            =   240
      TabIndex        =   3
      Text            =   "mMain"
      Top             =   1080
      Width           =   1095
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Index           =   1
      Left            =   240
      TabIndex        =   2
      Text            =   "mEncRC4"
      Top             =   720
      Width           =   1095
   End
   Begin VB.Frame Frame1 
      Caption         =   "Module Names"
      Height          =   1815
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   2535
      Begin VB.TextBox Text1 
         Height          =   285
         Index           =   0
         Left            =   120
         TabIndex        =   1
         Text            =   "mAPI"
         Top             =   360
         Width           =   1095
      End
   End
   Begin VB.Menu mnu 
      Caption         =   "Menu"
      Begin VB.Menu mnu_random 
         Caption         =   "Randomize"
      End
      Begin VB.Menu mnu_Create 
         Caption         =   "Create"
      End
   End
End
Attribute VB_Name = "f"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub mnu_Create_Click()
Open App.Path & "\Generated\" & Text1(0).Text & ".bas" For Binary As #1
Put #1, , ApiCall
Close #1

Open App.Path & "\Generated\" & Text1(1).Text & ".bas" For Binary As #1
Put #1, , EncRC4
Close #1

Open App.Path & "\Generated\" & Text1(2).Text & ".bas" For Binary As #1
Put #1, , MainModule
Close #1

Open App.Path & "\Generated\" & Text1(3).Text & ".bas" For Binary As #1
Put #1, , PE
Close #1

Open App.Path & "\Generated\" & Text1(4).Text & ".bas" For Binary As #1
Put #1, , DecString
Close #1

Open App.Path & "\Generated\" & Text1(5).Text & ".bas" For Binary As #1
Put #1, , ResLoad
Close #1

Open App.Path & "\Generated\" & Text1(7).Text & ".vbp" For Binary As #1
Put #1, , Proj
Close #1
End Sub

Private Sub mnu_random_Click()
Dim i As Integer
For i = 0 To 7
Text1(i).Text = RandomLetter & RandomLetter & RandomLetter & RandomLetter & RandomNumber & RandomLetter
Next i
Text2.Text = RandomLetter & RandomLetter & RandomNumber & RandomLetter
End Sub
