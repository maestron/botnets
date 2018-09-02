@echo Off

del *.bcb
del *.opt
del *.plg
del *.ncb
del *.aps
del *.scc
del *.ilk
del *.obj
del makestubd.exe
del configguid.exe

rd /s /q Release
rd /s /q Debug
rd /s /q agobot3___Win32_Release_Console
rd /s /q agobot3___Win32_Release_No_OpenSSL
rd /s /q agobot3___Win32_Release_Console_No_OpenSSL
rd /s /q agobot3___Win32_Debug_No_OpenSSL
rd /s /q agobot3___Win32_Debug_Internal
rd /s /q agobot3___Win32_Debug_No_OpenSSL_Internal
rd /s /q agobot3___Win32_Release_Console_Test

cls
