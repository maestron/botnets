@echo off
echo Cleaning up...
cd bin/Release
del *.* /y
cd..
rd /s /q Release
:EXIT