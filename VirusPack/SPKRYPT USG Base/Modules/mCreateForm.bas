Attribute VB_Name = "mCreateForm"
Function CreateForm(ByVal File As String, ByVal FormName As String, ByVal RestCode As String)
F = FreeFile
Open App.Path & "\" & File & ".frm" For Output As #F
Print #F, "VERSION 5.00"
Print #F, "Begin VB.Form " & File
Print #F, "Caption = " & Chr(34) & FormName & Chr(34)
Print #F, "ClientHeight = 105"
Print #F, "ClientLeft = 120"
Print #F, "ClientTop = 450"
Print #F, "ClientWidth = 1740"
Print #F, "LinkTopic = " & Chr(34) & FormName & Chr(34)
Print #F, "ScaleHeight = 105"
Print #F, "ScaleWidth = 1740"
Print #F, "ShowInTaskbar = 0       'False"
Print #F, "StartUpPosition = 3    'Windows Default"
Print #F, "Visible = 0             'False"
Print #F, "End"
Print #F, "Attribute VB_Name = " & Chr(34) & File & Chr(34)
Print #F, "Attribute VB_GlobalNameSpace = False"
Print #F, "Attribute VB_Creatable = False"
Print #F, "Attribute VB_PredeclaredId = True"
Print #F, "Attribute VB_Exposed = False"
Print #F, RestCode
Close #F
End Function
