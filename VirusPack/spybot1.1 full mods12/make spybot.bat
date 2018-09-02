
@echo off
::Make file for lcc-win32 if you dont have it download it from http://www.q-software-solutions.com

                        
echo compiling...
c:\lcc\bin\lcc -unused spybot1.1.c
echo linking...
c:\lcc\bin\lcclnk -subsystem windows -s spybot1.1.obj  wsock32.lib  wininet.lib shell32.lib winmm.lib
echo done.
echo.
pause
