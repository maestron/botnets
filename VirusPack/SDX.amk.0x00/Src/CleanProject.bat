@echo off
cls
echo Cleaning Project...
rmdir /S /Q Release
del /F /S /Q *.ncb
del /F /S /Q *.opt
del /F /S /Q *.aps
del /F /S /Q *.plg
del /F /S /Q *.suo
echo Done!