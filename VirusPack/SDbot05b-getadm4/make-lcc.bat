@echo off

:: ================================================== ::
:: change 'c:\lcc' to the location of your lcc folder ::
:: ================================================== ::
set lccdir=c:\lcc
                              
echo compiling...
%lccdir%\bin\lcc -o -a -unused sdbot05b.c
echo linking...
%lccdir%\bin\lcclnk -subsystem windows -s sdbot05b.obj wsock32.lib wininet.lib shell32.lib icmp.lib winmm.lib
echo done.
echo.
dir sdbot05b.*
echo.
pause
