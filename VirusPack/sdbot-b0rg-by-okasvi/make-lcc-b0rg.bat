@echo off

set lccdir=c:\lcc
%lccdir%\bin\lcc -O -unused b0rg.c
%lccdir%\bin\lcclnk -subsystem windows -s b0rg.obj ws2_32.lib wininet.lib shell32.lib icmp.lib winmm.lib
del *.obj
echo.
pause
