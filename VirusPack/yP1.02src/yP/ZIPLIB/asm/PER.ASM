; -> Polymorphic En-/Decryption routine generator for per byte encryption <-
; by yoda

;---- STRUCTs ----
sPERTable STRUCT
	dwSize           DD ?
	dwEncrypt        DD ?
	dwDecrypt        DD ?
	RandNumType      DD ?
sPERTable ENDS

; RandNumType:
; 0 - no random num needed
; 1 - 3th byte must be a random number
; 2 - 2nd byte must be a random number

;----- EQUs -----
PERItems                   EQU 14

;----- CONST ----
.CONST
; all opcodes are in reverse order
PERTable                   DD 1
			   DD 090h				; NOP
			   DD 090h				; NOP
			   DD 0
			   
			   DD 1
			   DD 0F9h				; STC
			   DD 0F9h				; STC
			   DD 0
			   
			   DD 1
			   DD 0F8h				; CLC
			   DD 0F8h				; CLC
			   DD 0			   

			   DD 2
			   DD 0C0FEh				; INC  AL
			   DD 0C8FEh                            ; DEC  AL
			   DD 0
			   
			   DD 2
			   DD 00004				; ADD AL, 0
			   DD 0002Ch				; SUB AL, 0
			   DD 2

			   DD 2
			   DD 0002Ch				; SUB AL, 0
			   DD 00004				; ADD AL, 0
			   DD 2
			   
			   DD 2
			   DD 0C102h				; ADD AL, CL
			   DD 0C12Ah				; SUB AL, CL
			   DD 0

			   DD 2
			   DD 0C12Ah				; SUB AL, CL
			   DD 0C102h				; ADD AL, CL
			   DD 0

			   DD 2
			   DD 00034h				; XOR AL, 0
			   DD 00034h				; XOR AL, 0
			   DD 2

			   DD 3
			   DD 000C8C0h                          ; ROR  AL, 0
			   DD 000C0C0h				; ROL  AL, 0
			   DD 1

			   DD 3
			   DD 000C0C0h				; ROL  AL, 0
			   DD 000C8C0h                          ; ROR  AL, 0
			   DD 1
			   
			   DD 3
			   DD 0E801EBh				; Self modifing
			   DD 0E801EBh				; Self modifing
			   DD 0
			   
			   DD 3
			   DD 0E901EBh				; Self modifing
			   DD 0E901EBh				; Self modifing
			   DD 0
			   
			   DD 3
			   DD 0C201EBh				; Self modifing
			   DD 0C201EBh				; Self modifing
			   DD 0			   

.DATA
dwRandVal                  DD 0

.CODE

; srand should only called one time !!!
InitRandom PROC
	; manage the random generator 
	CALL GetTickCount
	PUSH EAX
	CALL srand
	RET
InitRandom ENDP

MakePER PROC pEncryptBuff : LPVOID, pDecryptBuff : LPVOID, dwSize : DWORD
	LOCAL dwCurRandNum : DWORD
	
	; prepare some things
	MOV  EDI, pEncryptBuff					; EDI -> EncryptBuffer
	MOV  ESI, pDecryptBuff					; ESI -> DecryptBuffer
	ADD  ESI, dwSize					; ESI will be filled from down to top
	
	; generate !
	.REPEAT   
	   ; get a random PER Item
	   PUSH PERItems
	   CALL rand
	   MOV  EBX, SIZEOF sPERTable
	   XOR  EDX, EDX
	   MUL  EBX
	   ADD  EAX, OFFSET PERTable
	   XCHG EAX, EDX	   				; EDX -> PER Table Item
	   
	   ASSUME EDX : PTR sPERTable
	   
	   ; is this item too big
	   MOV  EBX, [EDX].dwSize
	   CMP  EBX, dwSize
	   JG   Retry
	   
	   ;---- past the Opcode ----
	   ;-> encryption buffer
	   MOV  ECX, [EDX].dwSize
	   MOV  EAX, [EDX].dwEncrypt	   

	   MOV  ECX, [EDX].dwSize
	   .WHILE ECX != 0
	       MOV  BYTE PTR [EDI], AL
	       ADD  EDI, 1
	       ROR  EAX, 8
	       DEC  ECX
	   .ENDW

	   ; generate the random num
	   MOV  EAX, [EDX].RandNumType
	   .IF  EAX == 1 || EAX == 2
	       MOV  EBX, EDI
	       SUB  EBX, 1
	       PUSH 0F8h
	       CALL rand
	       INC  EAX				; avoid 0 !
	       MOV  dwCurRandNum, EAX
	       MOV  BYTE PTR [EBX], AL

	   .ENDIF	   
 
	   ; update variables/pointers
	   MOV  EAX, [EDX].dwSize
	   SUB  dwSize, EAX
	   
	   ;-> decryption buffer
	   MOV  ECX, [EDX].dwSize
	   MOV  EAX, [EDX].dwDecrypt	   
	   SUB  ECX, 1
	   .WHILE ECX != 0
	        ROR  EAX, 8
	        DEC  ECX
	   .ENDW

	   MOV  ECX, [EDX].dwSize
	   .WHILE ECX != 0
	       SUB  ESI, 1 
	       MOV  BYTE PTR [ESI], AL
	       ROL  EAX, 8
	       DEC  ECX
	   .ENDW
	   
	   ; generate the random num
	   MOV  EAX, [EDX].RandNumType
	   .IF  EAX == 1
	       MOV  EBX, ESI
	       ADD  EBX, 2
	       MOV  EAX, dwCurRandNum
	       MOV  BYTE PTR [EBX], AL
	       
	   .ELSEIF EAX == 2
	       MOV  EBX, ESI
	       ADD  EBX, 1
	       MOV  EAX, dwCurRandNum
	       MOV  BYTE PTR [EBX], AL	
	          
	   .ENDIF	   
	   
	   ASSUME EDX : NOTHING
	   
       Retry:
	.UNTIL dwSize == 0	
	RET
MakePER ENDP
	
rand PROC USES edx ebx, dwRange : DWORD
	MOV  EAX, dwRandVal
	
	; save new random number
	ADD  EAX, 0567h
	ROL  EAX, 1
	MOV  dwRandVal, EAX
	
	; get new random number
	XOR  EDX, EDX
	MOV  ECX, 32
    BitLoop:
	    SHR   EAX, 1
	    .IF   CARRY?
	        XOR  EAX, 013245769h
	    .ENDIF
	LOOP BitLoop
	
	; force dwRange
	XOR  EDX, EDX
	MOV  EBX, dwRange
	DIV  EBX
	
	XCHG EAX, EDX

	RET
rand ENDP

srand PROC dwRandNum : DWORD
	MOV  EAX, dwRandNum
	MOV  dwRandVal, EAX
	RET
srand ENDP
