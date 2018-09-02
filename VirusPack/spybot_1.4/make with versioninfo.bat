
@echo off
::Make file for lcc-win32 if you dont have it download it from http://www.q-software-solutions.com

                        
echo compiling...
c:\lcc\bin\lcc -unused spybot.c
c:\lcc\bin\lrc recource.rc
echo linking...
c:\lcc\bin\lcclnk -subsystem windows -s spybot.obj recource.res ws2_32.lib  wininet.lib shell32.lib winmm.lib 
echo done (spybot.exe)
echo.
pause
