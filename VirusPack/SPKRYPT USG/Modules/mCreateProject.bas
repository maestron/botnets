Attribute VB_Name = "mCreateProject"
Function ProjectCreate(ByVal ProjectFile As String, ByVal ProjectName As String, ClassModule1 As String, classmodule1name, ClassModule2 As String, classmodule2name, Form1 As String, Optional modules As Integer, Optional modulename As String, Optional modulefile As String, Optional path As Boolean, Optional path2 As String)
F = FreeFile
Open path2 & "\" & ProjectFile & ".vbp" For Output As #F
Print #F, "Type=Exe"
Print #F, "Reference=*\G{00020430-0000-0000-C000-000000000046}#2.0#0#C:\Windows\SysWOW64\stdole2.tlb#OLE Automation"
Print #F, "Class=" & classmodule1name & ";" & ClassModule1 & ".cls"
Print #F, "Class=" & classmodule2name & ";" & ClassModule2 & ".cls"
If modules <> 0 Then
Print #F, "Module=" & modulename & ";" & modulefile & ".bas"
End If
Print #F, "Form =" & Form1 & ".frm"
Print #F, "Startup =" & Chr(34) & Form1 & Chr(34)
Print #F, "HelpFile =" & Chr(34) & Chr(34)
Print #F, "Title ="; Chr(34) & StrGen(4, 10) & Chr(34)
Print #F, "ExeName32 =" & Chr(34) & ProjectFile & ".exe" & Chr(34)
If path = True Then
Print #F, "Path32 =" & Chr(34) & "C:\" & Chr(34)
Else
Print #F, "Path32 =" & Chr(34) & App.path & Chr(34)
End If
Print #F, "Command32 =" & Chr(34) & Chr(34)
Print #F, "Name =" & Chr(34) & StrGen(2, 20); Chr(34)
Print #F, "HelpContextID =" & Chr(32) & " 0 " & Chr(32)
Print #F, "CompatibleMode ="; 0; ""
Randomize
Print #F, "MajorVer =" & Int(Rnd * 15) + 2
Randomize
Print #F, "MinorVer = " & Int(Rnd * 15) + 2
Randomize
Print #F, "RevisionVer = " & Int(Rnd * 15) + 2
Randomize
Print #F, "AutoIncrementVer = " & Int(Rnd * 15) + 2
Print #F, "ServerSupportFiles = 0"
Print #F, "VersionCompanyName = " & StrGen(2, 20) & Chr(34)
Print #F, "CompilationType = -1"
Print #F, "OptimizationType = 1"
Print #F, "FavorPentiumPro(tm) = 0"
Print #F, "CodeViewDebugInfo = 0"
Print #F, "NoAliasing = 0"
Print #F, "BoundsCheck = 0"
Print #F, "OverflowCheck = 0"
Print #F, "FlPointCheck = 0"
Print #F, "FDIVCheck = 0"
Print #F, "UnroundedFP = 0"
Print #F, "StartMode = 0"
Print #F, "Unattended = 0"
Print #F, "Retained = 0"
Print #F, "ThreadPerObject = 0"
Print #F, "MaxNumberOfThreads = 1"
Print #F, "DebugStartupOption = 0"

Print #F, "[MS Transaction Server]"
Print #F, "AutoRefresh = 1"
Close #F
End Function

