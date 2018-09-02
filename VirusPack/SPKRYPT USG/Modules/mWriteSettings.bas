Attribute VB_Name = "mWriteSettings"
Function WriteSettings(ByVal SettingsFile As String, SplitKey As String, path As String)
F = FreeFile
Open path & "\" & SettingsFile & ".SpKSettings" For Output As #F
Print #F, SplitKey
Close #F
End Function

