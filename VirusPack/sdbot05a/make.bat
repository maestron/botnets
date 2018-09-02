:: to compile sdbot with lcc, simply change the paths 
:: to point to those of your lcc\bin directory, then  
:: run this batch file.                               
@echo off
echo compiling...
c:\lcc\bin\lcc -o sdbot05a.c
echo linking...
c:\lcc\bin\lcclnk -subsystem windows -s sdbot05a.obj wsock32.lib wininet.lib shell32.lib
echo done.
echo.
dir sdbot05a.*
pause
