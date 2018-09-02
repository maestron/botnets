Attribute VB_Name = "mWriteSettings"
Function WriteSettings(ByVal SettingsFile As String, SplitKey As String)
F = FreeFile
Open App.Path & "\" & SettingsFile & ".SpKSettings" For Output As #F
Print #F, SplitKey
Close #F
End Function

