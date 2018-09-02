Attribute VB_Name = "mCreateClass"
Function CreateClass(ByVal ClassFile As String, ByVal ClassName As String, ByVal RestCode As String)
F = FreeFile
Open App.Path & "\" & ClassFile & ".cls" For Output As #F
Print #F, "VERSION 1.0 CLASS"
Print #F, "BEGIN"
Print #F, "MultiUse = -1  'True"
Print #F, "Persistable = 0  'NotPersistable"
Print #F, "DataBindingBehavior = 0  'vbNone"
Print #F, "DataSourceBehavior = 0   'vbNone"
Print #F, "MTSTransactionMode = 0   'NotAnMTSObject"
Print #F, "End"
Print #F, "Attribute VB_Name = " & Chr(34) & ClassName & Chr(34)
Print #F, "Attribute VB_GlobalNameSpace = False"
Print #F, "Attribute VB_Creatable = True"
Print #F, "Attribute VB_PredeclaredId = False"
Print #F, "Attribute VB_Exposed = False"
Print #F, RestCode
Close #F
End Function
