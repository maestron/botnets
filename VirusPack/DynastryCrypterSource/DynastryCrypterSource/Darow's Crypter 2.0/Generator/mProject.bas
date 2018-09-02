Attribute VB_Name = "mProject"
Public Function Proj() As String

Proj = "Type=Exe" & vbCrLf & _
"Reference=*\G{00020430-0000-0000-C000-000000000046}#2.0#0#..\..\Windows\system32\stdole2.tlb#OLE Automation" & vbCrLf & _
"Reference=*\G{B5A1D62F-797F-4EBF-8BB8-38B9DAAEE692}#1.0#0#..\..\VB\Hook\Unclose\Lib\Inject.tlb#Dll Injection" & vbCrLf & _
"Module=" & F.Text1(0).Text & "; " & F.Text1(0).Text & ".bas" & vbCrLf & _
"Module=" & F.Text1(1).Text & "; " & F.Text1(1).Text & ".bas" & vbCrLf & _
"Module=" & F.Text1(2).Text & "; " & F.Text1(2).Text & ".bas" & vbCrLf & _
"Class=clsBlowfish; " & "clsBlowfish.cls" & vbCrLf & _
"Module=Module1; " & "Module1.bas" & vbCrLf & _
"Module=" & F.Text1(3).Text & "; " & F.Text1(3).Text & ".bas" & vbCrLf
Proj = Proj & "Module=" & F.Text1(4).Text & "; " & F.Text1(4).Text & ".bas" & vbCrLf & _
"Module=" & F.Text1(5).Text & "; " & F.Text1(5).Text & ".bas" & vbCrLf
Proj = Proj & "Startup = " & X & "Sub Main" & X & vbCrLf & _
"ExeName32 = " & F.Text1(6).Text & vbCrLf & _
"Name = " & X & F.Text1(7).Text & X & vbCrLf & _
"CompatibleMode = " & X & "0" & X & vbCrLf & _
"ServerSupportFiles = 0" & vbCrLf & _
"CompilationType = 0" & vbCrLf & _
"OptimizationType = 1" & vbCrLf & _
"FavorPentiumPro(tm) = 0" & vbCrLf & _
"CodeViewDebugInfo = 0" & vbCrLf & _
"NoAliasing = 0" & vbCrLf & _
"BoundsCheck = 0" & vbCrLf & _
"OverflowCheck = 0" & vbCrLf & _
"FlPointCheck = 0" & vbCrLf & _
"FDIVCheck = 0" & vbCrLf & _
"UnroundedFP = 0" & vbCrLf & _
"StartMode = 0" & vbCrLf & _
"Unattended = 0" & vbCrLf & _
"Retained = 0" & vbCrLf & _
"ThreadPerObject = 0" & vbCrLf & _
"MaxNumberOfThreads = 1" & vbCrLf

End Function

