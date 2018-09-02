@echo off

:: ====================================================== ::
:: change 'c:\mingw' to the location of your mingw folder ::
:: ====================================================== ::
set mingw=c:\mingw

echo compiling sdbot05b.c...
%mingw%\bin\g++ sdbot05b.c -o sdbot05b.exe -L %mingw%\lib %mingw%\lib\libwsock32.a %mingw%\lib\libwininet.a %mingw%\lib\libshell32.a %mingw%\lib\libth32.a -s -Os -mwindows
echo done.
echo.
dir sdbot05b.*
echo.
pause
