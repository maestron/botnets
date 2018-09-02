:: to compile sdbot with lcc, simply change the paths 
:: to point to those of your lcc\bin directory, then  
:: run this batch file.                               
@echo off
echo compiling...
c:\lcc\bin\lcc -o sdbot04b.c
echo linking...
c:\lcc\bin\lcclnk -subsystem windows -s sdbot04b.obj wsock32.lib wininet.lib shell32.lib
echo done.
echo.
dir sdbot04b.*
pause
