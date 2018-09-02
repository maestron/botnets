@echo off
cls
echo Session Opened.
:routine
echo Enter a command:
set /p command=
%command%
echo.
goto routine