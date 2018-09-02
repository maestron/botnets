@echo off

:: ================================================== ::
:: change 'd:\lcc' to the location of your lcc folder ::
:: ================================================== ::
set lccdir=c:\lcc

:: ====================================================== ::
:: change 'd:\masm32' to the location of your masm folder ::
:: ====================================================== ::
set masm32dir=c:\masm32
 %lccdir%\bin\lcc -o -a -unused spybot.c
echo linking sdbot...
%lccdir%\bin\lcclnk -dll -subsystem windows -s spybot.obj ws2_32.lib wininet.lib shell32.lib winmm.lib
                             
echo building resource...
echo #include "%masm32dir%\include\resource.h" >> rsrc.rc
echo 1000 RCDATA DISCARDABLE spybot.dll >>  rsrc.rc
%masm32dir%\bin\rc /v rsrc.rc
echo converting resource...
%masm32dir%\bin\cvtres /machine:ix86 rsrc.res
echo assembling installer...
%masm32dir%\bin\ml /c /coff spybot.asm
echo linking installer...
%masm32dir%\bin\link /filealign:0x200 /merge:.data=.text /ignore:4078 /section:.text,RWX /LIBPATH:c:\masm32\lib /subsystem:windows spybot.obj rsrc.obj
@echo off
del rsrc.rc
del rsrc.obj
del rsrc.res
echo done.
echo.
pause
